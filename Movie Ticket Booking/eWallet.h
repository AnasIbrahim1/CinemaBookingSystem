#pragma once
#include <iostream>
using namespace std;

class eWallet {

private:
	double current_balance;
	short int CVV;
	long long int number;
	short int month;
	short int year;

public:
	eWallet() {
		current_balance = 0;
		CVV = 0;
		number = 0;
		month = 0;
		year = 0;
	};
	// setter for the values of the attributes
	void set(short int CV, long long int num, int mon, int yr, double current) {
		current_balance = current;
		CVV = CV;
		number = num;
		month = mon;
		year = yr;
	}

	void withdraw(double cash) { // withdraw cash if current_balnace is enough
		if (current_balance - cash >= 0) { current_balance -= cash; }
		else {
			cout << "Your current balance is not enough!\n\n";
		}
	}

	void add_to_balance(double cash) {
		current_balance += cash;
	}
	// getters
	double get_balance() { return current_balance; }
	short int get_cvv() { return CVV; }
	long long get_number() { return number; }
	short int get_month() { return month; }
	short int get_year() { return year; }

	void display_current_balance() {
		cout << "Your current balance now is: " << current_balance << endl << endl;
	}

	void display_info() { // display whole info for the credit card (customer service part of the program)
		cout << endl;
		display_current_balance();
		cout << "CVV = " << CVV << endl << endl;
		cout << "Credit Card Number = " << number << endl << endl;
		cout << "Expiry date (month/year): " << month << "/" << year << endl << endl;
	}
};
