#pragma once
#include <iostream>
#include "Movies.h"
using namespace std;

class Ticket
{
private:
	Movies movie;
	Seat seat;
	int movieindex;
	char payment_method;
	double paid_amount;
public:
	Movies getmovie() { return movie; }
	void setmovie(Movies x, int i) { // set movie index and the movie
		movie = x; 
		movieindex = i;
	}

	Seat getseat() { return seat; }
	void setseat(string s_num) {
		seat = movie.get_seat(s_num);
	}

	void set_paymentmethod(char c) { payment_method = c; } // 'c' or 'w' for cash or wallet respectively
	char get_paymentmethod() { return payment_method; }

	void set_paidamount(double pa) { paid_amount = pa; }
	double get_paidamount() { return paid_amount; }

	int get_movieindex() { return movieindex; } 
	// movies[.....(ticket).get_movieindex] which returns a movie
};

