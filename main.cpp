#include <vector>
#include <iostream>
#include <sstream>
#include "wordSearch.h"

using namespace std;

bool isNumber(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input.at(i))) {
            return false;
        }
    }
    return true;
}

int getInput() {
    string input;
    cout << "Please select a size for your wordsearch (between 5 - 50): ";
    cin >> input;
    while (!(isNumber(input))) {
        cout << "Sorry, that is not a valid number. Please enter a positive integer: ";
        cin >> input;
    }
    int size = 0;
    stringstream ss(input);
    ss >> size;
    if (!(size >= 5)) {
        cout << size << " is too small, creating default 5x5 wordsearch." << endl;
        size = 5;
    }
    if (!(size <= 50)) {
        cout << size << " is too big, creating default 10x10 wordsearch." << endl;
        size = 10;
    }
    return size;
}


int main() {
    const int arrSize = 12;
    string prophets[arrSize] = { "Nephi", "Lehi","Alma","Korihor","Lamoni", "Abish", "Shiblon", "Moroni",
                                    "Mormon", "Amalickiah", "Gadianton", "Isaiah"};
    string locations[arrSize] = { "Ammonihah", "Jerusalem", "Zarahemla", "Bountiful", "Morianton", "Sidon", "Cumorah", "Zion",
                                    "Desolation", "Manti", "Nephihah", "Anitparah"};
    string scripture[arrSize] = { "Covenants", "Restoration", "Commandments", "Missionaries", "Redemption", "Contention", "Repentance", 
                                    "Messiah", "Israel", "Faith", "Baptism", "Resurrection"};

    int input;
    cout << "Select a wordsearch to generate:" << endl;
    cout << "1. People\t2. Locations\t3. Themes\t4. Custom Wordsearch" << endl << "Input: ";
    cin >> input;
    while (input > 4 || input < 1) {
        cout << "Sorry, that is not a valid selection. Please enter 1,2,3, or 4" << endl << "Input: ";
        cin >> input;
    }

    if (input == 4) {
        wordSearch myWordSearch(getInput());
        string wordToAdd;
        cout << "Please enter a word to add: ";
        cin >> wordToAdd;
        while (!myWordSearch.addWord(wordToAdd)) {
            cout << "Next word (Enter DONE to generate wordsearch): ";
            cin >> wordToAdd;
        }
        myWordSearch.printGrid();
    }
    else {
        wordSearch myWordSearch(17);
        if (input == 1) {
            for (int i = 0; i < arrSize; i++) {
                myWordSearch.addWord(prophets[i]);
            }
        }
        else if (input == 2) {
            //add Locations Library
            for (int i = 0; i < arrSize; i++) {
                myWordSearch.addWord(locations[i]);
            }
        }
        else {
            //add Scripture Library
            for (int i = 0; i < arrSize; i++) {
                myWordSearch.addWord(scripture[i]);
            }
        }
        myWordSearch.printGrid();
    }
   

}

