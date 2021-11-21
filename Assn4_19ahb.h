
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "sstream"
#include <stdlib.h>

typedef char* charArrayPtr;

using namespace std;

class JumblePuzzle{
public:
//accessor methods.
//getSize returns the size of the matrix.
//getRowPos returns the row position. Is used in checking if the guess-location of the word is correct.
//getColPos similarly returns the column position. Is used in checking if the guess-location of the word is correct.
//getDirection is used with a direction (n,e,s,w) and returns the direction of the word based on the row/col answer.
    int getRowPos() const;
    int getColPos() const;
    int getSize() const;
    char getDirection() const;

    //gets the matrix. returns a copy of the original to prevent memory leaks.
    charArrayPtr* getJumble() const;

JumblePuzzle(const string& wordToFind, const string& difficulty); //constructor. takes in the word to hide and the difficulty.
JumblePuzzle(const JumblePuzzle &correct); //copy constructor, used for returning a copy of the original matrix. prevents mem. leaks
~JumblePuzzle();  //destructor. gets rid of matrix from heap after termination or word's location has been correctly guessed

//assignment overloading operator.
JumblePuzzle& operator=(const JumblePuzzle& correct);

private:
//private declarations of the values-> don't want these values to be accessed / changed. leaving them public would
//cause leaks.
    int row;    //for the rows
    int column;    //for the columns
    int length; //for length of word
    char direction; //for direction of word
    charArrayPtr* matrix; //pretty sure this pointer should be private as well because it holds an address which you don't want leaked
    string wordToFind; //word to find
};

class BadJumbleException{ //class for throwing incorrect inputs.
public:
    BadJumbleException(const string&);
    string& what();

private:
    string message;

};

#ifndef INC_320ASSIGNMENT4_ASSN4_19AHB_H
#define INC_320ASSIGNMENT4_ASSN4_19AHB_H

#endif //INC_320ASSIGNMENT4_ASSN4_19AHB_H
