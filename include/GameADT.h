/**
 * \file GameADT.h
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides an ADT representing a model for the game of FreeCell
 *   including board state and its transitions.
 */
#ifndef GAME_ADT_H
#define GAME_ADT_H

#include <array>
#include <tuple>
#include <vector>

#include "CardADT.h"
#include "GameTypes.h"
#include "StackADT.h"


/**
 * \brief Represents the state of a FreeCell game.
 * \details The columns are represented as an array of 16 Stack instances with
 *   an enumeration from GameTypes and an integer to identify each stack with
 *   a placement on the board (e.g., (Cascade, 0) for the first cascade).
 */
class GameT {
    private:
        std::array<Stack<CardT>, 16> m_cols;

        /**
         * \brief Determines whether a given (PlacementT, unsigned int) pair is
         *   a valid position on the board.
         */
        bool isValidPlacement(PlacementT p, unsigned int i) const;

        /**
         * \brief Determines whether the given card can be placed on the
         *   `j`th foundation.
         */
        bool isValidBuild(CardT c, unsigned int j);

        /**
         * \brief Determines whether the given card can be stacked on the
         *   `j`th cascade.
         */
        bool isValidStack(CardT c, unsigned int j);

        /**
         * \brief Implementation-specific function for getting a vector of all
         *   possible board positions.
         */
        std::vector<std::tuple<PlacementT, unsigned int>> getAllPositions() const;

    public:
        /**
         * \brief Constructs a new GameT instance with a randomly shuffled
         *   playing field.
         */
        GameT();

        /**
         * \brief Constructs a new GameT instance with a given board state.
         * \param cols All columns on the board.
         *   Columns [0,7] are the cascades.
         *   Columns [8,11] are the free cells.
         *   Columns [12,15] are the foundations.
         * \throws invalid_board if the board does not contain all 52 distinct
         *   playing cards in valid stacks.
         */
        GameT(std::array<Stack<CardT>, 16> cols);

        /**
         * \brief Determines whether the game has concluded with a victory.
         * \return True if the state is won.
         */
        bool hasWon() const;

        /**
         * \brief Determine whether the given move is a valid move in the
         *   current playing state.
         * \details Example: Checking whether we can move the card in the
         *   2nd cascade to the 1st open cell.
         *   \code{.cpp}
         *   isValidMove(Cascade, 1, Cell, 0)
         *   \endcode
         * \param p Source placement.
         * \param i Source column index. 0-indexed.
         * \param q Destination placement.
         * \param j Destination column index. 0-indexed.
         * \throws invalid_placement if either the source or destination
         *   placement are not valid playing positions. Cell indices must be
         *   in [0,3]. Foundation indices must be in [0,3]. Cascade indices
         *   must be in [0,7].
         * \throws empty_source if the source position has no card to move.
         * \return True if this move can be made.
         */
        bool isValidMove(PlacementT p, unsigned int i, PlacementT q, unsigned int j);

        /**
         * \brief Determine whether there are any remaining valid moves which
         *   could be played in the current state.
         * \return True if there are no valid moves.
         */
        bool noValidMoves();

        /**
         * \brief Updates the playing state given a valid source position and
         *   destination position representing a move.
         * \param p Source placement.
         * \param i Source column index. 0-indexed.
         * \param q Destination placement.
         * \param j Destination column index. 0-indexed.
         * \throws invalid_placement if either the source or destination
         *   placement are not valid playing positions. Cell indices must be
         *   in [0,3]. Foundation indices must be in [0,3]. Cascade indices
         *   must be in [0,7].
         * \throws empty_source if the source position has no card to move.
         */
        void performMove(PlacementT p, unsigned int i, PlacementT q, unsigned int j);

        /**
         * \brief Retrieves the Stack instance given an associated board
         *   column. Required for the View to render game state.
         * \throws invalid_placement if the given placement is not a valid
         *   column.
         * \return Stack instance at given column.
         */
        Stack<CardT> & getCol(PlacementT p, unsigned int i);
};

#endif
