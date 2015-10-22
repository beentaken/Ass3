/**************************************************************************************************************
 *	Ben Wardrop 4413234
 *	CSCI262 Assignment 3
 *	Event.h
 *	last Modified: Ben 12/10/15
 **************************************************************************************************************/

#include "event.h"

Event::Event()
{
	this -> cde		=	Event::N;
	this -> minimum =	-1;
	this -> maximum =	-1;
	this -> weight	=	0;
}

Event::Event(string in) //Construct Event from string
{
	std::stringstream ss;
	ss >> *(this);
	//std::cerr << "fromString:		" << *(this) << std::endl;
}

string Event::toString()					//Create a string representation
{
	Event value;
	std::stringstream sin;
	sin << value;
	string ret = sin.str();
	return ret;
}
