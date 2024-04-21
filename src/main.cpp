#pragma once
#include  <SFML/Graphics.hpp>
#include "listing.h"
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
    Result(int place, Listing l, sf::Font& font)
    {
        std::cout << place + ". " + l.name;
        sf::Text one(std::to_string(place) + ". " + l.name, font, 16);
        sf::Text two(std::string("Price: ") + std::to_string(l.price) + std::string(", Longitude: ") + std::to_string(l.longitude) + ", Latitude: " + std::to_string(l.latitude) + ", " + l.city + ", " + l.state, font, 14);
        lineOne = one;
        lineTwo = two;
        setText(lineOne, 670.0f, 100 + place * 50, sf::Color::Black);
        setText(lineTwo, 690.0f, 100 + place * 50 + 18, sf::Color::Black);
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
    fs::path path(fs::canonical(argv[0]));
    fs::path font1 = path.parent_path() / "Roboto-Regular.ttf";
    fs::path font = path.parent_path() / "Roboto-Bold.ttf";
    std::string font1Path{ path.u8string() };
    std::string font2Path{ path.u8string() };

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
    if (!robotoBold.loadFromFile("Roboto-Bold.ttf"))
        std::cout << "error: sheeesh";
    robotoBold.loadFromFile("Roboto-Bold.ttf");

    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AirCompare");
    sf::Text title("AirCompare", robotoBold, 32);
    sf::Text price("Price: ", robotoRegular, 20);
    sf::Text location("Location: ", robotoRegular, 20);
    sf::Text results("Results: ", robotoBold, 32);
    setText(title, 150.0f, 100.0f, sf::Color::Black);
    setText(price, 150.0f, 200.0f, sf::Color::Black);
    setText(location, 150.0f, 300.0f, sf::Color::Black);
    setText(results, 150.0f + windowWidth / 2.0f, 100.0f, sf::Color::Black);

    sf::RectangleShape separationLine;
    separationLine.setSize(sf::Vector2f(1, windowHeight));
    separationLine.setOutlineColor(sf::Color::Black);
    separationLine.setOutlineThickness(1);
    separationLine.setFillColor(sf::Color::Black);
    separationLine.setPosition(windowWidth / 2.2f, 1);

    // input boxes
    TextBox priceBox(170.0f, 230.0f, "Dollars/night: ", robotoRegular, 15);
    TextBox longitudeBox(170.0f, 330.0f, "Longitude: ", robotoRegular, 15);
    TextBox latitudeBox(170.0f, 360.0f, "Latitude: ", robotoRegular, 15);
    TextBox stateBox(170.0f, 390.0f, "State abbrv.: ", robotoRegular, 2);
    interactables.emplace_back(&priceBox);
    interactables.emplace_back(&longitudeBox);
    interactables.emplace_back(&latitudeBox);
    interactables.emplace_back(&stateBox);

    // selection boxes

    Checkbox mergeSort(170.0f, 470.0f, "Merge Sort?", robotoRegular);
    interactables.emplace_back(&mergeSort);

    Checkbox heapSort(170.0f, 500.0f, "Heap Sort?", robotoRegular);
    interactables.emplace_back(&heapSort);

    // run
    RunButton runButton(windowWidth / 4.4f, 700.0f, "GO!", robotoBold);
    interactables.emplace_back(&runButton);

    // starts the program out with a default of 'mergeSort'
    mergeSort.OnClick();


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
                            if (interactables.at(i) == &mergeSort)
                            {
                                if (heapSort.selected)
                                    heapSort.OnClick();
                            }
                            if (interactables.at(i) == &heapSort)
                            {
                                if (mergeSort.selected)
                                    mergeSort.OnClick();
                            }
                            i = interactables.size();
                        }
                    }
                }
            }
        }

        if (runButton.running)
        {
            runButton.running = false;
            // run sorts, get 10 results
            float timeTaken = 1.1f; // eventually with the timer function
            runButton.DisplayMessage("Computed in " + std::to_string(timeTaken) + " milliseconds.");
            Listings topTen;
            topTen.listings.push_back(Listing());
            topTen.listings.push_back(Listing());
            topTen.listings.push_back(Listing());
            topTen.listings.push_back(Listing());
            topTen.listings.push_back(Listing());
            topTen.listings.push_back(Listing());

            

            for (int i = 0; i < topTen.listings.size(); i++)
            {
                std::cout << topTen.listings.at(i).name;
                Result r(i + 1, topTen.listings.at(i), robotoRegular);
                resultList.push_back(r);
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
