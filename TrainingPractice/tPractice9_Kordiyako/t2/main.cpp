using namespace std;
/**
    (4 балла) Пусть дана без ошибок формула, имеющая следующий синтаксис:
    <формула>::=<цифра> | max(<формула>, < формула >) | min (<формула>,< формула >)
    <цифра>::=0  1  2  3  4  5  6  7  8   9
    Например, 8 или max(4, min(3, 5)) или  min(min(3, 5), max(2, max(3, 4))).
*/
#define CATCH_CONFIG_MAIN
#include "practice9.h"
#include "catch.hpp"
//#include "practice9.h"

TEST_CASE( "Simple formula" ) {
    SECTION( "number" ) {
        REQUIRE(computeMinMaxString("0") == 0);
        REQUIRE(computeMinMaxString("5") == 5);
        REQUIRE(computeMinMaxString("9") == 9);
    }
    SECTION( "min" ) {
        REQUIRE(computeMinMaxString("min(1, 2)") == 1);
        REQUIRE(computeMinMaxString("min(3, 2)") == 2);
        REQUIRE(computeMinMaxString("min(4, 4)") == 4);
    }
    SECTION( "max" ) {
        REQUIRE(computeMinMaxString("max(1, 2)") == 2);
        REQUIRE(computeMinMaxString("max(3, 2)") == 3);
        REQUIRE(computeMinMaxString("max(4, 4)") == 4);
    }
}
TEST_CASE( "Complex formula" ) {
    SECTION( "two layers: min(min, number)/(number, min)" ) {
        REQUIRE(computeMinMaxString("min(min(1, 3), 2)") == 1);
        REQUIRE(computeMinMaxString("min(2, min(1, 3))") == 1);
        REQUIRE(computeMinMaxString("min(min(3, 5), 2)") == 2);
        REQUIRE(computeMinMaxString("min(2, min(3, 5))") == 2);
    }
    SECTION( "two layers: min(max, number)/(number, max)" ) {
        REQUIRE(computeMinMaxString("min(max(1, 3), 2)") == 2);
        REQUIRE(computeMinMaxString("min(2, max(1, 3))") == 2);
        REQUIRE(computeMinMaxString("min(max(1, 5), 6)") == 5);
        REQUIRE(computeMinMaxString("min(6, max(1, 5))") == 5);
    }
    SECTION( "two layers: min(min, min)" ) {
        REQUIRE(computeMinMaxString("min(min(1, 3), min(2, 8))") == 1);
        REQUIRE(computeMinMaxString("min(min(2, 8), min(1, 3))") == 1);
    }
    SECTION( "two layers: min(max, max)" ) {
        REQUIRE(computeMinMaxString("min(max(1, 3), max(2, 8))") == 3);
        REQUIRE(computeMinMaxString("min(max(2, 8), max(1, 3))") == 3);
    }
    SECTION( "two layers: min(max, min)/(min, max)" ) {
        REQUIRE(computeMinMaxString("min(max(1, 3), min(2, 7))") == 2);
        REQUIRE(computeMinMaxString("min(min(2, 7), max(1, 3))") == 2);
        REQUIRE(computeMinMaxString("min(max(1, 5), min(8, 6))") == 5);
        REQUIRE(computeMinMaxString("min(min(8, 6), max(1, 5))") == 5);
    }

    SECTION( "two layers: max(min, number)/(number, min)" ) {
        REQUIRE(computeMinMaxString("max(min(1, 3), 2)") == 2);
        REQUIRE(computeMinMaxString("max(2, min(1, 3))") == 2);
        REQUIRE(computeMinMaxString("max(min(3, 5), 2)") == 3);
        REQUIRE(computeMinMaxString("max(2, min(3, 5))") == 3);
    }
    SECTION( "two layers: max(max, number)/(number, max)" ) {
        REQUIRE(computeMinMaxString("max(max(1, 3), 2)") == 3);
        REQUIRE(computeMinMaxString("max(2, max(1, 3))") == 3);
        REQUIRE(computeMinMaxString("max(max(1, 5), 6)") == 6);
        REQUIRE(computeMinMaxString("max(6, max(1, 5))") == 6);
    }
    SECTION( "two layers: max(min, min)" ) {
        REQUIRE(computeMinMaxString("max(min(1, 3), min(2, 8))") == 2);
        REQUIRE(computeMinMaxString("max(min(2, 8), min(1, 3))") == 2);
    }
    SECTION( "two layers: max(max, max)" ) {
        REQUIRE(computeMinMaxString("max(max(1, 3), max(2, 8))") == 8);
        REQUIRE(computeMinMaxString("max(max(2, 8), max(1, 3))") == 8);
    }
    SECTION( "two layers: max(max, min)/(min, max)" ) {
        REQUIRE(computeMinMaxString("max(max(1, 3), min(2, 7))") == 3);
        REQUIRE(computeMinMaxString("max(min(2, 7), max(1, 3))") == 3);
        REQUIRE(computeMinMaxString("max(max(1, 5), min(8, 6))") == 6);
        REQUIRE(computeMinMaxString("max(min(8, 6), max(1, 5))") == 6);
    }
}

