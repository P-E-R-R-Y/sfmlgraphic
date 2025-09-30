/**
 * @file SfmlSound.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-28
 * 
 * @addtogroup sfml
 * @{
 */

#ifndef SFMLSOUND_HPP_
#define SFMLSOUND_HPP_

//Sfml
#include <SFML/Audio.hpp>

//Interface
#include "ISound.hpp"

class SfmlSound: public graphic::ISound {

    public:

        SfmlSound(std::string path): _buffer(path), _sound(_buffer) {
            _sound.setVolume(100.f);
        }

        ~SfmlSound() override = default;

        bool isReady() const override {
            return (!_buffer.getSampleCount());
        }

        /**
         * @brief play the sound
         */
        void play() override {
            _sound.play();
        }

        /**
         * @brief pause the sound
         * 
         */
        void pause() override {
            _sound.pause();
        }

        /**
         * @brief stop the sound and reset it to the beginning
         * 
         */
        void stop() override {
            _sound.stop();
        }

        /**
         * @brief set the volume of the sound
         * 
         * @param volume 
         */
        void setVolume(float volume) override {
            _sound.setVolume(volume*100.0);
        }

        /**
         * @brief get the volume of the sound
         * 
         * @return float 
         */
        float getVolume() const override {
            return _sound.getVolume() * 0.01;
        }

    private:
        const sf::SoundBuffer _buffer;
        sf::Sound _sound;
};

#endif /* !SFMLSOUND_HPP_ */