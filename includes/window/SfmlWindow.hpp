/**
 * @file SfmlWindow.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-29
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLWINDOW_HPP_
#define SFMLWINDOW_HPP_

//Sfml
#include <SFML/Graphics.hpp>

//Interface
#include "IWindow.hpp"

//encapsulation
#include "SfmlEvent.hpp"
#include "SfmlPolygon.hpp"
#include "SfmlSprite.hpp"
#include "SfmlModel.hpp"
#include "SfmlText.hpp"
#include "SfmlCamera.hpp"

#include <iostream>

/**
 * @brief Sfml Window class
 */
class SfmlWindow : public graphic::IWindow {

    public:
        SfmlWindow(int32_t screenWidth, int32_t screenHeight, std::string title)
            : _window(sf::VideoMode({static_cast<uint32_t>(screenWidth), static_cast<uint32_t>(screenHeight)}), title), _event(nullptr), _deltaClock() {
        };

        ~SfmlWindow() {};

        //GLOBAL

        //IsWindowReady for init fails
        //WindowShouldClose for escape & alt+f4
        //quitRequested when user ask to close the app under is own condition
        bool isOpen() override {
             return _window.isOpen();
        };

        void close() override {
            _window.close();
        };

        //EVENT
        void linkEvent(graphic::IEvent *event) override {
            _event = static_cast<SfmlEvent *>(event);
        };
        
        bool pollEvent() override {
            _event->_event = _window.pollEvent();

            return _event->_event.has_value();
        }

        //not define cause eventClose is internally define using Key::Escape
        void eventClose() override {
            if (_event->_event->is<sf::Event::Closed>() || 
                (_event->_event->is<sf::Event::KeyPressed>() && _event->_event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape))
                _window.close();
        };
        
        //TIME
        void setFrameLimit(int32_t limit) override {
            _window.setFramerateLimit(limit);
        };

        int32_t getDelta() override {
            return static_cast<int32_t>(_deltaTime.asMilliseconds());
        };

        //2D
        void beginDraw() override {
             _window.clear();
        };

        void endDraw() override {
            _window.display();
            _deltaTime = _deltaClock.restart();
        };

        void drawPoly(graphic::IPolygon *polygon) override {
            SfmlPolygon *sfmlpolygon = static_cast<SfmlPolygon *>(polygon);

            _window.draw(sfmlpolygon->_vertices);
        }
        
        void drawSprite(graphic::ISprite *sprite) override {
            SfmlSprite *sfmlsprite = static_cast<SfmlSprite *>(sprite);
            
            _window.draw(sfmlsprite->_sprite.value());
        };
        
        void drawText(graphic::IText* text) override {
            SfmlText* sfmlText = static_cast<SfmlText *>(text);

            _window.draw(sfmlText->_text.value());
        }

        //3D
        //Draw3 (Carve)
        void beginMode3(graphic::ICamera *camera) override {
            _camera = static_cast<SfmlCamera *>(camera);
         }
        
        void drawModel(graphic::IModel *model) override { /*no 3D*/ }

        void endMode3() override { _camera =  nullptr; }

        bool beginAudio() override {
            //nothing to do for SFML
            return true;
        };

        void endAudio() override {
            //nothing to do for SFML
        };

    private:
        sf::RenderWindow _window;
        SfmlEvent *_event;
        SfmlCamera *_camera;

        //time
        sf::Clock _deltaClock;
        sf::Time _deltaTime;
};

#endif /* !SFMLWINDOW_HPP_ */