#pragma once
#include "listing.h"


Listing::Listing(std::string& listing)
{
	std::vector<std::string> vals;
	std::stringstream ss(listing);
	std::string s;
	while (getline(ss, s, ','))
	{
		vals.push_back(s);
	}
	id = vals.at(1);
	name = vals.at(2);
	hostID = vals.at(3);
	hostName = vals.at(4);
	neighborhood = vals.at(5);
	neighborhoodGroup = vals.at(6);
	latitude = stof(vals.at(7));
	longitude = stof(vals.at(8));
	entireHome = (vals.at(9) == "Entire home/apt") ? true : false;
	int price = stoi(vals.at(10));
	int minimumNights = stoi(vals.at(11));
	state = vals.at(19);
	city = vals.at(20);
}

Listings::Listings(std::vector<std::string>& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		Listing l(str.at(i));
		listings.push_back(l);
	}
}