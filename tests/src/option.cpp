#include <catch2/catch_test_macros.hpp>

#include <ftd/data/option.hpp>
#include <memory>
#include <string>

using ftd::Option;

TEST_CASE("Type assertions", "[option][type]") {
    Option<int> o1{2};
    Option<int> o2{};
    const auto o3 = ftd::make_option(4);
    Option<std::string> os{"hello"};

    REQUIRE(std::is_trivially_destructible_v<decltype(o1)>);
    REQUIRE(std::is_trivially_destructible_v<decltype(o2)>);
    REQUIRE(std::is_trivially_destructible_v<decltype(o3)>);
    REQUIRE_FALSE(std::is_trivially_destructible_v<decltype(os)>);
}

TEST_CASE("Option default constructor creates uninitialized object", "[option][default_constructor]") {
    Option<int> option;
    REQUIRE(!option.is_initialized());
    REQUIRE(!option);
}

TEST_CASE("Option copy constructor and copy assignment operator initialize object with copy of value", "[option][copy]") {
    int x = 5;
    Option<int> option1(x);
    REQUIRE(option1.is_initialized());
    REQUIRE(*option1 == x);

    Option<int> option2;
    option2 = option1;
    REQUIRE(option2.is_initialized());
    REQUIRE(*option2 == x);
}

TEST_CASE("Option move constructor and move assignment operator initialize object with moved value", "[option][move]") {
    int x = 5;
    Option<int> option1(std::move(x));
    REQUIRE(option1.is_initialized());
    REQUIRE(*option1 == 5);

    Option<int> option2;
    option2 = std::move(option1);
    REQUIRE(option2.is_initialized());
    REQUIRE(*option2 == 5);
}

TEST_CASE("Option is_initialized function returns correct value", "[option][is_initialized]") {
    Option<int> option1;
    REQUIRE(!option1.is_initialized());

    int x = 5;
    Option<int> option2(x);
    REQUIRE(option2.is_initialized());
}

TEST_CASE("Option value function and dereference operator return reference to contained value for initialized object and cause segfault for uninitialized object", "[option][value]") {
    int x = 5;
    Option<int> option1(x);
    REQUIRE(*option1 == x);

    // TODO: Add test for segfault
}

TEST_CASE("make_option creates initialized Option with contained value", "[option][make_option]") {
    int x = 5;
    Option<int> option = ftd::make_option(x);
    REQUIRE(option.is_initialized());
    REQUIRE(*option == x);
}

TEST_CASE("make_option with rvalue creates initialized Option with moved contained value", "[option][make_option][rvalue]") {
    Option<std::unique_ptr<int>> option = ftd::make_option(std::make_unique<int>(5));
    REQUIRE(option.is_initialized());
    REQUIRE(**option == 5);
}

TEST_CASE("make_option with nullptr creates uninitialized Option", "[option][make_option][nullptr]") {
    auto option = ftd::make_option<int*>(nullptr);
    REQUIRE(!option.is_initialized());
}
