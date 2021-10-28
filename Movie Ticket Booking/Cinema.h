#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>
#include "Client.h"
#include "Movies.h"
using namespace std;

class Cinema
{
private:
	short int users_num = 0; // The number of users, loaded from "loaduseraccs()" function, is updated, and saved
								// at the end of the program
	Client users[100]; // array of users, maximum 100
	Movies movies[7]; // array of seven movies
	short int user_index; // user_index, known after login or creating an account
public:
	void beginprogram() {
		load_useraccs();
		setupmovies();
		loadeWallets();
		loadtickets();
		introduce();
		enter();
		wait();
		main_prog(main_menu());
	}

	void endprogram() {
		save_useraccs();
		saveeWallets();
		savetickets();
		for (int i = 0; i < 7; i++)
		{
			movies[i].saveseats();
		}
	}

	void introduce() { // Outputs the shape of the introduction to the program
		string y;
		string x = "Simple Movie Ticket Booking System";
		for (short int i = 0; i < x.length(); i++) {
			y += "_";
		}
		cout << " " << y << " " << "\n"
			<< "|" << x << "|" << "\n"
			<< "|" << y << "|" << "\n\n"
			<< "\t" << "Welcome Customer!\n\n";
	}

	void enter() { // login/creating an account system
		string ch;
		while (true) // validates input, if the input is valid it breaks, otherwise it continues the loop
		{
			cout << "Do you have an account?\n";
			cout << "Enter \"y\" for yes, and \"n\" for no: ";
			cin >> ch; // character which determines the user has an account or not
			if (ch == "y") { // login if yes
				user_index = login();
				if (user_index == -1) { cout << "The username/password is incorrect!\n\n"; }
				// login returns -1 if the user is not found, otherwise, it returns the index of the user
				// in the array of users
				else { break; }
			}
			else if (ch == "n") { // create an account if no
				cout << "Please create an account\n\n";
				create_acc();
				user_index = users_num - 1; // when he/she creates an account, the index in the array is the users_num
											// but less than by 1
				break; // break from the "while (true)" loop
			}
			else {
				cout << "Please enter a valid input!\n\n";
			}
		}
	}

	void wait() {
		string temp2; cout << "Please type and enter anything to continue: "; cin >> temp2;
	}

	void create_acc() {
		string a, b, b2; // a is email, b is password and b2 is password confirmation
		cout << "Email: ";
		cin >> a;
		while (true) // validates if password and confirmed password are equal, if they are it breaks
		{
			cout << "Password: ";
			cin >> b;
			cout << "Confirm password: ";
			cin >> b2;
			if (b2 != b) { cout << "Passwords do not match! Please try again.\n\n"; }
			else { break; } // break from the while loop when the passwords match
		} 
		users[users_num].set_acc(a, b); // sets email and password for the user
		cout << "First name: ";
		string fn; cin >> fn;
		users[users_num].set_firstname(fn); // sets first name
		cout << "Last name: ";
		string ln; cin >> ln;
		users[users_num].set_lastname(ln); // sets last name
		cout << "\nAccount successfully created!\n\n";
		users_num++;
	}

	short int login() {
		string a, b;
		cout << "Email: ";
		cin >> a;
		cout << "Password: ";
		cin >> b;
		for (short int i = 0; i < users_num; i++) {
			if (users[i].get_email() == a && users[i].get_password() == b) 
			{ 
				cout << "Successfully logged in!\n\n";
				return i; 
			}
		} 
		return -1;
	}

