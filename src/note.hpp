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
#ifndef NOTE_HPP
#define NOTE_HPP 

////////////////////////////////////////////////////////////////////////////////
// Headers                                                                    //
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>

// Note 
////////////////////////////////////////////////////////////////////////////////
class Note : public std::string {
    friend class boost::serialization::access; // boost needs access to private
    private:
        // boost serialization
        ////////////////////////////////////////////////////////////////////////
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
                ar & boost::serialization::base_object<std::string>(*this);
                ar & version;
        }
};

// Typedef for vector of Notes
////////////////////////////////////////////////////////////////////////////////
typedef std::vector<Note> note_vector;

#endif 
