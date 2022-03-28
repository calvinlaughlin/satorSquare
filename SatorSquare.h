#pragma once

#include "grid.h"
#include "strlib.h"
#include "vector.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
#include <iostream>
#include <string>

bool checkSatorSquare(Vector<std::string> square);

std::string reverseWord(std::string word);

void findSatorSquares(Vector<std::string>& validWords, Vector<std::string>& square,
                      Set<Vector<std::string>>& solutions, int pos);

void findSatorSquaresAll(Vector<std::string>& validWords, Vector<std::string>& square,
                         Set<Vector<std::string>>& solutions, int pos);

Vector<std::string> findWords(std::string filename);

void printSatorSquare(Vector<std::string> square);