	short int main_menu() {
		system("cls");
		cout << "                     Welcome to our Cinema, " 
			 << users[user_index].get_firstname() << " " << users[user_index].get_lastname() << "!\n"
			 << "_________________________________________________________________________\n\n"
			 << " (1) Display available movies\n"
			 << " (2) Book a new ticket\n"
			 << " (3) Customer service\n"
		 	 << " (4) Return to login menu\n"
	 		 << " (5) Register/re-register Electronic Wallet (Visa, MasterCard, ... etc)\n"
			 << " (6) End the program\n\n";
		string menu;
		while (true) { // validate input
			cout << "Choose a number from 1 to 6: (depending on the need from the menu above) ";
			cin >> menu;
			if (menu.length() > 1 || menu[0] > '6' || menu[0] < '1') { 
				// check if menu is a string of length more than 1 or is a character not between '1'
				// and '6'
				cout << "Please enter a valid input!\n\n"; 
			}
			else {
				return menu[0] - '1' + 1; 
				// menu belongs to {"1","2",...,"6"}
				// menu[0] belongs to {'1','2','3',...,'6'}
				// menu[0] - '1' belongs to {0,1,2,...,5}
				// menu[0] - '1' + 1 belongs to {1,2,3,...,6}
				break;
			}
		}
	}

	void main_prog(int a) {
		switch (a) {
		case 1:
			display_movies();
			break;
		case 2:
			book();
			break;
		case 3:
			cs_check(customer_service_main());
			break;
		case 4:
			system("cls");
			introduce();
			enter();
			wait();
			main_prog(main_menu());
			break;
		case 5:
			registereWallet();
			break;
		case 6:
			endprogram();
			break;
		}
	}

	void display_movies() {
		system("cls");
		displaymovies();
		cout << "Type and enter the number of the movie or \"mainmenu\" if you want to return to the main menu: ";
		string input; cin >> input;
		while (true) {
			if (input == "mainmenu") {
				main_prog(main_menu());
				break;
			}
			else if (input.length() == 1 && input[0] >= '1' && input[0] <= '7')
			{
				short int index = input[0] - '1'; // return the index of the chosen movie
				// input[0] belongs to {'1','2',...,'7'}
				// input[0] - '1' belongs to {0,1,2,..,6}
				movies[index].display_seats();
				cout << "Timing of this movie is: " << movies[index].get_timing() << endl << endl;
				while (true) {
					cout << "Type and enter \"m\" if you want to choose another movie,\n"
						<< "or \"mainmenu\" if you want to return to the main menu: ";
					string input2;
					cin >> input2;
					if (input2 == "m") { display_movies(); break; }
					else if (input2 == "mainmenu") {
						main_prog(main_menu());
						break;
					}
					else { cout << "Please enter a valid input!\n"; }
				}
				break;
			}
			else {
				cout << "Please enter a valid input!\n\n";
				display_movies(); break;
			}
		}
	}

	void displaymovies() {
		system("cls");
		for (int i = 0; i < 7; i++) {
			cout << "(" << i + 1 << ") " << movies[i].get_name() << "\n";
		}
		cout << "\n100 L.E for a normal seat in each, 200 for a VIP seat\n";
		cout << "Note: when booking a ticket, you're going to need the number of the movie\n\n";
	}

	void book() {
		system("cls");
		cout << "If at any time you want to return to the main menu,"
			<< " type and enter \"mainmenu\"\n\n";
		cout << "Enter the number of the movie (available in the movies menu): ";
		string movienum;
		cin >> movienum;
		int mn = 0;
		if (movienum.length() == 1 && movienum[0] >= 49 && movienum[0] <= 55) {
			mn = movienum[0] - 48;
			cout << "You chose the movie: " << movies[mn - 1].get_name() << endl;
			cout << "Here are the seats for this movie: \n";
			movies[mn - 1].display_seats();
			book2(mn);
		}
		else if (movienum == "mainmenu") { main_prog(main_menu()); }
		else {
			cout << "Please enter a valid input!\n\n";
			wait();
			book();
		}
	}

	void book2(int mn) {
		cout << "Choose a seat (enter the seat number): ";
		string seatnum;
		cin >> seatnum;
		if (seatnum.length() != 2 || seatnum[0] < 65 || seatnum[0] > 73 || seatnum[1] < 49 || seatnum[1] > 55) {
			if (seatnum == "mainmenu") { main_prog(main_menu()); }
			else {
				cout << "Please enter a valid input!\n\n";
				book2(mn);
			}
		}
		else if (!movies[mn - 1].get_seat(seatnum).getAvail()) {
			cout << "This seat isn't available!\n\n";
			book2(mn);
		}
		else {
			book3(mn, seatnum);
		}
	}

