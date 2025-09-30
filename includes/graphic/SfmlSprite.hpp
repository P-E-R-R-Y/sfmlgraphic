/**
 * @file SfmlSprite.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Sfml
 * @{
 */


#ifndef SFMLSPRITE_HPP_
#define SFMLSPRITE_HPP_

//Sfml
#include <SFML/Graphics.hpp>

//Interface
#include "ISprite.hpp"

/**
 * @brief Sfmllib Sprite class
 */
class SfmlSprite : public graphic::ISprite {

    public:
        SfmlSprite(std::string path) {
            try {
                _texture.emplace(path);                // construct texture
                _sprite.emplace(_texture.value());     // construct sprite with texture
            } catch (const sf::Exception& e) {
                std::cerr << "Failed to load sprite: " << e.what() << std::endl;
            }
        }

        ~SfmlSprite() override = default;

        bool isReady() const override {
            return _sprite.has_value();
        }

        Vector4f getBounds() const override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            sf::FloatRect rect = _sprite->getGlobalBounds();

            return {rect.position.x, rect.position.y, rect.size.x, rect.size.y};
        }

        void setCrop(Vector4f rect) override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            _rect = sf::IntRect{sf::Vector2i{static_cast<int32_t>(rect.x), static_cast<int32_t>(rect.y)}, sf::Vector2i{static_cast<int32_t>(rect.w), static_cast<int32_t>(rect.h)}};
            _sprite->setTextureRect(_rect);
        }

        Vector2f getPosition() const override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            sf::Vector2f pos = _sprite->getPosition();

            return {static_cast<double>(pos.x), static_cast<double>(pos.y)};
        }
        void setPosition(Vector2f position) override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            _sprite->setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
        }

        float getRotation() const override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            return _sprite->getRotation().asDegrees();
        }

        void setRotation(float angle, bool isRad = false) override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            if (isRad)
                _sprite->setRotation(sf::radians(angle));
            else
                _sprite->setRotation(sf::degrees(angle));

        }

        Vector2f getSize() const override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            sf::Vector2f scale = _sprite->getScale();
            sf::Vector2f size = _sprite->getLocalBounds().size;
            
            return {static_cast<double>(size.x * scale.x), static_cast<float>(size.y * scale.y)};
        }

        void setSize(Vector2f size) override {
            if (!_sprite.has_value())
                throw std::runtime_error("SfmlSprite: sprite is invalid");

            sf::Vector2f bounds = _sprite->getLocalBounds().size;
            _sprite->setScale({
                static_cast<float>(size.x / bounds.x),
                static_cast<float>(size.y / bounds.y)
            });
        }

        friend class SfmlWindow;

    private:
        sf::IntRect _rect;
        std::optional<sf::Texture> _texture;
        std::optional<sf::Sprite> _sprite;
};

#endif /* !SFMLSPRITE_HPP_ */