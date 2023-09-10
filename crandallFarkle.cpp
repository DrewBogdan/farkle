/*
 *  Crandall's Purpousfully Mediocre Farkle Rolling in C++
 *
 *  Contributors:
 *      Aaron S. Crandall <crandall@gonzaga.edu>
 *  Copyright: 2023
 *
 */


#include <iostream>
#include <cstdlib>
#include<ctime>

using namespace std;




int main(int argc, char* argv[]) {
    srand(time(0));
    cout << "Farkle Rolling and Scoring" << endl;

    int dice[6];
    for( int i = 0; i < 6; i++ ) {
        dice[i] = rand() % 6 + 1;
    }

    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (dice[j] > dice[j + 1]) {
                int temp = dice[j];
                dice[j] = dice[j + 1];
                dice[j + 1] = temp;
            }
        }
    }

    // Testing hand with known values
    int testHand[6] = { 2, 2, 3, 6, 6, 6};
    for( int i = 0; i < 6; i++ ) {
        dice[i] = testHand[i];
    }


    cout << "Hand: ";
    for( int i = 0; i < 6; i++ ) {
        cout << dice[i] << " ";
    }
    cout << endl;

    int diceNumberCount[7];
    for( int i = 0; i < 7; i++ ) {
        diceNumberCount[i] = 0;
    }

    for( int i = 0; i < 6; i++ ) {
        diceNumberCount[dice[i]]++;
    }

    cout << "Quantity of each die value: ";
    for( int i = 1; i < 7; i++ ) {
        cout << diceNumberCount[i] << " ";
    }
    cout << endl;


    bool isFarkle = true;

    if( diceNumberCount[1] != 0 || diceNumberCount[5] != 0 ) {
        isFarkle = false;
    }

    for( int i = 2; i < 7; i++ ) {
        if(diceNumberCount[i] >= 3) {
            isFarkle = false;
        }
    }

    int pairCount = 0;
    for( int i = 1; i < 7; i++ ) {
        if( diceNumberCount[i] == 2 ) {
            pairCount++;
        }
    }
    if( pairCount == 3 ) {
        isFarkle = false;
    }

    int meldScore = 0;
    if( isFarkle ) {
        cout << "Farkle! Points: 0" << endl;
    } else {
        string userInput = "";
        int meld[6] = {0, 0, 0, 0, 0, 0};
        bool done = false;

        while( !done) {
            // Print status
cout << "*************************** Current hand and meld *******************" << endl;
cout << " Die   Hand |   Meld" << endl;
cout << "------------+---------------" << endl;
for(int i = 0; i < 6; i++ ) {
    char option = 'A' + i;
    cout << " (" << option << ")    ";
    if(dice[i] != 0) {
        cout << dice[i];
    } else {
        cout << " ";
    }
    cout << "   |     ";
    if(meld[i] != 0) {
        cout << meld[i];
    } else {
        cout << " ";
    }
    cout << endl;
}

cout << "------------+---------------" << endl;
cout << "                Meld is: ";
bool isValidMeld = false;

// TODO: Count valid meld
// Calculate meld score too


if(isValidMeld) {
    cout << "Valid";
} else {
    cout << "Invalid";
}
cout << endl;

cout << "                Meld Score: " << meldScore << endl;
cout << endl;

cout << " (B) Bank Meld, End Turn" << endl;
cout << " (Q) Quit game" << endl;;
cout << endl;

            // Get user input
            // Update status
            done = true;
        }

    }


}