#ifndef _BUSLIB_H
#define _BUSLIB_H

#include <iostream>
#include <string>

using namespace std;

// struct declarartions;
struct busStop
{
	string busStopName;
	busStop* left;
	busStop* right; 


	busStop(string stop, busStop* l = NULL, busStop* r = NULL )
		:busStopName(stop), left(l), right(r)
	{
	}
	
};

struct busLine
{

	string busLineName;
	busLine* next;
	busStop* busStops;

	busLine(string line, busStop* stops = NULL ,busLine* n = NULL )
		:busLineName(line), next(n), busStops(stops)
	{
	}

};

class storage
{
	public:
		// constructers
		storage(busLine *h = NULL)
		{
			head = h;
		} 
		// functions;
		// storage functions creating the data;
		void add_stop(busStop * & stop_head, busStop *& tail, string stop_name);
		void add_line( busLine *&tail, string line_name, busStop* stops);
		// operation functions
		void printBusLines(); // it prints the whole data;
		void addBusLine(); // it adds a new BusLine with its BusStops;
		void addBusStop(); // it adds a new BusStop in an existing BusLine;
		void deleteBusLine(); // it deletes a BusLine;
		void deleteBusStop();// it deletes a busStop in a BusLine;
		void pathfinder(); // it find a path from a busStop to another one;
		void DeleteAll(); // it deletes the whole data;
	private: 
		busLine* head;

};


#endif