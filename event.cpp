/**************************************************************************************************************
 *	Ben Wardrop 4413234
 *	CSCI262 Assignment 3
 *	Event.h
 *	last Modified: Ben 26/10/15
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
	if(e.minimum >= 0) os << e.minimum; os << ':';
	if(e.maximum >= 0) os << e.minimum; os << ':';
	os << e.unit << ':';
	os << e.weight << ':';
	//os << e.mean << ':';
	//os << e.stdDev << ':';
	return os;
}

std::istream & operator >> (std::istream & in, Event & e)
{
	char tempCDE = 'N';
	getline(in,e.name,':');
	in >> tempCDE; in.ignore();
	if(in.peek() == ':')
	{
		in.ignore();
	}
	else
	{
		in >> e.minimum;
		in.clear();
		in.ignore();
	}
	if(in.peek() == ':')
	{
		in.ignore();
	}
	else
	{
		in >> e.maximum;
		in.ignore();
		in.clear();
	}
	if(in.peek() == ':')
	{
		in.ignore();
	}
	else
	{
		getline(in,e.unit,':');
	}
	if(in.peek() == ':')
	{
		in.ignore();
	}
	else
	{
		in >> e.weight;
		in.ignore();
		in.clear();
	}
	//in >> e.mean; in.ignore();
	//in >> e.stdDev; in.ignore();
	in.ignore();

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
	this -> minimum =	-1;
	this -> maximum =	-1;
	this -> weight	=	0;
}

Event::Event(string in) //Construct Event from string
{
	fromString(in);
}

char Event::getCDE()
{
	char ret;
	switch(this->cde)
	{
		case Event::C:
			ret = 'C';
			break;
		case Event::D:
			ret = 'D';
			break;
		case Event::E:
			ret = 'E';
			break;
		default:
			ret = 'N';
	}
	return ret;
}

void Event::setCDE(char cde)
{
	switch(cde)
	{
		case 'C':
		case 'c':
			 this->cde = Event::C;
			break;
		case 'D':
		case 'd':
			this->cde = Event::D;
			break;
		case 'E':
		case 'e':
			this->cde = Event::E;
			break;
		default:
			this->cde = Event::N;
	}
}

void Event::fromString(std::string input)	//Asign values from string
{
	std::stringstream ss;
	ss << input;
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

bool Event::readEvents(std::istream& ins, int& size, Event*& e)
{
	string s;
	ins >> size;
	ins.ignore(2,'\n');
	ins.clear();
	e = new Event[size];
	for(int i = 0; i < size; i++)
	{
		getline(ins,s,'\n');
		//std::cerr << "string:		" << s << std::endl;
		e[i].fromString(s);
		//std::cerr <<"value:		" << e[i] << std::endl;
	}
	return true;
}

bool Event::readStats(std::istream& ins, int& size, Event*& e)
{
	int n = 0;
	string s;
	ins >> n;
	if(n != size)
	{
		std::cerr << "Error: Stats and Events have differing sizes" << std::endl;
		std::cerr << "did you provide the wrong files?" << std::endl;
	}
	ins.ignore(2,'\n');
	ins.clear();
	for(int i = 0; i < size; i++)
	{
		getline(ins,s,'\n');
		e[i].statString(s);
	}
	return true;
}

void Event::statString(string stats)
{
	std::stringstream ss;
	ss << stats;
	getline(ss,stats,':');
	ss >> this->mean;
	//std::cerr << this->mean;
	ss.ignore(2,':');
	ss.clear();
	ss << stats;
	ss >>this->stdDevation;
	//std::cerr << this->stdDevation << std::endl;
}

/*
Log::Log()
{
	size = 0;
}

Log(std::istream& in, string eventFile, string statsFile);
{
	in >> size;
	std:: cerr << size;
	in.ignore();
	Event temp;
	for(int i = 0; i < size; i++)
	{
		in >> temp;
		set.push_back(temp);
		//std:: cerr << set[i] << std::endl;
	}
}

void Log::print(std::ostream& os)
{
	for(int i = 0; i < size; ++i)
	{
		os << set[i];
	}
}
*/

