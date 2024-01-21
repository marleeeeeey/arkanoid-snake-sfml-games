#include <gtest/gtest.h>

struct Children
{
    std::string name;
    int age;
    std::map<std::string, int> data;

    auto operator<=>( const Children& other ) const = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( Children, name, age, data );
};

TEST( NlohmannJson, BasicsFromManual )
{
    std::string jsonDoc = R"json(
    {
        "name": "John",
        "age": 30,
        "city": "New York",
        "scores": [95, 88, 75],
        "info": {
            "married": false,
            "children": {
                "name": "Ann",
                "age": 5,
                "data": {
                    "a": 1,
                    "b": 2
                }
            }
        }
    }
    )json";

    json parsed = json::parse( jsonDoc );
    json childrenJson = getElementByPath( parsed, "info.children" ).value();

    Children childrenOne;
    childrenOne.name = childrenJson["name"];
    childrenOne.age = childrenJson["age"];
    childrenOne.data = childrenJson["data"];

    EXPECT_EQ( childrenJson["name"], "Ann" );
    EXPECT_EQ( childrenJson["age"], 5 );
    EXPECT_EQ( childrenJson["data"]["a"], 1 );
    EXPECT_EQ( childrenJson["data"]["b"], 2 );

    Children childrenTwo = childrenJson;
    EXPECT_EQ( childrenOne, childrenTwo );

    Children childrenThree = childrenJson.get<Children>();
    EXPECT_EQ( childrenOne, childrenThree );
}
