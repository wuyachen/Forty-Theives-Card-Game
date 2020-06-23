#include "catch.h"

#include "CardADT.h"
#include "Exceptions.h"
#include "GameADT.h"
#include "GameTypes.h"
#include "StackADT.h"
#include <iostream>


Stack<CardT> makeColumn(unsigned int capacity, int n, SuitT suits[], RankT ranks[]);
std::array<Stack<CardT>, 16> makeGame();
std::array<Stack<CardT>, 16> makeGameNoMoves();
std::array<Stack<CardT>, 16> makeGameEmptyCascade();
std::array<Stack<CardT>, 16> makeGameWon();


TEST_CASE("tests for GameT", "[GameT]") {

    SECTION("shuffled constructor") {
        GameT g;
        for (PlacementT p : { Cell, Foundation }) {
            for (int i = 0; i < 4; i++) {
                REQUIRE(g.getCol(p, i).isEmpty());
                REQUIRE(g.getCol(p, i).capacity() == (p == Cell ? 1 : 13));
            }
        }

        for (int i = 0; i < 8; i++) {
            REQUIRE(!g.getCol(Cascade, i).isEmpty());
            REQUIRE(g.getCol(Cascade, i).capacity() == 19);
            REQUIRE(g.getCol(Cascade, i).seq().size() == (i < 4 ? 7 : 6));
        }
    }


    SECTION("unary constructor") {
        GameT g(makeGame());
        REQUIRE(true);
    }


    /**
     * "Test case fro detecting winning game board"
     */
    SECTION("has won returns true") {
        GameT g(makeGameWon());
        REQUIRE(g.hasWon());
    }


    SECTION("has won returns false") {
        GameT g(makeGame());
        REQUIRE(!g.hasWon());
    }


    SECTION("has won returns false on nearly won game") {
        GameT g(makeGameWon());
        g.performMove(Foundation, 0, Cell, 0);
        REQUIRE(!g.hasWon());
    }


    SECTION("is valid move throws exception for invalid placement") {
        GameT g(makeGame());
        REQUIRE_THROWS_AS(
            g.isValidMove(Cascade, 8, Cascade, 0),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.isValidMove(Cell, 4, Cascade, 0),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.isValidMove(Cascade, 0, Foundation, 4),
            invalid_placement
        );
    }


    SECTION("is valid move throws exception for empty source") {
        GameT g(makeGame());
        REQUIRE_THROWS_AS(
            g.isValidMove(Cell, 0, Foundation, 0),
            empty_source
        );
    }


    SECTION("is valid move returns true for valid build") {
        GameT g(makeGame());
        // Ace of Clubs to empty foundation
        REQUIRE(g.isValidMove(Cascade, 1, Foundation, 0));
    }


    SECTION("is valid move returns true for valid second build") {
        GameT g(makeGame());
        g.performMove(Cascade, 1, Foundation, 3);
        // 2 of Clubs to Ace of Clubs on foundation
        REQUIRE(g.isValidMove(Cascade, 3, Foundation, 3));
    }


    SECTION("is valid move returns true for valid stack") {
        GameT g(makeGame());
        // Queen of Hearts to King of Clubs
        REQUIRE(g.isValidMove(Cascade, 7, Cascade, 6));
    }


    SECTION("is valid move returns true for empty cell") {
        GameT g(makeGame());
        for (int i = 0; i < 8; i++) {
            REQUIRE(g.isValidMove(Cascade, i, Cell, 0));
        }
    }


    SECTION("is valid move returns true for empty cascade") {
        GameT g(makeGameEmptyCascade());
        REQUIRE(g.isValidMove(Cascade, 0, Cascade, 7));
    }


    /**
     * "Test case for moving to free cell, when no free cells available"
     */
    SECTION("is valid move returns false for full free cell") {
        GameT g(makeGame());
        g.performMove(Cascade, 0, Cell, 0);
        REQUIRE(!g.isValidMove(Cascade, 0, Cell, 0));
    }


    /**
     * "Test case for an invalid move between columns"
     */
    SECTION("is valid move returns false for invalid stack based on suit") {
        GameT g(makeGame());
        // Ace of Clubs to 2 of Clubs
        REQUIRE(!g.isValidMove(Cascade, 1, Cascade, 3));
    }


    SECTION("is valid move returns false for invalid stack based on rank") {
        GameT g(makeGame());
        // 5 of Diamonds to 9 of Spades
        REQUIRE(!g.isValidMove(Cascade, 2, Cascade, 0));
        REQUIRE(!g.isValidMove(Cascade, 0, Cascade, 2));
    }


    SECTION("is valid move returns false for invalid build based on suit") {
        GameT g(makeGame());
        g.performMove(Cascade, 1, Foundation, 3);
        // 2 of Spades on to Ace of Clubs
        REQUIRE(!g.isValidMove(Cascade, 0, Foundation, 3));
    }


    SECTION("is valid move returns false for invalid build based on rank") {
        GameT g(makeGame());
        g.performMove(Cascade, 1, Foundation, 3);
        // King of Clubs on to Ace of Clubs
        REQUIRE(!g.isValidMove(Cascade, 6, Foundation, 3));
    }


    SECTION("is valid move returns false between foundations") {
        GameT g(makeGame());
        g.performMove(Cascade, 1, Foundation, 0);
        REQUIRE(!g.isValidMove(Foundation, 0, Foundation, 1));
    }


    SECTION("no valid moves returns false when a move exists") {
        GameT g(makeGame());
        REQUIRE(!g.noValidMoves());
    }


    SECTION("no valid moves returns true when no move exists") {
        GameT g(makeGameNoMoves());
        REQUIRE(g.noValidMoves());
    }


    SECTION("perform move throws invalid placement") {
        GameT g(makeGame());
        REQUIRE_THROWS_AS(
            g.performMove(Cascade, 8, Cascade, 0),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.performMove(Cell, 4, Cascade, 0),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.performMove(Cascade, 0, Foundation, 4),
            invalid_placement
        );
    }


    SECTION("perform move throws invalid move") {
        GameT g(makeGame());
        REQUIRE_THROWS_AS(
            g.performMove(Cascade, 0, Cascade, 0),
            invalid_move
        );
    }


    SECTION("perform move changes state correctly, moving to free cell when one is available") {
        GameT g(makeGame());
        g.performMove(Cascade, 1, Foundation, 0);
        REQUIRE(g.getCol(Cascade, 1).seq().size() == 6);
        REQUIRE(g.getCol(Foundation, 0).seq().size() == 1);
        REQUIRE(g.getCol(Foundation, 0).peek().suit() == Clubs);
        REQUIRE(g.getCol(Foundation, 0).peek().rank() == Ace);
        REQUIRE(g.getCol(Cascade, 1).peek().suit() == Clubs);
        REQUIRE(g.getCol(Cascade, 1).peek().rank() == 10);
    }


    SECTION("get col returns correct column reference") {
        GameT g(makeGame());
        for (int i = 0; i < 8; i++) {
            REQUIRE(g.getCol(Cascade, i).capacity() == 19);
        }
        for (int i = 0; i < 4; i++) {
            REQUIRE(g.getCol(Cell, i).capacity() == 1);
        }
        for (int i = 0; i < 4; i++) {
            REQUIRE(g.getCol(Foundation, i).capacity() == 13);
        }
    }


    SECTION("get col throws invalid placement") {
        GameT g(makeGame());
        REQUIRE_THROWS_AS(
            g.getCol(Cascade, 8),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.getCol(Cell, 4),
            invalid_placement
        );
        REQUIRE_THROWS_AS(
            g.getCol(Foundation, 4),
            invalid_placement
        );

    }

}


