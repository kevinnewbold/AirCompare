#pragma once
#include  <SFML/Graphics.hpp>
#include "listing.h"
#include "data.h"
#include "heapsort.h"
#include "mergesort.h"
#include <iostream>
#include <filesystem>

void setText(sf::Text& t, float x, float y, sf::Color c)
{
    sf::FloatRect textRect = t.getLocalBounds();
    t.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    t.setPosition(sf::Vector2f(x, y));
    t.setFillColor(c);
}

void setText(sf::Text& t, float x, float y)
{
    sf::FloatRect textRect = t.getLocalBounds();
    t.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    t.setPosition(sf::Vector2f(x, y));
}


class InteractableObj
{
private:
    
public:
    bool writable = false;
    std::string data;
    int maxDataLength = 0;
    virtual void OnClick()
    {
        std::cout << "click!";
    }
    virtual void Select()
    {

    }
    virtual void Deselect()
    {

    }
    virtual void Draw(sf::RenderWindow& window)
    {
        std::cout << "if you see me....run";
    }
    virtual sf::FloatRect GetGlobalBounds()
    {
        return sf::FloatRect();
    }
    virtual void SetData()
    {

    }
};

class Checkbox : public InteractableObj
{
public:
    sf::RectangleShape box;
    sf::Text label;
    bool selected = false;
    float width = 13.0f;
    float height = 13.0f;
    Checkbox(float xPos, float yPos, std::string labelText, sf::Font& font)
    {
        box.setSize(sf::Vector2f(width, height));
        box.setOutlineColor(sf::Color::Blue);
        box.setOutlineThickness(2);
        box.setPosition(xPos, yPos);
        sf::Text l(labelText, font, 15);
        label = l;
        box.setFillColor(sf::Color::Transparent);
        setText(label, xPos - 50, yPos + 10, sf::Color::Black);
    }
    void OnClick() override
    {
        selected = !selected;
        if (selected)
        {
            box.setFillColor(sf::Color::Blue);
        }
        else
            box.setFillColor(sf::Color::Transparent);
    }
    void Draw(sf::RenderWindow& window) override
    {
        window.draw(box);
        window.draw(label);
    }
    sf::FloatRect GetGlobalBounds() override
    {
        return box.getGlobalBounds();
    }
    void Select() override
    {
        box.setOutlineColor(sf::Color::Black);
    }
    void Deselect() override
    {
        box.setOutlineColor(sf::Color::Blue);
    }
};

class TextBox : public InteractableObj
{
public:
    sf::RectangleShape textBox;
    sf::Text label;
    sf::Text inside;
    int inputBoxWidth = 150;
    int inputBoxHeight = 20;

    TextBox(float xPos, float yPos, std::string labelText, sf::Font& font, int maxLength)
    {
        writable = true;
        maxDataLength = maxLength;
        textBox.setSize(sf::Vector2f(inputBoxWidth, inputBoxHeight));
        textBox.setOutlineColor(sf::Color::Black);
        textBox.setOutlineThickness(1);
        textBox.setPosition(xPos, yPos);
        sf::Text l(labelText, font, 15);
        label = l;
        sf::Text i("", font, 15);
        inside = i;
        setText(label, xPos - 50, yPos + 10, sf::Color::Black);
        setText(inside, xPos, yPos, sf::Color::Black);
    }
    void Draw(sf::RenderWindow& window) override
    {
        inside.setString(data);
        window.draw(textBox);
        window.draw(label);
        window.draw(inside);
    }
    sf::FloatRect GetGlobalBounds() override
    {
        return textBox.getGlobalBounds();
    }
    void Select() override
    {
        textBox.setOutlineColor(sf::Color::Red);
    }
    void Deselect() override
    {
        textBox.setOutlineColor(sf::Color::Black);
    }
    void SetData() override
    {
        inside.setString(data);
    }
};

class Result
{
public:
    sf::Text lineOne;
    sf::Text lineTwo;
    // Displays like:
    // 1. [listing name]
    //      Price: [price], Longitude: [latitude], Latitude: [latitude]
    Result(int place, Listing l, sf::Font& font, sf::Font& font2)
    {
        sf::Text one(std::to_string(place) + ". " + l.name, font2, 18);
        sf::Text two(std::string("Price: ") + l.price + std::string(", Longitude: ") + l.longitude + ", Latitude: " + l.latitude + ", " + l.city + ", " + l.state, font, 14);
        lineOne = one;
        lineTwo = two;
        setText(lineOne, 670.0f, 100 + place * 50, sf::Color::Black);
        setText(lineTwo, 690.0f, 100 + place * 50 + 20, sf::Color::Black);
    }
    void Draw(sf::RenderWindow& window)
    {
        window.draw(lineOne);
        window.draw(lineTwo);
    }
};

