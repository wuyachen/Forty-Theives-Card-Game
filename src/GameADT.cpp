/**
 * \file GameADT.cpp
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides an ADT representing a model for the game of FreeCell
 *   including board state and its transitions.
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <vector>

#include "Exceptions.h"
#include "GameADT.h"
#include "GameTypes.h"


GameT::GameT() {
    for (int i = 0; i < 8; i++) {
        // Cascades only require a capacity of 19, because they be dealt with
        // up to 7 cards on them, and if the last card is a King then 12 more
        // cards could be stacked on top.
        m_cols[i] = Stack<CardT>(19);
    }
    for (int i = 8; i < 12; i++) {
        // Instead of handling cells particularly, just make them bounded
        // stacks of capacity 1.
        m_cols[i] = Stack<CardT>(1);
    }
    for (int i = 12; i < 16; i++) {
        m_cols[i] = Stack<CardT>(13);
    }

    std::vector<CardT> deck;
    for (int i = 0; i < 52; i++) {
        deck.push_back(CardT(static_cast<SuitT>(i / 13), i % 13));
    }
    std::random_shuffle(deck.begin(), deck.end());
    for (int i = 0; i < 52; i++) {
        m_cols[i % 8].push(deck[i]);
    }
}


GameT::GameT(std::array<Stack<CardT>, 16> cols)
    : m_cols(cols)
{}


bool GameT::isValidPlacement(PlacementT p, unsigned int i) const {
    if (p == Cascade) {
        return i <= 7;
    }
    return i <= 3;
}


bool GameT::isValidBuild(CardT c, unsigned int j) {
    auto s = getCol(Foundation, j);
    if (s.isEmpty()) {
        return c.rank() == 1;
    }

    return (
        s.peek().suit() == c.suit() &&
        s.peek().rank() == c.rank() - 1
    );
}


bool GameT::isValidStack(CardT c, unsigned int j) {
    auto s = getCol(Cascade, j);
    if (s.isEmpty()) {
        return true;
    }

    return (
        s.peek().isRed() != c.isRed() &&
        s.peek().rank() - 1 == c.rank()
    );
}


bool GameT::hasWon() const {
    for (int i = 12; i <= 15; i++) {
        if (m_cols[i].isEmpty()) {
            return false;
        }

        if (m_cols[i].peek().rank() != King) {
            return false;
        }
    }

    return true;
}


bool GameT::isValidMove(PlacementT p, unsigned int i, PlacementT q, unsigned int j) {
    bool isValid = isValidPlacement(p, i) && isValidPlacement(q, j);
    if (!isValid) {
        throw invalid_placement();
    }

    Stack<CardT> src = getCol(p, i);
    Stack<CardT> dst = getCol(q, j);
    if (src.isEmpty()) {
        throw empty_source();
    }

    switch (q) {
        case Cell:
            return dst.isEmpty();
        case Foundation:
            if (p == Foundation) {
                return false;
            }
            return isValidBuild(src.peek(), j);
        case Cascade:
            return isValidStack(src.peek(), j);
    }

    return true;
}


std::vector<std::tuple<PlacementT, unsigned int>> GameT::getAllPositions() const {
    std::vector<std::tuple<PlacementT, unsigned int>> moves;
    for (PlacementT p : { Cascade, Cell, Foundation }) {
        for (int j = p == Cascade ? 7 : 3; j >= 0; j--) {
            moves.push_back(std::make_tuple(p, j));
        }
    }

    return moves;
}


bool GameT::noValidMoves() {
    std::vector<std::tuple<PlacementT, unsigned int>> positions = getAllPositions();
    PlacementT p, q;
    unsigned int i, j;
    for (auto a : positions) {
        std::tie(p, i) = a;
        if (getCol(p, i).isEmpty()) {
            continue;
        }

        for (auto b : positions) {
            if (a == b) {
                continue;
            }

            std::tie(q, j) = b;
            if (isValidMove(p, i, q, j)) {
                return false;
            }
        }
    }

    return true;
}


void GameT::performMove(PlacementT p, unsigned int i, PlacementT q, unsigned int j) {
    bool isValid = isValidPlacement(p, i) && isValidPlacement(q, j);
    if (!isValid) {
        throw invalid_placement();
    }

    if (!isValidMove(p, i, q, j)) {
        throw invalid_move();
    }

    Stack<CardT> &src = getCol(p, i);
    Stack<CardT> &dst = getCol(q, j);
    dst.push(src.peek());
    src.pop();
}


Stack<CardT> & GameT::getCol(PlacementT p, unsigned int i) {
    if (!isValidPlacement(p, i)) {
        throw invalid_placement();
    }

    switch (p) {
        case Cascade:
            return m_cols[i];
        case Cell:
            return m_cols[i + 8];
        case Foundation:
            return m_cols[i + 12];
    }

    return m_cols[0];  // This cannot happen, the switch;case is complete.
}
