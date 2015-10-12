/**************************************************************************************************************
 *	Ben Wardrop 4413234
 *	CSCI262 Assignment 3 
 *	Event.h
 *	last Modified: Ben 12/10/15
 *
 *	In order to process the logs we need a structure to read into.
 *	That is our Event class.
 *
 *	Each event has a type C, D or E
 * 	C and D represent continuous and discrete respectively. Discrete events must take integer values and occur
 *	one at a time, continuous events don’t need to take an integer value and an occurance of that event may
 *	be of any value. E events are discrete events that may have a value other than one associated with them.
 *
 *	Discrete events and the weights cannot be negetive though E events can be
 *	Continuous events need be recorded to two decimal places
 *
 * 	Event has
 *		1. Name, can be a compund word		
 *		2. CDE
 *		3. Minimum
 * 		4. Maximum
 * 		5. Unit
 * 		6. Weight 
 * 
 * 	some examples
 *
 *	Logins:D:0:::2:
 * 	Name	Logins
 *	CDE		D
 *	Minimum	0
 *	Maximum	NA
 *	Unit	NA
 *	Weight	2
 *
 *	Time online:C:0:1440:minutes:3:
 * 	Name	Time online
 *	CDE		C
 *	Minimum	0
 *	Maximum	1440
 *	Unit	minutes
 *	Weight	3
 *
 *  Money made:E:::cents:2:   This text came straight from the file, does money have 1/1 cent to weight?
 * 	Name	Money Made
 *	CDE		E
 *	Minimum	NA
 *	Maximum	NA
 *	Unit	cents
 *	Weight	2
 *
 *  Emails sent:D:0:::1:
 * 	Name	Emails sent
 *	CDE		D
 *	Minimum	0
 *	Maximum	NA
 *	Unit	NA
 *	Weight	1
 *
 *	Download volume:E:0::bits:1:
 * 	Name	Download volume
 *	CDE		E
 *	Minimum	0
 *	Maximum	NA
 *	Unit	bits
 *	Weight	1
 *******************************************************************************************************/
#ifndef _EVENT_H
#define _EVENT_H
#include <string>
#include <iostream>
#include <sstream>

using std::string;
	

class Event
{
	
	public:
		enum CDE {C, D, E, N}; //Continous, Descrete, E?, Null			

		Event();
		Event(string in); //Construct Event from string
		~Event();

		string	getName()			{return this->name;}
		void 	setName(string n)	{this->name = n;}
		float	getmin()			{return this->minimum;}
		void	setmin(float m)		{this->minimum = m;}
		float	getmax()			{return this->maximum;}
		void	setmax(float m)		{this->maximum = m;}
		string 	getUnit()			{return this->unit;}
		void	setUnit(string u)	{this->unit = u;}
		string 	getWeight()			{return this->unit;}
		void	setWeight(int w)	{this->weight = w;}	
		
		void	fromString(string input);	//Asign values from string
		string	toString(); 				//Create a string representation
	private:
		string name;
		CDE		cde;
		float	minimum;
		float	maximum;
		string	unit;
		int		weight;
};

#endif //_EVENT_H