	void book3(int mn, string seatnum) {
		string pay;
		int tempPrice;
		if (users[user_index].get_numtickets() >= 5) {
			cout << "You're a special client! You've booked more than 5 tickets! You'll get 20% discount.\n\n";
			tempPrice = ((movies[mn - 1].get_seat(seatnum).get_price() * 8) / 10);
		}
		else {
			tempPrice = movies[mn - 1].get_seat(seatnum).get_price();
		}
		cout << "Note: after this step, you cannot go back to the main menu except after the ticket is booked.\n";
		cout << "Payment Method (W = by Credit Card, C = by Cash): ";
		cin >> pay;
		if (pay.length() != 1 && pay[0] != 'W' && pay[0] != 'C') {
			if (pay == "mainmenu") { main_prog(main_menu()); }
			else {
				cout << "Please enter a valid input\n\n";
				book3(mn, seatnum);
			}
		}
		else {
			if (pay[0] == 'W') {
				if (users[user_index].check_ewallet()) {
					cout << "Ticket successfully booked!\n";
					users[user_index].get_ewallet().withdraw(tempPrice);
					cout << "\nPrice is: " << tempPrice << endl;
					users[user_index].get_ewallet().display_current_balance();
					movies[mn - 1].reserve_seat(seatnum);
					users[user_index].set_ticket(users[user_index].get_numtickets()).setmovie(movies[mn - 1], mn - 1);
					users[user_index].set_ticket(users[user_index].get_numtickets()).setseat(seatnum);
					users[user_index].set_ticket(users[user_index].get_numtickets()).set_paymentmethod('w');
					users[user_index].set_ticket(users[user_index].get_numtickets()).set_paidamount(tempPrice);
					users[user_index].displayticket(users[user_index].get_numtickets());
					users[user_index].increment_numtickets();
					wait();
					main_prog(main_menu());

				}
				else {
					cout << "You don't have an eWallet registered in our database!\n\n";
					cout << "To register, go back to the main menu\n\n";
					book3(mn, seatnum);
				}
			}
			else if (pay[0] == 'C') {
				cout << "Ticket successfully booked!\n";
				movies[mn - 1].reserve_seat(seatnum);
				cout << "\nPrice is: " << tempPrice << endl;
				users[user_index].set_ticket(users[user_index].get_numtickets()).setmovie(movies[mn - 1], mn - 1);
				users[user_index].set_ticket(users[user_index].get_numtickets()).setseat(seatnum);
				users[user_index].set_ticket(users[user_index].get_numtickets()).set_paymentmethod('c');
				users[user_index].set_ticket(users[user_index].get_numtickets()).set_paidamount(tempPrice);
				users[user_index].displayticket(users[user_index].get_numtickets());
				users[user_index].increment_numtickets();
				wait();
				main_prog(main_menu());
			}
			else {
				cout << "Please enter a valid input\n\n";
				book3(mn, seatnum);
			}
		}
	}

	int customer_service_main() {
		system("cls");
		cout << "What do need help with? :)\n\n"
			<< "(1) View currently booked tickets\n"
			<< "(2) Display credit card information\n"
			<< "(3) Unbook a ticket (ticket ID needed)\n"
			<< "(4) Change Email/Password\n"
			<< "(5) Get back to main menu\n\n";
		string csmenu;
		while (true) {
			cout << "Choose a number from 1 to 5 (depending on the need from the menu above): ";
			cin >> csmenu;
			if (csmenu.length() > 1 || csmenu[0] > '5' || csmenu[0] < '1') {
				cout << "Please enter a valid input!\n\n";
			}
			else {
				return (csmenu[0] - '1' + 1);
			}
		}
	}

