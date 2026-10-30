#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace std;

//Function prototype
void setText(sf::Text &text, float x, float y);

int main() {

    //Window dimensions
    unsigned windowWidth = 1200;
    unsigned windowHeight = 800;

    //Create welcome window
    sf::RenderWindow welcomeWindow(sf::VideoMode({windowWidth, windowHeight}), "Home Screen");

    //Filter window for later
    sf::RenderWindow filterWindow;

    //Simple arial font
    const sf::Font font("resources/arial.ttf");

    //Welcome message text
    sf::Text welcomeText(font);
    welcomeText.setString("WELCOME TO SPOTIFY SONG SUGGESTOR!");
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setCharacterSize(36);
    setText(welcomeText, (windowWidth/2), (windowHeight/2) - 150);

    //Direction text
    sf::Text startText(font);
    startText.setString("Click The Logo to Begin");
    startText.setStyle(sf::Text::Bold);
    startText.setCharacterSize(30);
    setText(startText, (windowWidth/2), (windowHeight/2) - 100);

    //Create button to advance in program
    sf::Texture spotifyTexture;
    if (!spotifyTexture.loadFromFile("resources/Spotify_Primary_Logo_RGB_Black.png")) {
        cout << "Could not load spotify texture" << endl;
        return 1;
    }

    Button spotifyButton(spotifyTexture);
    spotifyButton.buttonPosition((windowWidth/2 - 100), (windowHeight/2));

    //Create button here to use for two different screens. Set position later
    sf::Texture homeTexture;
    if (!homeTexture.loadFromFile("resources/house-png-202.png")) {
        cout << "Could not load home texture" << endl;
        return 1;
    }

    Button homeButton(homeTexture);

    //Welcome window start
    while (welcomeWindow.isOpen()) {

        //Event loop
        while (const std::optional event = welcomeWindow.pollEvent()){

            //User clicks 'X' in top right
            if (event->is<sf::Event::Closed>()) {
                welcomeWindow.close();
            }

            //User clicks
            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {

                //Get location of where user clicks
                sf::Vector2i mousePosition = mousePress->position;
                int x = mousePosition.x;
                int y = mousePosition.y;

                //If user left-clicked
                if (mousePress->button == sf::Mouse::Button::Left) {

                    //If user left-clicked on the button to advance in application
                    if (spotifyButton.withinBounds(x, y)) {

                        //Close welcome window
                        welcomeWindow.close();

                        //Create the window that will have suer filter in
                        filterWindow.create(sf::VideoMode({windowWidth, windowHeight}), "Filter Screen");

                        homeButton.buttonPosition(windowWidth/2 - 200, windowHeight - 125);

                        //Search button info
                        sf::Texture searchTexture;
                        if (!searchTexture.loadFromFile("resources/search-icon-png-9965.png")) {
                            cout << "Could not load search texture" << endl;
                            return 1;
                        }

                        Button searchButton(searchTexture);
                        searchButton.buttonPosition((windowWidth/2 - 50), windowHeight - 220);
                        searchButton.getSprite().setScale({0.5, 0.5});

                        //Drop down button info
                        sf::Texture dropdownTexture;
                        if (!dropdownTexture.loadFromFile("resources/dropdown.png")) {
                            cout << "Could not load search texture" << endl;
                            return 1;
                        }

                        Button dropdownButton(dropdownTexture);
                        float dropdownPositionX = 200;
                        float dropdownPositionY = 250;
                        dropdownButton.buttonPosition(dropdownPositionX, dropdownPositionY);
                        dropdownButton.getSprite().setScale({1.0, 1.0});

                        //Starting conditions for the genre drop box. Hand selected a few genres since there were 114 in the dataset
                        std::vector<std::string> genres = {"pop", "rock", "country", "alternative", "hip-hop", "jazz", "edm", "electronic", "indie-pop", "dancehall", "r-n-b"};
                        bool genreOpen = false;
                        int genreIndex = 0;

                        //The selected genre
                        sf::Text selectedGenre(font);
                        selectedGenre.setCharacterSize(30);
                        setText(selectedGenre, dropdownPositionX + 50, dropdownPositionY);

                        //Set the text for each genre option from drop down
                        std::vector<sf::Text> genreOptions;
                        for (int i = 0; i < genres.size(); ++i) {
                            sf::Text genre(font);
                            genre.setString(genres[i]);
                            genre.setCharacterSize(20);
                            setText(genre, dropdownPositionX + 70, dropdownPositionY + 60 + (35 * i));
                            genreOptions.push_back(genre);
                        }

                        //Filter window start
                        while (filterWindow.isOpen()) {

                            //Event loop
                            while (const std::optional event = filterWindow.pollEvent()) {

                                //User clicks 'X' in top right
                                if (event->is<sf::Event::Closed>()) {
                                    filterWindow.close();
                                }

                                //User clicks
                                if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {

                                    //Get location of where user clicks
                                    sf::Vector2i mousePosition = mousePress->position;
                                    float x = mousePosition.x;
                                    float y = mousePosition.y;

                                    //If user left-clicked
                                    if (mousePress->button == sf::Mouse::Button::Left) {

                                        //If user left-clicked on the button to go back to home screen
                                        if (homeButton.withinBounds(x, y)) {

                                            //Close filter window
                                            filterWindow.close();

                                            //Goes back to welcome window
                                            welcomeWindow.create(sf::VideoMode({windowWidth, windowHeight}), "Filter Screen");
                                        }

                                        //Open/close the dropdown for genres depending on current state
                                        else if (dropdownButton.withinBounds(x, y)) {
                                            genreOpen = !genreOpen;
                                        }

                                        //If the options for genre should be showing
                                        else if (genreOpen) {
                                            for (int i = 0; i < genreOptions.size(); i++) {
                                                if (genreOptions[i].getGlobalBounds().contains({x, y})) {
                                                    genreIndex = i;
                                                    genreOpen = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            //Draw filter window features
                            filterWindow.clear(sf::Color::Green);
                            selectedGenre.setString(genres[genreIndex]);
                            filterWindow.draw(selectedGenre);
                            filterWindow.draw(homeButton.getSprite());
                            filterWindow.draw(searchButton.getSprite());
                            filterWindow.draw(dropdownButton.getSprite());

                            //If the menu options should be showing display the options
                            if (genreOpen) {
                                for (const auto& genre : genreOptions) {
                                    filterWindow.draw(genre);
                                }
                            }
                            filterWindow.display();
                        }
                    }
                }
            }
        }

        //Display welcome window features
        welcomeWindow.clear(sf::Color::Green);
        welcomeWindow.draw(spotifyButton.getSprite());
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(startText);
        welcomeWindow.display();

    }
}

//Function to set the position of text for screens
void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x/2.0f, textRect.position.y + textRect.size.y/2.0f});
    text.setPosition(sf::Vector2f(x, y));
}