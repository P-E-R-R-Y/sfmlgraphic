/**
 * @file SfmlGraphicModule.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-30
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLGRAPHIC_MODULE_HPP
#define SFMLGRAPHIC_MODULE_HPP

#include "SfmlWindow.hpp"
#include "SfmlCamera.hpp"

#include "SfmlModel.hpp"
#include "SfmlPolygon.hpp"
#include "SfmlSprite.hpp"
#include "SfmlText.hpp"

#include "SfmlEvent.hpp"
#include "SfmlKeyboard.hpp"
#include "SfmlMouse.hpp"

#include "SfmlMusic.hpp"
#include "SfmlSound.hpp"

#include "IGraphicModule.hpp"

class SfmlGraphicModule : public IGraphicModule {

public:
    SfmlGraphicModule() = default;
    ~SfmlGraphicModule() = default;

    /* Window */

    graphic::IWindow *createWindow(int32_t screenWidth, int32_t screenHeight, std::string title) override {
        return new SfmlWindow(screenWidth, screenHeight, title);
    }
    void deleteWindow(graphic::IWindow *window) override {
        delete window;
    }

    /* 3D */

    graphic::ICamera *createCamera() override {
        return new SfmlCamera();
    }
    void deleteCamera(graphic::ICamera *camera) override {
        delete camera;
    }
    
    graphic::IModel *createModel() override {
        return new SfmlModel();
    }
    void deleteModel(graphic::IModel *model) override {
        delete model;
    }

    /* 2D */

    graphic::IPolygon *createPolygon(std::vector<Vector2f> points) override {
        return new SfmlPolygon(points);
    }
    void deletePolygon(graphic::IPolygon *polygon) override {
        delete polygon;
    }

    graphic::ISprite *createSprite(std::string path) override {
        return new SfmlSprite(path);
    }
    void deleteSprite(graphic::ISprite *sprite) override {
        delete sprite;
    }

    graphic::IText *createText(std::string text, std::string font) override {
        return new SfmlText(text, font);
    }
    void deleteText(graphic::IText *text) override {
        delete text;
    }

    /* Event */

    graphic::IEvent *createEvent() override {
        return new SfmlEvent();
    }
    void deleteEvent(graphic::IEvent *event) override {
        delete event;
    }

    graphic::IKeyboard *createKeyboard(graphic::IEvent *event) override {
        return new SfmlKeyboard(event);
    }
    void deleteKeyboard(graphic::IKeyboard *keyboard) override {
        delete keyboard;
    }

    graphic::IMouse *createMouse(graphic::IEvent *event) override {
        return new SfmlMouse(event);
    }
    void deleteMouse(graphic::IMouse *mouse) override {
        delete mouse;
    }

    /* Audio */ 

    graphic::IMusic *createMusic(std::string path) override {
        return new SfmlMusic(path);
    }
    void deleteMusic(graphic::IMusic *music) override {
        delete music;
    }

    graphic::ISound *createSound(std::string path) override {
        return new SfmlSound(path);
    }
    void deleteSound(graphic::ISound *sound) override {
        delete sound;
    }

    const std::string getType() const override {
        return "graphic";
    }
    const std::string getName() const override {
        return "SFML";
    }

    void update() override {}
};

#endif /* !IGRAPHIC_MODULE_HPP */