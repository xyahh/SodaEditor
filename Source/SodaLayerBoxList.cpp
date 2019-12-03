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

void LayerListBoxItemData::deleteItem(int indexOfItemToDelete)
{
	layerInfo.remove(indexOfItemToDelete);
}

/*
==============================================================================
LIST COMPONENT
==============================================================================
*/

LayerListComponent::LayerListComponent(LayerListBox& lb, LayerListBoxItemData& data, int rn, SodaCanvas* sodaCanvas_)
	: listBox(lb), layerData(data), rowNum(rn)
{
	//set the canvas
	sodaCanvas = sodaCanvas_;

	//make the activate button & bind its click to the canvas activate layer func
	activateLayerButton.setButtonText("Activate");
	activateLayerButton.onClick = [this]()
	{
		sodaCanvas->setActiveLayer(layerData.layerInfo[rowNum]->layerID);
	};
	addAndMakeVisible(activateLayerButton);

	//make the delete button & bind its click to the canvas delete layer func
	deleteLayerButton.setButtonText("X");
	deleteLayerButton.onClick = [this]()
	{
		sodaCanvas->deleteLayer(layerData.layerInfo[rowNum]->layerID);
	};
	addAndMakeVisible(deleteLayerButton);

	
}

LayerListComponent::~LayerListComponent()
{
	
}

void LayerListComponent::paint(Graphics& g)
{
	auto& info = layerData.layerInfo;
	if (info[rowNum] == nullptr || sodaCanvas == nullptr) return;

	if (sodaCanvas->isActiveLayer(info[rowNum]->layerID))
		g.fillAll(Colours::lightsalmon);
	else 
		g.fillAll(Colours::lightgrey);	

	layerData.paintContents(rowNum, g, getLocalBounds());
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

int LayerListBoxModel::getNumRows()
{
	return layerData.getNumItems();
}

void LayerListBoxModel::paintListBoxItem(int, Graphics &, int, int, bool)
{
}

Component* LayerListBoxModel::refreshComponentForRow(int rowNumber,
	bool isRowSelected,
	Component *existingComponentToUpdate)
{
	ScopedPointer<LayerListComponent> item(dynamic_cast<LayerListComponent*>(existingComponentToUpdate));
	if (isPositiveAndBelow(rowNumber, layerData.getNumItems()))
	{
		item = new LayerListComponent(listBox, (LayerListBoxItemData&)layerData, rowNumber, sodaCanvas);
	}
	return item.release();
}