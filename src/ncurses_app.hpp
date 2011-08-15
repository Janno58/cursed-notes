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
#ifndef NCURSES_APP_HPP
#define NCURSES_APP_HPP
///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <booknote.hpp>
#include <ncurses/ncurses.hpp>
#include <ncurses/header.hpp>
#include <ncurses/footer.hpp>
#include <ncurses/itemlist.hpp>
#include <ncurses/filler.hpp>
#include <signal.h>
#include <stack>

///////////////////////////////////////////////////////////////////////////////
// Ncurses interface specific stuff
///////////////////////////////////////////////////////////////////////////////
class Ncurses_app {
    public:
        // Constructor
        ///////////////////////////////////////////////////////////////////////
        Ncurses_app(Booknote *);
        
        // Destructor
        ///////////////////////////////////////////////////////////////////////
        ~Ncurses_app();
        
        // Run ncurses interface!
        ///////////////////////////////////////////////////////////////////////
        void Run();
        
        // True  - rebuild/resize all ncurses elements and the window
        // False - nothing
        ///////////////////////////////////////////////////////////////////////
        static bool resize;
        
        // Callback for SIGWINCH, window resize signal
        ///////////////////////////////////////////////////////////////////////
        void static SigWinch(int);
    
    private:
        // Acts on given input
        ///////////////////////////////////////////////////////////////////////
        void ActOnInput(unsigned int); 
        
        // Stack of booknotes
        ///////////////////////////////////////////////////////////////////////
        std::stack<Booknote *> BookStack; 

        NC::NCurses * NCurse;
        NC::Header  * Header;
        NC::Footer  * Footer;
        NC::ItemList* ItemLs;
        NC::Filler  * Filler;
       
        int           cycle;      
        bool          running;  // kill switch
};

///////////////////////////////////////////////////////////////////////////////
#endif /* NCURSES_APP_HPP */
