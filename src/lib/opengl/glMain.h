//
// Author: Marwane Khsime 
// Date: 2017-03-27 23:34:59 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-27 23:34:59
//

#ifndef GL_MAIN_HPP
# define GL_MAIN_HPP

// GLEW
# define GLEW_STATIC

#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// SYSTEM
#include <sstream>
#include <functional>
#include <exception>
#include <memory>
// SOIL
#include <SOIL/SOIL.h>
// SOUND
#include "SoundManager.hpp"
// EVENTS
#include "Event.hpp"
#include "glEventsCorrespondence.hpp"
// GAME STATE
#include "GameState.hpp"
// IGFX
#include "IGfxLib.hpp"

// MAP
#include "Map.hh"
#include "Game.hh"

# define WIDTH_RATIO        this->_tileWidth
# define HEIGHT_RATIO       this->_tileHeight

namespace arcade {

    // EVENTS
    static std::vector<arcade::Event> _lastEvents;

    class LibOpenGl : public IGfxLib {

        private:
            // GRAPHIC
            size_t                  _tileWidth;
            size_t                  _tileHeight;
            std::unique_ptr<Game>   _snake;

            // std::unique_ptr<IGUI>   _GUI;

            // GLFW
            GLFWwindow      *_window;
            const GLuint    _width;
            const GLuint    _height;
            // SOUND
            SoundManager    _soundManager;
            // Member Functions
            void            runGFX();
            void            putTileColor(ITile const &tile, size_t x, size_t y);
            void            putTileSprite(ITile const &tile, size_t x, size_t y);
            //bool            loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);
            GLuint          LoadGLTexture(const std::string &filepath);

        public:

            // Constructor / Destructor
            LibOpenGl();
            ~LibOpenGl();

            // Keyboard Management
            static void     keyCallback(GLFWwindow *, int key, int scancode, int action, int mode);
            static void     mouseCallback(GLFWwindow *,  int button, int action, int mode);

            // Event manager
            bool    pollEvent(Event &);

            // Sound Manager
            bool    doesSupportSound() const;
            void    soundControl(const Sound &soundToControl);
            void    loadSound(std::vector<std::pair<std::string, SoundType> > const &soundsToLoad);

            // 
            // Updates
            //void    updateGUI(IGUI const &gui); 

            // Graphic
            void    updateMap(IMap const &map);
            // void    updateGUI(IGUI const &GUI);
            void    clear();
            void    display();

            virtual void loadSounds(std::vector<std::pair<std::string, SoundType > > const &sounds);
            virtual void loadSprites(std::vector<std::unique_ptr<ISprite> > &&sprites);
            virtual void updateGUI(IGUI &gui);
        };
}

#endif // GL_MAIN_HPP