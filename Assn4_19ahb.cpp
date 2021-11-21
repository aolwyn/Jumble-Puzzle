#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "sstream"
#include <stdlib.h>
#include "Assn4_19ahb.h"
//include headers

using namespace std;//use the namespace

JumblePuzzle::JumblePuzzle(const string& wordToFind, const string& difficulty) {
    //makes sure it takes the correct value by explicitly stating
    this->wordToFind = wordToFind;
    length = wordToFind.length();
    if (length < 3 || length > 10) {
        throw BadJumbleException("Invalid length. Length of word must be between 3 and 10 characters long.");
    }//close if

    if(difficulty == "easy")
    {
        length= length*2;
    }//close if easy
    else if(difficulty == "medium")
    {
      length = length*3;
    }//close if medium

    else if(difficulty == "hard")
    {
        length = length * 4;
    }//close if hard
    else{
        throw BadJumbleException("Invalid difficulty. Difficulty must be: easy, medium, or hard.");
    }//close invalid entry

    //create array
    matrix = new char*[length];
    for (int i = 0; i < length; ++i) {
        matrix[i] = new char[length];
    }

    srand(time(NULL)); //need this to get rand() stuff

const char* availableRandomLetters = "abcdefghijklmonpqrstuvwxyz"; //char[] of available letters of the alphabet
const char* availableDirections = "nesw"; //char[] of directions

//flag for proper placement
bool successfulPlacement = false;

//put random letters in array
for(int i = 0; i < length; ++i) {
    for(int j = 0; j < length; ++j)
    {
        matrix[i][j] = (char) availableRandomLetters[rand() % 25]; //take a random letter from the char array and places it in matrix
    }//close for int j

} //close for int i

//place word into array using random starting row and column and random direction
        //while the word hasn't been successfully placed, loop through the direction and random placements.
        //keep trying until you get it
        while(!successfulPlacement)
        {
            column = rand() % length; //get random column start
            row = rand() % length;    //get random row start
            direction = availableDirections[rand()%4]; //choose a random direction to go in

            if(direction == 'n'){ //if the direction is north
                for (int i = 0; i < wordToFind.length(); ++i) {
                    if((row-i)<0){//out of bounds check
                        break;
                    }else if(i==(wordToFind.length() -1)){//last letter going north
                        matrix[row - i][column] = wordToFind.at(i);
                        successfulPlacement = true;
                    }else{
                        matrix[row - i][column] = wordToFind.at(i); //place as normal
                    }//end else
                }//end for
            }//end direction 'n'
            else if(direction == 'w'){
                for (int i = 0; i < wordToFind.length(); ++i) {
                    if((column-i) < 0){ //out of bounds check
                        break;
                    }else if( i==(wordToFind.length() -1)){ //last letter going west
                        matrix[row][column - i] = wordToFind.at(i);
                        successfulPlacement = true;
                    }else{
                        matrix[row][column - i] = wordToFind.at(i); //place as normal
                    }//close else
                }//close for
            }//close direction 'e'
            else if(direction == 'e'){
                for (int i = 0; i < wordToFind.length(); ++i) {
                    if((column+i) > length - 1 ){ //out of bounds check
                        break;
                    }else if( i==(wordToFind.length() -1)){
                        matrix[row][column + i] = wordToFind.at(i); //last letter going east
                        successfulPlacement = true;
                    }else{
                        matrix[row][column + i] = wordToFind.at(i); //place letters normally
                    }//close else
                }//close for
            }//close direction 'e'
            else{
                for (int i = 0; i < wordToFind.length(); ++i) {
                    if((row+i) > length - 1){//out of bounds check
                        break;
                    }else if(i==(wordToFind.length() -1)){//last letter going south
                        matrix[row + i][column] = wordToFind.at(i);
                        successfulPlacement = true;
                    }else{
                        matrix[row + i][column] = wordToFind.at(i); //place letters normally
                    }//end else
                }//end for
            }//end direction 's'
        }//close while not successful word placement in array

}//close JumblePuzzle

//copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle &correct){
    row = correct.row;
    length = correct.length;
    column = correct.column;
    direction = correct.direction;
    wordToFind = correct.wordToFind;
    matrix = correct.getJumble();

}//close copy constructor

//accessor methods for getting the row, the column, the size of the matrix, and the direction of the word
int JumblePuzzle::getRowPos() const { return row; }
int JumblePuzzle::getColPos() const { return column; }
int JumblePuzzle::getSize() const { return length; }
char JumblePuzzle::getDirection() const { return direction; }

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& correct){  //overloads the operator
    //delete because instructions told me to
    if (this != &correct){
        for (int i = 0; i < length; ++i) {
            delete [] matrix[i];
            matrix[i] = nullptr;
        }//close for loop
        delete [] matrix;
        matrix = nullptr;

        //copy over all the variables
        row = correct.row;
        length = correct.length;
        column = correct.column;
        direction = correct.direction;
        wordToFind = correct.wordToFind;
        matrix = correct.getJumble();
    }//close if
    return *this;

}//close operator= overload

//destructor for JumblePuzzle.
JumblePuzzle::~JumblePuzzle(){
//delete the array of pointers and then set them to NULL
    for (int i = 0; i < length; ++i) {
        delete [] matrix[i];
        matrix[i] = nullptr;
    }//close for loop
    delete [] matrix;
    matrix = nullptr;
}//close JumblePuzzle destructor

charArrayPtr *JumblePuzzle::getJumble() const {
    charArrayPtr* copiedJumble = new char*[length]; //create a new matrix that will be used to hold same data
                                                    //as the other matrix but will prevent mem. leaks
    //initialize it the same way as we initialized the other one
    for (int i = 0; i < length; ++i) {
        copiedJumble[i] = new char[length]; //create the rows + columns
    }//close for i

    //nested for loop to transfer the values from the matrix into the copy
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            copiedJumble[i][j] = matrix[i][j];
        }//close for j
    }//close for i

    return copiedJumble;  //after the copy has been successfully filled, return the copy.
}//close getJumble()

BadJumbleException::BadJumbleException(const string& m) : message(m) {}//exception handling

string& BadJumbleException::what()  {
    return message;
}


