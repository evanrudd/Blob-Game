//
// Created by Evan Rudd on 10/2/22.
//

#include <iostream>
#include "Blob.h"

int Blob::GetXCoord() const {
    return xCoord;
}

int Blob::GetYCoord() const {
    return yCoord;
}

int Blob::GetHealth() const {
    return health;
}

void Blob::SetXCoord(int xValue) {
    xCoord = xValue;
}

void Blob::SetYCoord(int yValue) {
    yCoord = yValue;
}

void Blob::SetHealth(int healthValue) {
    health = healthValue;
}

void Blob::SetPower(int powerValue) {
    power = powerValue;
}

std::ostream & operator<<(std::ostream &out, Blob blob) {
    if (blob.health <= 0) {
        out << "is dead." << std::endl;
        return out;
    }

    out << "Location: (" << blob.xCoord << "," << blob.yCoord << ")" << std::endl;
    return out;
}

Blob::Blob() {
    color = 0; // placeholder, main.cpp handles setting the corresponding team colors
    xCoord = 0;
    yCoord = 0;
    health = 100;
    power = 10;
}

void Blob::SetColor(char c) {
    color = c;
}

void Blob::Move(char direction, Blob blobs[]) {

    char newDirection;

    if (direction == 'N' || direction == 'n') {
        int y = yCoord + 1;
        int x = xCoord;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    std::cout << "You cannot move to this spot, there is an enemy blob here." << std::endl;
                    std::cout << "Enter a different direction to move in (E, S, W): " << std::endl;
                    std::cin >> newDirection;
                    this->Move(newDirection, blobs);
                    return;
                }
            }
        }
        yCoord++;

    } else if (direction == 'E' || direction == 'e') {
        int y = yCoord;
        int x = xCoord + 1;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    std::cout << "You cannot move to this spot, there is an enemy blob here." << std::endl;
                    std::cout << "Enter a different direction to move in (N, S, W): " << std::endl;
                    std::cin >> newDirection;
                    this->Move(newDirection, blobs);
                    return;
                }
            }
        }
        xCoord++;
    } else if (direction == 'S' || direction == 's') {
        int y = yCoord - 1;
        int x = xCoord;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    std::cout << "You cannot move to this spot, there is an enemy blob here." << std::endl;
                    std::cout << "Enter a different direction to move in (N, E, W): " << std::endl;
                    std::cin >> newDirection;
                    this->Move(newDirection, blobs);
                    return;
                }
            }
        }
        yCoord--;
    } else if (direction == 'W' || direction == 'w') {
        int y = yCoord;
        int x = xCoord - 1;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    std::cout << "You cannot move to this spot, there is an enemy blob here." << std::endl;
                    std::cout << "Enter a different direction to move in (N, E, S): " << std::endl;
                    std::cin >> newDirection;
                    this->Move(newDirection, blobs);
                    return;
                }
            }
        }
        xCoord--;
    }
}

bool Blob::Attack(char direction, Blob blobs[]) const {
    if (direction == 'N' || direction == 'n') {
        int x = xCoord;
        int y = yCoord + 1;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    int newHealth = blobs[i].GetHealth() - power;
                    blobs[i].SetHealth(newHealth);

                    if (newHealth <= 0) {
                        return true;
                    }
                }
            }
        }

    } else if (direction == 'E' || direction == 'e') {
        int x = xCoord + 1;
        int y = yCoord;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    int newHealth = blobs[i].GetHealth() - power;
                    blobs[i].SetHealth(newHealth);

                    if (newHealth <= 0) {
                        return true;
                    }
                }
            }
        }
    } else if (direction == 'S' || direction == 's') {
        int y = yCoord - 1;
        int x = xCoord;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    int newHealth = blobs[i].GetHealth() - power;
                    blobs[i].SetHealth(newHealth);

                    if (newHealth <= 0) {
                        return true;
                    }
                }
            }
        }
    } else if (direction == 'W' || direction == 'w') {
       int x = xCoord - 1;
       int y = yCoord;

        for (int i = 0; i < 8; i++) {
            if (x == blobs[i].GetXCoord() && y == blobs[i].GetYCoord()) {
                if (color != blobs[i].GetColor()) {
                    int newHealth = blobs[i].GetHealth() - power;
                    blobs[i].SetHealth(newHealth);

                    if (newHealth <= 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

char Blob::GetColor() const {
    return color;
}

Blob Blob::operator+(Blob blob) const {

    Blob newBlob;

    newBlob.SetXCoord(blob.xCoord);
    newBlob.SetYCoord(blob.yCoord);
    newBlob.SetColor(blob.color);

    newBlob.SetHealth(health + blob.health);

    if (power > blob.power) {
        newBlob.SetPower(power + 2);
    } else {
        newBlob.SetPower(blob.power + 2);
    }

    return newBlob;
}



