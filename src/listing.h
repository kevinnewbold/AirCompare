#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Listing
{
public:
    Listing() = default;
    explicit Listing(std::string id, std::string name, std::string price,
        std::string city, std::string state, std::string latitude, std::string longitude);
    std::string id;
    std::string name;
    std::string latitude;
    std::string longitude;
    std::string price;
    std::string state;
    std::string city;
    // Not everything is read from the file as some data is useless for our purposes
};
