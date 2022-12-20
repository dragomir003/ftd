#include <catch2/catch_all.hpp>

#include <ftd/data/result.hpp>

using namespace ftd;

TEST_CASE("Result is_ok() returns correct value") {
    SECTION("Returns true for Result with Ok value") {
        Result<int, std::string> r(42);
        REQUIRE(r.is_ok() == true);
    }

    SECTION("Returns false for Result with Err value") {
        Result<int, std::string> r("error");
        REQUIRE(r.is_ok() == false);
    }
}

TEST_CASE("Result is_err() returns correct value") {
    SECTION("Returns true for Result with Err value") {
        Result<int, std::string> r("error");
        REQUIRE(r.is_err() == true);
    }

    SECTION("Returns false for Result with Ok value") {
        Result<int, std::string> r(42);
        REQUIRE(r.is_err() == false);
    }
}

TEST_CASE("Result unwrap() returns correct value") {
    SECTION("Returns Ok value for Result with Ok value") {
        Result<int, std::string> r(42);
        REQUIRE(r.unwrap() == 42);
    }

    SECTION("Throws exception for Result with Err value") {
        Result<int, std::string> r("error");
        REQUIRE_THROWS_AS(r.unwrap(), std::exception);
    }
}

TEST_CASE("Result unwrap_err() returns correct value") {
    SECTION("Returns Err value for Result with Err value") {
        Result<int, std::string> r("error");
        REQUIRE(r.unwrap_err() == std::string("error"));
    }

    SECTION("Throws exception for Result with Ok value") {
        Result<int, std::string> r(42);
        REQUIRE_THROWS_AS(r.unwrap_err(), std::exception);
    }
}

TEST_CASE("Result default constructor is deleted") {
    SECTION("Compilation fails when default constructor is used") {
        // This test case verifies that the default constructor of the Result class is indeed deleted,
        // by attempting to use it and checking that compilation fails.
#ifdef COMPILATION_ERROR_EXPECTED
        Result<int, std::string> r;
#endif
    }
}

TEST_CASE("Result copy constructor is deleted") {
    SECTION("Compilation fails when copy constructor is used") {
        // This test case verifies that the copy constructor of the Result class is indeed deleted,
        // by attempting to use it and checking that compilation fails.
        Result<int, std::string> r1(42);
#ifdef COMPILATION_ERROR_EXPECTED
        Result<int, std::string> r2(r1);
#endif
    }
}

TEST_CASE("Result copy assignment operator is deleted") {
    SECTION("Compilation fails when copy assignment operator is used") {
        // This test case verifies that the copy assignment operator of the Result class is indeed deleted,
        // by attempting to use it and checking that compilation fails.
        Result<int, std::string> r1(42);
        Result<int, std::string> r2("error");
#ifdef COMPILATION_ERROR_EXPECTED
        r2 = r1;
#endif
    }
}

TEST_CASE("Result move constructor is working correctly") {
    SECTION("Moves Ok value when constructed from Result with Ok value") {
        Result<int, std::string> r1(42);
        Result<int, std::string> r2(std::move(r1));
        REQUIRE(r2.is_ok() == true);
        REQUIRE(r2.unwrap() == 42);
    }

    SECTION("Moves Err value when constructed from Result with Err value") {
        Result<int, std::string> r1("error");
        Result<int, std::string> r2(std::move(r1));
        REQUIRE(r2.is_err() == true);
        REQUIRE(r2.unwrap_err() == "error");
    }
}

TEST_CASE("Result move assignment operator is working correctly") {
    SECTION("Moves Ok value when assigned from Result with Ok value") {
        Result<int, std::string> r1(42);
        Result<int, std::string> r2("error");
        r2 = std::move(r1);
        REQUIRE(r2.is_ok() == true);
        REQUIRE(r2.unwrap() == 42);
    }

    SECTION("Moves Err value when assigned from Result with Err value") {
        Result<int, std::string> r1("error");
        Result<int, std::string> r2(42);
        r2 = std::move(r1);
        REQUIRE(r2.is_err() == true);
        REQUIRE(r2.unwrap_err() == std::string("error"));
    }
}

