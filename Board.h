#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <string>
#include "CharStack.h"

using namespace std;

class Board
{
private:
    struct Node
    {
        CharStack stack;
        Node* right;
        Node* left;
        Node* down;
        Node* up;

        Node(int size) : stack(size), right(NULL), left(NULL), down(NULL), up(NULL) {}
    };

    Node* head;

    bool isFlat(Node* ptr) const;
    char topChar(Node* ptr) const;

public:
    Board(ifstream& infile);
    void deleteAll();
    int makeMove(char player, string path);
    bool allFull() const;
    void display() const;
    int countTop(char player) const;
};

#endif