Stack<CardT> makeColumn(unsigned int capacity, std::vector<SuitT> suits, std::vector<RankT> ranks) {
    Stack<CardT> s(capacity);
    for (unsigned int i = 0; i < suits.size(); i++) {
        s.push(CardT(suits[i], ranks[i]));
    }

    return s;
}


std::array<Stack<CardT>, 16> makeGame() {
    std::array<Stack<CardT>, 16> arr;
    std::vector<SuitT> suits[8] = {
        { Spades, Spades, Spades, Hearts, Clubs, Hearts, Spades },
        { Clubs, Clubs, Spades, Hearts, Diamonds, Clubs, Clubs },
        { Diamonds, Hearts, Clubs, Spades, Diamonds, Hearts, Diamonds },
        { Diamonds, Diamonds, Diamonds, Hearts, Diamonds, Spades, Clubs },
        { Diamonds, Spades, Diamonds, Diamonds, Hearts, Spades },
        { Hearts, Clubs, Spades, Hearts, Clubs, Spades },
        { Hearts, Diamonds, Clubs, Spades, Clubs, Clubs },
        { Diamonds, Hearts, Clubs, Spades, Hearts, Hearts }
    };
    std::vector<RankT> ranks[8] = {
        { Jack, 3, 6, 8, 5, 9, 2 },
        { Queen, 9, 9, Jack, 10, 10, Ace },
        { 8, 4, 6, Ace, 7, 2, 5 },
        { 2, King, Ace, Ace, Jack, 5, 2 },
        { 4, 7, 6, 3, 3, 10 },
        { 6, 8, 4, 5, Jack, Queen },
        { 7, Queen, 3, 8, 4, King },
        { 9, King, 7, King, 10, Queen }
    };
    for (int i = 0; i < 8; i++) {
        arr[i] = makeColumn(19, suits[i], ranks[i]);
    }
    for (int i = 8; i < 16; i++) {
        arr[i] = Stack<CardT>(i < 12 ? 1 : 13);
    }

    return arr;
}


