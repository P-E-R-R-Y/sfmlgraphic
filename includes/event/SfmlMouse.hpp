/**
 * @file SfmlMouse.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-29
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLMOUSE_HPP_
#define SFMLMOUSE_HPP_

//Sfml
#include "SFML/Window.hpp"

//Interface
#include "IMouse.hpp"

#include "SfmlEvent.hpp"

/**
 * @brief Raylib Mouse class
 */
class SfmlMouse : public graphic::IMouse {

    public:
        SfmlMouse(graphic::IEvent *event) {
            _event = static_cast<SfmlEvent *>(event);
        }

        ~SfmlMouse() {
        }

        bool isButtonPressed(Buttons key) const override {
            if (const sf::Event::MouseButtonPressed* pressed =
                    _event->_event->getIf<sf::Event::MouseButtonPressed>()) {
                return pressed->button == _buttons.at(key);
            }
            return false;
        }

        bool isButtonDown(Buttons key) const override {
            return sf::Mouse::isButtonPressed(_buttons.at(key));
        }

        bool isButtonReleased(Buttons key) const override {
            if (const sf::Event::MouseButtonReleased* released =
                    _event->_event->getIf<sf::Event::MouseButtonReleased>()) {
                return released->button == _buttons.at(key);
            }
            return false;
        }

        bool isButtonUp(Buttons key) const override {
            return !sf::Mouse::isButtonPressed(_buttons.at(key));
        }
                
        Vector2f getPosition() const override {
            const sf::Vector2i v = sf::Mouse::getPosition();
            return Vector2f{static_cast<double>(v.x), static_cast<double>(v.y)};
        }

        void setPosition(Vector2f position) override {
            sf::Mouse::setPosition({static_cast<int>(position.x), static_cast<int>(position.y)});
        }

        float GetMouseWheelMove() const override {
            if (const sf::Event::MouseWheelScrolled* scroll = _event->_event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scroll->wheel == sf::Mouse::Wheel::Vertical)
                    return static_cast<float>(scroll->delta);
                }
            return 0.0f;
        }

    private:
        SfmlEvent *_event;
        
        const std::unordered_map<Buttons, sf::Mouse::Button> _buttons = {
            { Buttons::BUTTON_LEFT, sf::Mouse::Button::Left },
            { Buttons::BUTTON_RIGHT, sf::Mouse::Button::Right },
            { Buttons::BUTTON_MIDDLE, sf::Mouse::Button::Middle },

            { Buttons::EXTRA_BUTTON_1, sf::Mouse::Button::Extra1 },
            { Buttons::EXTRA_BUTTON_2, sf::Mouse::Button::Extra2 },
        };
};

#endif /* !RAYMOUSE_HPP_ */