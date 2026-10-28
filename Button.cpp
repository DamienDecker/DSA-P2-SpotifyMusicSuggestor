#include "Button.h"

Button::Button(const sf::Texture& texture) : sprite(texture) {
    sprite.setTexture(texture);
    sprite.setScale({0.25f, 0.25f});
    sf::FloatRect bound = sprite.getGlobalBounds();
    width = static_cast<int>(bound.size.x);
    height = static_cast<int>(bound.size.y);
    x = 0;
    y = 0;
}

void Button::buttonPosition(float _x, float _y) {
    x = _x;
    y = _y;
    sprite.setPosition({x, y});
}

void Button::buttonTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

bool Button::withinBounds(float _x, float _y) const {
    return sprite.getGlobalBounds().contains({_x, _y});
}

sf::Sprite& Button::getSprite() {
    return sprite;
}