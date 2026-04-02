
#include <iostream>
#include <string>
#include <cctype>
#include "feedback.h"

using namespace std;

// defining node for linked list
struct node
{
    int digit;
    node* next;
};

// checks whether a digit is in the possible/impossible list
bool exists(node* head, int value)
{
    node* temp = head;
    while (temp != nullptr)
    {
        if (temp->digit == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// adds a new digit to the list while keeping the list sorted
void addNode(node*& head, int value)
{
    if (exists(head, value))
        return;

    node* newNode = new node;
    newNode->digit = value;
    newNode->next = nullptr;

    if (head == nullptr || value < head->digit)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    node* temp = head;
    while (temp->next != nullptr && temp->next->digit < value)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// deletes all nodes in the linked list
void deleteList(node*& head)
{
    while (head != nullptr)
    {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

// counts how many nodes are in the linked list
int sizeOfList(node* head)
{
    int count = 0;
    while (head != nullptr)
    {
        count++;
        head = head->next;
    }
    return count;
}

// prints all digits in the linked list
void printList(node* head)
{
    node* temp = head;
    while (temp != nullptr)
    {
        cout << temp->digit;
        if (temp->next != nullptr)
            cout << " ";
        temp = temp->next;
    }
    cout << endl;
}

// removes all digits that are less than or equal to the given value
void removeLessOrEqual(node*& head, int value)
{
    while (head != nullptr && head->digit <= value)
    {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    node* curr = head;
    while (curr != nullptr && curr->next != nullptr)
    {
        if (curr->next->digit <= value)
        {
            node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else
        {
            curr = curr->next;
        }
    }
}

// removes digits that are greater than or equal to the given value
void removeGreaterOrEqual(node*& head, int value)
{
    while (head != nullptr && head->digit >= value)
    {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    node* curr = head;
    while (curr != nullptr && curr->next != nullptr)
    {
        if (curr->next->digit >= value)
        {
            node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else
        {
            curr = curr->next;
        }
    }
}

// updates the possible and impossible digits according to the feedback
void processDigit(node*& impossibleHead, node*& possibleHead, int guessedDigit, char feedbackChar)
{
    if (feedbackChar == 'G')
    {
        for (int i = 0; i <= guessedDigit; i++)
            addNode(impossibleHead, i);

        if (possibleHead == nullptr)
        {
            for (int i = guessedDigit + 1; i <= 9; i++)
                addNode(possibleHead, i);
        }
        else
        {
            removeLessOrEqual(possibleHead, guessedDigit);
        }
    }
    else if (feedbackChar == 'L')
    {
        for (int i = guessedDigit; i <= 9; i++)
            addNode(impossibleHead, i);

        if (possibleHead == nullptr)
        {
            for (int i = 0; i < guessedDigit; i++)
                addNode(possibleHead, i);
        }
        else
        {
            removeGreaterOrEqual(possibleHead, guessedDigit);
        }
    }
    else if (feedbackChar == 'F')
    {
        deleteList(possibleHead);
        addNode(possibleHead, guessedDigit);

        for (int i = 0; i <= 9; i++)
        {
            if (i != guessedDigit)
                addNode(impossibleHead, i);
        }
    }
}
// checks if the guess is valid
bool ValidOrInvalidGuess(const string& guess)
{
    return guess.length() == 2 &&
        isdigit(guess[0]) &&
        isdigit(guess[1]);
}

// checks if the game is solved
bool isgameSolved(node* imp1, node* pos1, node* imp2, node* pos2)
{
    if (sizeOfList(pos1) == 1 && sizeOfList(pos2) == 1)
        return true;

    if (sizeOfList(imp1) == 9 && sizeOfList(imp2) == 9)
        return true;

    return false;
}

// finds the secret digit for the slot
int findSecretDigit(node* impossibleHead, node* possibleHead)
{
    if (sizeOfList(possibleHead) == 1)
        return possibleHead->digit;

    for (int i = 0; i <= 9; i++)
    {
        if (!exists(impossibleHead, i))
            return i;
    }

    return -1;
}

//prints all list
void printAllLists(node* imp1, node* pos1, node* imp2, node* pos2)
{
    cout << "Linked lists:" << endl;

    cout << "Slot: 1" << endl;
    cout << "Impossibles: ";
    printList(imp1);
    cout << "Possibles: ";
    printList(pos1);
    cout << endl;

    cout << "Slot: 2" << endl;
    cout << "Impossibles: ";
    printList(imp2);
    cout << "Possibles: ";
    printList(pos2);
    cout << endl;
}

int main()
{
    int gameID;
    cout << "Please enter a game ID." << endl;
    cin >> gameID;

    // linked lists for slot 1 and slot 2 (possible and impossible digits)
    node* impossible1 = nullptr;
    node* possible1 = nullptr;
    node* impossible2 = nullptr;
    node* possible2 = nullptr;

    string guess;

    // game loop
    while (true)
    {
        // ask user for a guess
        cout << "Enter your guess." << endl;
        cin >> guess;

        // check if guess is valid
        while (!ValidOrInvalidGuess(guess))
        {
            cout << "Invalid guess. Enter your guess." << endl;
            cin >> guess;
        }
        // get feedback 
        string feedback = get_the_feedback(guess, gameID); // oracle function :contentReference[oaicite:0]{index=0}

        // convert guess characters to digits
        int digit1 = guess[0] - '0';
        int digit2 = guess[1] - '0';

        // update possible and impossible lists according to feedback
        processDigit(impossible1, possible1, digit1, feedback[0]);
        processDigit(impossible2, possible2, digit2, feedback[1]);

        // print current linked lists
        printAllLists(impossible1, possible1, impossible2, possible2);

        // check if the game is solved
        if (isgameSolved(impossible1, possible1, impossible2, possible2))
            break;
    }

    // find the final digits of the secret number
    int secret1 = findSecretDigit(impossible1, possible1);
    int secret2 = findSecretDigit(impossible2, possible2);

    // print the secret number
    cout << "The secret number is: " << secret1 << secret2 << endl;
    cout << "Congrats! Now, deleting the lists..." << endl;
    
    // delete dynamic memory
    deleteList(impossible1);
    deleteList(possible1);
    deleteList(impossible2);
    deleteList(possible2);

    return 0;
}
