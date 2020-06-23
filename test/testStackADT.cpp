#include "catch.h"

#include "Exceptions.h"
#include "StackADT.h"


TEST_CASE("tests for Stack", "[Stack]") {

    SECTION("bounded constructor") {
        Stack<int> s(1);
        s.push(1);
        REQUIRE(s.peek() == 1);
        REQUIRE(s.capacity() == 1);
    }


    SECTION("invalid capacity for bounded constructor") {
        REQUIRE_THROWS_AS(
            Stack<int>(0),
            invalid_capacity
        );
        REQUIRE_THROWS_AS(
            Stack<int>(-1),
            invalid_capacity
        );
    }


    SECTION("capacity getter") {
        Stack<int> s(10);
        REQUIRE(s.capacity() == 10);
    }


    SECTION("is empty returns true") {
        Stack<int> s(1);
        REQUIRE(s.isEmpty());
    }


    SECTION("is empty returns false") {
        Stack<int> s(1);
        s.push(1);
        REQUIRE(!s.isEmpty());
    }


    SECTION("is full returns false") {
        Stack<int> s(1);
        REQUIRE(!s.isFull());
        s.push(1);
        REQUIRE(s.isFull());
    }


    SECTION("push, peek, and pop maintain FILO ordering") {
        const int lo = 1;
        const int hi = 3;
        Stack<int> s(3);
        for (int i = hi; i >= lo; i--) {
            s.push(i);
        }

        for (int i = lo; i <= hi; i++) {
            REQUIRE(s.peek() == i);
            s.pop();
        }
        REQUIRE(s.isEmpty());
    }


    SECTION("push throws full") {
        Stack<int> s(1);
        s.push(1);
        REQUIRE_THROWS_AS(s.push(2), full);
    }


    SECTION("peek throws empty") {
        Stack<int> s(1);
        REQUIRE_THROWS_AS(s.peek(), empty);
    }


    SECTION("pop throws empty") {
        Stack<int> s(1);
        REQUIRE_THROWS_AS(s.pop(), empty);
    }


    SECTION("seq returns new sequence") {
        Stack<int> s(2);
        s.push(1);
        s.push(2);
        std::vector<int> seq = s.seq();
        REQUIRE(seq.size() == 2);
        REQUIRE(seq[0] == 1);
        REQUIRE(seq[1] == 2);
    }

}
