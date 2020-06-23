#include "catch.h"

#include "CardADT.h"
#include "GameTypes.h"


TEST_CASE("tests for CardT", "[CardT]") {

    SECTION("constructor and getters") {
        CardT c(Hearts, Ace);
        REQUIRE(c.suit() == Hearts);
        REQUIRE(c.rank() == Ace);
    }


    SECTION("is red returns true") {
        CardT c(Hearts, Ace);
        REQUIRE(c.isRed());
        CardT d(Diamonds, 4);
        REQUIRE(d.isRed());
    }


    SECTION("is red returns false") {
        CardT c(Spades, Ace);
        REQUIRE(!c.isRed());
        CardT d(Clubs, 4);
        REQUIRE(!d.isRed());
    }

}
