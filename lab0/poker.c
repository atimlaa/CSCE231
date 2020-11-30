/* HOMEWORK 0
 * STUDENT: <<Aryan Timla>>
*/

/* This simple program should populate a standard 52-card deck and then
 * randomly select five cards from the deck.  It will then print the
 * poker hand and report the best way it can be characterized (flush, full
 * house, one pair, high card, etc.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"


card deck[52];          // a "deck" of 52 cards


void populateDeck()
{
        /* ADD CODE HERE TO PLACE THE 52 STANDARD CARDS IN DECK[] */
        card* blankCard = (card*)malloc(sizeof(card));

        for (int i = 1; i < 52; i++) {
          blankCard = createCard(i%13, i%4, blankCard);
          deck[i] = *blankCard;
        }
}


card* sort(card* subdeck, int size)
{
    card temp;
    for (int i = 0; i < size-1; i++)
        for (int j = i+1; j < size; j++)
            if (subdeck[i].value > subdeck[j].value)
            {
                temp = subdeck[i];
                subdeck[i] = subdeck[j];
                subdeck[j] = temp;
            }
    return subdeck;
}


card* getHand(card* emptyHand, int sizeOfHand)
/* Randomly selects "sizeOfHand" cards and returns them.  The emptyHand argument must
 * have space for at least "sizeOfHand" cards.
 */{
    int selection;
    for (int i = 0; i < sizeOfHand; i++)
    {
        selection = rand() % 52;
        emptyHand[i] = deck[selection];     // if this were more robust, we'd check for duplicates
    }
    return sort(emptyHand,sizeOfHand);
}


int isPair(card* hand, int sizeOfHand)
/* Returns 1 if two of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
        /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int pair = 0;
    for (int i = 0; i < sizeOfHand-1; i++)
        pair = pair || (hand[i].value == hand[i+1].value);   // because hand is sorted, a pair must be two adjacent cards
    return pair;
}


int isTwoPair(card* hand, int sizeOfHand)
/* Returns 1 if two of the cards in "hand" are a pair and two other are also a pair; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
    int numberOfPairs = 0;
    card* partialHand;
    int i=0;
    while (i < sizeOfHand)
    {                               /* RECALL THAT ARRAYS ARE POINTERS */
        partialHand = hand + i;     /* THIS IS CHANGING THE ADDRESS IN THE "PARTIALHAND" POINTER TO A DIFFERENT PART OF THE ARRAY */
        if (isPair(partialHand,2))
        {
            numberOfPairs++;
            i += 2;
        }
        else
        {
            i++;
        }
    }
    return (numberOfPairs == 2);
}


int isThreeOfKind(card* hand, int sizeOfHand)
/* Returns 1 if three of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
        /* WRITE THIS FUNCTION */
        int ThreeOfKind = 0;
        for (int i = 0; i < sizeOfHand-1; i++)
            ThreeOfKind = (hand[i].value == hand[i+1].value == hand[i+2].value);
        return ThreeOfKind;
}


int isStraight(card* hand, int sizeOfHand)
/* Returns 1 if the cards have contiguous values; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
        /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int notStraight = 0;
    for (int i = 0; i < sizeOfHand-1; i++)
        notStraight = notStraight + (hand[i+1].value - hand[i].value - 1);
    return !notStraight;
}


int isFlush(card* hand, int sizeOfHand)
/* Returns 1 if the cards all have the same suit; returns 0 otherwise.
 */{
        /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int flush = 1;
    int suit = hand[0].suit;
    for (int i = 1; i < sizeOfHand; i++)
        flush = flush && (hand[i].suit == suit);
    return flush;
}


int isFullHouse(card* hand, int sizeOfHand)
/* Returns 1 if three of the  cards in "hand" are three of a kind and another two are a pair; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
        /* WRITE THIS FUNCTION */
        return isThreeOfKind(hand,sizeOfHand) && isPair(hand,sizeOfHand);

}


int isFourOfKind(card* hand, int sizeOfHand)
/* Returns 1 if four of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
        /* WRITE THIS FUNCTION */
        int FourOfKind = 0;
        for (int i = 0; i < sizeOfHand-1; i++)
            FourOfKind = (hand[i].value == hand[i+1].value == hand[i+2].value == hand[i+3].value);
        return FourOfKind;
}


int isStraightFlush(card* hand, int sizeOfHand)
/* Returns 1 if the cards in "hand" are both a straight and a flush; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value.
 */{
    return isStraight(hand,sizeOfHand) && isFlush(hand,sizeOfHand);
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    populateDeck();
    int sizeOfHand = 5;
    card* emptyHand = (card*)malloc(sizeOfHand*sizeof(card));
        /* ADD WHATEVER CODE HERE YOU NEED */
        card* hand = getHand(emptyHand,5);

        char* emptyString = malloc(20);

        for (int i = 0; i < sizeOfHand; i++) {
          printf("%s\n", displayCard(&hand[i],emptyString) );
          // printf("%d of %u\n", hand[i].value, hand[i].suit);
        }
        if (isPair(hand, sizeOfHand)) {
          printf("This hand is a pair\n");
        }
        else if (isThreeOfKind(hand, sizeOfHand)) {
          printf("This hand is a ThreeOfKind\n");
        }
        else if (isTwoPair(hand, sizeOfHand)) {
          printf("This hand is a two pair\n");
        }
        else if (isFourOfKind(hand, sizeOfHand)) {
          printf("This hand is a FourOfKind\n");
        }
        else if (isStraight(hand, sizeOfHand)) {
          printf("This hand is a straight\n");
        }
        else if (isFlush(hand, sizeOfHand)) {
          printf("This hand is a flush\n");
        }
        else if (isFullHouse(hand, sizeOfHand)) {
          printf("This hand is a full house YAY!!\n");
        }
        else if (isStraightFlush(hand, sizeOfHand)) {
          printf("This hand is a StraightFlush DAMN!!\n");
        }
        // else{
        //   printf("This hand is a %s of %s high\n", hand[4].value, hand[4].suit);
        // }

    return 0;
}
