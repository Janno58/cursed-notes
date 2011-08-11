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
#ifndef ncurses_projlist_hpp
#define ncurses_projlist_hpp

////////////////////////////////////////////////////////////////////////////////
#include <projbook.hpp>
#include <notebook.hpp>
#include <ncurses/itemlist.hpp>
#include <ncurses/windowelement.hpp>
#include <ncurses.h>

////////////////////////////////////////////////////////////////////////////////
namespace NC {

////////////////////////////////////////////////////////////////////////////////
class ProjList : public ItemList {
    public:
        // Constructor
        ////////////////////////////////////////////////////////////////////////
        ProjList(Projbook *);
        
        // Destructor
        ////////////////////////////////////////////////////////////////////////
        ~ProjList();

    private:
        // Prints ProjBook contents
        ////////////////////////////////////////////////////////////////////////
        void PrintToPad();
        
        // Returns size of Notebook
        ////////////////////////////////////////////////////////////////////////
        unsigned int mySize();

        Projbook * pb; // pointer to projbook with all the notebooks!
};

////////////////////////////////////////////////////////////////////////////////
};

////////////////////////////////////////////////////////////////////////////////
#endif /* ncurses_projlist_hpp */

