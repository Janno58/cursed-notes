################################################################################
# Copyright (c) 2011 Janno Tikka
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
################################################################################
set(REAL_SRCROOT ${CMAKE_SOURCE_DIR}/src)
set(TEST_SRCROOT ${CMAKE_SOURCE_DIR}/tests/src)

set(SRC
    ${REAL_SRCROOT}/notebook.cpp
    ${REAL_SRCROOT}/notebook.hpp
    ${TEST_SRCROOT}/notebook_test.cpp
    
    ${REAL_SRCROOT}/projbook.cpp
    ${REAL_SRCROOT}/projbook.hpp
    ${TEST_SRCROOT}/projbook_test.cpp
)

add_executable(cursednotes_test ${SRC}) 
target_link_libraries(cursednotes_test ncurses boost_unit_test_framework boost_filesystem boost_system boost_serialization)
