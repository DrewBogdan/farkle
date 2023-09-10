/*
 *  Crandall's Purposefully Mediocre Farkle Rolling in C++
 *
 *  Contributors:
 *      Aaron S. Crandall <crandall@gonzaga.edu>
 * 
 *  Copyright: 2023
 * 
 *  License: Only for class uses
 *
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;



int main(int argc, char* argv[]) {
    srand(time(0));
    cout << "Farkle Rolling and Scoring Terrible C++ Example" << endl;

    int dice[6];
    for( int i = 0; i < 6; i++ ) {
        dice[i] = rand() % 6 + 1;
    }

    // Testing hand with known values
    // int testHand[6] = { 1, 5, 5, 3, 4, 5};
    // for( int i = 0; i < 6; i++ ) {
    //    dice[i] = testHand[i];
    // }

    // Sort the hand the hard way
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (dice[j] > dice[j + 1]) {
                int temp = dice[j];
                dice[j] = dice[j + 1];
                dice[j + 1] = temp;
            }
        }
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

    int totalScore = 0;
    if( isFarkle ) {
        cout << "Farkle! Points: 0" << endl;
    } else {
        string userInput = "";
        int meldScore = 0;
        int meld[6] = {0, 0, 0, 0, 0, 0};
        bool done = false;

        while( !done) {
            // Print status
            cout << endl;
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
bool isValidMeld = false;

    {   // Calculate the meld
        meldScore = 0; // Reset each time user changes meld dice
        int meldDiceCount = 0;
        int meldDice[6] = {0,0,0,0,0,0};
        for(int i = 0; i < 6; i++ ) {
            if( meld[i] != 0 ) {
                meldDice[meldDiceCount] = meld[i];
                meldDiceCount++;
            }
        }

        int meldDiceSizesCount[7] = {0,0,0,0,0,0,0};
        for( int i = 0; i < 6; i++ ) {
            meldDiceSizesCount[meldDice[i]]++;
        }

        // cout << endl;
        // cout << "Meld dice sizes count: ";
        // for( int i = 1; i < 7; i++ ) {
        //    cout << meldDiceSizesCount[i] << " ";
        // }
        // cout << endl;

        // Check straight
        bool isStraight = true;
        for( int i = 1; i < 7; i++ ) {
            if( meldDiceSizesCount[i] != 1 ) {
                isStraight = false;
            }
        }
        if( isStraight ) {
            meldScore += 1000;
        } else {
            // Check 3 pairs
            int pairCount = 0;
            for( int i = 1; i < 7; i++ ) {
                if( meldDiceSizesCount[i] == 2) {
                    pairCount++;
                }
            }
            if( pairCount == 3 ) {
                meldScore += 750;
            } else {
                // Check triples +
                bool isTripleSet = false;
                for( int i = 1; i < 7; i++ ) {
                    if( meldDiceSizesCount[i] >= 3 ) {
                        // Found triple (or more!)
                        isTripleSet = true;
                        int tripleSetPoints = 0;
                        if(i == 1) {
                            tripleSetPoints = 1000;
                        } else {
                            tripleSetPoints = i * 100;
                        }
                        if( meldDiceSizesCount[i] > 3 ) { // 4 + in set
                            tripleSetPoints += (meldDiceSizesCount[i] - 3) * 100 * i;
                        }
                        meldScore += tripleSetPoints;
                    }
                }

                // Add 1's & 5's if unused
                if( meldDiceSizesCount[1] < 3) {
                    meldScore += meldDiceSizesCount[1] * 100;
                }

                if( meldDiceSizesCount[5] < 3) {
                    meldScore += meldDiceSizesCount[5] * 50;
                }
            }
        }
    }



cout << "                Meld Score: " << meldScore << endl;
cout << endl;

cout << " (K) BanK Meld & End Round" << endl;
cout << " (Q) Quit game" << endl;;
cout << endl;
cout << "Enter letters for your choice(s): ";
cin >> userInput;

// cout << "User entered: " << userInput;

            for( int i = 0; i < userInput.length(); i++ ) {
                char letter = toupper(userInput[i]);
                if( letter >= 'A' && letter <= 'F' ) {
                    int index = letter - 'A';
                    if(dice[index] != 0) {
                        meld[index] = dice[index];
                        dice[index] = 0;
                    } else {
                        dice[index] = meld[index];
                        meld[index] = 0;
                    }
                } else if(letter == 'Q') {
                    done = true;
                } else if(letter == 'K') {
                    done = true;
                    totalScore += meldScore;
                }
                
            }
        }
    }

    cout << endl;
    cout << "Round over. Total score is now: " << totalScore << endl;
    cout << endl;


}