#include <boost/any.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "JsonGrammar.h"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

std::string ReadFile(const char* fileName)
{
    std::ifstream fs(fileName);
    std::ostringstream ss;
    ss << fs.rdbuf();

    return ss.str();
}

int main(int argc, const char* argv[])
{
    std::string source = ReadFile(argv[1]);
    JsonGrammar< std::string::iterator > grammar;
    boost::any v;
    bool r = boost::spirit::qi::phrase_parse( source.begin(), source.end(), grammar, boost::spirit::ascii::space, v );
    if( r ) {
        auto a = boost::any_cast< std::map< std::string, boost::any > >( v );
        for( auto it = a.begin(); it != a.end(); ++it ) {
            std::cout << it->first << std::endl;
        }
    }
    return 0;
}