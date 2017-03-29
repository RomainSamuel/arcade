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

// OPENAL
#include <AL/al.h>
#include <AL/alc.h>

// SNDFILE
#include <sndfile.h>

// SYSTEM
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <functional>

#include <exception>

#include "Event.hpp"
#include "GameState.hpp"
#include "glEventsCorrespondence.hpp"

// TODO : consts

namespace arcade {

    // EVENTS
    static std::vector<arcade::Event> _lastEvents;

    class LibOpenGl {
    private:

        // GLFW
        GLFWwindow      *_window;
        const GLuint    _width;
        const GLuint    _height;

        // SOUND
        std::map<size_t, ALuint> _sounds;

        // Member Functions
        void            runGFX();
        bool            initOpenAl();
        void            shutDownOpenAl();
        void            pushEvent();

    public:

        // Constructor / Destructor
        LibOpenGl(GLuint width, GLuint height);
        ~LibOpenGl();

        // Keyboard Management
        static void     keyCallback(GLFWwindow *, int key, int scancode, int action, int mode);
        static void     mouseCallback(GLFWwindow *,  int button, int action, int mode);

        // Pool event
        bool    pollEvent(Event &);

        // Sound
        struct  Sound {
            enum SoundMode { UNIQUE, REPEAT };
            int               id;
            SoundMode         mode;

            Sound(int _id, SoundMode _mode = UNIQUE) : id(_id), mode(_mode) {}
        };

        bool    doesSupportSound() const;
        void    loadSound(std::vector<std::string> const &sounds);
        void    playSound(const Sound &sound);

        // Updates
        //void    updateMap(IMap const &map);
        //void    updateGUI(IGUI const &gui);
    };

}
#endif // GL_MAIN_HPP