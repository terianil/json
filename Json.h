#include <boost/any.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "JsonGrammar.h"

using namespace std;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;



class Json
{
public:
    Json(const char* fileName)
    {
        std::string source = this->ReadFile(fileName);
        JsonGrammar<std::string::iterator> grammar;

        bool parsed = boost::spirit::qi::phrase_parse(
                source.begin(),
                source.end(),
                grammar,
                boost::spirit::ascii::space,
                this->rawData );

        if(!parsed)
        {
            std::cout << "error parsing json document!!!" << std::endl;

            return;
        }

        this->root = boost::any_cast<std::map<std::string, boost::any>>(this->rawData);
    }

    void PrintKeys()
    {
        for( auto it = root.begin(); it != root.end(); ++it ) {
            std::cout << it->first << std::endl;
        }
    }

    bool ContainsKey(string key)
    {
        return this->root.find(key) != root.end();
    }

    template<typename T>
    T GetMemberValue(string key)
    {
        auto found = this->root.find(key);

        if(found != root.end())
        {
            return boost::any_cast<T>((*found).second);
        }

        return T();
    }

    template<typename T>
    bool CheckValueType(string key)
    {
        auto found = this->root.find(key);

        if(found != root.end())
        {
            try {
                auto test = boost::any_cast<T>((*found).second);

                return true;
            }
            catch(...)
            {
                return false;
            }
        }

        return false;
    }

private:
    boost::any rawData;
    std::map<std::string, boost::any> root;

    std::string ReadFile(const char* fileName)
    {
        std::ifstream fs(fileName);
        std::ostringstream ss;
        ss << fs.rdbuf();

        return ss.str();
    }
};