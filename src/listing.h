#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Listing
{
public:
	Listing(std::string& listing);
	Listing() {}
	std::string id = "0";
	std::string name = "KevHouse";
	std::string hostID = "0";
	std::string hostName = "kev";
	std::string neighborhood = "KevLand";
	std::string neighborhoodGroup = "KevLand Central";
	float latitude = 111.11f;
	float longitude = 111.11f;
	// since there are only two room types, we'll distinguish by listing if it is an entire home or not.
	// if not entire home, it must be a private room.
	bool entireHome = false;
	int price = 111;
	int minimumNights = 30;
	// all info for reviews is not read from file, as that is useless for our project
	std::string state = "CA";
	std::string city = "Los Angeles";
};

class Listings
{
public:
	Listings(std::vector<std::string>& str);
	std::vector<Listing> listings = {};
	Listings() {}
};