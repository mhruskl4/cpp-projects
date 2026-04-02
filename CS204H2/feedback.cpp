#include "feedback.h"
#include <string>
using namespace std;

int mypower(int a, int b, int m) // I didn't change this
{
    int res = 1;
    a = a % m;
    for(int i=1 ; i<=b ; ++i)
        res = (res * a) % m;
    return res;
}

string secretNumber (int gameID) // this changed to reflect the following: it is ok to have duplicates, thus no need to check the uniquness with loop, and mod 100 not 1000
{
    string s = "  ";
    gameID = gameID*gameID % 15307;
    int secret = mypower (393, gameID, 15307) % 100;
    s[1] = secret % 10 + 48;
    s[0] = (secret / 10) % 10 + 48;
    return s;
}




string get_the_feedback (string guess, int game_id)
{
    string secret_number = secretNumber(game_id);

    string feedback_str(2,' '); // only two this time
    for (int i = 0; i < 2; i++)
    {
        if (guess[i] == secret_number[i]) // if found
            feedback_str[i] = 'F';
        else if (guess[i] < secret_number[i]) // if greater
            feedback_str[i] = 'G';
        else
            feedback_str[i] = 'L'; // if lower
    }
    return feedback_str;
}
