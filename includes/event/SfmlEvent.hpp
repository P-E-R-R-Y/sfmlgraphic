/**
 * @file SfmlEvent.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-28
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLEVENT_HPP
#define SFMLEVENT_HPP

//Sfmllib (without conflict)
#include <SFML/Window.hpp>

//Interface
#include "IEvent.hpp"

/**
 * @brief Sfmllib Event class
 * @section graphic hello
 */
class SfmlEvent : public graphic::IEvent {
  public:
    friend class SfmlKeyboard;
    friend class SfmlMouse;
    friend class SfmlWindow;

    SfmlEvent() = default;
    ~SfmlEvent() = default;

  protected:    //your variables here
      std::optional<sf::Event> _event;
};

#endif // SFMLEVENT_HPP
