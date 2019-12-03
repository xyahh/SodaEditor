//custom layer list 

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SodaCanvas;

struct LayerListBoxItemData
{
	struct FLayerInfo
	{
		FLayerInfo(const String& name, bool isActive_)
			: layerName(name) {}

		FLayerInfo(String&& name, bool isActive_) noexcept
			: layerName(std::move(name)){}

		String layerName;
		size_t layerID;
	};

	OwnedArray<FLayerInfo> layerInfo;

	//returns the amount of layernames there are 
	virtual int getNumItems();

	virtual void paintContents(int rowNum, Graphics& g, Rectangle<int> bounds);

	virtual void deleteItem(int indexOfItemToDelete);
};

class LayerListBox : public ListBox
{
};


class LayerListComponent : public Component
{
public:
	LayerListComponent(LayerListBox& lb, LayerListBoxItemData& data, int rn, SodaCanvas* sodaCanvas);
	virtual ~LayerListComponent();

	void paint(Graphics&) override;
	void resized() override;

protected:
	//ptr to canvas so that we can call 'Activate Layer' or 'Destroy layer' when the 
	// buttons are clicked
	SodaCanvas* sodaCanvas;
	Rectangle<int> dataArea;
	TextButton activateLayerButton;
	TextButton deleteLayerButton;

	//pointer to the model data found in the parent. to avoid having to always do dynamic cast 
	LayerListBoxItemData& layerData;
	LayerListBox& listBox;
	int rowNum;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerListComponent)
};

// Customized DraggableListBoxModel overrides refreshComponentForRow() to ensure that every
// list-item Component is a MyListComponent.
class LayerListBoxModel : public ListBoxModel
{
public:
	LayerListBoxModel(LayerListBox& lb, LayerListBoxItemData& md)
		: listBox(lb), layerData(md) {}

	void setCanvas(SodaCanvas* sodaCanvas_);

	int getNumRows() override;
	void paintListBoxItem(int, Graphics &, int, int, bool) override;
	Component* refreshComponentForRow(int, bool, Component*) override;

private:
	SodaCanvas* sodaCanvas;

	// Draggable model has a reference to its owner ListBox, so it can tell it to update after DnD.
	LayerListBox &listBox;

	// It also has a reference to the model data, which it uses to get the current items count,
	// and which it passes to the DraggableListBoxItem objects it creates/updates.
	LayerListBoxItemData& layerData;
};