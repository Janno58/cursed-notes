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
#ifndef ncurses_header_hpp
#define ncurses_header_hpp

///////////////////////////////////////////////////////////////////////////////
#include <ncurses/windowelement.hpp>
#include <ncurses.h>
#include <string>

///////////////////////////////////////////////////////////////////////////////
#define HEADER_HEIGHT 2

///////////////////////////////////////////////////////////////////////////////
namespace NC {

// First line is some information
// Second line is horizontal bar
///////////////////////////////////////////////////////////////////////////////
class Header : public WindowElement {
    public:
        // Constructor
        ////////////////////////////////////////////////////////////////////////
        Header();

        // Destructor
        ////////////////////////////////////////////////////////////////////////
        virtual ~Header();

        // Recreate header
        ////////////////////////////////////////////////////////////////////////
        void Recreate(size_t, size_t);

        // Refresh but dont actually print anything
        ////////////////////////////////////////////////////////////////////////
        void Refresh();

        // Print some information on first line of the program
        ////////////////////////////////////////////////////////////////////////
        void PrintStatus(int, int, std::string);
};

///////////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////
#endif

