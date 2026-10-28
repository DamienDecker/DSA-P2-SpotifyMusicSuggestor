//
// Created by Damien on 10/27/2026.
//

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x/2.0f, textRect.position.y + textRect.size.y/2.0f});
    text.setPosition(sf::Vector2f(x, y));
}

int main() {
    unsigned windowWidth = 1200;
    unsigned windowHeight = 800;
    sf::RenderWindow welcomeWindow(sf::VideoMode({windowWidth, windowHeight}), "Home Screen");

    const sf::Font font("resources/arial.ttf");

    sf::Text welcomeText(font);
    welcomeText.setString("WELCOME TO SPOTIFY SONG SUGGESTOR!");
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setCharacterSize(36);
    setText(welcomeText, (windowWidth/2), (windowHeight/2) - 150);

    sf::Text startText(font);
    startText.setString("Click The Logo to Begin");
    startText.setStyle(sf::Text::Bold);
    startText.setCharacterSize(30);
    setText(startText, (windowWidth/2), (windowHeight/2) - 100);

    sf::Texture spotifyTexture;
    if (!spotifyTexture.loadFromFile("resources/Spotify_Primary_Logo_RGB_Black.png")) {
        cout << "Could not load spotify texture" << endl;
        return 1;
    }

    sf::Sprite spotifySprite(spotifyTexture);
    spotifySprite.setPosition({static_cast<float>(windowWidth/2 - 100), static_cast<float>(windowHeight/2)});
    spotifySprite.setScale({0.25f, 0.25f});

    while (welcomeWindow.isOpen()) {
        while (const std::optional event = welcomeWindow.pollEvent()){
            if (event->is<sf::Event::Closed>()) {
                welcomeWindow.close();
            }
        }

        welcomeWindow.clear(sf::Color::Green);
        welcomeWindow.draw(spotifySprite);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(startText);
        welcomeWindow.display();

    }
}