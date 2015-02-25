#include <boost/any.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

using qi::lexeme;
using qi::double_;
using qi::bool_;
using ascii::char_;

template< typename Iterator >
struct JsonGrammar : qi::grammar< Iterator, boost::any(), ascii::space_type > {
    JsonGrammar(): JsonGrammar::base_type( root ) {
        root = object.alias();
        object = '{' >> pair % ',' >> '}';
        pair = string >> ':' >> value;
        value = array | string | double_ | bool_;
        array = '[' >> value % ',' >> ']';
        string = lexeme[ '\"' >> *( char_ - '\"' ) >> '\"' ];
    }

    qi::rule< Iterator, boost::any(), ascii::space_type > root;
    qi::rule< Iterator, std::map< std::string, boost::any >(), ascii::space_type > object;
    qi::rule< Iterator, std::pair< std::string, boost::any >(), ascii::space_type > pair;
    qi::rule< Iterator, boost::any(), ascii::space_type > value;
    qi::rule< Iterator, std::vector< boost::any >(), ascii::space_type > array;
    qi::rule< Iterator, std::string(), ascii::space_type > string;
};