std::array<Stack<CardT>, 16> makeGameNoMoves() {
    // No Ace on the top of each column.
    // All cells filled.
    // No moves available between cascades.

    std::array<Stack<CardT>, 16> arr;
    std::vector<SuitT> suits[8] = {
        { Spades, Spades, Spades, Hearts, Clubs },
        { Clubs, Clubs, Spades, Hearts, Diamonds, Clubs, Clubs },
        { Diamonds, Hearts, Clubs, Spades, Diamonds, Hearts, Diamonds },
        { Diamonds, Diamonds, Diamonds, Hearts, Diamonds, Spades, Clubs },
        { Diamonds, Spades, Diamonds, Diamonds, Hearts, Spades },
        { Hearts, Clubs, Spades, Hearts, Clubs, Spades },
        { Hearts, Diamonds, Clubs, Spades, Clubs, Clubs },
        { Diamonds, Hearts, Hearts, Spades }
    };
    std::vector<RankT> ranks[8] = {
        { Jack, 3, 6, 8, 5, 9 },
        { Queen, 10, 9, Jack, 10, Ace, 9 },
        { 8, 4, 6, Ace, 7, 2, 5 },
        { 2, King, Ace, Ace, Jack, 5, 2 },
        { 4, 10, 6, 3, 3, 7 },
        { 6, 8, 4, 5, Jack, Queen },
        { 7, Queen, 3, 8, 4, King },
        { 9, Queen, 10, King }
    };
    for (int i = 0; i < 8; i++) {
        arr[i] = makeColumn(19, suits[i], ranks[i]);
    }
    for (int i = 8; i < 16; i++) {
        arr[i] = Stack<CardT>(i < 12 ? 1 : 13);
    }

    arr[8] = Stack<CardT>(1);
    arr[8].push(CardT(Spades, 2));
    arr[9] = Stack<CardT>(1);
    arr[9].push(CardT(Hearts, 9));
    arr[10] = Stack<CardT>(1);
    arr[10].push(CardT(Clubs, 7));
    arr[11] = Stack<CardT>(1);
    arr[11].push(CardT(Hearts, King));

    return arr;
}


std::array<Stack<CardT>, 16> makeGameEmptyCascade() {
    std::array<Stack<CardT>, 16> arr;
    std::vector<SuitT> suits[8] = {
        { Spades, Spades, Spades, Hearts, Clubs, Hearts, Spades },
        { Clubs, Clubs, Spades, Hearts, Diamonds, Clubs, Diamonds },
        { Diamonds, Hearts, Clubs, Spades, Diamonds, Hearts, Diamonds },
        { Diamonds, Diamonds, Diamonds, Hearts, Diamonds, Spades, Clubs },
        { Diamonds, Spades, Diamonds, Diamonds, Hearts, Spades },
        { Hearts, Clubs, Spades, Hearts, Clubs, Spades },
        { Hearts, Diamonds, Clubs, Spades, Clubs, Clubs, Hearts }
    };
    std::vector<RankT> ranks[8] = {
        { Jack, 3, 6, 8, 5, 9, 9 },
        { Queen, 9, 2, Jack, 10, 10, 9 },
        { 8, 4, 6, Ace, 7, 2, 5 },
        { 2, King, Ace, Ace, Jack, 5, 2 },
        { 4, 7, 6, 3, 3, 10 },
        { 6, 8, 4, 5, Jack, Queen },
        { 7, Queen, 3, 8, 4, King, Queen }
    };
    for (int i = 0; i < 8; i++) {
        arr[i] = makeColumn(19, suits[i], ranks[i]);
    }
    arr[7] = Stack<CardT>(19);

    arr[8] = Stack<CardT>(1);
    arr[8].push(CardT(Hearts, 10));
    arr[9] = Stack<CardT>(1);
    arr[9].push(CardT(Spades, King));
    arr[10] = Stack<CardT>(1);
    arr[10].push(CardT(Clubs, 7));
    arr[11] = Stack<CardT>(1);
    arr[11].push(CardT(Hearts, King));

    arr[12] = Stack<CardT>(13);
    arr[12].push(CardT(Clubs, Ace));

    for (int i = 13; i < 16; i++) {
        arr[i] = Stack<CardT>(13);
    }

    return arr;
}


std::array<Stack<CardT>, 16> makeGameWon() {
    std::array<Stack<CardT>, 16> arr;
    for (int i = 0; i < 8; i++) {
        arr[i] = Stack<CardT>(19);
    }
    for (int i = 8; i < 12; i++) {
        arr[i] = Stack<CardT>(1);
    }
    for (int i = 0; i < 4; i++) {
        arr[i + 12] = Stack<CardT>(13);
        for (int j = Ace; j <= King; j++) {
            arr[i + 12].push(CardT(static_cast<SuitT>(i), j));
        }
    }

    return arr;
}
