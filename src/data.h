#pragma once
#include "listing.h"
#include <fstream>
#include <cmath>
using namespace std;

vector<pair<Listing, double>> readData(const string& fileName, double price, double latitude, double longitude);