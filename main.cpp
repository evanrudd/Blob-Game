#include <iostream>
#include "Blob.h"

int main() {
    bool gameActive = true;
    char currentTurn = 'b';
    int blobNum;
    char action;
    char direction;
    srand(time(NULL));

    Blob blobs[8];

    for (int i = 0; i < 8; i++) {

        blobs[i].SetXCoord(rand() % 10);
        blobs[i].SetYCoord(rand() % 10);

        if (i < 4) {
            blobs[i].SetColor('b');
        } else {
            blobs[i].SetColor('r');
        }
    }

    while(gameActive) {
        // check if any blobs are on the same space from the previous turn
        for (int i = 0; i < 8; i++) {
            int x = blobs[i].GetXCoord();
            int y = blobs[i].GetYCoord();
            if (i < 4) {
                // check the first 4 blobs (blue team) to see if coords match
                for (int p = i+1; p < 4; p++) {
                    if (x == blobs[p].GetXCoord() && y == blobs[p].GetYCoord()) {
                        blobs[i] = blobs[i] + blobs[p];
                        blobs[p].SetHealth(0);
                    }
                }
            } else {
                // check the second 4 blobs (red team) to see if coords match
                for (int p = i+1; p < 8; p++) {
                    if (x == blobs[p].GetXCoord() && y == blobs[p].GetYCoord()) {
                        blobs[i] + blobs[p];
                        blobs[p].SetHealth(0);
                    }
                }
            }
        }

        // then showing coords of blobs
        for (int i = 0; i < 8; i++) {
            if (i == 0) {
                std::cout << "-=- Blue Blobs -=-" << std::endl;
            } else if (i == 4) {
                std::cout << std::endl << "-=- Red Blobs -=-" << std::endl;
            }

            std::cout << "Blob " << i << " " << blobs[i];
            //std::cout << blobs[i];
        }

        // blue turn
        if (currentTurn == 'b') {
            // choose blob
            std::cout << std::endl << "BLUE TURN:" << std::endl;
            std::cout << "Choose a Blob (enter #): ";
            std::cin >> blobNum;

            // validate blob chosen
            while (blobNum > 3 || blobNum < 0 || blobs[blobNum].GetHealth() <= 0) {
                std::cout << "You must choose a blob from your team that is alive! Ex. (0, 1, 2, 3)" << std::endl;
                std::cout << "Choose a Blob (enter #): ";
                std::cin >> blobNum;
            }

            // move or attack
            std::cout << "Move or Attack? ('M' or 'A'): ";
            std::cin >> action;

            if (action == 'M') {
                std::cout << "Direction? (N, E, S, W): ";
                std::cin >> direction;
                blobs[blobNum].Move(direction, blobs);
                currentTurn = 'r';
            } else if (action == 'A') {
                std::cout << "Direction? (N, E, S, W): ";
                std::cin >> direction;
                if (blobs[blobNum].Attack(direction, blobs)) {
                    currentTurn = 'b';
                } else {
                    currentTurn = 'r';
                }
            }
        } else {
        // red turn
            // choose blob
            std::cout << std::endl << "RED TURN:" << std::endl;
            std::cout << "Choose a Blob (enter #): ";
            std::cin >> blobNum;

            // validate blob chosen
            while (blobNum < 4 || blobNum > 7 || blobs[blobNum].GetHealth() <= 0) {
                std::cout << "You must choose a blob from your team that is alive! Ex. (4, 5, 6, 7)" << std::endl;
                std::cout << "Choose a Blob (enter #): ";
                std::cin >> blobNum;
            }

            // move or attack
            std::cout << "Move or Attack? ('M' or 'A'): ";
            std::cin >> action;

            if (action == 'M') {
                std::cout << "Direction? (N, E, S, W): ";
                std::cin >> direction;
                blobs[blobNum].Move(direction, blobs);
                currentTurn = 'b';
            } else if (action == 'A') {
                std::cout << "Direction? (N, E, S, W): ";
                std::cin >> direction;
                if (blobs[blobNum].Attack(direction, blobs)) {
                    currentTurn = 'r';
                } else {
                    currentTurn = 'b';
                }
            }
        }

        int blueBlobsDead = 0;
        int redBlobsDead = 0;

        for (int i = 0; i < 8; i++) {
            if (i < 4) {
                if (blobs[i].GetHealth() <= 0) {
                    blueBlobsDead++;
                }
            } else {
                if (blobs[i].GetHealth() <= 0) {
                    redBlobsDead++;
                }
            }
        }

        if (blueBlobsDead == 4) {
            gameActive = false;
            std::cout << std::endl;
            std::cout << "-=-=-=-=-=-=-=-" << std::endl;
            std::cout << "Red Team Wins!";
            std::cout << "-=-=-=-=-=-=-=-" << std::endl;
        } else if (redBlobsDead == 4) {
            gameActive = false;
            std::cout << std::endl;
            std::cout << "-=-=-=-=-=-=-=-" << std::endl;
            std::cout << "Blue Team Wins!";
            std::cout << "-=-=-=-=-=-=-=-" << std::endl;
        }
    }
    return 0;
}