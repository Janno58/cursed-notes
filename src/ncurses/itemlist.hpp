////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#ifndef ncurses_itemlist_hpp
#define ncurses_itemlist_hpp

////////////////////////////////////////////////////////////////////////////////
#include <notebook.hpp>
#include <ncurses/windowelement.hpp>
#include <ncurses.h>

////////////////////////////////////////////////////////////////////////////////
namespace NC {

////////////////////////////////////////////////////////////////////////////////
enum ScrollDirection {ScrollUp, ScrollDown};

////////////////////////////////////////////////////////////////////////////////
enum Color { clDefault, clBlack, clRed, clGreen, clYellow, clBlue, clMagenta, clCyan, clWhite, clEnd };

////////////////////////////////////////////////////////////////////////////////
class ItemList : public WindowElement{
    public:
        // Recreates the pad used for drawing, used for coping with resizes
        ////////////////////////////////////////////////////////////////////////
        void Recreate(size_t ,size_t);
        
        // Copies pad contents to real screen but does not update
        ////////////////////////////////////////////////////////////////////////
        void Refresh();
        
        // Makes next or previous item active 
        ////////////////////////////////////////////////////////////////////////
        void Scroll(ScrollDirection);

        // Returns nr of currently active/selected item 
        ////////////////////////////////////////////////////////////////////////
        int GetSelected();
       
        // Toggels the hilight of currently selected item
        ////////////////////////////////////////////////////////////////////////
        bool hilight_selected;     

        // Colours!
        ////////////////////////////////////////////////////////////////////////
        Color   TextColor;
        Color   BackColor;

    protected:
        
        // Print book contents, book dependent and should be implemented in
        // derived class
        ////////////////////////////////////////////////////////////////////////
        virtual void PrintToPad() = 0;
        
        // Return amount of elements in underlying book
        ////////////////////////////////////////////////////////////////////////
        virtual unsigned int mySize() = 0;

        // Selects next ( 1 down) item 
        ////////////////////////////////////////////////////////////////////////
        void myScrollDown();
        
        // Selects previous ( 1 up) item 
        ////////////////////////////////////////////////////////////////////////
        void myScrollUp();    

        // Holds the size of the screen, all the space left over from header 
        // and footer get used here
        ////////////////////////////////////////////////////////////////////////
        unsigned int screen_size;

        // These hold the range of items shown on screen
        ///////////////////////////////////////////////////////////////////////
        unsigned int screen_start;
        unsigned int screen_end; 
       
        // Currently selected item number, must be between screen_start and 
        // screen_end
        //////////////////////////////////////////////////////////////////////// 
        unsigned int selected;   // Holds the current selected item number
        
        // Holds pads size from last PrintToPad(), only changes when PrintToPad
        // is called.
        ////////////////////////////////////////////////////////////////////////
        unsigned int    lprint_size;
};

////////////////////////////////////////////////////////////////////////////////
};

////////////////////////////////////////////////////////////////////////////////
#endif/*ncurses_itemlist_hpp */

