#include <fstream>
#include <sstream>
#include <iostream>
#include "JsonGrammar.h"

using namespace std;
using namespace boost::spirit;

string ReadFile(const char* fileName)
{
    std::ifstream fs(fileName);
    std::ostringstream ss;
    ss << fs.rdbuf();
    std::string data = ss.str();
}

int main(int argc, char *argv[])
{
    std::string data = ReadFile(argv[1]);

    JsonGrammar grammar;
    auto info = parse(data.c_str(), grammar, boost::spirit::space_p);
    if (info.hit)
    {
        if (info.full)
            std::cout << "parsed" << std::endl;
        else
            std::cout << "parsed partially" << std::endl;
    }
    else
        std::cout << "parsing error: '" << info.stop << "'" << std::endl;

    return 0;
}