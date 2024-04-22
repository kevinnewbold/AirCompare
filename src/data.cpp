#include "data.h"


vector<pair<Listing, double>> readData(const string& fileName) {
    fstream file;
    file.open(fileName, ios::in);
    string row;
    string data;
    string data2;
    string temp;
    vector<pair<Listing,double>> differences;
    vector<string> dataset;
    bool comma = false;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return differences;
    }

    // first row doesn't contain data
    getline(file, row);

    int count = 0;

    while(getline(file, row)) {
        dataset.clear();
        stringstream s(row);
        while(getline(s, data, ',')) {
            comma = false;
            if (data[0] == '\"' && data[data.length() - 1] != '\"') {
                while(!comma) {
                    getline(s, data2, '\"');
                    data += data2;
                    getline(s, data2, ',');
                    if (data2.length() == 0 || data2[data2.length() - 1] == '\"') {
                        comma = true;
                    }
                }
            }
            dataset.push_back(data);
        }

        pair<Listing, double> airbnb;
        Listing listing = Listing(dataset.at(1), dataset.at(2), dataset.at(10),
                                  dataset.at(20), dataset.at(19),
                                  dataset.at(7), dataset.at(8));
        airbnb.first = listing;
        airbnb.second = 0;
        differences.push_back(airbnb);
        
    }
    return differences;
}

void getDifferences(vector<pair<Listing, double>>& listings, double price, double longitude, double latitude)
{
    for(int i = 0; i < listings.size(); i++)
    {
        double diff = (abs(latitude - stod(listings.at(i).first.latitude)) + abs(longitude - (stod(listings.at(i).first.longitude)))
            + abs(price - stod(listings.at(i).first.price)));
        listings.at(i).second = diff;
    }
}

void getDifferences(vector<pair<Listing, double>>& listings, double price, double longitude, double latitude, string state)
{

    for (int i = 0; i < listings.size(); i++)
    {
        double diff = (abs(latitude - stod(listings.at(i).first.latitude)) + abs(longitude - (stod(listings.at(i).first.longitude)))
            + abs(price - stod(listings.at(i).first.price)));
        listings.at(i).second = diff;
    }
}
