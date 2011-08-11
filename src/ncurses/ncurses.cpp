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
#include <ncurses/ncurses.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace NC {

///////////////////////////////////////////////////////////////////////////////
NCurses::NCurses() {
    /* Initialize curses */
    initscr();
    
    noecho();
    cbreak();
    curs_set(0);

    // following code is owned by Andrzej Rybczak @ electricityispower@gmail.com
    const int ColorsTable[] =
    {
        COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
        COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE
    };

    if(has_colors())
    {
        start_color();
        use_default_colors();
        int num = 1;
        int i = -1;
        for (; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                init_pair(num++, ColorsTable[j], i < 0 ? i : ColorsTable[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
NCurses::~NCurses() {
    curs_set(1);
    endwin();
}

///////////////////////////////////////////////////////////////////////////////
};
