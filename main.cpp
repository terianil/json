#include <iostream>

#include "Json.h"
#include "Performance.h"


using namespace std;


int main(int argc, const char* argv[])
{
    cout << "mem before: " << GetMemorySize() << endl;
    auto time1 = Time();

    auto json = new Json(argv[1]);

    auto time2 = Time();

    cout << "mem after: " << GetMemorySize() << endl;
    cout << "loading time, ms: " << TimeDiff(time1, time2).tv_nsec / 1024 << endl;

    cout << "----------Json members:--------" << endl;
    json->PrintKeys();
    cout << endl;

    cout << "imie: " << json->GetMemberValue<string>("imie") << endl;

    cout << "'numer' type is double: " << json->CheckValueType<double>("numer") << endl;
    cout << "'numer' type is string: " << json->CheckValueType<string>("numer") << endl;
    cout << "numer: " << json->GetMemberValue<double>("numer") << endl;

    cout << endl;
    cout << "Testing nested objects:" << endl;
    cout << "'nested' type is nested: " << json->IsNestedObject("nested") << endl;
    cout << "'nested' member members:" << endl;
    json->GetNestedObject("nested").PrintKeys();

    cout << endl;
    cout << "Testing arrays:" << endl;
    cout << "'array' type is array: " << json->IsArray("array") << endl;
    cout << "'nested' member members:" << endl;
    for (auto e:json->GetArrayOfType<double>("array"))
    {
        cout << "array element: " << e << endl;
    }

    return 0;
}