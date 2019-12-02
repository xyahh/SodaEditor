//This CPP file gotten from https://github.com/getdunne/juce-draggableListBox
//Copyright below:
/*
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
*/

#include "DraggableListBox.h"

void DraggableListBoxItem::paint(Graphics& g)
{
	modelData.paintContents(rowNum, g, getLocalBounds());

	if (insertAfter)
	{
		g.setColour(Colours::red);
		g.fillRect(0, getHeight() - 3, getWidth(), 3);
	}
	else if (insertBefore)
	{
		g.setColour(Colours::red);
		g.fillRect(0, 0, getWidth(), 3);
	}
}

void DraggableListBoxItem::mouseEnter(const MouseEvent&)
{
	savedCursor = getMouseCursor();
	setMouseCursor(MouseCursor::DraggingHandCursor);
}

void DraggableListBoxItem::mouseExit(const MouseEvent&)
{
	setMouseCursor(savedCursor);
}

void DraggableListBoxItem::mouseDrag(const MouseEvent&)
{
	if (DragAndDropContainer* container = DragAndDropContainer::findParentDragContainerFor(this))
	{
		container->startDragging("DraggableListBoxItem", this);
	}
}

void DraggableListBoxItem::updateInsertLines(const SourceDetails &dragSourceDetails)
{
	if (dragSourceDetails.localPosition.y < getHeight() / 2)
	{
		insertBefore = true;
		insertAfter = false;
	}
	else
	{
		insertAfter = true;
		insertBefore = false;
	}
	repaint();
}

void DraggableListBoxItem::hideInsertLines()
{
	insertBefore = false;
	insertAfter = false;
	repaint();
}

void DraggableListBoxItem::itemDragEnter(const SourceDetails& dragSourceDetails)
{
	updateInsertLines(dragSourceDetails);
}

void DraggableListBoxItem::itemDragMove(const SourceDetails& dragSourceDetails)
{
	updateInsertLines(dragSourceDetails);
}

void DraggableListBoxItem::itemDragExit(const SourceDetails& /*dragSourceDetails*/)
{
	hideInsertLines();
}

void DraggableListBoxItem::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
	if (DraggableListBoxItem* item = dynamic_cast<DraggableListBoxItem*>(dragSourceDetails.sourceComponent.get()))
	{
		if (dragSourceDetails.localPosition.y < getHeight() / 2)
			modelData.moveBefore(item->rowNum, rowNum);
		else
			modelData.moveAfter(item->rowNum, rowNum);
		listBox.updateContent();
	}
	hideInsertLines();
}

int DraggableListBoxModel::getNumRows() 
{ 
	return modelData.getNumItems(); 
}

void DraggableListBoxModel::paintListBoxItem(int, Graphics & g, int, int, bool)
{
}

Component* DraggableListBoxModel::refreshComponentForRow(int rowNumber,
	bool /*isRowSelected*/,
	Component *existingComponentToUpdate)
{
	ScopedPointer<DraggableListBoxItem> item(dynamic_cast<DraggableListBoxItem*>(existingComponentToUpdate));
	if (isPositiveAndBelow(rowNumber, modelData.getNumItems()))
	{
		item = new DraggableListBoxItem(listBox, modelData, rowNumber);
	}
	return item.release();
}
