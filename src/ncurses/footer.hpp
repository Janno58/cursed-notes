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
////////////////////////////////////////////////////////////////////////////////
#include <ncurses/windowelement.hpp>
#include <ncurses.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////
#ifndef ncurses_footer_hpp
#define ncurses_footer_hpp

////////////////////////////////////////////////////////////////////////////////
namespace NC {

////////////////////////////////////////////////////////////////////////////////
class Footer : public WindowElement {
    public:
        
        // Constructor
        ////////////////////////////////////////////////////////////////////////
        Footer();
        
        // Destructor
        ////////////////////////////////////////////////////////////////////////
        virtual ~Footer();
        
        // Recreate footer to match new given size
        ////////////////////////////////////////////////////////////////////////
        void Recreate(size_t, size_t); 
        
        // Make footer ready to be drawn on screen
        ////////////////////////////////////////////////////////////////////////
        void Refresh();

        // Prints given std::string at y_statusline, cols = 0
        ////////////////////////////////////////////////////////////////////////
        void PrintStatus(std::string);
        
        // Gets a string from user, this function is such a mess!
        ////////////////////////////////////////////////////////////////////////
        std::string GetString();
    
        // Gets a string from user, with start string, so its more of edit
        // thingy 
        ////////////////////////////////////////////////////////////////////////
        std::string GetString(std::string);
};

////////////////////////////////////////////////////////////////////////////////
};

////////////////////////////////////////////////////////////////////////////////
#endif

