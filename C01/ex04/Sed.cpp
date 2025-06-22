#include "Sed.hpp"

Sed::Sed(const std::string &filename, const std::string &s1, const std::string &s2)
    : _filename(filename), _s1(s1), _s2(s2) {}

int Sed::replace() {
    std::ifstream infile(_filename.c_str());
    if (!infile) {
        std::cerr << "Error: Cannot open file " << _filename << std::endl;
        return 1;
    }

    std::ofstream outfile((_filename + ".replace").c_str());
    if (!outfile) {
        std::cerr << "Error: Cannot create output file" << std::endl;
        infile.close();
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = 0;
        while ((pos = line.find(_s1, pos)) != std::string::npos) {
            line = line.substr(0, pos) + _s2 + line.substr(pos + _s1.length());
            pos += _s2.length();
        }
        outfile << line << std::endl;
    }

    infile.close();
    outfile.close();
    return 0;
}

/*
 std::ifstream infile(_filename.c_str());
Open the file _filename for reading using ifstream (input file stream)
.c_str() is used to convert the std::string into a C-style string, required by older C++ APIs
Open a new file named filename.replace for writing using ofstream (output file stream)
std::string::npos is a special constant in C++ that means “not found”.
Loop: Read each line and replace text
If it finds one, we replace i
If it returns npos, we stop the loop

Read one line at a time from infile into line
Looks for every instance of _s1 in the current line , replace , 
Keeps updating pos so it doesn't get stuck in a loop

Let’s say:
line = "I love cake. I love pie."

_s1 = "love"

_s2 = "eat"

First match is at pos = 2 (starts at "love")

Then:

cpp
Copy
Edit
line.substr(0, pos)           // "I "            (everything before "love")
+ _s2                         // "eat"           (replacement)
+ line.substr(pos + _s1.length()) // " cake. I love pie." (everything after "love")
 // Move past the inserted string to find the next match
*/