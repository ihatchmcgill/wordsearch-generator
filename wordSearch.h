#pragma once
#include <vector> 
#include <string>

using namespace std;

class wordSearch {

private:
	int size;
	vector<vector<char>> theGrid;
	vector<vector<char>> offLimits;
	vector<string> addedWords = {};
	

public:
	wordSearch(int size);
	~wordSearch();


	void fillRandom();
	bool addWord(string newWord);
	void printGrid();
	bool isCollisionHorizontal(int x, int y, string word);
	bool isCollisionVertical(int x, int y, string word);
	bool isCollisionDiag(int x, int y, string word, int dir);
	int getStartingRow(string word, int insertType,int dir);
	int getStartingCol(string word, int insertType);
	bool insertHoriz(int& row, int& col, string word);
	bool insertVert(int& row, int& col, string word);
	bool insertDiag(int& row, int& col, string word, int dir);
	string flipWord(string word);

};