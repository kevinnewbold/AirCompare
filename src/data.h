#pragma once
#include "listing.h"
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<pair<Listing, double>> readData(const string& fileName);
void getDifferences(vector<pair<Listing, double>>& listings, double price, double longitude, double latitude);