# Tile Matching Board Solver (C++)

This project is a console-based C++ program that reads a board from a file and removes matching letter pairs according to specific rules.

## Description

The board consists of lowercase letters (`a-z`) and `-` characters.

The program repeatedly searches for removable pairs of the same letter and removes them from the board until no more removable pairs remain.

A tile is considered **removable** if:

- It is located on the border of the board, or
- There is a clear path to the border (up, down, left, or right) consisting only of `-` characters.

After each removal, the board is printed again so the user can see the updated state.

## Input File Format

The board is read from a text file.

Example:


abca
b--b
cabc


Rules:
- All rows must have the same length
- Only characters `a-z` and `-` are allowed

## Program Output

The program prints:

- The initial board
- Each pair removed and their coordinates
- The updated board after each removal
- A final message when no more removable pairs exist

## Language

C++

## Author

Mehir Uşaklı
