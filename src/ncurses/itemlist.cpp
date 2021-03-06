///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011 Janno Tikka
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////
#include <ncurses/itemlist.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace NC {

///////////////////////////////////////////////////////////////////////////////
ItemList::ItemList(Booknote * notebook) {
    Book          = notebook;
    lprint_size = 0;
    selected    = 0;
    screen_size = LINES - 4; // 4 is the space used by header and footer
    screen_start= 0;
    screen_end  = LINES-4;
    TextColor   = clYellow;
    BackColor   = clBlack;   
    hilight_selected = true;
    ElementPad = newpad(Book->size(), COLS);

    this->PrintToPad(); 
}

///////////////////////////////////////////////////////////////////////////////
ItemList::~ItemList() {
    delwin(ElementPad);
}

////////////////////////////////////////////////////////////////////////////////
void ItemList::PrintToPad() {
    unsigned int cur_row = 0;
    lprint_size = Book->size();
   
    // color on 
    wattron(ElementPad, COLOR_PAIR(TextColor));          

    for(std::list<Booknote *>::iterator itr = Book->begin(); itr != Book->end(); itr++) {
        
        if(cur_row == selected && hilight_selected) {
            // change current color include fancy background color
            wattron(ElementPad, COLOR_PAIR(TextColor*8+BackColor));   
            // Fill with spaces so we get background color 
            for(int j = 0; j <= COLS; j++)
                mvwprintw(ElementPad, cur_row, j, " ");
        }    
       
        // Print Notebook name and size
        mvwprintw(ElementPad, cur_row, 0, "%s", (*itr)->message.c_str());
        
        // If item contains sub items -> print size
        if((*itr)->size() > 0) {
            mvwprintw(ElementPad, cur_row, COLS-4, "%s", (*itr)->SizeString().c_str());
        }

        // Restore to normal color 
        wattron(ElementPad, COLOR_PAIR(TextColor));      
        // next row
        cur_row++; 
    }

    // color off
    wattroff(ElementPad, COLOR_PAIR(TextColor));          
}

///////////////////////////////////////////////////////////////////////////////
unsigned int ItemList::mySize() {
    return Book->size();
}

///////////////////////////////////////////////////////////////////////////////
void ItemList::Recreate(size_t lines, size_t cols) {
    delwin(ElementPad);
    
    ElementPad = newpad(lines, cols);
    
    screen_size= LINES - 4; // 4 is the space used by header and footer
    screen_end = screen_start + screen_size;

    //@TODO: Maybe make selected a new class and move some of this there

    // Item deleted and active thing left behind
    ////////////////////////////////////////////////////////////////////////////   
    while(selected+1 > mySize() && mySize() != 0) {
        selected--;
    }

    // selected item has been left behind when making window smaller
    ////////////////////////////////////////////////////////////////////////////
    while(selected >= screen_end && selected != 0) {
        selected--;
    }
    
    // selected item has been left behind when making window bigger
    ////////////////////////////////////////////////////////////////////////////
    while(selected < screen_start) {
        selected++;
    }
   
    // screen_start != 0 even tho we could fit more items on screen!
    ////////////////////////////////////////////////////////////////////////////
    while(screen_size > mySize() && screen_start != 0 && selected != 0) {
        screen_start--;
    }

    this->PrintToPad();     
}

///////////////////////////////////////////////////////////////////////////////
void ItemList::Refresh() {
    // Needs resizing?
    if(this->needsResize || mySize() != lprint_size) {
        this->needsResize = false;
        this->Recreate(mySize(), COLS);
    }

    // REFRESH
    pnoutrefresh(ElementPad, screen_start, 0, 2, 0, LINES-2, COLS);
}

///////////////////////////////////////////////////////////////////////////////
void ItemList::myScrollDown() {
    // selected + 1 because selected starts counting from zero
    // but mySize() from 1
    if(selected+1 < mySize()) {
        selected++;

        if(selected+1 > screen_end)
           screen_start++;     
    }
}

///////////////////////////////////////////////////////////////////////////////
void ItemList::myScrollUp() {

    if(selected != 0) {
        selected--;
    
        if(selected < screen_start)
            screen_start--;
    }
}

///////////////////////////////////////////////////////////////////////////////
void ItemList::Scroll(ScrollDirection sd) {
    this->needsResize = true;    

    if(sd == ScrollDown)
        this->myScrollDown();
    
    if(sd == ScrollUp)
        this->myScrollUp();
}

///////////////////////////////////////////////////////////////////////////////
int ItemList::GetSelected() {
    return selected;
}

///////////////////////////////////////////////////////////////////////////////
};

