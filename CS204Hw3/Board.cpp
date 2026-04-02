#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

Board::Board(ifstream& infile) : head(NULL)
{
    string line;

    if (!getline(infile, line))
    {
        return;
    }

    Node* prevRowHead = NULL;
    Node* prevInRow = NULL;

    // First row
    for (int i = 0; i < static_cast<int>(line.length()); i++)
    {
        int size = line[i] - '0';
        Node* newNode = new Node(size);

        if (head == NULL)
        {
            head = newNode;
        }

        if (prevInRow != NULL)
        {
            prevInRow->right = newNode;
            newNode->left = prevInRow;
        }

        prevInRow = newNode;
    }

    prevRowHead = head;

    // Remaining rows
    while (getline(infile, line))
    {
        Node* currRowHead = NULL;
        Node* currPrev = NULL;
        Node* upper = prevRowHead;

        for (int i = 0; i < static_cast<int>(line.length()); i++)
        {
            int size = line[i] - '0';
            Node* newNode = new Node(size);

            if (currRowHead == NULL)
            {
                currRowHead = newNode;
            }

            // Horizontal links
            if (currPrev != NULL)
            {
                currPrev->right = newNode;
                newNode->left = currPrev;
            }

            // Vertical links
            if (upper != NULL)
            {
                upper->down = newNode;
                newNode->up = upper;
                upper = upper->right;
            }

            currPrev = newNode;
        }

        prevRowHead = currRowHead;
    }
}

bool Board::isFlat(Node* ptr) const
{
    return ptr->stack.isEmpty() && ptr->stack.isFull();
}

char Board::topChar(Node* ptr) const
{
    char ch;
    ptr->stack.pop(ch);
    ptr->stack.push(ch);
    return ch;
}

int Board::makeMove(char player, string path)
{
    if (head == NULL)
    {
        return 3;
    }

    Node* curr = head;

    for (int i = 0; i < static_cast<int>(path.length()); i++)
    {
        if (path[i] == 'r')
        {
            if (curr->right == NULL)
            {
                return 3;
            }
            curr = curr->right;
        }
        else if (path[i] == 'l')
        {
            if (curr->left == NULL)
            {
                return 3;
            }
            curr = curr->left;
        }
        else if (path[i] == 'u')
        {
            if (curr->up == NULL)
            {
                return 3;
            }
            curr = curr->up;
        }
        else if (path[i] == 'd')
        {
            if (curr->down == NULL)
            {
                return 3;
            }
            curr = curr->down;
        }
    }

    if (isFlat(curr))
    {
        return 2;
    }

    if (curr->stack.isFull())
    {
        return 1;
    }

    curr->stack.push(player);
    return 0;
}

bool Board::allFull() const
{
    Node* rowPtr = head;

    while (rowPtr != NULL)
    {
        Node* colPtr = rowPtr;

        while (colPtr != NULL)
        {
            if (!colPtr->stack.isFull())
            {
                return false;
            }
            colPtr = colPtr->right;
        }

        rowPtr = rowPtr->down;
    }

    return true;
}

void Board::display() const
{
    Node* rowPtr = head;

    while (rowPtr != NULL)
    {
        Node* colPtr = rowPtr;

        while (colPtr != NULL)
        {
            if (isFlat(colPtr))
            {
                cout << 'X';
            }
            else if (colPtr->stack.isEmpty())
            {
                cout << '-';
            }
            else
            {
                cout << topChar(colPtr);
            }

            colPtr = colPtr->right;
        }

        cout << endl;
        rowPtr = rowPtr->down;
    }
}

int Board::countTop(char player) const
{
    int count = 0;
    Node* rowPtr = head;

    while (rowPtr != NULL)
    {
        Node* colPtr = rowPtr;

        while (colPtr != NULL)
        {
            if (!isFlat(colPtr) && !colPtr->stack.isEmpty())
            {
                if (topChar(colPtr) == player)
                {
                    count++;
                }
            }

            colPtr = colPtr->right;
        }

        rowPtr = rowPtr->down;
    }

    return count;
}

void Board::deleteAll()
{
    Node* rowPtr = head;

    while (rowPtr != NULL)
    {
        Node* nextRow = rowPtr->down;
        Node* colPtr = rowPtr;

        while (colPtr != NULL)
        {
            Node* temp = colPtr;
            colPtr = colPtr->right;
            delete temp;
        }

        rowPtr = nextRow;
    }

    head = NULL;
}
