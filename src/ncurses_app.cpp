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
Ncurses_app::Ncurses_app(Projbook * pbook) {
    Books  = pbook;

    NCurse = new NC::NCurses();
    Header = new NC::Header();
    Footer = new NC::Footer();
    ItemLs = new NC::ProjList(Books);
    Filler = new NC::Filler();
    CurBook= NULL; 
    cycle  = 0;
    screen = 0;
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

///////////////////////////////////////////////////////////////////////////////
void Ncurses_app::ActOnInput(unsigned int userinp) {
    // Space - change between Projbook and Notebook view
    ////////////////////////////////////////////////////////////////////
    if(userinp == ' ') {
        // Choose notebook
        if(screen == 0) {
            if(ItemLs->GetSelected() != -1) {
                Switch_View(&Books->at(ItemLs->GetSelected()));
            }
        }

        // If notebook is open, change back to Notebook selection screen
        else if(screen == 1) {
            if(ItemLs->GetSelected() != -1 && CurBook != NULL) {
                Switch_View();
            }
        }
        cycle = 0;
    }

    // User wants this operation shut down asap! 
    ////////////////////////////////////////////////////////////////////
    if(userinp == 'q')
        running = false;
        
    // Go down 1 item 
    ////////////////////////////////////////////////////////////////////
    if(userinp == 'j' or userinp == KEY_DOWN) {
        ItemLs->Scroll(NC::ScrollDown);
        cycle = 0;
    }
        
    // Go up 1 item 
    ////////////////////////////////////////////////////////////////////
    if(userinp == 'k' or userinp == KEY_UP) {
        ItemLs->Scroll(NC::ScrollUp);
        cycle = 0;
    }

    // Delete currently selected item
    ////////////////////////////////////////////////////////////////////   
    if(userinp == 'd') {
        try {
            // Remove project
            if(screen == 0)
                Books->Remove(ItemLs->GetSelected());            
            // Remove note
            else if(screen == 1 && CurBook != NULL)
                CurBook->Remove(ItemLs->GetSelected());            
        } catch (Notebook::remove_note_exception) {
            Footer->PrintStatus("Erro removing item, nothing to remove?");
            return;
        } catch (Projbook::remove_book_exception) {
            Footer->PrintStatus("Erro removing item, nothing to remove?");
            return;
        }

        ItemLs->needsResize=true;
    }       

    // Add new item
    ////////////////////////////////////////////////////////////////////
    if(userinp == 'n') {
        std::string user_str = Footer->GetString();
        
        // Only save if non empty 
        ////////////////////////////////////////////////////////////////
        if(!user_str.empty()) {
            // New notebook
            if(screen == 0) 
                Books->Add(user_str);
            // New note
            else if(screen == 1 && CurBook != NULL)
                CurBook->Add(user_str);
            
            Footer->PrintStatus("Added!");
            resize=true;
        } else {
            Footer->PrintStatus("Empty?!"); 
        }
    }

    // Edit item 
    ////////////////////////////////////////////////////////////////////
    if(userinp == 'e') {
        std::string user_str;

        // Change notebook name
        if(screen == 0) {
            user_str = Footer->GetString(Books->at(ItemLs->GetSelected()).Name);
            // Dont need no empty name
            if(!user_str.empty()) {
                Books->at(ItemLs->GetSelected()).Name.assign(user_str);
                ItemLs->needsResize=true;
            }
        }

        // Change note
        else if(screen == 1 && CurBook != NULL) {
            user_str = Footer->GetString(CurBook->at(ItemLs->GetSelected()));
            // Dont need no empty name
            if(!user_str.empty()) {
                CurBook->at(ItemLs->GetSelected()).assign(user_str);
                ItemLs->needsResize=true;
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
void Ncurses_app::Switch_View() {
    if(CurBook != NULL && screen == 1) {
        CurBook = NULL;
        screen = 0;
        delete ItemLs;
        ItemLs = new NC::ProjList(Books); 
    }
}

///////////////////////////////////////////////////////////////////////////////
void Ncurses_app::Switch_View(Notebook * new_book) {
    if(CurBook == NULL && screen == 0) {
        CurBook = new_book;
        screen  = 1;
        delete ItemLs;
        ItemLs = new NC::NoteList(CurBook); 
    }
}

///////////////////////////////////////////////////////////////////////////////
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

        if(screen == 0) {
            Header->PrintStatus(Books->size(), ItemLs->GetSelected() + 1);
        } else if(screen == 1 && CurBook != NULL) {
            Header->PrintStatus(CurBook->size(), ItemLs->GetSelected() + 1);
        }

        cycle++;

        if(cycle < 75 && !ItemLs->hilight_selected) {
            ItemLs->hilight_selected = true; 
            ItemLs->needsResize = true;
        } else if(cycle > 75 && ItemLs->hilight_selected) {
            ItemLs->hilight_selected = false; 
            ItemLs->needsResize = true;
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