	void cs_check(int a) {
		switch (a) {
		case 1:
			cs_1();
			break;
		case 2:
			cs_2();
			break;
		case 3:
			cs_3();
			break;
		case 4:
			cs_4();
			break;
		case 5:
			main_prog(main_menu());
			break;
		}
	}

	void cs_1() {
		system("cls");
		cout << "Welcome, "
			<< users[user_index].get_firstname() << " " << users[user_index].get_lastname() << "!\n\n";
		if (users[user_index].get_numtickets()) {
			cout << "Here are your currently booked tickets: \n";
			for (int i = 0; i < users[user_index].get_numtickets(); i++) {
				users[user_index].displayticket(i);
			}
			wait();
			cs_check(customer_service_main());
		}
		else {
			cout << "You currently don't have any booked tickets.\n\n";
			wait();
			cs_check(customer_service_main());
		}
	}

	void cs_2() {
		system("cls");
		cout << "Welcome, "
			<< users[user_index].get_firstname() << " " << users[user_index].get_lastname() << "!\n\n";
		users[user_index].get_ewallet().display_info();
		wait();
		cs_check(customer_service_main());
	}

	void cs_3() {
		system("cls");
		cout << "Welcome, "
			<< users[user_index].get_firstname() << " " << users[user_index].get_lastname() << "!\n\n";
		cout << "If you want to return to the main customer service menu, enter \"mainmenu\" \n"
			<< "If you enter the ticket ID, you've unbooked the ticket.\n\n";
		if (users[user_index].get_numtickets()) {

			while (true) {
				cout << "Enter Ticket ID: ";
				string ticketID; cin >> ticketID;
				bool tb = false;
				// The following after the "||" are unwanted conditions of input
				// if anyone of them is true, the variable tb becomes true, or else it stays false
				tb = tb || ticketID.length() != 6;
				tb = tb || ticketID.substr(0, 4) != "9966";
				tb = tb || (ticketID[4] != '0' && ticketID[4] != '1');
				tb = tb || ticketID[5] > '9';
				tb = tb || ticketID[5] < '0';
				tb = tb || ticketID.substr(4, 6) == "00";
				// If tb stays false (i.e. none of the unwanted conditions is true), this if statement won't execute.
				if (tb) {
					cout << "Please enter a valid input!\n\n";
				}
				else {
					if (ticketID.substr(4, 6) == "10") {
						if (users[user_index].get_ticket(9).get_paymentmethod() == 'w') {
							double tempo = users[user_index].get_ticket(9).get_paidamount();
							users[user_index].get_ewallet().add_to_balance(tempo);
						}
						string snum = users[user_index].get_ticket(9).getseat().getSeatNum();
						movies[users[user_index].get_ticket(9).get_movieindex()].unreserve_seat(snum);
						users[user_index].decrement_numtickets();
						break;
					}
					else {
						int index = ticketID[5] - '1';
						if (index + 1 > users[user_index].get_numtickets()) {
							cout << "Please enter a valid input!\n\n";
						}
						else if (index + 1 == users[user_index].get_numtickets()) {
							if (users[user_index].get_ticket(index).get_paymentmethod() == 'w') {
								double tempo = users[user_index].get_ticket(index).get_paidamount();
								users[user_index].get_ewallet().add_to_balance(tempo);
							}
							string snum2 = users[user_index].get_ticket(index).getseat().getSeatNum();
							movies[users[user_index].get_ticket(index).get_movieindex()].unreserve_seat(snum2);
							users[user_index].decrement_numtickets();
							break;
						}
						else {
							string snum3 = users[user_index].get_ticket(index).getseat().getSeatNum();
							movies[users[user_index].get_ticket(index).get_movieindex()].unreserve_seat(snum3);
							if (users[user_index].get_ticket(index).get_paymentmethod() == 'w') {
								double tempo = users[user_index].get_ticket(index).get_paidamount();
								users[user_index].get_ewallet().add_to_balance(tempo);
							}
							for (int i = index; i < users[user_index].get_numtickets() - 1; i++) {
								int ind = users[user_index].get_ticket(i + 1).get_movieindex();
								users[user_index].set_ticket(i).setmovie(users[user_index].get_ticket(i + 1).getmovie(), ind);
								users[user_index].set_ticket(i).setseat(users[user_index].get_ticket(i + 1).getseat().getSeatNum());
								users[user_index].set_ticket(i).set_paidamount(users[user_index].get_ticket(i + 1).get_paidamount());
								users[user_index].set_ticket(i).set_paymentmethod(users[user_index].get_ticket(i + 1).get_paymentmethod());
							}
							users[user_index].decrement_numtickets();
							break;
						}
					}
				}
			}
			cout << "\nTicket successfully unbooked!\n\n";
			wait();
			cs_check(customer_service_main());
		}
		else {
			cout << "You currently don't have any booked tickets.\n\n";
			wait();
			cs_check(customer_service_main());
		}
	}

