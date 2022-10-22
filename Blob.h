//
// Created by Evan Rudd on 10/2/22.
//

#ifndef ASSIGNMENT2_BLOB_H
#define ASSIGNMENT2_BLOB_H

#include <cstdlib>
#include "iostream"

class Blob {
    friend std::ostream& operator<<(std::ostream& out, Blob blob);
public:
    Blob();
    int GetXCoord() const;
    int GetYCoord() const;
    int GetHealth() const;
    char GetColor() const;
    void SetXCoord(int);
    void SetYCoord(int);
    void SetColor(char);
    void SetHealth(int);
    void SetPower(int);
    void Move(char direction, Blob* blobs);
    bool Attack(char direction, Blob* blobs) const;
    Blob operator+(Blob) const;


private:
    int health;
    int power;
    char color;
    int xCoord;
    int yCoord;
};

#endif //ASSIGNMENT2_BLOB_H
