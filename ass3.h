/*****************************************************************
*	CSCI262 Assignment 3 
*	ass3.h
*	last Modified: zs 17/10/15
******************************************************************/

#ifndef _ASS3_H
#define _ASS3_H
#include <iostream>
#include <fstream>
#include <cmath> //sqrt(), log()
#include <cstdlib> //rand(), srand()
#include <vector>
#include <ctime> //time()
#include "event.h"

/*****************************************************************
*	Psuedocode for Initial Input & Activity Engine/Log Gen
*	
*	read in stats and events;
*		check for discrepencies 
*		ie(different events,mean is out of range(min, max)
*	
*	create objects with data;
*	create Array of event objects;
*	iterate number of days	
*		irterate through array;
*			randomise values according to
*			distrubution (normal distrib)
*			->save to log;
*	LOG FORMAT
*	
*	day:name:[CDE]:value:units
******************************************************************/

//Now non c++11 friendly
//Box muller method get rand num based on a normal distribution
double generate(double mean, double stddev, double min, double max)
{
	static double n2 = 0.0;
	static int n2_cached = 0;
	if (!n2_cached)
	{
		double x, y, r;
		do //choose a point x,y in the unit circle uniformly at random
		{
			x = 2.0*rand()/RAND_MAX - 1;
			y = 2.0*rand()/RAND_MAX - 1;

			r = x*x + y*y;
		}
		while (r == 0.0 || r > 1.0);
		{
			//apply box-muller transform on x and y
    			double d = sqrt(-2.0*log(r)/r);
    			double n1 = x*d;
			n2 = y*d;
			//scale and translate to our mean,stddev
			double result = n1*stddev + mean;
			n2_cached = 1;
			if(result > max || result < min)
				generate(mean,stddev,min,max);
			else
				return result;
		}
	}
	else
	{
		//cache result to reduce comp time
		n2_cached = 0;
		if((n2*stddev + mean) > max || (n2*stddev + mean) < min)
			generate(mean,stddev,min,max);
		else
			return n2*stddev + mean;
	}
}

/******************************************************************************
*
*	ACTIVITY ENGINE - LOG GENERATION	
*	Arguments: array of events, days, output stream
*	Uses 'Generator' class
*
*	Output: write to ostream in format
*
*	Day x
*	name:value:units
*		...
*
*******************************************************************************/

void activityEngine(Event event[], int days, std::ofstream & out)
{
	srand(time(NULL)); // for generate
	std::cout << "Log generation started...\n";
	out << event.size() << std::endl;
	for(int i=0;i<days;i++)
	{
		std::cout << "Day " << i << std::endl;
		out << "Day " << i << std::endl;
		for(int j=0;j<event.size();j++)
		{
			//check event type
			if(event[i].cde=='C')
			{
				double g = generate(event[i].mean, event[i].stdDev, event[i].minimum, event[i].maximum);
				out << event[i].name << ':' <<  g << ':' << event[i].units << std::endl;
			}
			else if(event[i].cde=='D')
			{
				double g = generate(event[i].mean, event[i].stdDev, event[i].minimum, 999999);
				out << event[i].name << ':' <<  g << ':' << event[i].units << std::endl;				
			}
			else if(event[i].cde=='E')
			{
				double g = generate(event[i].mean, event[i].stdDev, -999999, 999999);
				out << event[i].name << ':' <<  g << ':' << event[i].units << std::endl;
			}
			else
				out << "Error log entry" << std::endl;
		}
	}
	std::cout << "Completed.\n";
}

/******************************************************************************
*
*	ANALYSIS ENGINE	
*	Arguments: in file - intput stream, save output stream
*
*	read in -> calculate stats for each day -> save
*
*	Format for read in:
*	-No of types of events
*	-Day x
*	-name:value:units
*		...
*
*******************************************************************************/
struct Statistics
{
	public:
	std::string name;
	std::string units;
	double * values; // one index = one day
	double total;
	double mean;
	double stddev;
	Statistics(int n) {values = new double[n];}
	~Statistics {delete [] values;}
};

void analysisEngine(std::ifstream & in, std::ofstream & out, int days)
{
	std::cout << "\nAnalysis started...\n";
	int n; // = number of events
	in >> n; // get top line
	std::vector<Statistics> logs(n, Statistics(days));
	for(int i =0; i<days;i++)
	{
		string temp;
		int dayN;
		in >> temp >> dayN;
		if(temp!="Day" || dayN!= (i-1))
		{
			std::cout << "Error reading file\n"; 				return;
		}

		//iterate through events;
		for(int j = 0; j<n;j++)
		{
			getline(in,logs[j].name,':');
			in.ignore();
			getline(in,logs[j].values[i],':')
			in.ignore();
			getline(in,logs[j].units,':')
		}
	}
	//calculate;
	std::cout << "Calculating statistics...\n";
	out << n << std::endl;
	for(int i =0; i<n;i++)
	{
		logs[i].total = Total(logs[i].values,n);
		logs[i].mean = mean(logs[i].values,n);
		logs[i].stddev = stdDev(logs[i].values,n);
		//print to file
		//format: name:total:mean:stdDev based on Stats.txt
		out << logs[i].name << ":" << logs[i].total << ":" << logs[i].mean << ":" << logs[i].stddev << std::endl;
	}
	std::cout << "Saved to file\n";
		
}
//-----------  Stat functions  -------------
double stdDev(double data[], int n) //
{
	double mean=0.0, sum_deviation=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;

	for(int i=0; i<n;++i)
		sum_deviation+=(data[i]-mean)*(data[i]-mean);

	return sqrt(sum_deviation/n);           
}

double mean(double data[], int n)
{
	double mean=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;
	return mean;           
}


double Total(double data[],int n)
{	
	double total;
	for(int i=0; i<n;++i)
	{
		total+=data[i];
	}
	return total;
}
//-------------------------------------------
#endif