	void cs_4() {
		system("cls");
		cout << "Welcome, "
			<< users[user_index].get_firstname() << " " << users[user_index].get_lastname() << "!\n\n";
		cout << "What do you want to change, email or password?\n\n";
		cout << "Note: if you proceed from this step, you have to change email or password and cannot go back to"
			<< " the main customer service menu\n\n";
		cout << "Enter \"e\" for email or \"p\" for password or \"m\" for main customer service menu: ";
		string inp; cin >> inp;
		while (true) {
			if (inp == "e") {
				cout << "Enter the new email: ";
				string em; cin >> em;
				users[user_index].set_email(em);
				cout << "Email successfully changed!\n\n";
				wait();
				break;
			}
			else if (inp == "p") {
				cout << "Enter the new password: ";
				string pa; cin >> pa;
				users[user_index].set_password(pa);
				cout << "Password successfully changed!\n\n";
				wait();
				break;
			}
			else if (inp == "m") {
				break;
			}
			else {
				cout << "\nPlease enter a valid input\n\n";
			}
		}
		cs_check(customer_service_main());
	}

	void setupmovies() {
		movies[0].set_name("The Avengers - Endgame");
		movies[1].set_name("The Conjuring");
		movies[2].set_name("The Amazing Spiderman");
		movies[3].set_name("The LEGO Batman");
		movies[4].set_name("Batman Begins");
		movies[5].set_name("Titanic");
		movies[6].set_name("Avatar");
		for (int i = 0; i < 7; i++) // Iterate seven times to load each movies' seats availability
									// and setup the seat numbers
		{
			movies[i].loadseats();
		}
		movies[0].set_timing("Friday January 1st: from 5 PM to 8 PM");
		movies[2].set_timing("Friday January 1st: from 8 PM to 11 PM");
		movies[1].set_timing("Friday January 1st: from 11 PM to 1 AM");
		movies[3].set_timing("Saturday January 2nd: from 5 PM to 8 PM");
		movies[4].set_timing("Saturday January 2nd: from 8 PM to 11 PM");
		movies[5].set_timing("Sunday January 3rd: from 5 PM to 8 PM");
		movies[6].set_timing("Sunday January 3rd: from 8 PM to 11 PM");
	}

	void registereWallet() {
		system("cls");
		cout << "Note: if you confirmed that you want to proceed with the registration, "
			 << "you cannot go back to the main menu until after the registration is done.\n\n";
		cout << "Do you want to proceed with registration?\n";
		while (true) {
			cout << "Enter \"y\" for yes, and \"n\" for no: ";
			string c;
			cin >> c;
			if (c == "y" || c == "Y") {
				cout << endl;
				cout << "--------------------------------------------------------\n";
				cout << "Current balance in the electronic wallet: ";
				double balance; cin >> balance;
				cout << "\nCredit card number: ";
				long long num; cin >> num;
				cout << "\nCVV: ";
				short int cvv; cin >> cvv;
				cout << "\nExpiry date month: ";
				short int mon; cin >> mon;
				cout << "\nExpiry date year: ";
				short int yr; cin >> yr;
				cout << "Credit card successfully registered!\n\n";
				users[user_index].get_ewallet().set(cvv, num, mon, yr, balance);
				users[user_index].registerewallet();
				wait();
				main_prog(main_menu()); break;
			}
			else if (c == "n" || c == "N") {
				wait();
				main_prog(main_menu()); break;
			}
			else {
				cout << "Please enter a valid input!\n\n";
			}
		}
	}

