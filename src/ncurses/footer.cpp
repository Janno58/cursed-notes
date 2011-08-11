///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011 Janno Tikka
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the follopadg conditions:
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
#include <ncurses/footer.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace NC {

///////////////////////////////////////////////////////////////////////////////
Footer::Footer() {
    // init
    y_statusline= 1;
    ElementPad  = newpad(2, COLS);
    
    this->SetTimeout(50);
    keypad(ElementPad, true);   
    
    mvwhline(ElementPad,  0, 0, ACS_HLINE, COLS);
}

///////////////////////////////////////////////////////////////////////////////
Footer::~Footer() {
    delwin(ElementPad);
}

///////////////////////////////////////////////////////////////////////////////
void Footer::Recreate(size_t lines, size_t cols) {
    delwin(ElementPad);
    ElementPad = newpad(lines, cols);
    
    keypad(ElementPad, true);
    
    mvwhline(ElementPad,  0, 0, ACS_HLINE, COLS);
    
    this->SetTimeout(50);
}

///////////////////////////////////////////////////////////////////////////////
void Footer::Refresh() {
    // Does it need a good old fashioned resize?
    if(this->needsResize) {
        this->needsResize = false;
        this->Recreate(2, COLS);
    }

    pnoutrefresh(ElementPad, 0, 0, (LINES-2), 0, LINES, COLS);
}

///////////////////////////////////////////////////////////////////////////////
void Footer::PrintStatus(std::string status) {
    if(ElementPad != NULL) { 
        if(status.length() > 0) {
            mvwprintw(ElementPad, y_statusline, 0, "%s", status.c_str());
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
std::string Footer::GetString() {
    std::string    user_str;
    bool            input = true;
    int             uchar;
    int             counter = 0;
    
    keypad(ElementPad, true);

    do {
        this->BlankLine(y_statusline);
        mvwprintw(ElementPad, y_statusline, 0, "%s", user_str.c_str());
        
        // Print the fancy char pointer vertical line thingy
        ////////////////////////////////////////////////////////////////////////
        if(counter == 0)
            mvwaddch(ElementPad, 1, 0, ACS_VLINE);
        else
            mvwaddch(ElementPad, 1, counter, ACS_VLINE);
        
        // The | and character typed previously by user get drawn 
        ////////////////////////////////////////////////////////////////////////
        Refresh(); doupdate();
        
        uchar = ReadKey(); 

        // These get ignored
        if(uchar < 10 || (uchar > 10 && uchar != 21 && uchar < 32)) 
            continue;
        
        switch(uchar) {
            case ERR: 
            // enter
            case '\n':
            {
                input = false;
                break;
            }
            
            // backspace 
            case 127: case KEY_BACKSPACE:
            {
            }

            // left
            case KEY_LEFT:
            {
                if(counter > 0) {
                    counter--;
                }         
                
                if (uchar != KEY_BACKSPACE && uchar != 127)
                    break; 
            }

            // delete
            case KEY_DC:
            {
                if(!user_str.empty()) {
                    user_str.erase(user_str.end() - 1);
                }
                break;
            }           

            // anything else
            default:
            {
                user_str.push_back(uchar);
                counter++;
                break;
            }
        }
    } while (input);    

    this->BlankLine(y_statusline);

    return user_str;
}

////////////////////////////////////////////////////////////////////////////////
std::string Footer::GetString(std::string start_string) {
    std::string     user_str    = start_string;
    unsigned int    counter     = start_string.size();
    bool            input = true;
    int             uchar;
    
    keypad(ElementPad, true);

    do {
        this->BlankLine(y_statusline);
        mvwprintw(ElementPad, y_statusline, 0, "%s", user_str.c_str());
        
        // Print the fancy char pointer vertical line thingy
        ////////////////////////////////////////////////////////////////////////
        if(counter == 0)
            mvwaddch(ElementPad, 1, 0, ACS_VLINE);
        else
            mvwaddch(ElementPad, 1, counter, ACS_VLINE);
        
        // The | and character typed previously by user get drawn 
        ////////////////////////////////////////////////////////////////////////
        Refresh(); doupdate();
        
        uchar = ReadKey(); 

        // These get ignored
        if(uchar < 10 || (uchar > 10 && uchar != 21 && uchar < 32)) 
            continue;
        
        switch(uchar) {
            case ERR: 
            // enter
            case '\n':
            {
                input = false;
                break;
            }
            
            // backspace 
            case 127: case KEY_BACKSPACE:
            {
            }

            // left
            case KEY_LEFT:
            {
                if(counter > 0) {
                    counter--;
                }         
                
                if (uchar != KEY_BACKSPACE && uchar != 127)
                    break; 
            }

            // delete
            case KEY_DC:
            {
                if(!user_str.empty()) {
                    user_str.erase(user_str.end() - 1);
                }
                break;
            }           

            // anything else
            default:
            {
                user_str.push_back(uchar);
                counter++;
                break;
            }
        }
    } while (input);    

    this->BlankLine(y_statusline);

    return user_str;
}
///////////////////////////////////////////////////////////////////////////////
};

