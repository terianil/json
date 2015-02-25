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

    void PrintKeys() const
    {
        for( auto it = root.begin(); it != root.end(); ++it ) {
            std::cout << it->first << std::endl;
        }
    }

    bool ContainsKey(string key) const
    {
        return this->root.find(key) != root.end();
    }

    template<typename T>
    const T GetMemberValue(string key) const
    {
        auto found = this->root.find(key);

        if(found != root.end())
        {
            return boost::any_cast<T>((*found).second);
        }

        return T();
    }

    template<typename T>
    bool CheckValueType(string key) const
    {
        auto found = this->root.find(key);

        if(found != root.end())
        {
            try
            {
                auto first = (*found).first;
                auto second = (*found).second;

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

    bool IsNestedObject(string key) const
    {
        return CheckValueType<std::map<std::string, boost::any>>(key);
    }

    const Json GetNestedObject(string key)
    {
        auto newRoot = this->GetMemberValue<std::map<std::string, boost::any>>(key);

        return Json(newRoot);
    }

    bool IsArray(string key) const
    {
        return CheckValueType<vector<boost::any>>(key);
    }

    template<typename T>
    const vector<T> GetArrayOfType(string key) const
    {
        vector<T> out;

        auto o = GetMemberValue<std::vector<boost::any>>(key);

        for(auto e : o)
        {
            out.push_back(boost::any_cast<T>(e));
        }

        return out;
    }

private:
    boost::any rawData;
    std::map<std::string, boost::any> root;

    Json(std::map<std::string, boost::any> newRoot)
    {
        this->root = newRoot;
    }

    std::string ReadFile(const char* fileName)
    {
        std::ifstream fs(fileName);
        std::ostringstream ss;
        ss << fs.rdbuf();

        return ss.str();
    }
};