#ifndef _CHARSTACK_H
#define _CHARSTACK_H

class CharStack
{
private:
    char* stackArray;
    int stackSize;
    int top;

public:
    CharStack(int);
    ~CharStack();

    bool push(char);
    bool pop(char&);

    bool isFull();
    bool isEmpty();
};

#endif
