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
#ifndef ncurses_windowelement_hpp
#define ncurses_windowelement_hpp

///////////////////////////////////////////////////////////////////////////////
#include <ncurses.h>

///////////////////////////////////////////////////////////////////////////////
namespace NC {

// Hosts some code that all things that want to be drawn on screen share 
///////////////////////////////////////////////////////////////////////////////
class WindowElement {
    public:
        // Constructor
        ///////////////////////////////////////////////////////////////////////
        WindowElement();
        
        // Virtual destructor
        ///////////////////////////////////////////////////////////////////////
        virtual ~WindowElement();

        // Causes recreation of given element
        // so it gets new size
        ///////////////////////////////////////////////////////////////////////
        virtual void Recreate(size_t, size_t) {};
        
        // Refreshes but does not update really, need to call doupdate later 
        ///////////////////////////////////////////////////////////////////////
        virtual void Refresh() {};
        
        // Gets one key from ElementPad, call might be blocking depending on
        // ElementPad timeout 
        ///////////////////////////////////////////////////////////////////////
        virtual int  ReadKey();
       
        // Clears given line unless otherwise specified
        ///////////////////////////////////////////////////////////////////////
        virtual void BlankLine(int = 0);        

        // Sets pad timeout:
        // -1 = ReadKey is blocking
        // >0 = ReadKey returns after given wait time
        ///////////////////////////////////////////////////////////////////////
        virtual void SetTimeout(int = 50);
              
        int needsResize;
        
    protected:
        int       y_statusline;
        WINDOW  * ElementPad;

///////////////////////////////////////////////////////////////////////////////
};
   
///////////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////
#endif
