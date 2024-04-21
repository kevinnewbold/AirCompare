#include "listing.h"

Listing::Listing(std::string id, std::string name, std::string price,
                 std::string city, std::string state, std::string latitude, std::string longitude) {
    this->id = std::move(id);
    this->name = std::move(name);
    this->price = std::move(price);
    this->city = std::move(city);
    this->state = std::move(state);
    this->latitude = std::move(latitude);
    this->longitude = std::move(longitude);
}