#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include "wordSearch.h"

wordSearch::wordSearch(int _size) {
    size = _size;
    srand(time(0));
    fillRandom();
}
wordSearch::~wordSearch() {

}

bool wordSearch::addWord(string word) {
    if (word == "DONE") {
        return true;
    }

    for (int i = 0; i < word.length(); i++) {
        word.at(i) = tolower(word.at(i));
    }

    if (word.length() > size) {
        cout << "Sorry, that word is too big." << endl;
        return false;
    }

    for (int i = 0; i < addedWords.size(); i++) {
        if (word == addedWords.at(i)) {
            cout << "Sorry, that word is already in the wordsearch." << endl;
            return false;
        }
    }
 

    int randomStartRow;
    int randomStartCol;
    int insertType = rand () % 6;

    //INSERT HORIZONTAL
    if (insertType == 0) {
        randomStartRow = getStartingRow(word, 0, 0);
        randomStartCol = getStartingCol(word, 0);

        if (insertHoriz(randomStartRow, randomStartCol, word)) {
            cout << "Sorry, the wordsearch is getting full. Try a smaller word." << endl;
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);      //Update offLimits grid
            randomStartCol++;
        }
        cout << word << " ADDED" << endl;
    }
    //INSERT HORIZONTAL (backwards)
    if (insertType == 1) {
        randomStartRow = getStartingRow(word, 1, 0);
        randomStartCol = getStartingCol(word, 1);
        word = flipWord(word);

        if (insertHoriz(randomStartRow, randomStartCol, word)) {
            cout << "Sorry, the wordsearch is getting full. Try a smaller word." << endl;
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);        //Update offLimits grid
            randomStartCol++;
        }
        word = flipWord(word);
        cout << word << " ADDED" << endl;
    }
    //INSERT VERTICAL (bottom to top)
    if (insertType == 2) {
        randomStartRow = getStartingRow(word, 2, 0);
        randomStartCol = getStartingCol(word, 2);
        word = flipWord(word);
        if (insertVert(randomStartRow, randomStartCol, word)) {
            cout << "Sorry, the wordsearch is getting full. Try a smaller word." << endl;
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);      //Update offLimits grid
            randomStartRow++;
        }
        word = flipWord(word);
        cout << word << " ADDED" << endl;

    }
    
    //INSERT VERTICAL (top to bottom)
    if (insertType == 3) {
        randomStartRow = getStartingRow(word, 3, 0);
        randomStartCol = getStartingCol(word, 3);

        if (insertVert(randomStartRow, randomStartCol, word)) {
            cout << "Sorry, the wordsearch is getting full. Try a smaller word." << endl;
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);      //Update offLimits grid
            randomStartRow++;
        }
        cout << word << " ADDED" << endl;

    }
    //INSERT DIAG (forwards)
    if (insertType == 4) {
        int randDir = rand() % 2;
        randomStartRow = getStartingRow(word, 4, randDir);
        randomStartCol = getStartingCol(word, 4);

        if (insertDiag(randomStartRow, randomStartCol, word, randDir)) { 
            cout << "Sorry, the wordsearch is getting full. Try a smaller word." << endl;
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);//Update offLimits grid
            if (randDir == 0) {
                randomStartRow++;
            }
            else {
                randomStartRow--;
            }
            randomStartCol++;
        }
        cout << word << " ADDED" << endl;

    }
    if (insertType == 5) { // Diag Backwards
        int randDir = rand() % 2;
        randomStartRow = getStartingRow(word, 4, randDir);
        randomStartCol = getStartingCol(word, 4);
        word = flipWord(word);
        

        if (insertDiag(randomStartRow, randomStartCol, word, randDir)) { 
            cout << "Sorry, the wordsearch is getting full. Try a smaller word.";
            return false;
        }

        for (int i = 0; i < word.length(); i++) {                 //Make replacement
            theGrid[randomStartRow][randomStartCol] = word.at(i);
            offLimits[randomStartRow][randomStartCol] = word.at(i);      //Update offLimits grid
            if (randDir == 0) {
                randomStartRow++;
            }
            else {
                randomStartRow--;
            }
            randomStartCol++;
        }
        word = flipWord(word);
        cout << word << " ADDED" << endl;

    }
    addedWords.push_back(word); //add words to words vector
    return false;
}

void wordSearch::fillRandom() {
    for (int i = 0; i < size; i++) { //POPULATE GRID W/ RANDOM CHARACTERS a-z
        vector<char> currentRow;
        for (int j = 0; j < size; j++) {
            currentRow.push_back((rand() % 26) + 97);
        }
        theGrid.push_back(currentRow);
    }

    for (int i = 0; i < size; i++) { //POPULATE OFFLIMITS W/ 0's
        vector<char> currentRow;
        for (int j = 0; j < size; j++) {
            currentRow.push_back('-');
        }
        offLimits.push_back(currentRow);
    }


}

void wordSearch::printGrid() {
    ofstream toFile("wordSearch.txt");
    toFile << "Word Search\n" << "---------------------------------\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            toFile << theGrid[i][j] << " ";
        }
        toFile << endl;
    }
    toFile << endl;

    toFile << "Words to Find\n" << "---------------------------------\n";
    int wordsAdded = 0;
    for (int i = 0; i < addedWords.size(); i++) {
        toFile << addedWords.at(i) << "\t";
        if (addedWords.at(i).length() < 12) {
            toFile << "\t";
            if (addedWords.at(i).length() < 6) {
                toFile << "\t";
            }
        }
            wordsAdded++;
            if (wordsAdded % 3 == 0) {
                toFile << endl;
            }
    }

    toFile << "\n\nAnswer Key\n---------------------------------\n";
    for (int i = 0; i < size; i++) {        //print offlimits grid.
        for (int j = 0; j < size; j++) {
            toFile << offLimits[i][j] << " ";
        }
        toFile << endl;
    }
    toFile.close();
    cout << "Wordsearch generated. Good luck!" << endl;
}

