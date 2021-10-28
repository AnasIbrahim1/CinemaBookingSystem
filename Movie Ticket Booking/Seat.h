#pragma once
#include <iostream>
using namespace std;

class Seat
{
private:
	string seat_num;
	bool Availability;
	double Price;
public:
	Seat() {
		seat_num = ""; Availability = true;  Price = 100;
	}

	void make_VIP() { Price = 200; }

	double get_price() { return Price; }

	void setSeatNum(string x) {
		seat_num = x;
	}

	string getSeatNum() {
		return seat_num;
	}

	bool getAvail() {
		return Availability;
	}
	void reserve() {
		Availability = false;
	}
	void unreserve() {
		Availability = true;
	}
};

