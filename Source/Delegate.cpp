/*
  ==============================================================================

    FDelegate
    Created: 1 Dec 2019 12:20:08am
    Author:  Juan Marcelo Portillo

  ==============================================================================
*/

#include "Delegate.h"
#include <functional>
#include <deque>
#include <map>
#include <atomic>


template<class ...Ax>
/*
@ FDelegate Class
@ Used for Binding and Executing Functions that are in different parts of the Code.
@ Warning: Please Comment Thoroughly on What is being Bound to make use of IntelliSense
@ and also include Function Signature in these comments.

@ FDelegate Instances can be called by multiple Threads
*/
class FDelegate
{
	using FuncType = std::function<void(const Ax&...)>;
	using FuncContainer = std::deque<FuncType>;

private:

	/*
	@ Makes sure that only 1 thread succeeds in aquiring the 'lock' on
	@ the Delegate.
	*/
	bool CAS(bool Old, bool New)
	{
		return std::atomic_compare_exchange_strong
		(reinterpret_cast<volatile std::atomic_bool*>(&Busy), &Old, New);
	}

public:

	/*
	@ Binds a new Func to be executed when this Delegate is Called
	@ Return UINT: The ID of the Bound Func (to then be able to Unbind it Separately)
	*/
	size_t Bind(const FuncType& Fx)
	{
		while (!CAS(false, true)) {}

		Functions.emplace_back(Fx);
		size_t FuncID = FunctionIndex++;
		FunctionLocator.emplace(FuncID, Functions.size() - 1);

		CAS(true, false);
		return FuncID;
	}

	/*
	@ Binds a new Func to be executed when this Delegate is Called
	@ Return UINT: The ID of the Bound Func (to then be able to Unbind it Separately)
	*/
	size_t Bind(FuncType&& Fx) noexcept
	{
		while (!CAS(false, true)) {}

		Functions.emplace_back(std::move(Fx));
		size_t FuncID = FunctionIndex++;
		FunctionLocator.emplace(FuncID, Functions.size() - 1);

		CAS(true, false);
		return FuncID;
	}

	/*
	Deallocates all Bound Functions.
	Further Calls of this Delegate will not Call these Funcs
	*/
	void UnbindAll()
	{
		while (!CAS(false, true)) {}

		FunctionLocator.clear();
		Functions.clear();

		CAS(true, false);
	}

	/*
	Deallocates a Bound Function by ID.
	Further Calls of this Delegate will not Call this Deallocated Func
	*/
	void Unbind(unsigned int FunctionID)
	{
		while (!CAS(false, true)) {}

		auto Iter = FunctionLocator.find(FunctionID);
		if (Iter == FunctionLocator.end())
		{
			CAS(true, false);
			return;
		}

		size_t IndexToErase = Iter->second;

		// Decrease all Keys (deque indices) that are greater than IndexToErase
		// to Update the Map to the Correct Moved Indices
		for (auto& Mapping : FunctionLocator)
			if (Mapping.second > IndexToErase)
				--Mapping.second;
		Functions.erase(Functions.begin() + IndexToErase);

		FunctionLocator.erase(Iter);
		CAS(true, false);
	}

	/*
	@ Calls all the Functions that were Bound to this Delegate
	@ The parameters of the Call are also passed into the Bound Functions
	*/
	void Call(const Ax&... Args)
	{
		while (!CAS(false, true)) {}
		for (auto& Fx : Functions)
			Fx(Args...);
		CAS(true, false);
	}

	/*
	@ Calls the Functions by first Moving them to a
	@ New Location that will be Destroyed (i.e. Removed) from Memory
	@ This SHOULD be used when you want to call Functions only once and then
	@ get rid of them!
	*/
	void CallOnce(const Ax&... Args)
	{
		while (!CAS(false, true)) {}

		if (Functions.empty())
		{
			CAS(true, false);
			return;
		}
		auto FuncToExec = std::move(Functions);
		CAS(true, false);
		UnbindAll();

		while (CAS(false, true)) {}
		for (auto& Fx : FuncToExec)
			Fx(Args...);

		CAS(true, false);
	}

public:

	size_t						FunctionIndex = 0;
	std::map<size_t, size_t>	FunctionLocator;
	FuncContainer				Functions;
	volatile bool				Busy{ false };
};