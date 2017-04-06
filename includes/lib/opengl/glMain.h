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
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// SYSTEM
#include <functional>
#include <exception>
#include <memory>
// SOUND
#include "SoundManager.hpp"
// EVENTS
#include "Event.hpp"
#include "glEventsCorrespondence.hpp"
// GAME STATE
#include "GameState.hpp"
// IGFX
#include "IGfxLib.hpp"

namespace arcade {

    // EVENTS
    static std::vector<arcade::Event> _lastEvents;

    class LibOpenGl {

        private:
            // GRAPHIC
            //            std::unique_ptr<IMap>   _map;
            // std::unique_ptr<IGUI>   _GUI;

            // GLFW
            GLFWwindow      *_window;
            const GLuint    _width;
            const GLuint    _height;
            // SOUND
            SoundManager    _soundManager;
            // Member Functions
            void            runGFX();
            bool            loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);

        public:

            // Constructor / Destructor
            LibOpenGl(GLuint width, GLuint height);
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
            // void    updateMap(IMap const &map);
            // void    updateGUI(IGUI const &GUI);
            void    clear();
            void    display();
        };
}

#endif // GL_MAIN_HPP