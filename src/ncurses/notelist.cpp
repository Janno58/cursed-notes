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
#include <ncurses/notelist.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace NC {

///////////////////////////////////////////////////////////////////////////////
NoteList::NoteList(Notebook * nbook) {
    nb          = nbook;
    lprint_size = 0;
    selected    = 0;
    screen_size = LINES - 4; // 4 is the space used by header and footer
    screen_start= 0;
    screen_end  = LINES-4;
    TextColor   = clYellow;
    BackColor   = clBlack;   

    ElementPad = newpad(nb->size(), COLS);

    this->PrintToPad();    
}

///////////////////////////////////////////////////////////////////////////////
NoteList::~NoteList() {
    delwin(ElementPad);
}

////////////////////////////////////////////////////////////////////////////////
void NoteList::PrintToPad() {
    unsigned int cur_row = 0;
    lprint_size = nb->size();
   
    // color on 
    wattron(ElementPad, COLOR_PAIR(TextColor));          

    for(note_vector::iterator itr = nb->begin(); itr < nb->end(); itr++) {
        
        if(cur_row == selected) {
            // change current color include fancy background color
            wattron(ElementPad, COLOR_PAIR(TextColor*8+BackColor));   
            // Fill with spaces so we get background color 
            for(int j = 0; j <= COLS; j++)
                mvwprintw(ElementPad, cur_row, j, " ");
        }    
        
        // Print note contents
        mvwprintw(ElementPad, cur_row, 0, "%s", (*itr).c_str());    

        // Restore to normal color 
        wattron(ElementPad, COLOR_PAIR(TextColor));      
        // next row
        cur_row++; 
    }

    // color off
    wattroff(ElementPad, COLOR_PAIR(TextColor));          
}

///////////////////////////////////////////////////////////////////////////////
unsigned int NoteList::mySize() {
    return nb->size();
}

///////////////////////////////////////////////////////////////////////////////
};

