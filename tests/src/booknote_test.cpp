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
#define BOOST_TEST_MODULE unimportantstuff 
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

////////////////////////////////////////////////////////////////////////////////
#include <booknote.hpp>
#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE (booknote)

// Test Booknote::Add()
////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE (Add) {
    Booknote bn("test");

    BOOST_CHECK_NO_THROW(bn.Add("Need to write more test cases!!!", 0));
    BOOST_CHECK_THROW(bn.Add("", 0), Booknote::add_exception);
}

// Test Booknote::Remove()
////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE (Remove) {
    Booknote bn;

    BOOST_CHECK_THROW(bn.Remove(0), Booknote::remove_exception);
    BOOST_CHECK_NO_THROW(bn.Add("Need to write more test cases!!!", 0));
    BOOST_CHECK_NO_THROW(bn.Remove(0));
}

// Test Booknote::message
////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE (message) {
    Booknote bn;

    BOOST_CHECK_NO_THROW(bn.message.assign("TestyName"));
    BOOST_CHECK_EQUAL(bn.message, "TestyName");
}

////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE_END()
