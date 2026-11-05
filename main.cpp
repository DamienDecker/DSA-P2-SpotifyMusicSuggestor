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
    sf::RenderWindow songsWindow;

    //Making green color that replicates the green for spotify
    sf::Color darkGreen(30, 190, 80);

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

    //Create home button here to use for two different screens. Set position later
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

                        //Genre dropdown
                        Button genreButton(dropdownTexture);
                        genreButton.buttonPosition(200, 250);
                        genreButton.getSprite().setScale({1.0, 1.0});

                        //Feature dropdown
                        Button featureButton(dropdownTexture);
                        featureButton.buttonPosition(850, 250);
                        featureButton.getSprite().setScale({1.0, 1.0});

                        //Starting conditions for the genre drop box. Hand selected a few genres since there were 114 in the dataset
                        std::vector<std::string> genres = {"pop", "rock", "country", "alternative", "hip-hop", "jazz", "edm", "electronic", "indie-pop", "dancehall", "r-n-b"};
                        bool genreOpen = false;
                        int genreIndex = 0;

                        //Starting conditions for feature dropdown and vector features user can sort by
                        std::vector<std::string> features = {"danceability", "energy", "key", "loudness", "speechiness", "acousticness", "liveness", "valence", "tempo", "instrumentalness"};
                        bool featureOpen = false;
                        int featureIndex = 0;

                        //The selected genre
                        sf::Text selectedGenre(font);
                        selectedGenre.setCharacterSize(30);
                        setText(selectedGenre, 250, 250);

                        //The selected feature
                        sf::Text selectedFeature(font);
                        selectedFeature.setCharacterSize(30);
                        setText(selectedFeature, 900, 250);

                        //Set the text for each genre option from drop down
                        std::vector<sf::Text> genreOptions;
                        for (int i = 0; i < genres.size(); ++i) {
                            sf::Text genre(font);
                            genre.setString(genres[i]);
                            genre.setCharacterSize(20);
                            setText(genre, 270, 310 + (35 * i));
                            genreOptions.push_back(genre);
                        }

                        //Set the text for each feature option from drop down
                        std::vector<sf::Text> featureOptions;
                        for (int i = 0; i < features.size(); ++i) {
                            sf::Text feature(font);
                            feature.setString(features[i]);
                            feature.setCharacterSize(20);
                            setText(feature, 970, 310 + (35 * i));
                            featureOptions.push_back(feature);
                        }

                        //Prompt for user to enter name
                        sf::Text songsPrompt(font);
                        songsPrompt.setString("Enter the number of songs you would like to see (Max 20):");
                        songsPrompt.setStyle(sf::Text::Bold);
                        songsPrompt.setFillColor(sf::Color::White);
                        songsPrompt.setCharacterSize(18);
                        setText(songsPrompt, (windowWidth/2), (windowHeight/2) + 75);

                        //Properties for number of songs user types in
                        sf::Text number(font);
                        number.setStyle(sf::Text::Bold);
                        number.setFillColor(sf::Color::White);
                        number.setCharacterSize(18);
                        setText(number, (windowWidth/2), (windowHeight/2) + 100);

                        //Displays cursor to start
                        string numSongs = "|";
                        number.setString(numSongs);

                        //Initial boolean condition
                        bool invalidSongs = false;

                        //Message when user does not have valid number of songs entry
                        sf::Text error(font);
                        error.setString("Invalid number of songs");
                        error.setStyle(sf::Text::Bold);
                        error.setFillColor(sf::Color::Red);
                        error.setCharacterSize(18);
                        setText(error, (windowWidth/2), (windowHeight/2) + 150);

                        //Filter window start
                        while (filterWindow.isOpen()) {

                            //Event loop
                            while (const std::optional event = filterWindow.pollEvent()) {

                                //User clicks 'X' in top right
                                if (event->is<sf::Event::Closed>()) {
                                    filterWindow.close();
                                }

                                //The text a user types in
                                else if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {

                                    //If user backspaces when there is at least 1 character entered
                                    if (textEvent->unicode == 8 && numSongs.length() > 1) {
                                        numSongs = numSongs.substr(0, numSongs.length() - 1);
                                        numSongs[numSongs.length() - 1] = '|';
                                    }

                                    //User enters a numerical character
                                    else if (textEvent->unicode >= '0' && textEvent->unicode <= '9' && numSongs.size() < 3) {
                                        char num = static_cast<char>(textEvent->unicode);
                                        numSongs[numSongs.length() - 1] = num;
                                        numSongs += '|';
                                    }

                                    //Sets correct value of new string and displays it to user as they type it
                                    number.setString(numSongs);
                                }

                                //User clicks
                                else if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {

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

                                        if (searchButton.withinBounds(x, y)) {

                                            //Condition that user tries to search when number of songs input is empty
                                            bool noInput = false;
                                            if (numSongs.length() == 1) {
                                                invalidSongs = true;
                                                noInput = true;
                                            }

                                            //Turns the string on number of songs into an int if there is an input
                                            int songs;
                                            if (!noInput) {
                                                songs = stoi(numSongs.substr(0, numSongs.length() - 1));
                                            }

                                            //Validation for number of songs
                                            if (songs > 20 || noInput) {
                                                invalidSongs = true;
                                            }

                                            //Program continue to result screen
                                            else {
                                                invalidSongs = false;
                                                noInput = false;
                                                filterWindow.close();

                                                //Height of screen dependent on number of songs user searches
                                                songsWindow.create(sf::VideoMode({windowWidth, static_cast<unsigned>(songs * 40) + 100}), "Suggestion Screen");

                                                //Used to draw the lines to separate the song information we display
                                                sf::VertexArray line(sf::PrimitiveType::Lines, songs * 2);

                                                //Home button at bottom
                                                homeButton.buttonPosition(windowWidth/2 - 50, songs * 40 + 10);
                                                homeButton.getSprite().setScale({0.2, 0.2});

                                                //Need to insert here the sorted songs
                                                //selectedGenre and selectedFeature

                                                //Result window open
                                                while (songsWindow.isOpen()) {

                                                    //Event loop
                                                    while (const std::optional event = songsWindow.pollEvent()) {

                                                        //User clicks 'X' in top right
                                                        if (event->is<sf::Event::Closed>()) {
                                                            songsWindow.close();
                                                        }

                                                        //User clicks
                                                        else if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                                                            //Get location of where user clicks
                                                            sf::Vector2i mousePosition = mousePress->position;
                                                            float x = mousePosition.x;
                                                            float y = mousePosition.y;

                                                            //If user left-clicked
                                                            if (mousePress->button == sf::Mouse::Button::Left) {
                                                                //If user left-clicked on the button to go back to home screen
                                                                if (homeButton.withinBounds(x, y)) {

                                                                    //Close result window
                                                                    songsWindow.close();

                                                                    //Goes back to welcome window
                                                                    welcomeWindow.create(sf::VideoMode({windowWidth, windowHeight}), "Filter Screen");
                                                                }
                                                            }
                                                        }
                                                    }

                                                    //Draw features of the result window
                                                    songsWindow.clear(darkGreen);

                                                    //Draws each line along with the text of the song info for each line
                                                    int vertexIndex = 0;
                                                    for (int i = 1; i <= songs; i+= 1) {
                                                        line[vertexIndex].position = sf::Vector2f(0.f, i * 40);
                                                        vertexIndex += 1;

                                                        line[vertexIndex].position = sf::Vector2f(windowWidth, i * 40);
                                                        vertexIndex += 1;

                                                        //Song info. Need to change "Test" to the info for each song
                                                        sf::Text songInfo(font);
                                                        songInfo.setString("Test");
                                                        songInfo.setStyle(sf::Text::Bold);
                                                        songInfo.setFillColor(sf::Color::White);
                                                        songInfo.setCharacterSize(20);
                                                        setText(songInfo, (25), (i * 40 - 20));
                                                        songsWindow.draw(songInfo);
                                                    }

                                                    songsWindow.draw(line);
                                                    songsWindow.draw(homeButton.getSprite());
                                                    songsWindow.display();
                                                }
                                            }
                                        }

                                        //Open/close the dropdown for genres depending on current state
                                        if (genreButton.withinBounds(x, y)) {
                                            genreOpen = !genreOpen;
                                        }

                                        //If the options for genre should be showing
                                        if (genreOpen) {
                                            for (int i = 0; i < genreOptions.size(); i++) {
                                                if (genreOptions[i].getGlobalBounds().contains({x, y})) {
                                                    genreIndex = i;
                                                    genreOpen = false;
                                                    break;
                                                }
                                            }
                                        }

                                        //Open/close the dropdown for feature depending on current state
                                        if (featureButton.withinBounds(x, y)) {
                                            featureOpen = !featureOpen;
                                        }

                                        //If the options for feature should be showing
                                        if (featureOpen) {
                                            for (int i = 0; i < featureOptions.size(); i++) {
                                                if (featureOptions[i].getGlobalBounds().contains({x, y})) {
                                                    featureIndex = i;
                                                    featureOpen = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            //Draw filter window features
                            filterWindow.clear(darkGreen);
                            selectedGenre.setString(genres[genreIndex]);
                            selectedFeature.setString(features[featureIndex]);
                            filterWindow.draw(selectedGenre);
                            filterWindow.draw(selectedFeature);
                            filterWindow.draw(homeButton.getSprite());
                            filterWindow.draw(searchButton.getSprite());
                            filterWindow.draw(genreButton.getSprite());
                            filterWindow.draw(featureButton.getSprite());
                            filterWindow.draw(songsPrompt);
                            filterWindow.draw(number);

                            //If user should be seeing error message
                            if (invalidSongs) {
                                filterWindow.draw(error);
                            }

                            //If the menu options should be showing for genres display the options
                            if (genreOpen) {
                                for (const auto& genre : genreOptions) {
                                    filterWindow.draw(genre);
                                }
                            }

                            //If the menu options should be showing for features display the options
                            if (featureOpen) {
                                for (const auto& feature : featureOptions) {
                                    filterWindow.draw(feature);
                                }
                            }
                            filterWindow.display();
                        }
                    }
                }
            }
        }

        //Display welcome window features
        welcomeWindow.clear(darkGreen);
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