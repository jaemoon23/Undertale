#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class WrappedText : public sf::Drawable, public sf::Transformable
{
private:
    sf::Text text;
    float maxWidth = 300.f;

public:
    WrappedText();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(text, states);
    }

    void setFont(const sf::Font& font) { text.setFont(font); }
    void setCharacterSize(unsigned int size) { text.setCharacterSize(size); }
    void setFillColor(const sf::Color& color) { text.setFillColor(color); }
    void setMaxWidth(float width) { maxWidth = width; }
    void setString(const std::wstring& str);

    const sf::Text& getText() const { return text; }
    sf::FloatRect getLocalBounds() const { return text.getLocalBounds(); }
    sf::FloatRect getGlobalBounds() const { return getTransform().transformRect(text.getLocalBounds()); }
};
