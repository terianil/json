#include <boost/spirit.hpp>

struct JsonGrammar : public boost::spirit::grammar<JsonGrammar>
{
    template <typename Scanner>
    struct definition
    {
        boost::spirit::rule<Scanner> object, element, string, value, number;

        definition(const JsonGrammar& self)
        {
            using namespace boost::spirit;
            object = "{" >> element >> *("," >> element) >> "}";
            element = string >> ":" >> value;
            string = "\"" >> *~ch_p("\"") >> "\"";
            value = string | number;
            number = real_p;
        }

        const boost::spirit::rule<Scanner>& start()
        {
            return object;
        }
    };
};