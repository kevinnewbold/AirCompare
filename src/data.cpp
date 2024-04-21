vector<pair<Listing, double>> readData(const string& fileName, double price, double latitude, double longitude) {
    fstream file;
    file.open(fileName, ios::in);
    string row;
    string data;
    string data2;
    string temp;
    vector<pair<Listing,double>> differences;
    vector<string> dataset;
    bool comma;

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
                    if (data2[data2.length() - 1] == '\"' || data2.length() == 0) {
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
        double diff = (abs(latitude - stod(listing.latitude)) + abs(longitude - (stod(listing.longitude)))
                       + abs(price - stod(listing.price)));
        airbnb.first = listing;
        airbnb.second = diff;
        differences.push_back(airbnb);
        count++;
    }
    return differences;
}
