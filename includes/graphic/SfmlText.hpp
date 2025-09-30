/**
 * @file SfmlText.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-03
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLTEXT_HPP_
#define SFMLTEXT_HPP_

#include <iostream>

//sfml
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//Interface
#include "IText.hpp"

class SfmlText: public graphic::IText {

    public:
        SfmlText(std::string data, std::string path) {
            try {
                _font.emplace(path);                // construct texture
                _text.emplace(_font.value());     // construct sprite with texture
            } catch (const sf::Exception& e) {
                std::cerr << "Failed to load text: " << e.what() << std::endl;
            }
        }

        ~SfmlText() override {}

        bool isReady() const override {
            return _text.has_value(); 
        }

        void setText(const std::string text) override {
            _text->setString(text);
        }

        std::string getText() const override {
            return _text->getString();
        }

        void setFont(std::string path) override {
            try {
                _font = sf::Font(path);
            } catch (const sf::Exception& e) {
                std::cerr << "Failed to load font: " << e.what() << std::endl;
            }
            _text->setFont(_font.value());
        }

        void setFontSize(unsigned int size)  override {
            _text->setCharacterSize(size);
        }
        unsigned int getFontSize() const override {
            return _text->getCharacterSize();
        }
        

        void setTextColor(Color color) override {
            _text->setFillColor(sf::Color(color.r,color.g, color.b, color.a));
        }

        Color getTextColor() const override {
            const sf::Color color = _text->getFillColor();
            
            return Color{color.r, color.g, color.b, color.a};
        }

        void setPosition(Vector2f position) override {
            _text->setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
        }
        Vector2f getPosition() const override {
            const sf::Vector2f pos = _text->getPosition();
            
            return Vector2f{static_cast<double>(pos.x), static_cast<double>(pos.y)};
        }

        void setRotation(float angle) override {
            _text->setRotation(sf::degrees(angle));
        }

        float getRotation() const override {
            return _text->getRotation().asDegrees();
        }

        friend class SfmlWindow;

    private:
        std::optional<sf::Font> _font;
        std::optional<sf::Text> _text;

};

#endif /* !SFMLTEXT_HPP_ */