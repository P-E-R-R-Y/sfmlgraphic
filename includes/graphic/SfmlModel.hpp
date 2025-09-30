/**
 * @file SfmlModel.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLMODEL_HPP_
#define SFMLMODEL_HPP_

//Sfmllib (without conflict)
#include <SFML/Graphics.hpp>

//Interface
#include "IModel.hpp"

/**
 * @brief Sfmllib Model class
 */
class SfmlModel : public graphic::IModel {

    public:

        /**
         * @brief Construct a new Sfml Model object
         */
        SfmlModel() {
            _position = {0, 0, 0};
            _size = {1, 1, 1};
        }

        ~SfmlModel() = default;

        Vector3f getPosition() const override {
            return {_position.x, _position.y, _position.z};
        }

        void setPosition(Vector3f position) override {
            _position = position;
        }

        friend class SfmlWindow;

    private:
        Vector3f _position;
        Vector3f _size;
};

#endif /* !SFMLMODEL_HPP_ */