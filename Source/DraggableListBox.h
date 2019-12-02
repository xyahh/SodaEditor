//This H file gotten from https://github.com/getdunne/juce-draggableListBox
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

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

// Your item-data container must inherit from this, and override at least the first
// four member functions.
struct DraggableListBoxItemData
{
	virtual int getNumItems() = 0;
	virtual void paintContents(int, Graphics&, Rectangle<int>) = 0;

	virtual void moveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore) = 0;
	virtual void moveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter) = 0;

	// If you need a dynamic list, override these functions as well.
	virtual void deleteItem(int /*indexOfItemToDelete*/) {};
	virtual void addItemAtEnd() {};
};

// DraggableListBox is basically just a ListBox, that inherits from DragAndDropContainer.
// Declare your list box using this type.
class DraggableListBox : public ListBox, public DragAndDropContainer
{
};

// Everything below this point should be generic.
class DraggableListBoxItem : public Component, public DragAndDropTarget
{
public:
	DraggableListBoxItem(DraggableListBox& lb, DraggableListBoxItemData& data, int rn)
		: listBox(lb), modelData(data), rowNum(rn) {}

	// Component
	void paint(Graphics& g) override;
	void mouseEnter(const MouseEvent&) override;
	void mouseExit(const MouseEvent&) override;
	void mouseDrag(const MouseEvent&) override;

	// DragAndDropTarget
	bool isInterestedInDragSource(const SourceDetails&) override { return true; }
	void itemDragEnter(const SourceDetails&) override;
	void itemDragMove(const SourceDetails&) override;
	void itemDragExit(const SourceDetails&) override;
	void itemDropped(const SourceDetails&) override;
	bool shouldDrawDragImageWhenOver() override { return true; }

	// DraggableListBoxItem
protected:
	void updateInsertLines(const SourceDetails &dragSourceDetails);
	void hideInsertLines();

	int rowNum;
	DraggableListBoxItemData& modelData;
	DraggableListBox& listBox;

	MouseCursor savedCursor;
	bool insertAfter = false;
	bool insertBefore = false;
};

class DraggableListBoxModel : public ListBoxModel
{
public:
	DraggableListBoxModel(DraggableListBox& lb, DraggableListBoxItemData& md)
		: listBox(lb), modelData(md) {}

	int getNumRows() override;
	void paintListBoxItem(int, Graphics &, int, int, bool) override;

	Component* refreshComponentForRow(int, bool, Component*) override;

protected:
	// Draggable model has a reference to its owner ListBox, so it can tell it to update after DnD.
	DraggableListBox &listBox;

	// It also has a reference to the model data, which it uses to get the current items count,
	// and which it passes to the DraggableListBoxItem objects it creates/updates.
	DraggableListBoxItemData& modelData;
};