	void saveeWallets() {
		ofstream str;
		str.open("eWallets.txt");
		for (int i = 0; i < users_num; i++) {
			// balance, number, cvv, month, year, registration condition
			str << users[i].get_ewallet().get_balance() << "\t";
			str << users[i].get_ewallet().get_number() << "\t";
			str << users[i].get_ewallet().get_cvv() << "\t";
			str << users[i].get_ewallet().get_month() << "\t";
			str << users[i].get_ewallet().get_year() << "\t";
			str << users[i].check_ewallet() << "\n";
		}
		str.close();
	}

	void loadeWallets() { // loads eWallets info
		ifstream str;
		str.open("eWallets.txt");
		double balance;
		long long num;
		short int cvv, mon, yr;
		bool tempbool; // temporary boolean for storing if the user has registered the eWallet or not
		for (int i = 0; i < users_num; i++) {
			str >> balance >> num >> cvv >> mon >> yr >> tempbool;
			users[i].get_ewallet().set(cvv, num, mon, yr, balance);
			// because the get_ewallet function returns by reference, we can edit the values of
			// the attributes for each user
			if (tempbool) { users[i].registerewallet(); } // if tempbool was true meaning the eWallet
			// was registered, it registers eWallet using the functions
			else { users[i].unregistereWallet(); }
		}
		str.close();
	}

	void save_useraccs() {
		ofstream str;
		str.open("Useraccounts.txt");
		str << users_num << "\n";
		for (short int i = 0; i < users_num; i++) {
			str << users[i].get_email() << "\t" << users[i].get_password() << "\t"
				<< users[i].get_firstname() << "\t" << users[i].get_lastname() << "\n";
		}
		str.close();
	}

	void load_useraccs() {
		ifstream str;
		str.open("Useraccounts.txt");
		str >> users_num; // input the number of users
		string e, p, fn, ln; // email, password, first name, last name
		for (int i = 0; i < users_num; i++) {
			str >> e >> p >> fn >> ln;
			users[i].set_acc(e, p); // set account, email to e and password to p
			users[i].set_firstname(fn);
			users[i].set_lastname(ln);
		}
		str.close();
	}

	void savetickets() {
		ofstream str;
		str.open("Tickets.txt");
		int temp;
		for (int i = 0; i < users_num; i++) {
			temp = users[i].get_numtickets(); // temp is the number of tickets
			str << temp << endl;
			for (int j = 0; j < temp; j++) {
				str << users[i].get_ticket(j).get_movieindex() << "\t"
					<< users[i].get_ticket(j).getseat().getSeatNum() << "\t"
					<< users[i].get_ticket(j).get_paymentmethod() << "\t"
					<< users[i].get_ticket(j).get_paidamount() << endl;
			}
		}
		str.close();
	}

	void loadtickets() {
		ifstream str;
		str.open("Tickets.txt");
		int temp;
		int movieindex;
		string seat;
		char pm;
		double pa;
		for (int i = 0; i < users_num; i++) { // loop to go over each user
			str >> temp; // temp is the number of tickets
			users[i].set_numtickets(temp);
			for (int j = 0; j < temp; j++) { // loop to go over each ticket each user has according to temp
											 // which is the number of tickets
				str >> movieindex;
				str >> seat;
				str >> pm;
				str >> pa;
				users[i].set_ticket(j).setmovie(movies[movieindex], movieindex);
				users[i].set_ticket(j).setseat(seat);
				users[i].set_ticket(j).set_paymentmethod(pm);
				users[i].set_ticket(j).set_paidamount(pa);
			}
		}
		str.close();
	}
};

