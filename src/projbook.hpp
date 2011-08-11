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
#ifndef projbook_hpp
#define projbook_hpp
///////////////////////////////////////////////////////////////////////////////
// Headers                                                                   //
///////////////////////////////////////////////////////////////////////////////
#include <notebook.hpp>
// std/stl
#include <exception>
#include <algorithm>
// boost
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>

///////////////////////////////////////////////////////////////////////////////
// Holds collection of notebooks, uses std::map as base class and only adds few
// convinience functions                                                      
///////////////////////////////////////////////////////////////////////////////
class Projbook : public notebook_vector {
    friend class boost::serialization::access; // boost needs access to private
    public:
        // Constructor
        ////////////////////////////////////////////////////////////////////////
        Projbook();
        
        // Destructor
        ////////////////////////////////////////////////////////////////////////
        ~Projbook();
     
        // Add new item
        void Add(std::string);

        // Removes item by ID
        ////////////////////////////////////////////////////////////////////////
        void Remove(unsigned int);        
        
        // Exceptions
        ////////////////////////////////////////////////////////////////////////
            // Can not add new item
            ////////////////////////////////////////////////////////////////////
            class add_book_exception : public std::exception { };

            // Can not remove item
            ////////////////////////////////////////////////////////////////////
            class remove_book_exception : public std::exception { };
    
    private:
        // boost serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            if(version == 0) {
            }
            
            ar & boost::serialization::base_object<notebook_vector>(*this);
        }
};

#endif 
