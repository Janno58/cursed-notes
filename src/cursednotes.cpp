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
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <ncurses_app.hpp>
#include <projbook.hpp>
#include <pbio.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace stuff
///////////////////////////////////////////////////////////////////////////////
namespace bfs = boost::filesystem;

///////////////////////////////////////////////////////////////////////////////
// Cursed Notes entry point 
///////////////////////////////////////////////////////////////////////////////
int main() {
    bool run = true;

    bfs::path home_path(getenv("HOME"));
    bfs::path cnfg_path(home_path / ".config/");
    bfs::path prog_path(home_path / ".config/cursednotes/");
    bfs::path full_path(home_path / ".config/cursednotes/cursednotes.bin");

    // Paths okay?
    if(!exists(home_path)) {
        std::cerr << "Problem with $HOME path!" << std::endl;
        run = false;
    } else if(!exists(cnfg_path)) {
        std::cerr << "Problem with $HOME/.config path!" << std::endl;
        run = false;
    } else if(!exists(prog_path)) {
        std::cout << "Trying to create $HOME/.config/cursednotes dir" << std::endl;

        // We can and try create this for user!
        if(create_directory(prog_path)) {
            std::cout << "Dir created succesfully!" << std::endl;
        } else {
            std::cerr << "Problem creating the dir!" << std::endl;
            run = false;
        }
    } 
    
    // If there was error with paths, no point in running
    if(run) {
        Projbook    * pb        = new Projbook();    
        pbio        * pio       = new pbio(full_path);
        Ncurses_app * interface = new Ncurses_app(pb = pio->Read());
        
        interface->Run();
        pio->Write(pb);   

        delete interface;
        delete pio;
        delete pb;
    }
    return false;
}
