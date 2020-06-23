/**
 * \file GameTypes.h
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides type definitions and enumerations for a game of FreeCell.
 */
#ifndef GAME_TYPES_H
#define GAME_TYPES_H


/**
 * \brief Describes the valid types of columns of cards on the board.
 */
enum PlacementT {
    Cell,        ///< The open cell positions.
    Foundation,  ///< The foundations where winning columns are placed.
    Cascade      ///< The playing stacks.
};


/**
 * \brief Describes the possible card suits.
 */
enum SuitT {
    Spades,
    Clubs,
    Hearts,
    Diamonds
};


/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;


/**
 * \brief RankT for an Ace.
 */
#define Ace    1

/**
 * \brief RankT for an Jack.
 */
#define Jack   11

/**
 * \brief RankT for a Queen.
 */
#define Queen  12

/**
 * \brief RankT for a King.
 */
#define King   13

#endif
