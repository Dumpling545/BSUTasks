#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "practice9.h"

TEST_CASE( "Positive" ) {
    SECTION( "two edges equal test" ) {
        REQUIRE(triangleType(3, 3, 5) == 1);
        REQUIRE(triangleType(3, 5, 3) == 1);
        REQUIRE(triangleType(5, 3, 3) == 1);
    }
    SECTION( "three edges equal test" ) {
        REQUIRE(triangleType(3, 3, 3) == 2);
    }
    SECTION( "int overflow test" ) {
        REQUIRE(triangleType(2147483647, 2147483647, 1) == 1);
        REQUIRE(triangleType(2147483647, 1, 2147483647) == 1);
        REQUIRE(triangleType(1, 2147483647, 2147483647) == 1);
    }
    /*SECTION( "unsigned int overflow test" ) {
        REQUIRE(triangleType(4294967295, 4294967295, 1) == 1);
        REQUIRE(triangleType(4294967295, 1, 4294967295) == 1);
        REQUIRE(triangleType(1, 4294967295, 4294967295) == 1);
    }*/
}
TEST_CASE( "Negative" ) {
    SECTION( "all edges are different" ) {
        REQUIRE(triangleType(3, 4, 5) == 0);
    }
    SECTION( "two edges are too short" ) {
        REQUIRE(triangleType(5, 2, 1) == -1);
        REQUIRE(triangleType(2, 1, 5) == -1);
        REQUIRE(triangleType(1, 2, 5) == -1);
    }
    SECTION( "two edges are too short - strict inequalities test" ) {
        REQUIRE(triangleType(2, 2, 4) == -1);
        REQUIRE(triangleType(2, 4, 2) == -1);
        REQUIRE(triangleType(4, 2, 2) == -1);
    }
    SECTION( "negative length of edges" ) {
        REQUIRE(triangleType(-1, -1, 3) == -1);
        REQUIRE(triangleType(-1, 3, -1) == -1);
    }
    SECTION( "zero length of edges" ) {
        REQUIRE(triangleType(0, 2, 2) == -1);
        REQUIRE(triangleType(2, 0, 2) == -1);
        REQUIRE(triangleType(2, 2, 0) == -1);
    }
    SECTION( "not enough data test" ) {
        REQUIRE(triangleType(1, 2) == -1);
        REQUIRE(triangleType(1) == -1);
        REQUIRE(triangleType() == -1);
    }
}
