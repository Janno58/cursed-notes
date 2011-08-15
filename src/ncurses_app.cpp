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
// Header
///////////////////////////////////////////////////////////////////////////////
#include <ncurses_app.hpp>

///////////////////////////////////////////////////////////////////////////////
bool Ncurses_app::resize;

///////////////////////////////////////////////////////////////////////////////
Ncurses_app::Ncurses_app(Booknote * note) {
    BookStack.push(note);

    NCurse = new NC::NCurses();
    Header = new NC::Header();
    Footer = new NC::Footer();
    ItemLs = new NC::ItemList(BookStack.top());
    Filler = new NC::Filler();
    cycle  = 0;
    running= true;

    signal(SIGWINCH, Ncurses_app::SigWinch);
}

///////////////////////////////////////////////////////////////////////////////
Ncurses_app::~Ncurses_app() {
    delete Filler;
    delete ItemLs;
    delete Footer;
    delete Header;
    delete NCurse;
}

///////////////////////////////////////////////////////////////////////////////
void Ncurses_app::SigWinch(int sig) {
    if(sig == SIGWINCH) {
        resize = true; 
    }
}

////////////////////////////////////////////////////////////////////////////////
void Ncurses_app::ActOnInput(unsigned int userinp) {
    // Open currently selected item
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == ' ') { try {
        Booknote * new_root = BookStack.top()->GetAt(ItemLs->GetSelected());
        BookStack.push(new_root);

        delete ItemLs;
        ItemLs = new NC::ItemList(BookStack.top());
        cycle = 0;
    // Can not open non existant Booknote
    } catch (Booknote::getat_exception) {
    // Rethrow unknown exception
    } catch (...) {
    }}

    // 'Close' currently selected item and open previously open item
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'p') {
        // We are at root item!
        if(BookStack.size() == 1) {
            return;
        } else {
            BookStack.pop();

            delete ItemLs;
            ItemLs = new NC::ItemList(BookStack.top());
            cycle = 0;
        }
    }

    // User wants this operation shut down asap! 
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'q')
        running = false;
        
    // Go down 1 item 
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'j' or userinp == KEY_DOWN) {
        ItemLs->Scroll(NC::ScrollDown);
        cycle = 0;
    }
        
    // Go up 1 item 
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'k' or userinp == KEY_UP) {
        ItemLs->Scroll(NC::ScrollUp);
        cycle = 0;
    }

    // Delete currently selected item
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'd') {
        try {
            BookStack.top()->Remove(ItemLs->GetSelected());
        } catch(Booknote::remove_exception) {
            Footer->PrintStatus("Could not remove item!");
        }
        
        ItemLs->needsResize=true;
    }       

    // Add new item
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'n') {
        try {
            BookStack.top()->Add(Footer->GetString(), ItemLs->GetSelected()+1);
        } catch(Booknote::add_exception) {
            Footer->PrintStatus("Could not add item!");
        }
    }

    // Edit item 
    ////////////////////////////////////////////////////////////////////////////
    if(userinp == 'e') { try {
        int pos = ItemLs->GetSelected();
        std::string orig_message = BookStack.top()->GetAt(pos)->message;
        std::string new_message  = Footer->GetString(orig_message);

        BookStack.top()->GetAt(pos)->message.assign(new_message);
        
        ItemLs->needsResize=true;
    } catch (Booknote::getat_exception()) {
        Footer->PrintStatus("Could not remove item!");
    }
    }
}

////////////////////////////////////////////////////////////////////////////////
void Ncurses_app::Run() {
    while(running) {
        try {
        if(resize) {
            endwin();
            refresh();
            
            timeout(10);
            getch();
            timeout(-1);     
     
            Header->needsResize = true;
            ItemLs->needsResize = true;
            Footer->needsResize = true;

            resize = false;   
        }
        
        Header->PrintStatus(BookStack.top()->size(), ItemLs->GetSelected()+1, BookStack.top()->message);
        
        cycle++;

        // enable selected item hilight
        if(cycle < 75 && !ItemLs->hilight_selected) {
            ItemLs->hilight_selected = true; 
            ItemLs->needsResize = true;
        }
        // disable selected item hilight
        else if(cycle > 75 && ItemLs->hilight_selected) {
            ItemLs->hilight_selected = false; 
            ItemLs->needsResize = true;
        }
        // Cap cycle to 500, no need for a overflow
        else if(cycle > 500) {
            cycle = 100;
        }

        Filler->Refresh();
        Header->Refresh();
        ItemLs->Refresh();
        Footer->Refresh();            

        doupdate();        
       
        ActOnInput(Footer->ReadKey());

        } catch (...) {
            std::cerr << "Unknown error!" << std::endl;
            running = false;
        } 
    }
}
