
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// this gives location in matris as row and column
struct Location { int r, c; };

// this controls if the file includes anything else except a-z and -
bool validCharControl(char ch) {
    return (ch >= 'a' && ch <= 'z') || ch == '-';
}
// print board row by row
void printBoard(const vector<vector<char>>& board) {
    int r = 0;
    while (r < (int)board.size()) {
        int c = 0;
        while (c < (int)board[r].size()) {
            cout << board[r][c];
            c++;
        }
        cout << "\n";
        r++;
    }
}

//Determines whether the tile is removable
bool RemovableControl(const vector<vector<char>>& board, int r, int c) {
    int num_r = (int)board.size();     // total rows
    int num_c = (int)board[0].size();  // total columns

    // already empty cells cannot be removed
    if (board[r][c] == '-') return false;

    // tile on the boundary automatically removable
    if (r == 0 || c == 0 || r == num_r - 1 || c == num_c - 1) return true;

    // direction check: up
    bool clearUp = true;
    int temp_r = r - 1;
    while (temp_r >= 0) {
        if (board[temp_r][c] != '-') {
            clearUp = false;
        }
        temp_r--;
    }
    if (clearUp) return true;

    // direction check: down
    bool clearDown = true;
    temp_r = r + 1;
    while (temp_r < num_r) {
        if (board[temp_r][c] != '-') {
            clearDown = false;
        }
        temp_r++;
    }
    if (clearDown) return true;

    // direction check: left
    bool clearLeft = true;
    int temp_c = c - 1;
    while (temp_c >= 0) {
        if (board[r][temp_c] != '-') {
            clearLeft = false;
        }
        temp_c--;
    }
    if (clearLeft) return true;

    // direction check: right
    bool clearRight = true;
    temp_c = c + 1;
    while (temp_c < num_c) {
        if (board[r][temp_c] != '-') {
            clearRight = false;
        }
        temp_c++;
    }
    if (clearRight) return true;

    return false;
}

//Searche for the first removable pair of the letter
bool findFirstRemovablePairForLetter(const vector<vector<char>>& board,
    char letter, Location& p1, Location& p2) {

    int num_r = (int)board.size();    // total rows
    int num_c = (int)board[0].size(); // total columns
    bool found = false;

    int r1 = 0;
    while (r1 < num_r && found==false) {
        int c1 = 0;
        while (c1 < num_c && found == false) {
            if (board[r1][c1] == letter) {
                if (RemovableControl(board, r1, c1)) {

                    int r2 = r1;
                    while (r2 < num_r && found == false) {
                        int startC = 0;
                        if (r2 == r1) startC = c1 + 1;
                        int c2 = startC;

                        while (c2 < num_c && found == false) {
                            if (board[r2][c2] == letter) {
                                if (RemovableControl(board, r2, c2)) {
                                    p1 = { r1, c1 };
                                    p2 = { r2, c2 };
                                    found = true;
                                }
                            }
                            c2++;
                        }
                        r2++;
                    }
                }
            }
            c1++;
        }
        r1++;
    }

    return found;
}

//Read board 
int readBoardFromFile(const string& filename, vector<vector<char>>& board) {
    ifstream fin(filename.c_str());
    if (!fin.is_open()) return 1;

    vector<string> lines;
    string line;

    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.size() == 0) {
            fin.close();
            return 2;
        }

        lines.push_back(line);
    }
    fin.close();

    if (lines.size() == 0) return 2;

    int cols = (int)lines[0].size();
    if (cols == 0) return 2;

    int i = 0;
    while (i < (int)lines.size()) {
        if ((int)lines[i].size() != cols) return 2;

        int j = 0;
        while (j < cols) {
            if (!validCharControl(lines[i][j])) return 2;
            j++;
        }
        i++;
    }

    // Copy to 2D vector
    board.assign((int)lines.size(), vector<char>(cols, '-'));
    int r = 0;
    while (r < (int)lines.size()) {
        int c = 0;
        while (c < cols) {
            board[r][c] = lines[r][c];
            c++;
        }
        r++;
    }

    return 0;
}


int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    vector<vector<char>> board;
    int status = readBoardFromFile(filename, board);

    if (status == 1) {
        cout << "\nError: Could not open file.\n";
        return 0;
    }
    if (status == 2) {
        cout << "\nError: Board is invalid.\n";
        return 0;
    }

    cout << "\nInitial board:\n";
    printBoard(board);

    bool removedInAnyRound = true;
    while (removedInAnyRound) {
        removedInAnyRound = false;

        int letter_index = 0;   
        while (letter_index < 26) {
            char letter = (char)('a' + letter_index);

            bool removedThisLetter = true;
            while (removedThisLetter) {
                removedThisLetter = false;

                Location p1, p2;
                bool found = findFirstRemovablePairForLetter(board, letter, p1, p2);

                if (found) {
                    board[p1.r][p1.c] = '-';
                    board[p2.r][p2.c] = '-';

                    cout << "\nRemoved " << letter << " at (" << p1.r << "," << p1.c
                        << ") and (" << p2.r << "," << p2.c << ")\n\n";
                    printBoard(board);

                    removedThisLetter = true;
                    removedInAnyRound = true;
                }
            }

            letter_index ++;
        }
    }

    cout << "No more removable pairs. Game finished.\n";
    return 0;
}



