#include <SFML/Graphics.hpp>

#ifndef DSA_P2_SPOTIFYMUSICSUGGESTOR_BUTTON_H
#define DSA_P2_SPOTIFYMUSICSUGGESTOR_BUTTON_H

class Button {
    sf::Sprite sprite;
    int width;
    int height;
    float x;
    float y;

public:
    Button(const sf::Texture& texture);
    void buttonPosition(float _x, float _y);
    void buttonTexture(const sf::Texture& texture);
    bool withinBounds(float _x, float _y) const;
    sf::Sprite& getSprite();
};

#endif //DSA_P2_SPOTIFYMUSICSUGGESTOR_BUTTON_H