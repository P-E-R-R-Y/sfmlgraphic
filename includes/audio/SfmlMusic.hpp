/**
 * @file SfmlMusic.hpp
 * @author @Perry-chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-28
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLMUSIC_HPP_
#define SFMLMUSIC_HPP_

//Sfmllib (without conflict)
#include <SFML/Audio.hpp>

//Interface
#include "IMusic.hpp"

class SfmlMusic: public graphic::IMusic {

    public:

        /**
         * @brief Construct a new Sfml Music
         * 
         * @param path 
         */
        SfmlMusic(std::string path): _music(path) {
            _music.setVolume(100.f);
        }
        
        /**
         * @brief Destroy the Sfml Music
         * 
         */
        ~SfmlMusic() override {
        }

        bool isReady() const override {
            return true; //IsMusicValid(_music);
        }

        /**
         * @brief play the music
         */
        void play() override {
            _music.play();
        }

        /**
         * @brief pause the music
         * 
         */
        void pause() override {
            _music.pause ();
        }

        /**
         * @brief stop the music and reset it to the beginning
         * 
         */
        void stop() override {
            _music.stop();
        }

        void update() override {            
        }

        /**
         * @brief set the volume of the music
         * 
         * @param volume 
         */
        void setVolume(float volume) override {            
            _music.setVolume(volume*100.f);
        }

        /**
         * @brief get the volume of the music or if not set the master volume
         * 
         * @return float 
         */
        float getVolume() const override {
            return _music.getVolume();
        }

        /**
         * @brief set the music to loop or not
         * 
         * @param loop 
         */
        void setLoop(bool loop) override {
            _music.setLooping(loop);
        }

        /**
         * @brief get if the music is looping or not
         * 
         * @return true 
         * @return false 
         */
        bool getLoop() const override {
            return _music.isLooping();
        }

        /**
         * @brief Set the time of the music in seconds
         * 
         * @param position 
         */
        void setTime(float position) override {
            _music.setPlayingOffset(sf::seconds(position));
        }

        /**
         * @brief Get the current time of the music in seconds
         * 
         * @return float 
         */
        float getTime() const override {
            return _music.getPlayingOffset().asSeconds();
        }

        /**
         * @brief Get the Length of the music
         * 
         * @return float 
         */
        float getLength() const override {
            return _music.getDuration().asSeconds();
        }

    private:

        sf::Music _music;
};

#endif /* !SfmlMUSIC_HPP_ */