/*
 * File: Sator Square
 * Calvin Laughlin, Spring 2021
 * --------------
 * Given a dictionary, this algorithm finds all valid Sator Squares as defined by the
 * Sator Square found in Pompeii, 40 AD. (*Factcheck?)
 */
#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include "SatorSquare.h"
#include "time.h"
using namespace std;

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    cout << "Finding English Sator Squares..." << endl;
    Vector<string> square = {"", "", "", "", ""};
    Vector<string> validWords = findWords("scrabble.txt");
    Set<Vector<string>> solutions;
    findSatorSquares(validWords, square, solutions, 0);
    for (Vector<string> solution : solutions) {
        printSatorSquare(solution);
    }
    return 0;
}
