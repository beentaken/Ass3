/**************************************************************************************************************
 *	Ben Wardrop 4413234
 *	CSCI262 Assignment 3 
 *	Event.h
 *	last Modified: Ben 12/10/15
 **************************************************************************************************************/

#include "event.h"

Event::Event()
{
	this -> cde		=	static_cast<CDE>(3); // N as part of CDE isn't regognized, what a pain.
	this -> minimum =	0;
	this -> maximum =	0;
	this -> weight	=	0;
}

Event::Event(string in) //Construct Event from string
{
	std::stringstream ss;
	ss << in;
	
	//working on directing the data from the string stream into the class
}

void	fromString(string input)	//Asign values from string
{

}
string	toString()					//Create a string representation
{

}
