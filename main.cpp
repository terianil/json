#include <iostream>

#include "Json.h"


using namespace std;


int main(int argc, const char* argv[])
{
    auto json = new Json(argv[1]);

    cout << "----------Json members:--------" << endl;
    json->PrintKeys();
    cout << endl;

    cout << "imie: " << json->GetMemberValue<string>("imie") << endl;

    cout << "'numer' type is double: " << json->CheckValueType<double>("numer") << endl;
    cout << "'numer' type is string: " << json->CheckValueType<string>("numer") << endl;
    cout << "numer: " << json->GetMemberValue<double>("numer") << endl;

    cout << endl;
    cout << "Test nested objects:" << endl;
    cout << "'nested' type is nested: " << json->IsNestedObject("nested") << endl;
    cout << "'nested' member members:" << endl;
    json->GetNestedObject("nested").PrintKeys();


    return 0;
}