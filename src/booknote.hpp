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
#ifndef booknote_hpp
#define booknote_hpp
///////////////////////////////////////////////////////////////////////////////
// Headers                                                                   //
///////////////////////////////////////////////////////////////////////////////
#include <list>
#include <exception>
#include <sstream>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>

///////////////////////////////////////////////////////////////////////////////
class Booknote : public std::list<Booknote *> {
    friend class boost::serialization::access; // boost needs access to private

    public:
        // Default constructor 
        ////////////////////////////////////////////////////////////////////////
        Booknote() {};


        // Constructor 
        ////////////////////////////////////////////////////////////////////////
        Booknote(std::string);

        // Destructor 
        ////////////////////////////////////////////////////////////////////////
        ~Booknote();
        
        // Add new item
        // @param text Item message
        // @param pos  Position to insert the item at
        ////////////////////////////////////////////////////////////////////////
        void Add(std::string text, int pos);

        // Remove item
        // @param pos  Position of item to remove
        ////////////////////////////////////////////////////////////////////////
        void Remove(int pos);

        // Access item on given position
        // @param pos   The requested item's position 
        ////////////////////////////////////////////////////////////////////////
        Booknote * GetAt(int pos);
        
        // Return size as a string
        ////////////////////////////////////////////////////////////////////////
        std::string SizeString();

        // size  > 0 notebook name
        // size == 0 the note itself
        ////////////////////////////////////////////////////////////////////////
        std::string message;

        // Could not add item 
        ////////////////////////////////////////////////////////////////////////
        class add_exception : public std::exception { };

        // Could not remove item 
        ////////////////////////////////////////////////////////////////////////
        class remove_exception : public std::exception { };
    
        // Could not return item at given position 
        ////////////////////////////////////////////////////////////////////////
        class getat_exception: public std::exception { };
    private:
        // boost serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & version;
            ar & boost::serialization::base_object<std::list<Booknote *> >(*this);
            ar & message;
        }
};

///////////////////////////////////////////////////////////////////////////////
#endif 
