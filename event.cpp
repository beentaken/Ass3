/**************************************************************************************************************
 *	Ben Wardrop 4413234
 *	CSCI262 Assignment 3
 *	Event.h
 *	last Modified: Ben 12/10/15
 **************************************************************************************************************/

#include "event.h"




std::ostream & operator << (std::ostream & os, Event & e)
{
	os << e.name << ':';
	switch(e.cde)
	{
		case Event::C:
			os << 'C';
			break;
		case Event::D:
			os << 'D';
			break;
		case Event::E:
			os << 'E';
			break;
		default:
			os << 'N';
	}
	os << ':';
	os << e.minimum << ':';
	os << e.maximum << ':';
	os << e.unit << ':';
	//os << e.mean << ':';
	//os << e.stdDev << ':';
	return os;
}

std::istream & operator >> (std::istream & in, Event & e)
{
	char tempCDE = 'N';
	getline(in,e.name,':');
	in >> tempCDE; in.ignore();
	in >> e.minimum; in.ignore();
	in >> e.maximum; in.ignore();
	getline(in,e.unit,':');
	in >> e.weight; in.ignore();
	//in >> e.mean; in.ignore();
	//in >> e.stdDev; in.ignore();
	switch(tempCDE)
	{
		case 'C':
			 e.cde = Event::C;
			break;
		case 'D':
			e.cde = Event::D;
			break;
		case 'E':
			e.cde = Event::E;
			break;
		default:
			e.cde = Event::N;
	}
	return in;
}

Event::Event()
{
	this -> cde		=	Event::N;
	this -> minimum =	0;
	this -> maximum =	0;
	this -> weight	=	0;
}

Event::Event(string in) //Construct Event from string
{
	fromString(in);
}

void Event::fromString(std::string input)	//Asign values from string
{
	std::stringstream ss;
	ss << input;
	ss >> *(this);
}

string toString()					//Create a string representation
{
	Event value;
	std::stringstream sin;
	sin << value;
	string ret = sin.str();
	return ret;
}