bool wordSearch::isCollisionHorizontal(int row, int col, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (offLimits[row][col] != '-'&& offLimits[row][col] != word.at(i)){ 
            return true;
        }
        else {
            col++;
            
        }
    }
    return false;
}

bool wordSearch::isCollisionVertical(int row, int col, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (offLimits[row][col] != '-' && offLimits[row][col] != word.at(i)) {
            return true;
        }
        else {
            row++;

        }
    }
    return false;
}

bool wordSearch::isCollisionDiag(int row, int col, string word, int dir) {  
    for (int i = 0; i < word.length(); i++) {
        if (offLimits[row][col] != '-' && offLimits[row][col] != word.at(i)) {
            return true;
        }
        else {
            if (dir == 0) { //Top to Bottow, rows increase index
               row++;
            }
            else {
                row--;
            }
            col++;
        }
    }
    return false;
}


int wordSearch::getStartingRow(string word, int insertType, int dir) {
    int row;
    if (insertType == 0 || insertType == 1) { //insert Horizontal
        row = rand() % size;
    }
    else if(insertType == 2 || insertType == 3){ //insert Vertically 
        if (size == word.length()) {
            return 0;               //can only fit in the 0th row
        }
        else {
            row = rand() % ((size + 1) - word.length()); //only valid row
        }
    }
    else { // insert Diag
        if (size == word.length()){
            if (dir == 0) {
               return 0;
            }
            else {
                return 1;
            }
        }
        else {
            if(dir == 0) { // Top to Bottom (down)
                row = rand() % ((size + 1) - word.length()); //only valid rows
            }
            else {
                row = (rand() % ((size + 1) - word.length())) + (word.length() - 1);
            }
        }

    }
    return row;
}

int wordSearch::getStartingCol(string word, int insertType) {
    int col;
    if (insertType == 2 || insertType == 3) { //insert Vertical
        col = rand() % size;
    }
    else { //insert Horizontal or Diagonally
        if (size == word.length()) {
            return 0;               //can only fit in the 0th col
        }
        else {
            col = rand() % ((size + 1) - word.length()); //only valid col
        }
    }
    return col;
}

bool wordSearch::insertHoriz(int& row, int& col, std::string word) {
    int numRowChecks = 0;
    int numColChecks = 0;
    while (isCollisionHorizontal(row, col, word)) { //When collision is found horizontal
        row++;
        //cout << "COLLISION...CHECKING NEXT ROW: " << row << endl; //Checks all rows below until end
        if (row > size - 1) { //reaches bottom, start over from top
          //cout << "STARTING FROM TOP ROW" << endl;
            row = 0;
        }
        numRowChecks++;
        if (numRowChecks >= size) { //completed max row checks, increase col
          //cout << "NOWHERE TO ADD WORD IN COL, CHECKING NEXT COL" << numColChecks << endl;
            if (word.length() + col >= size) {
                //cout << "STARTING FROM FIRST COL" << endl;
                col = 0;
            }
            else {
                col++;
            }
            numColChecks++;
            numRowChecks = 0;
            if (numColChecks > size - word.length()) {
                //cout << "GRID IS FULL" << endl;
                return true;
            }
        }
    }
    return false;
}

bool wordSearch::insertVert(int& row, int& col, std::string word) {
    int numRowChecks = 0;
    int numColChecks = 0;
    while (isCollisionVertical(row, col, word)) { //When collision is found horizontal
        col++;
        //cout << "COLLISION...CHECKING NEXT ROW: " << row << endl; //Checks all rows below until end
        if (col > size - 1) { //reaches bottom, start over from top
          //cout << "STARTING FROM TOP ROW" << endl;
            col = 0;
        }
        numColChecks++;
        if (numColChecks >= size ) { //completed max row checks, increase col
          //cout << "NOWHERE TO ADD WORD IN COL, CHECKING NEXT COL" << numColChecks << endl;
            if (word.length() + row >= size) {
                //cout << "STARTING FROM FIRST COL" << endl;
                row = 0;
            }
            else {
                row++;
            }
            numRowChecks++;
            numColChecks = 0;
            if (numRowChecks > size - word.length()) {
                //cout << "GRID IS FULL" << endl;
                return true;
            }
        }
    }
    return false;
}
bool wordSearch::insertDiag(int& row, int& col, std::string word, int dir) {
    int numRowChecks = 0;
    int numColChecks = 0;

    while (isCollisionDiag(row, col, word, dir)) { //When collision is found diagonally
        col++;
       
        if (col > size - word.length()) { //reaches right side of Grid
            col = 0;
        }
        numColChecks++;
        if (numColChecks >= size) { //completed max col checks, no where to put the word
           return true;
        }
    }
    return false;
}

string wordSearch::flipWord(string word) {
    stringstream ss;
    for (int i = word.length() - 1; i >= 0; i--) {                 //Make replacement
        ss << word.at(i);
    }
    return ss.str();
}