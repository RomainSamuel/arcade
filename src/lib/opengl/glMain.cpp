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

    // FUCK DIS SHIT
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Init GLFW
    if (!glfwInit())
        throw std::string("Failed to init GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Set all the required options for GLFW
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

    // this->_snake = std::make_unique<arcade::Game>();
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

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_ONE, GL_ONE);

    // Game loop
    // while (!glfwWindowShouldClose(this->_window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        // glfwPollEvents();

        // Clear screen
        // this->clear();

        // Update map
        // this->updateMap(this->_snake->getCurrentMap());

        // Render
        // this->display();
    // }
    while (42);
}

/*
** GRAPHIC
*/

void    arcade::LibOpenGl::updateMap(arcade::IMap const &map) {

    // Save Map properties
    size_t  nbLayers = map.getLayerNb();
    size_t  height = map.getHeight();
    size_t  width = map.getWidth();

    // Adjust the ratio between the game map and de window
    this->_tileWidth = this->_width / map.getWidth();
    this->_tileHeight = this->_height / map.getHeight();

    for (std::size_t layer = 0; layer < nbLayers; layer++) {

        for (std::size_t x = 0; x < width; x++) {

            for (std::size_t y = 0; y < height; y++) {
                // if (x == 4 && y == 4 && layer == 1)
                // {
                //     putTileSprite(map.at(layer, x, y), x, y);
                //     continue;
                // }
                // Check if the tile is a sprite
                if (map.at(layer, x, y).hasSprite()) {
                    putTileSprite(map.at(layer, x, y), x, y);
                }
                // If not, get the color
                else {
                    putTileColor(map.at(layer, x, y), x, y);
                }
            }
        }
    }
}

void    arcade::LibOpenGl::putTileColor(arcade::ITile const &tile, size_t x, size_t y) {

    // Set Color
    glColor4f((double)tile.getColor().r,
               (double)tile.getColor().g,
               (double)tile.getColor().b,
               (double)tile.getColor().a);

    // Adapt the coordinates for the viewport
    double  x_begin = WIDTH_RATIO * x / (this->_width / 2.0) - 1;
    double  x_end = WIDTH_RATIO * (x + 1) / (this->_width / 2.0) - 1;
    double  y_begin = HEIGHT_RATIO * y / (this->_height / 2.0) - 1;
    double  y_end = HEIGHT_RATIO * (y + 1) / (this->_height / 2.0) - 1;


    glBegin(GL_QUADS);

    glVertex2f(x_begin, y_end);     // Up Left
    glVertex2f(x_end, y_end);     // Up Right
    glVertex2f(x_end, y_begin);    // Bottom Right
    glVertex2f(x_begin, y_begin);   // Bottom Left

    glEnd();
}

void    arcade::LibOpenGl::putTileSprite(arcade::ITile const &tile, size_t x, size_t y) {

    double  x_begin = WIDTH_RATIO * x / (this->_width / 2.0) - 1/* + tile.getShiftX()*/;
    double  x_end = WIDTH_RATIO * (x + 1) / (this->_width / 2.0) - 1/* + tile.getShiftX()*/;
    double  y_begin = HEIGHT_RATIO * y / (this->_height / 2.0) - 1/* + tile.getShiftY()*/;
    double  y_end = HEIGHT_RATIO * (y + 1) / (this->_height / 2.0) - 1/* + tile.getShiftY()*/;

    glBegin(GL_QUADS);

    glVertex2f(x_begin, y_end);     // Up Left
    glVertex2f(x_end, y_end);     // Up Right
    glVertex2f(x_end, y_begin);    // Bottom Right
    glVertex2f(x_begin, y_begin);   // Bottom Left

    glEnd();

    (void)tile;
    (void)x;
    (void)y;
}


// void    arcade::LibOpenGl::updateGUI(IGUI const &GUI) {
//     this->_GUI.reset();
//     this->_GUI = std::make_unique<IGUI>(GUI);
// }

void    arcade::LibOpenGl::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void    arcade::LibOpenGl::display() {
        // Swap the screen buffers
        glfwSwapBuffers(this->_window);
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