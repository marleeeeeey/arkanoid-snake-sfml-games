#include <gtest/gtest.h>
#include <utils/Config.h>

struct Address
{
    std::string street;
    int housenumber{};
    int postcode{};

    auto operator<=>( const Address& ) const = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( Address, street, housenumber, postcode )
};

TEST( UtilsConfigReadCustomStructs, ReadAdress )
{
    Config::getInstance( Config::Mode::ForceReload, R"( 
        { 
            "address": {
                "street": "Georgia",
                "housenumber": 123,
                "postcode": 456
            }
        }
        )" );

    Address expectedAddress{ "Georgia", 123, 456 };

    const auto& addressFromConfig = getConfig<Address, "address">();
    EXPECT_EQ( expectedAddress, addressFromConfig );
}