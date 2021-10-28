#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Seat.h"
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>
using namespace std;

inline string ctos(char c) // converts from char to string 
{
	string s(1, c); // constructor takes the character and puts it in a string
	return s; // returns the string
}
class Movies
{
private:
	string name;
	Seat seats[9][7]; // 9 rows and 7 columns
	string timing;
public:
	Movies() { name = ""; timing = ""; }

	// getters and setters
	void set_name(string x) { name = x; }
	string get_name() { return name; }

	void set_timing(string x) { timing = x; }
	string get_timing() { return timing; }

	void reserve_seat(string s_num) {
		// The next two lines convert a string of seat number to indeses a and b in the array of seats[9][7]
		// we determine the row from the letter, and the column from the number beside it
		short int a = s_num[0] - 'A'; // s_num = "D3", s_num[0] = 'D', s_num[0] - 'A' = 3
		// 'A' = 0 (in index), 'B' = 1, 'C' = 2, 'D' = 3, ...
		short int b = s_num[1] - '1'; // s_num = "D3", s_num[1] = '3', s_num[0] - '1' = 2
		// '1' = 0 (in index), '2' = 1, '3' = 2, '4' = 3, ...
		seats[a][b].reserve();
	}

	void unreserve_seat(string s_num) {
		// The next two lines convert a string of seat number to indeses a and b in the array of seats[9][7]
		// we determine the row from the letter, and the column from the number beside it
		short int a = s_num[0] - 'A'; // s_num = "D3", s_num[0] = 'D', s_num[0] - 'A' = 3
		// 'A' = 0 (in index), 'B' = 1, 'C' = 2, 'D' = 3, ...
		short int b = s_num[1] - '1'; // s_num = "D3", s_num[1] = '3', s_num[0] - '1' = 2
		// '1' = 0 (in index), '2' = 1, '3' = 2, '4' = 3, ...
		seats[a][b].unreserve();
	}

	Seat get_seat(string s_num) { // same thing but only gets the seat
		short int a = s_num[0] - 'A';
		short int b = s_num[1] - '1';
		return seats[a][b];
	}

	void display_seats()
	{
		cout << endl;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // for editing the color of the seats
		for (int i = 0; i < 7; i++) { // nested loop for going through the first 7 rows (non-VIP)
			for (int j = 0; j < 7; j++)
			{
				if (seats[i][j].getAvail()) {
					SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					// if available, the color of the output is green
					cout << seats[i][j].getSeatNum() << " ";
				}
				else {
					// if not available, the color of the output is red
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << seats[i][j].getSeatNum() << " ";
				}
			}
			cout << "\n";
		}
		SetConsoleTextAttribute(h, 15); //set back to black background and white text
		cout << "VIP\n"; // indicate the next two rows are VIP
		for (int i = 7; i < 9; i++) { // nested loop going through the last two rows
			for (int j = 0; j < 7; j++)
			{
				if (seats[i][j].getAvail()) {
					SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					cout << seats[i][j].getSeatNum() << " ";
				}
				else {
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << seats[i][j].getSeatNum() << " ";
				}
			}
			cout << "\n";
		}
		cout << "\n\n";
		SetConsoleTextAttribute(h, 15); //set back to black background and white text
		cout << "Note: color is red when it's unavailable and green when it's available\n\n";
	}
	// every movie has his own array of seats and availability
	void saveseats() { // this function saves the seats availability for any certain movie
		ofstream str;
		string name1 = name + ".txt"; // name is a string, ".txt" is a string, name + ".txt" is a string
		// for instance if the name of the movie is "Avatar" (i.e. name = "Avatar"), then name1 = "Avatar.txt"
		str.open(name1);
		for (int i = 0; i < 9; i++) { // nested loop for saving the seats availability (reserved or not)
			for (int j = 0; j < 7; j++) {
				str << seats[i][j].getAvail() << "\n";
			}
		}
		str.close();
	}
	
	void loadseats() { // function loads the seats availability for any certain movie
		ifstream str;
		str.open((name + ".txt")); // same principle of naming as seats
		bool c;
		for (int i = 0; i < 9; i++) { // nested loop load the availability of the seats
			for (int j = 0; j < 7; j++) {
				str >> c; // input the availability in the boolean variable c,
				if (c) { seats[i][j].unreserve(); }
				else { seats[i][j].reserve(); }
				 // set the availabilty for each seat to c
				seats[i][j].setSeatNum((ctos('A' + i) + ctos('1' + j))); // setup the seat numbers
				// "C" = ctos('A' + 2), "3" = ctos('1' + 2), ctos('A' + 2) + ctos('1' + 2) = "C" + "3"
				// = "C3", setSeatNum("C3")
				if (i > 6) { seats[i][j].make_VIP(); } // changes the price of VIP seats for the last two rows
			}
		}
		str.close();
	}
};
