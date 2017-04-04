//
// Author: Marwane Khsime 
// Date: 2017-03-28 00:04:58 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-28 00:04:58
//

#include "glMain.h"


/*
** CONSTRUCTOR
*/
arcade::LibOpenGl::LibOpenGl(GLuint width, GLuint height) : _width(width), _height(height) {

    std::cout << "Lib OpenGl 3.3 Launched" << std::endl;

    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if ((this->_window = glfwCreateWindow(this->_width, this->_height, "Arcade", nullptr, nullptr)) == nullptr) {
        glfwTerminate();
        throw std::string("Failed to create GLFW window\n");
    }

    // Create a GLFWwindow object that we can use for GLFW's functions
    glfwMakeContextCurrent(this->_window);

    // Set the required callback functions
    glfwSetKeyCallback(this->_window, arcade::LibOpenGl::keyCallback);
    glfwSetMouseButtonCallback(this->_window, arcade::LibOpenGl::mouseCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
        throw std::string("Failed to initialize GLEW\n");

    // Define the viewport dimensions
    int frame_width, frame_height;
    glfwGetFramebufferSize(this->_window, &frame_width, &frame_height);  
    glViewport(0, 0, frame_width, frame_height);

    // Run Lib
    this->runGFX();
}

/*
** DESTRUCTOR
*/
arcade::LibOpenGl::~LibOpenGl() {
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

/*
**  Run GFX
*/
void    arcade::LibOpenGl::runGFX() {

    // Game loop
    glClearColor(0.2f, 0.6f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    while (!glfwWindowShouldClose(this->_window)) {

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer

        // Swap the screen buffers
        glfwSwapBuffers(this->_window);
    }
}

/*
** GRAPHIC
*/

// void    arcade::LibOpenGl::updateMap(IMap const &map) {
//     this->_map.reset();
//     this->_map = std::make_unique<IMap>(map);
// }

// void    arcade::LibOpenGl::updateGUI(IGUI const &GUI) {
//     this->_GUI.reset();
//     this->_GUI = std::make_unique<IGUI>(GUI);
// }

void    arcade::LibOpenGl::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void    arcade::LibOpenGl::display() {
    std::cout << "Display" << std::endl;   
}

/*
** EVENTS
*/
// Is called whenever a key is pressed/released via GLFW
void    arcade::LibOpenGl::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    std::cout << key << std::endl;
    if (action == GLFW_PRESS) {
        arcade::MousePos    current;
        arcade::MousePos    last;

        // Get current mouse position
        glfwGetCursorPos(window, &current.x, &current.y);
        // Get last mouse position
        last.x = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.x : current.x;
        last.y = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.y : current.y;

        arcade::Event       newEvent;

        newEvent.type = ET_KEYBOARD;
        newEvent.action = AT_PRESSED;
        newEvent.kb_key = (arcade::KeyboardKey)arcade::_glKeyboardKeys.find(key)->second;
        newEvent.pos_rel = last;
        newEvent.pos_abs = current;

        // Push in events vector
        _lastEvents.emplace_back(newEvent);
    }

    // Unused
    (void)scancode;
    (void)mode;
}

// Is caled whenever a mouse button is pressed/released via GLFW
void    arcade::LibOpenGl::mouseCallback(GLFWwindow *window, int button, int action, int mode) {
    std::cout << button << std::endl;
    if (action == GLFW_PRESS) {
        arcade::MousePos    current;
        arcade::MousePos    last;

        // Get current mouse position
        glfwGetCursorPos(window, &current.x, &current.y);
        // Get last mouse position
        last.x = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.x : current.x;
        last.y = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.y : current.y;

        arcade::Event       newEvent;

        newEvent.type = ET_MOUSE;
        newEvent.action = AT_PRESSED;
        newEvent.m_key = (arcade::MouseKey)arcade::_glMouseKey.find(button)->second;
        newEvent.pos_rel = last;
        newEvent.pos_abs = current;

        // Push in events vector
        _lastEvents.emplace_back(newEvent);
    }

    // Unused
    (void)window;
    (void)mode;
}

bool    arcade::LibOpenGl::pollEvent(Event &event) {
    if (_lastEvents.size() > 0) {
        arcade::Event   lastEvent = *_lastEvents.begin();
        event.type = lastEvent.type;
        event.action = lastEvent.action;

        if (lastEvent.type == ET_KEYBOARD) {
            event.kb_key = lastEvent.kb_key;
        } else if (lastEvent.type == ET_MOUSE) {
            event.m_key = lastEvent.m_key;
        } else {
            event.c_key = lastEvent.c_key;
        }

        event.pos_rel.x = lastEvent.pos_rel.x;
        event.pos_rel.y = lastEvent.pos_rel.y;
        event.pos_abs.x = lastEvent.pos_abs.x;
        event.pos_abs.y = lastEvent.pos_abs.y;

        // Remove event from list
        _lastEvents.erase(_lastEvents.begin());
        return true;
    }
    return false;
}

/*
** SOUND
*/

bool    arcade::LibOpenGl::doesSupportSound() const {
    return this->_soundManager.doesSupportSound();
}

void    arcade::LibOpenGl::loadSound(std::vector<std::pair<std::string, SoundType> > const &soundsToLoad) {
    this->_soundManager.loadSounds(soundsToLoad);
}

void    arcade::LibOpenGl::soundControl(const Sound &soundToControl) {
    this->_soundManager.soundControl(soundToControl);
}

void    test() {
    arcade::LibOpenGl   toto(800, 600);

    (void)toto;
}

int main() {
    test();
    return 0;
}