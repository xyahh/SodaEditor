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

#include "SodaLayerBoxList.h"
#include "SodaCanvas.h"

/*
==============================================================================
LIST BOX ITEM DATA
==============================================================================
*/

int LayerListBoxItemData::getNumItems()
{
	return layerInfo.size();
}

void LayerListBoxItemData::paintContents(int rowNum, Graphics & g, Rectangle<int> bounds)
{
	g.setColour(Colours::black);
	g.drawRect(bounds);
	g.drawText(layerInfo[rowNum]->layerName, bounds, Justification::centred);
}

void LayerListBoxItemData::moveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore)
{
	if (indexOfItemToMove <= indexOfItemToPlaceBefore)
		layerInfo.move(indexOfItemToMove, indexOfItemToPlaceBefore - 1);
	else
		layerInfo.move(indexOfItemToMove, indexOfItemToPlaceBefore);
}

void LayerListBoxItemData::moveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter)
{
	if (indexOfItemToMove <= indexOfItemToPlaceAfter)
		layerInfo.move(indexOfItemToMove, indexOfItemToPlaceAfter);
	else
		layerInfo.move(indexOfItemToMove, indexOfItemToPlaceAfter + 1);
}

void LayerListBoxItemData::deleteItem(int indexOfItemToDelete)
{
	layerInfo.remove(indexOfItemToDelete);
}

void LayerListBoxItemData::addItemAtEnd()
{
	layerInfo.add(new FLayerInfo("", false));
}

/*
==============================================================================
LIST COMPONENT
==============================================================================
*/

LayerListComponent::LayerListComponent(DraggableListBox& lb, LayerListBoxItemData& data, int rn, SodaCanvas* sodaCanvas_)
	: DraggableListBoxItem(lb, data, rn)
{
	sodaCanvas = sodaCanvas_;
	//cast to what we actually have, the LayerListBox
	layerData = dynamic_cast<LayerListBoxItemData*>(&modelData);	

	//set current item to active
	if (layerData)
		sodaCanvas->setActiveLayer(layerData->layerInfo[rowNum]->layerID);

	activateLayerButton.setButtonText("Activate");
	activateLayerButton.onClick = [this]()
	{
		if(layerData)
			sodaCanvas->setActiveLayer(layerData->layerInfo[rowNum]->layerID);
	};
	addAndMakeVisible(activateLayerButton);

	deleteLayerButton.setButtonText("X");
	deleteLayerButton.onClick = [this]()
	{
		if(layerData)
			sodaCanvas->deleteLayer(layerData->layerInfo[rowNum]->layerID);
	};
	addAndMakeVisible(deleteLayerButton);

	
}

LayerListComponent::~LayerListComponent()
{
	
}

void LayerListComponent::paint(Graphics& g)
{
	auto& info = layerData->layerInfo;
	if (layerData && sodaCanvas->isActiveLayer(info[rowNum]->layerID))
		g.fillAll(Colours::lightsalmon);
	else 
		g.fillAll(Colours::lightgrey);	
	DraggableListBoxItem::paint(g);
}

void LayerListComponent::resized()
{
	dataArea = getLocalBounds();
	activateLayerButton.setBounds(dataArea.removeFromLeft(90).withSizeKeepingCentre(75, 24));
	deleteLayerButton.setBounds(dataArea.removeFromRight(70).withSizeKeepingCentre(30, 24));
}


/*
==============================================================================
LIST BOX MODEL
==============================================================================
*/

void LayerListBoxModel::setCanvas(SodaCanvas * sodaCanvas_)
{
	sodaCanvas = sodaCanvas_;
}

Component* LayerListBoxModel::refreshComponentForRow(int rowNumber,
	bool isRowSelected,
	Component *existingComponentToUpdate)
{
	ScopedPointer<LayerListComponent> item(dynamic_cast<LayerListComponent*>(existingComponentToUpdate));
	if (isPositiveAndBelow(rowNumber, modelData.getNumItems()))
	{
		item = new LayerListComponent(listBox, (LayerListBoxItemData&)modelData, rowNumber, sodaCanvas);
	}
	return item.release();
}