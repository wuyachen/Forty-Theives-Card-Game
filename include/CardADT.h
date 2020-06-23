/**
 * \file CardADT.h
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides an ADT representing a standard playing card in the game of
 *   FreeCell.
 */
#ifndef CARD_ADT_H
#define CARD_ADT_H

#include "GameTypes.h"


/**
 * \brief ADT for a standard playing card.
 */
class CardT {
    private:
        SuitT m_s;
        RankT m_r;

    public:
        /**
         * \brief Constructs a new CardT instance.
         * \param S The suit of the card.
         * \param R The rank of the card.
         */
        CardT(SuitT S, RankT R);

        /**
         * \brief Gets the suit of the card.
         */
        SuitT suit() const;

        /**
         * \brief Gets the rank of the card.
         */
        RankT rank() const;

        /**
         * \brief Determine whether this card is red.
         * \return True if the card is a red suit.
         */
        bool isRed() const;
};

#endif
