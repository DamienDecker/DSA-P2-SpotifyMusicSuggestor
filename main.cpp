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

    //Text
    sf::Text welcomeText(font);
    welcomeText.setString("WELCOME TO SPOTIFY SONG SUGGESTOR!");
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setCharacterSize(36);
    setText(welcomeText, (windowWidth/2), (windowHeight/2) - 150);

    //Text
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
                                    int x = mousePosition.x;
                                    int y = mousePosition.y;

                                    //If user left-clicked
                                    if (mousePress->button == sf::Mouse::Button::Left) {

                                        //If user left-clicked on the button to to back to home screen
                                        if (homeButton.withinBounds(x, y)) {

                                            //Close filter window
                                            filterWindow.close();

                                            //Goes back to welcome window
                                            welcomeWindow.create(sf::VideoMode({windowWidth, windowHeight}), "Filter Screen");
                                        }
                                    }
                                }
                            }

                            //Draw filter window features
                            filterWindow.clear(sf::Color::Green);
                            filterWindow.draw(homeButton.getSprite());
                            filterWindow.draw(searchButton.getSprite());
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