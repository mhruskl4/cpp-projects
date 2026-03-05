#include <iostream>
#include <string>
using namespace std;

void Feedback(string secret, string guess) {
	string feedbackR="",feedbackW="", feedback="";
	
	for (int i = 0; i < 4; i++) {
		if (guess[i] == secret[i]) {
			feedbackR += "R";
		}
		else if (secret.find(guess[i]) != string::npos) {
			feedbackW += "W";
		}
	}
	feedback = feedbackR + feedbackW;
	cout << "Feedback: " << feedback << endl;
}



void GuessCheck(string& guess, string& breaker) {
	int sum = 0, countR = 0, countG = 0, countB = 0, countP = 0, countY = 0, countM = 0;
	bool check = true;
	do {
		cout << breaker << ", please enter your guess:" << endl;
		cin >> guess;
		check = true;
		sum = 0, countR = 0, countG = 0, countB = 0, countP = 0, countY = 0, countM = 0;
		if (guess.length() != 4) {
			cout << "Invalid guess!" << endl;
			check = false;
			
		}
		else {
			for (int i = 0; i < 4;) {
				char c = guess[i];

				if ((c == 'R') || (c == 'G') || (c == 'B') || (c == 'P') || (c == 'Y') || (c == 'M')) {
					if (c == 'R') {
						countR += 1;
					}
					else if (c == 'G') {
						countG += 1;
					}
					else if (c == 'B') {
						countB += 1;
					}
					else if (c == 'P') {
						countP += 1;
					}
					else if (c == 'Y') {
						countY += 1;
					}
					else if (c == 'M') {
						countM += 1;
					}
					i++;
				}
				else {
					cout << "Invalid guess!" << endl;
					check = false;
					break;
				}
			}
		}
		sum = countR + countG + countB + countP + countY + countM;
		if (check) {
			if ((sum == 4) && ((countR == 0) || (countR == 1)) && ((countG == 0) || (countG == 1)) && ((countB == 0) || (countB == 1)) && ((countP == 0) || (countP == 1)) && ((countY == 0) || (countY == 1)) && ((countM == 0) || (countM == 1))) {
				check = true;
			}
			else {
				check = false;
				cout << "Invalid guess!" << endl;
			}
		}
		
		
	} while (check == false);

}



int main() {
	
	string p1, p2, secret, guess, maker, breaker;
	int runs, sum, countR = 0, countG = 0, countB = 0, countP = 0, countY = 0, countM = 0;
	bool check = true;

	int p1_count = 0; // for p1 win
	int p2_count = 0; // for p2 win	
	
	cout << "Please enter the name of the player 1:" << endl;
	cin >> p1;
	cout << "Please enter the name of the player 2:" << endl;
	cin >> p2;
	cout <<endl<< "Welcome " << p1 << " and " << p2 << endl;
	cout << endl;
	do {
		cout << "Please enter the number of runs:" << endl;
		cin >> runs;
		if ((runs <= 0) || (runs % 2 != 0)) {
			cout << "Invalid number of runs!" << endl;
		}
	} while ((runs <= 0) || (runs % 2 != 0));
	bool state1 = false; // while counting who win how many runs not to have confusion
	for (int i = 0; i < runs; i++) {
		state1 = false;
		if (i % 2 == 0) {
			maker = p1;
			breaker = p2;
			state1 = true;
		}
		else {
			maker = p2;
			breaker = p1;
		}
		cout <<endl<< maker << ", it is your turn to select the secret!" << endl;
	    cout<< "Valid colors: R - Red, G - Green, B - Blue, P - Purple, Y - Yellow, M - Magenta" << endl;
		

		do {
			cout << maker << ", please enter your secret:" << endl;
			cin >> secret;
			check = true;
			sum = 0, countR = 0, countG = 0, countB = 0, countP = 0, countY = 0, countM = 0;
			if (secret.length() != 4) {
				cout << "Invalid secret!" << endl;
				check = false;

			}
			else {
				for (int i = 0; i < 4;) {
					char c = secret[i];

					if ((c == 'R') || (c == 'G') || (c == 'B') || (c == 'P') || (c == 'Y') || (c == 'M')) {
						if (c == 'R') {
							countR += 1;
						}
						else if (c == 'G') {
							countG += 1;
						}
						else if (c == 'B') {
							countB += 1;
						}
						else if (c == 'P') {
							countP += 1;
						}
						else if (c == 'Y') {
							countY += 1;
						}
						else if (c == 'M') {
							countM += 1;
						}
						i++;
					}
					else {
						cout << "Invalid secret!" << endl;
						check = false;
						break;
					}
				}
			}
			sum = countR + countG + countB + countP + countY + countM;
			if (check) {
				if ((sum == 4) && ((countR == 0) || (countR == 1)) && ((countG == 0) || (countG == 1)) && ((countB == 0) || (countB == 1)) && ((countP == 0) || (countP == 1)) && ((countY == 0) || (countY == 1)) && ((countM == 0) || (countM == 1))) {
					check = true;
				}
				else {
					check = false;
					cout << "Invalid secret!" << endl;
				}
			}


		} while (check == false);






		for (int guess_count = 0; guess_count < 6;) {
			GuessCheck(guess,breaker);
			if (guess == secret) {
				cout << breaker << ", you won this run!" << endl;
				if (state1) {
					p2_count++;
				}
				else {
					p1_count++;
				}
				break;
			}
			else {
				Feedback(secret, guess);
				guess_count++;
				if (state1) {
					p1_count++;
				}
				else {
					p2_count++;
				}
				
				if (guess_count == 6) {
					if (state1) {
						cout << p2 << ", you're out of chances, you lost this run!" << endl;
						p1_count++;
					}
					else {
						cout << p1 << ", you're out of chances, you lost this run!" << endl;
						p2_count++;
					}
				}
			}
		}
	}
	
	cout <<endl<< "The game has ended!" << endl;
	cout << p1 << ": " << p1_count << " - " << p2 << ": " << p2_count << endl;
	if (p1_count > p2_count) {
		cout << endl << "Congrats " << p1 << ", you have won the game!";
	}
	else if (p1_count < p2_count) {
		cout <<endl<< "Congrats " << p2 << ", you have won the game!";
	}
	else {
		cout<<endl << p1 << " and " << p2 << ", there is a tie!";
	}


	return 0;
}