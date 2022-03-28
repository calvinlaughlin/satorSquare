#include "grid.h"
#include "strlib.h"
#include "vector.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
#include <iostream>

using namespace std;

bool checkSatorSquare(Vector<string> square);
string reverseWord(string word);
void printSatorSquare(Vector<string> square);

/**
 * Given a Vector of validWords, an empty square Vector, an empty
 * solution Vector, and an int of the position to keep track during
 * the backtracking, this function finds all perfect squares with
 * any given dictionary and stores solutions to the solutions Vector.
 *
 * It tests perfect squares via recursive backtracking, using a choose,
 * explore, unchoose strategy.
 *
 * This is one solution for the problem that takes advantage of the mirrored
 * property of the square, so instead of traversing from top to bottom, it ends
 * in the middle by mirroring results to the bottom.
 */
void findSatorSquares(Vector<string>& validWords, Vector<string>& square,
                      Set<Vector<string>>& solutions, int pos) {
    if (checkSatorSquare(square)) {
        solutions.add(square);
    } else {
        for (int i = 0; i < validWords.size(); i++) {
            string current = validWords[i];
            string reversed = reverseWord(current);
            validWords.remove(i);
            string previous = square[pos];
            square[pos] = current; // choose
            square[4 - pos] = reversed;
            if (pos == 0 && current != reversed) { // explore
                findSatorSquares(validWords, square, solutions, pos + 1);
            } else if (pos == 1 && current != reversed){
                string wordAbove = square[0];
                if (current[0] == wordAbove[1] && current[4] == wordAbove[3]) {
                    findSatorSquares(validWords, square, solutions, pos + 1);
                }
            } else if (pos == 2 && current == reversed) {
                string topLine = square[0];
                string secondLine = square[1];
                if (current[0] == topLine[2] && current[1] == secondLine[2]) {
                    findSatorSquares(validWords, square, solutions, pos + 1);
                }
            }
            square[pos] = previous; // unchoose
            square[4 - pos] = reverseWord(previous);
            validWords.insert(i, current);
        }
    }
}

/**
 * Given a Vector of validWords, an empty square Vector, an empty
 * solution Vector, and an int of the position to keep track during
 * the backtracking, this function finds all perfect squares with
 * any given dictionary and stores solutions to the solutions Vector.
 *
 * It tests perfect squares via recursive backtracking, using a choose,
 * explore, unchoose strategy.
 *
 * This is another solution to the problem that does not take advantage of
 * the mirror property given in the hint, but it still produces the same output.
 * This function adds to the square from top to bottom, checking in the bottom if
 * it equals the top. There are many, many other ways to do this, and these are only
 * two ways.
 */
void findSatorSquaresAll(Vector<string>& validWords, Vector<string>& square,
                         Set<Vector<string>>& solutions, int pos) {
    if (checkSatorSquare(square)) {
        solutions.add(square);
    } else {
        for (int i = 0; i < validWords.size(); i++) {
            string current = validWords[i];
            validWords.remove(i);
            string previous = square[pos];
            square[pos] = current; // choose
            if (pos == 0) {
                findSatorSquaresAll(validWords, square, solutions, pos + 1);
            } else if (pos == 1){
                string wordAbove = square[0];
                if (current[0] == wordAbove[1] && current[4] == wordAbove[3]) {
                    findSatorSquaresAll(validWords, square, solutions, pos + 1);
                }
            } else if (pos == 2 && current == reverseWord(current)) {
                string topLine = square[0];
                string secondLine = square[1];
                if (current[0] == topLine[2] && current[1] == secondLine[2]) {
                    findSatorSquaresAll(validWords, square, solutions, pos + 1);
                }
            } else if (pos == 3) {
                if (reverseWord(current) == square[1]) {
                    findSatorSquaresAll(validWords, square, solutions, pos + 1);
                }
            } else if (pos == 4) {
                if (reverseWord(current) == square[0]){
                    findSatorSquaresAll(validWords, square, solutions, pos + 1);
                }
            }
            square[pos] = previous; // unchoose
            validWords.insert(i, current);
        }
    }
}

/**
 * This function checks the given Vector of the perfect square
 * and returns a bool of true if the square fits the parameters
 * of a perfect square, and false if the square is not a perfect square.
 */
bool checkSatorSquare(Vector<string> square) {
    for (int i = 0; i < 3; i++) {
        if (square[i] != reverseWord(square[4 - i]) || square[i] == "") {
            return false;
        }
    }
    return true;
}

/**
 * This helper function takes in a word string and reverses all of
 * its elements, returning a reversed string of the given word.
 */
string reverseWord(string word) {
    string reversed;
    for (int i = word.size() - 1; i >= 0; i--) {
        reversed += word[i];
    }
    return reversed;
}

/**
 * This function finds all words in a given dictionary that are length
 * 5 and have a valid reversed word, returning valid words to a Vector
 * that can be used in the recursive backtracking.
 */
Vector<string> findWords(string filename) {
    Lexicon lex(filename);
    Vector<string> validWords;
    for (string word : lex) {
        int size = word.length();
        string reversed = reverseWord(word);
        if (size == 5 && lex.contains(reversed)) {
            validWords.add(toUpperCase(word));
        }
    }
    return validWords;
}

/**
 * This given function prints the given square to the screen.
 *  Intended use with debugging.
 */
void printSatorSquare(Vector<string> square) {
    cout << " " << endl;
    for (string item : square) {
        for (char ch : item) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

/* * * * * * Test Cases Below This Point * * * * * */

PROVIDED_TEST("Testing checkSatorSquare") {
    Vector<string> sator = {"SATOR",
                            "AREPO",
                            "TENET",
                            "OPERA",
                            "ROTAS"};

    Vector<string> bogus = {"TENET",
                            "AREPO",
                            "SATOR",
                            "OPERA",
                            "TENET"};

    EXPECT(checkSatorSquare(sator));
    EXPECT(!checkSatorSquare(bogus));
}

PROVIDED_TEST("Testing findWords with words_small.txt") {
    Vector<string> words = findWords("words_small.txt");
    Set<string> check;
    for (string word : words) {
        check.add(word);
        EXPECT(word.size() == 5);
    }
    EXPECT(check.contains("PARTS"));
    EXPECT(check.contains("RADAR"));
    EXPECT(!check.contains("RABBIT"));
}

PROVIDED_TEST("findSatorSquares on words_small.txt") {
    Vector<string> square = {"", "", "", "", ""};
    Vector<string> validWords = findWords("scrabble.txt");
    Set<Vector<string>> solutions;
    findSatorSquares(validWords, square, solutions, 0);
    //findSatorSquaresAll(validWords, square, solutions, 0);
    for (Vector<string> solution : solutions) {
        printSatorSquare(solution);
    }
    cout << solutions.size() << endl;
    //EXPECT(solutions.size() == 6);
}

PROVIDED_TEST("findSatorSquares time trial comparison") {
    Vector<string> square1 = {"", "", "", "", ""};
    Vector<string> validWords1 = findWords("words_big.txt");
    Set<Vector<string>> solutions1;
    TIME_OPERATION(validWords1.size(), findSatorSquares(validWords1, square1, solutions1, 0));

    Vector<string> square2 = {"", "", "", "", ""};
    Vector<string> validWords2 = findWords("words_big.txt");
    Set<Vector<string>> solutions2;
    TIME_OPERATION(validWords2.size(), findSatorSquaresAll(validWords2, square2, solutions2, 0));
}