class RunButton : public InteractableObj
{
public:
    std::string price;
    std::string longitude;
    std::string latitude;
    std::string state;
    sf::RectangleShape box;
    sf::Text go;
    sf::Text error;
    bool running = false;

    RunButton(float xPos, float yPos, std::string text, sf::Font& font)
    {
        sf::Text g("GO!", font, 32);
        sf::Text e("", font, 16);
        go = g;
        error = e;
        setText(go, xPos, yPos, sf::Color::Red);
        setText(error, xPos - xPos / 1.6f, yPos + 28, sf::Color::Red);
    }
    void OnClick() override
    {
        std::vector<Listing> matches;
        // run sorts, get top 10 listings
        // display results on the right side
        if (!price.empty() && !longitude.empty() && !latitude.empty())
        {
            running = true;
            std::transform(state.begin(), state.end(), state.begin(), ::toupper);
            error.setString("Running...");
        }
        else
        {
            error.setString("Error: invalid input. Make sure longitude, latitude, \n and price are numbers and are filled out.");
        }

    }
    void DisplayMessage(std::string newMessage)
    {
        error.setString(newMessage);
    }
    void Draw(sf::RenderWindow& window) override
    {
        window.draw(go);
        window.draw(error);
    }
    sf::FloatRect GetGlobalBounds() override
    {
        return go.getGlobalBounds();
    }
};

void RunResults(std::vector<Listing>& listings, sf::Text& message, std::vector<Result>& results)
{

}


namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    // code from: https://stackoverflow.com/questions/70474834/i-cant-load-my-game-resources-into-sfml-with-cmake
    fs::path path(fs::canonical(argv[0]));
    fs::path font1 = path.parent_path() / "Roboto-Regular.ttf";
    fs::path font2 = path.parent_path() / "Roboto-Bold.ttf";
    fs::path data = path.parent_path() / "airbnb_listings_usa.csv";
    std::string font1Path{ font1.u8string() };
    std::string font2Path{ font2.u8string() };
    std::string listingsPath{ data.u8string() };

    // read data
    std::vector<std::pair<Listing, double>> listings = readData("airbnb_listings_usa.csv");

    int windowHeight = 800;
    int windowWidth = 1000;
    bool merge = true;
    std::vector<InteractableObj*> interactables;
    InteractableObj* selected = new InteractableObj();
    std::vector<Result> resultList;
    std::vector<std::string> rawStrings;
    

    // input variables
    std::string inputLatitude;
    std::string inputLongitude;
    std::string inputState;
    std::string inputPrice;

    // setup, text, fonts, etc
    sf::Font robotoBold;
    sf::Font robotoRegular;
    if (!robotoRegular.loadFromFile(font1Path))
        std::cout << "error: sheeeesh";
    robotoRegular.loadFromFile("Roboto-Regular.ttf");
    if (!robotoBold.loadFromFile(font1Path))
        std::cout << "error: sheeesh";
    robotoBold.loadFromFile(font2Path);

    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AirCompare");
    sf::Text title("AirCompare", robotoBold, 32);
    sf::Text price("Price: ", robotoRegular, 20);
    sf::Text location("Location: ", robotoRegular, 20);
    sf::Text results("Results: ", robotoBold, 32);
    setText(title, 150.0f, 100.0f, sf::Color::Black);
    setText(price, 150.0f, 200.0f, sf::Color::Black);
    setText(location, 150.0f, 300.0f, sf::Color::Black);
    setText(results, windowWidth / 1.50f, 100.0f, sf::Color::Black);

    sf::RectangleShape separationLine;
    separationLine.setSize(sf::Vector2f(1, windowHeight));
    separationLine.setOutlineColor(sf::Color::Black);
    separationLine.setOutlineThickness(1);
    separationLine.setFillColor(sf::Color::Black);
    separationLine.setPosition(windowWidth / 3.0f, 1);

    // input boxes
    TextBox priceBox(160.0f, 230.0f, "Dollars/night: ", robotoRegular, 15);
    TextBox longitudeBox(160.0f, 330.0f, "Longitude: ", robotoRegular, 15);
    TextBox latitudeBox(160.0f, 360.0f, "Latitude: ", robotoRegular, 15);
    TextBox stateBox(160.0f, 390.0f, "State abbrv.: ", robotoRegular, 2);
    interactables.emplace_back(&priceBox);
    interactables.emplace_back(&longitudeBox);
    interactables.emplace_back(&latitudeBox);
    interactables.emplace_back(&stateBox);

    // selection boxes

    Checkbox mergeSortBtn(170.0f, 470.0f, "Merge Sort?", robotoRegular);
    interactables.emplace_back(&mergeSortBtn);

    Checkbox heapSortBtn(170.0f, 500.0f, "Heap Sort?", robotoRegular);
    interactables.emplace_back(&heapSortBtn);

    // run
    RunButton runButton(160.0f, 700.0f, "GO!", robotoBold);
    interactables.emplace_back(&runButton);

    // starts the program out with a default of 'mergeSort'
    mergeSortBtn.OnClick();

    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }
            if (event.type == sf::Event::TextEntered && (std::isalpha(event.text.unicode) != 0 || std::isdigit(event.text.unicode) != 0 || event.text.unicode == '.' || event.text.unicode == '-'))
            {
                if (selected->writable)
                {
                    if (selected->data.length() < selected->maxDataLength)
                    {
                        selected->data += event.text.unicode;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Backspace)
                {
                    if (selected->writable)
                    {
                        if (selected->data.length() > 0)
                        {
                            selected->data.pop_back();
                            selected->SetData();
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    selected->Deselect();
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f pixelCoords = window.mapPixelToCoords(mousePos);
                    for (int i = 0; i < interactables.size(); i++)
                    {
                        if (interactables.at(i)->GetGlobalBounds().contains(pixelCoords))
                        {
                            interactables.at(i)->OnClick();
                            interactables.at(i)->Select();
                            selected = interactables.at(i);
                            if (interactables.at(i) == &mergeSortBtn)
                            {
                                if (heapSortBtn.selected)
                                {
                                    heapSortBtn.OnClick();
                                    merge = true;
                                }

                            }
                            if (interactables.at(i) == &heapSortBtn)
                            {
                                if (mergeSortBtn.selected)
                                {
                                    mergeSortBtn.OnClick();
                                    merge = false;
                                }
                            }
                            i = interactables.size();
                        }
                    }
                }
            }
        }

        if (runButton.running)
        {
            resultList.clear();
            runButton.running = false;
            runButton.Draw(window);
            auto start = std::chrono::high_resolution_clock::now();
            getDifferences(listings, std::stod(runButton.price), std::stod(runButton.longitude), std::stod(runButton.latitude));
            if (merge)
            {
                mergeSort(listings);
            }
            else
            {
                heapSort(listings, listings.size());
            }
            auto end = std::chrono::high_resolution_clock::now();
            float timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            runButton.DisplayMessage("Duration: " + std::to_string(timeTaken) + " milliseconds.");

            int count = 0;

            if (!runButton.state.empty())
            {
                while (resultList.size() < 10)
                {
                    if (listings.at(count).first.state == runButton.state)
                    {
                        Result r(resultList.size() + 1, listings.at(count).first, robotoRegular, robotoBold);
                        resultList.push_back(r);
                    }
                    count++;
                    if (count >= listings.size())
                        break;
                }
            }
            else
            {
                for (int i = 0; i < 10; i++)
                {
                    Result r(i + 1, listings.at(i).first, robotoRegular, robotoBold);
                    resultList.push_back(r);
                }
            }

        }

        window.clear(sf::Color::White);

        runButton.latitude = latitudeBox.data;
        runButton.longitude = longitudeBox.data;
        runButton.state = stateBox.data;
        runButton.price = priceBox.data;

        window.draw(title);
        window.draw(price);
        window.draw(location);
        window.draw(separationLine);
        window.draw(results);

        for (int i = 0; i < interactables.size(); i++)
        {
            interactables.at(i)->Draw(window);
        }
        for (int i = 0; i < resultList.size(); i++)
        {
            resultList.at(i).Draw(window);
        }
        window.display();
    }
    return 0;
}
