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
// Headers                                                                    //
////////////////////////////////////////////////////////////////////////////////
#include <booknote.hpp>

////////////////////////////////////////////////////////////////////////////////
Booknote::Booknote(std::string label) {
    message = label;
}

////////////////////////////////////////////////////////////////////////////////
Booknote::~Booknote() {
    while(!empty()) {
        delete back();
        pop_back();
    } 
}

///////////////////////////////////////////////////////////////////////////////
void Booknote::Add(std::string text, int pos) {
    if(text.empty())
        throw Booknote::add_exception();
    
    try {
        // No random access with std::list
        std::list<Booknote *>::iterator it = begin();
        for(int i = 0; i != pos; i++) {
            it++;
        }
        
        // Destrcutor will delete this
        Booknote * note = new Booknote(text);

        insert(it, note);
    } catch(...) {
        throw Booknote::add_exception();
    }
}

///////////////////////////////////////////////////////////////////////////////
void Booknote::Remove(unsigned int pos) {
    // Anything to remove?
    if(empty() or pos > size()-1) 
        throw Booknote::remove_exception();

    try {
        // No random access with std::list
        std::list<Booknote *>::iterator it = begin();
        for(unsigned int i = 0; i != pos; i++) {
            it++;
        }
        
        delete (*it);
        erase(it);
    } catch(...) {
        throw Booknote::remove_exception();
    }
}

///////////////////////////////////////////////////////////////////////////////
Booknote * Booknote::GetAt(int pos) {
    if(empty())
        throw Booknote::getat_exception();

    std::list<Booknote *>::iterator it = begin();
    for(int i = 0; i != pos; i++) {
           it++;
    }

    return (*it);
}

///////////////////////////////////////////////////////////////////////////////
std::string Booknote::SizeString() {
    std::stringstream stream;

    stream << size();

    return stream.str();
}
