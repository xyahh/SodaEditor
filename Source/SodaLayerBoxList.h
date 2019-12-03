/*
  ==============================================================================

	Based on the Example given at: https://github.com/getdunne/juce-draggableListBox
	Copyright below:

		MIT License
		
		Copyright (c) 2019 Shane Dunne
		
		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:
		
		The above copyright notice and this permission notice shall be included in all
		copies or substantial portions of the Software.
		
		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
		SOFTWARE.

  ==============================================================================
*/

#pragma once
#include "DraggableListBox.h"

class SodaCanvas;

struct LayerListBoxItemData : public DraggableListBoxItemData
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

	//we'll paint the contents in reverse, so that the top layer is 
	// also the layer at the top of the list
	virtual void paintContents(int rowNum, Graphics& g, Rectangle<int> bounds);

	virtual void moveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore);
	virtual void moveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter);

	// If you need a dynamic list, override these functions as well.
	virtual void deleteItem(int indexOfItemToDelete);

	virtual void addItemAtEnd();
};

// Custom list-item Component (which includes item-delete button)
class LayerListComponent : public DraggableListBoxItem
{
public:
	LayerListComponent(DraggableListBox& lb, LayerListBoxItemData& data, int rn, SodaCanvas* sodaCanvas);
	virtual ~LayerListComponent();

	void paint(Graphics&) override;
	void resized() override;

protected:

	size_t		onLayerDestroyedID;
	SodaCanvas* sodaCanvas;
	Rectangle<int> dataArea;
	TextButton activateLayerButton;
	TextButton deleteLayerButton;
	LayerListBoxItemData* layerData;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerListComponent)
};

// Customized DraggableListBoxModel overrides refreshComponentForRow() to ensure that every
// list-item Component is a MyListComponent.
class LayerListBoxModel : public DraggableListBoxModel
{
public:
	LayerListBoxModel(DraggableListBox& lb, DraggableListBoxItemData& md)
		: DraggableListBoxModel(lb, md) {}

	void setCanvas(SodaCanvas* sodaCanvas_);

	Component* refreshComponentForRow(int, bool, Component*) override;

private:
	SodaCanvas* sodaCanvas;
};