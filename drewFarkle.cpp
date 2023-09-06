using namespace std;

#include <iostream>
#include <vector>

// author - drew bogdan
// enjoy :)

bool check_saveable(int currdice[], int currsaved[], int index) {
    if (currdice[index] == 5 or currdice[index] == 1) {
        return true;
    }

    for (int x = 0; x < 6; x++) {
        if (currdice[index] == currsaved[x]) {
            return true;
        }
    }
    int same = 0;
    for (int x = 0; x < 6; x++) {
        if (currdice[index] == currdice[x]) {
            same++;
        }
    }
    if (same >= 3) {
        return true;
    }
    return false;
}


int main() {

    int saved = 0;
    int outdice[] = {0,0,0, 0,0,0};
    int saveddice[] = {-1,-1,-1,-1,-1,-1};
    srand(time(NULL));
    // create dice
    for (int x = 0; x < 6; x++) {
        int random = rand() % 5 + 1;
        outdice[x] = random;
    }

    // display roll
    cout << "Your starting roll: ";
    for (int die : outdice) {
        cout << die;
    }
    cout << endl;

    // ask for input
    cout << "Would you like to keep any of these dice (y/n)?" << endl;
    string input = "";
    cin >> input;


    for (int x = 0; x < input.length(); x++) {
        if(input.at(x) == 'y') {
            if (check_saveable(outdice, saveddice, x)) {
                saveddice[x] = outdice[x];
                outdice[x] = -1;
                saved++;
            }
            else {
                cout << "No possible meld for " << outdice[x] << endl;
            }
        }
    }
    bool reroll = true;
    bool bank = false;
    while (saved < 6) {
        cout << "Would you like to bank your score now? (y/n)" << endl;
        string ans = "";
        cin >> ans;
        if (ans == "y") {
            bank = true;
            break;
        }
        else {
            cout << "Roll of the dice: ";
            if (reroll) {
                for (int x = 0; x < 6; x++) {
                    int random = rand() % 5 + 1;
                    if (outdice[x] != -1) {
                        outdice[x] = random;
                    }
                }
                reroll = false;
            }
            for (int die: outdice) {
                if (die != -1) {
                    cout << die;
                }
            }
            cout << endl;

            bool farkle = true;
            for (int x = 0; x < 6; x++) {
                if (check_saveable(outdice, saveddice, x) && outdice[x] != -1) {
                    farkle = false;
                }
            }
            if (farkle) {
                cout << "Farkle!" << endl;
                exit(0);
            }

            cout << "Would you like to keep any of these dice (y/n)?" << endl;
            string input = "";
            cin >> input;

            int outindex = 0;
            bool badmeld = false;
            for (int x = 0; x < input.length(); x++) {
                if (outdice[outindex] == -1) {
                    for (int y = outindex; y < 6; y++) {
                        if (outdice[y] != -1) {
                            outindex = y;
                            break;
                        }
                    }
                }
                if (input.at(x) == 'y') {
                    if (check_saveable(outdice, saveddice, outindex)) {
                        saveddice[outindex] = outdice[outindex];
                        outdice[outindex] = -1;
                        saved++;
                        farkle = false;
                    } else {
                        cout << "No possible meld for " << outdice[outindex] << endl;
                        badmeld = true;
                    }
                }
                outindex++;
            }

            reroll = !badmeld;
        }
    }

    int ones = 0;
    int twos = 0;
    int threes = 0;
    int fours = 0;
    int fives = 0;
    int sixes = 0;

    if (bank) {
        for (int x = 0; x < 6; x++) {
            if (saveddice[x] == 1) {
                ones++;
            } else if (saveddice[x] == 2) {
                twos++;
            } else if (saveddice[x] == 3) {
                threes++;
            } else if (saveddice[x] == 4) {
                fours++;
            } else if (saveddice[x] == 5) {
                fives++;
            } else if (saveddice[x] == 6) {
                sixes++;
            }
        }

        int totalscore = 0;
        if (ones == 3) {
            totalscore += 1000;
        }
        if (twos == 3) {
            totalscore += 200;
        }
        if (threes == 3) {
            totalscore += 300;
        }
        if (fours == 3) {
            totalscore += 400;
        }
        if (fives == 3) {
            totalscore += 500;
        }
        if (sixes == 3) {
            totalscore += 600;
        }

        if (ones == 4 || twos == 4 || threes == 4 || fours == 4 || fives == 4 || sixes == 4) {
            totalscore += 1000;
        }
        if (ones == 5 || twos == 5 || threes == 5 || fours == 5 || fives == 5 || sixes == 5) {
            totalscore += 2000;
        }
        if (ones == 6 || twos == 6 || threes == 6 || fours == 6 || fives == 6 || sixes == 6) {
            totalscore += 3000;
        }

        // 4 of a kind 3 pair
        if ((ones == 4 && (twos == 2 || threes == 2 || fours == 2 || fives == 2 || sixes == 6)) ||
            (twos == 4 && (ones == 2 || threes == 2 || fours == 2 || fives == 2 || sixes == 6)) ||
            (threes == 4 && (ones == 2 || twos == 2 || fours == 2 || fives == 2 || sixes == 6)) ||
            (fours == 4 && (ones == 2 || twos == 2 || threes == 2 || fives == 2 || sixes == 6)) ||
            (fives == 4 && (ones == 2 || twos == 2 || threes == 2 || fours == 2 || sixes == 6)) ||
            (sixes == 4 && (ones == 2 || twos == 2 || threes == 2 || fours == 2 || fives == 2))) {
            totalscore += 1500;
        } // i wouldnt put this in your code...
        else if ((ones == 2 && twos == 2 && threes == 2) || (ones == 2 && twos == 2 && fours == 2) ||
                 (ones == 2 && twos == 2 && fives == 2) || (ones == 2 && twos == 2 && sixes == 2) ||
                 (ones == 2 && threes == 2 && fours == 2) || (ones == 2 && threes == 2 && fives == 2) ||
                 (ones == 2 && threes == 2 && sixes == 2) || (ones == 2 && fours == 2 && fives == 2) ||
                 (ones == 2 && fours == 2 && sixes == 2) || (ones == 2 && fives == 2 && sixes == 2) ||
                 (twos == 2 && threes == 2 && fours == 2) || (twos == 2 && threes == 2 && fives == 2) ||
                 (twos == 2 && threes == 2 && sixes == 2) || (twos == 2 && fours == 2 && fives == 2) ||
                 (twos == 2 && fours == 2 && sixes == 2) || (twos == 2 && fives == 2 && sixes == 2) ||
                 (threes == 2 && fours == 2 && fives == 2) || (threes == 2 && fours == 2 && sixes == 2) ||
                 (threes == 2 && fives == 2 && sixes == 2) || (fours == 2 && fives == 2 && sixes == 2)) {
            totalscore += 1500;
        }

        // run
        if (ones == 1 && twos == 1 && threes == 1 && fours == 1 && fives == 1 && sixes == 1) {
            totalscore += 2500;
        }

        totalscore += 50 * fives;
        totalscore += 100 * ones;

        cout << "Your total score is: " << totalscore << endl;

    }

}

