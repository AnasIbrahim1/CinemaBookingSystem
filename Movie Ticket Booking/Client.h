#pragma once
#include <iostream>
#include <fstream>
#include "eWallet.h"
#include "Seat.h"
#include "Ticket.h"
using namespace std;

class Client
{
private:
	string email;
	string password;
	string first_name;
	string last_name;
	bool eWalletregistered;
	eWallet wallet;
	Ticket tickets[10]; // a user has multiple tickets
	int num_of_tickets;
public:
	Client() {
		email = ""; password = ""; first_name = ""; last_name = ""; 
		eWalletregistered = false; // because the client's eWallet is not registered by default
		num_of_tickets = 0;
	}
	// getters and setters
	void set_acc(string x, string y) {
		email = x; password = y;
	} 
	void set_email(string x) { email = x; }
	void set_password(string x) { password = x; }
	string get_email() { return email; }
	string get_password() { return password; }

	string get_firstname() { return first_name; }
	string get_lastname() { return last_name; }
	void set_firstname(string x) { first_name = x; }
	void set_lastname(string x) { last_name = x; }

	eWallet& get_ewallet() { return wallet; }
	// user.get_ewallet() (returns a wallet of the user that can be edited by the functions in the eWallet class)
	// it returns by reference to allow access to edit
	void registerewallet() { eWalletregistered = true; }
	void unregistereWallet() { eWalletregistered = false; }
	bool check_ewallet() { return eWalletregistered; }

	void increment_numtickets() { num_of_tickets++; }
	void decrement_numtickets() { num_of_tickets--; }
	void set_numtickets(int i) { num_of_tickets = i; }
	int get_numtickets() { return num_of_tickets; }

	Ticket& set_ticket(int index) { return tickets[index]; }
	// same as returning eWallet by reference
	// The function takes index to determine which of the tickets we want to edit in the array "tickets[10]"
	Ticket get_ticket(int index) { return tickets[index]; }

	// function displays a ticket of index "index"
	void displayticket(int index) { // index belongs to {0,1,2,...,9} which corresponds to 1st, 2nd,...,10th ticket
		// which corresponds to 996601,996602,...,996609,996610
		cout << endl;
		cout << "---------------------- Movie Reservation ----------------------\n";
		cout << "Ticket ID: 9966"; 
		if (index == 9) { cout << index + 1 << endl; } 
		// if the index is 9, we should display the ticket ID as 996610
		else { cout << "0" << index + 1 << endl; } 
		// Otherwise, we should display the ticket ID as "99660" + (the index + 1)
		// for instance, if the index is 6, (since we start at 0 in indeses) then the ticket ID 996607
		// which is equivalent to 99660 and cout << 7 = index + 1 = 6 + 1
		cout << "Client name: " << first_name << " " << last_name << endl;
		cout << "Client email: " << email << endl;
		cout << "Client chosen movie: " << tickets[index].getmovie().get_name() << endl;
		// each ticket has a movie attribute, each of which has a name, gotten by getters
		cout << "Movie timing: " << tickets[index].getmovie().get_timing() << endl;
		// same but a ticket also has a seat attribute
		cout << "Seat number: " << tickets[index].getseat().getSeatNum() << endl;
		cout << "Paid amount: " << tickets[index].get_paidamount() << endl;
		cout << "Payement Method: ";
		// if statement checks if payment method attribute of a ticket (which is of type char) is equal to 'c'
		// or to 'w'
		if (tickets[index].get_paymentmethod() == 'c') { cout << "by cash\n"; }
		else { cout << "by eWallet\n"; }
		cout << "---------------------------------------------------------------\n\n";
	}
};

