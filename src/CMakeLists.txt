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
set(SRCROOT ${CMAKE_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/cursednotes.cpp
    ${SRCROOT}/notebook.cpp
    ${SRCROOT}/notebook.hpp
    ${SRCROOT}/projbook.cpp
    ${SRCROOT}/projbook.hpp
    ${SRCROOT}/pbio.cpp
    ${SRCROOT}/pbio.hpp
    ${SRCROOT}/note.hpp
    ${SRCROOT}/ncurses_app.hpp
    ${SRCROOT}/ncurses_app.cpp
    ${SRCROOT}/ncurses/ncurses.cpp
    ${SRCROOT}/ncurses/ncurses.hpp
    ${SRCROOT}/ncurses/header.cpp
    ${SRCROOT}/ncurses/header.hpp
    ${SRCROOT}/ncurses/footer.cpp
    ${SRCROOT}/ncurses/footer.hpp
    ${SRCROOT}/ncurses/projlist.cpp
    ${SRCROOT}/ncurses/projlist.hpp
    ${SRCROOT}/ncurses/notelist.cpp
    ${SRCROOT}/ncurses/notelist.hpp
    ${SRCROOT}/ncurses/itemlist.cpp
    ${SRCROOT}/ncurses/itemlist.hpp
    ${SRCROOT}/ncurses/filler.hpp
    ${SRCROOT}/ncurses/filler.cpp
    ${SRCROOT}/ncurses/windowelement.cpp
    ${SRCROOT}/ncurses/windowelement.hpp
)

add_executable(cursednotes ${SRC}) 
target_link_libraries(cursednotes ncurses boost_filesystem boost_system boost_serialization)
