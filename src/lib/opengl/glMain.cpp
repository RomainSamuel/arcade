//
// Author: Marwane Khsime 
// Date: 2017-03-28 00:04:58 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-28 00:04:58
//

#include "glMain.hh"

/*
** CONSTRUCTOR
*/
GLuint  textureIDx;
arcade::LibOpenGl::LibOpenGl() : _width(800), _height(600) {

    std::cout << "Lib OpenGl 3.3 Launched" << std::endl;

    // Init GLFW
    if (glfwInit() != GL_TRUE)
        throw std::string("Failed to init GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if ((this->_window = glfwCreateWindow(this->_width, this->_height, "Arcade openGL", nullptr, nullptr)) == nullptr) {
        glfwTerminate();
        throw std::string("Failed to create GLFW window\n");
    }

    // Create a GLFWwindow object that we can use for GLFW's functions
    glfwMakeContextCurrent(this->_window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        glfwTerminate( );
        throw std::string("Failed to initialize GLEW\n");
    }

    // Define the viewport dimensions
    int frame_width, frame_height;
    glfwGetFramebufferSize(this->_window, &frame_width, &frame_height);  

    if (this->_window == nullptr)
    {
        glfwTerminate( );
        throw std::string("Failed to create GLFW Window\n");
    }

    glViewport(0, 0, frame_width, frame_height);

    // Set the required callback functions
    glfwSetKeyCallback(this->_window, arcade::LibOpenGl::keyCallback);
    // Set the required callback functions
    glfwSetMouseButtonCallback(this->_window, arcade::LibOpenGl::mouseCallback);

    // Initialize GL parameters
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE, GL_ONE);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

/*
** DESTRUCTOR
*/
arcade::LibOpenGl::~LibOpenGl() {
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

/*
** GRAPHIC
*/
void    arcade::LibOpenGl::updateMap(arcade::IMap const &map) {

    if (map.getWidth() != 0 && map.getHeight() != 0) {

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

                drawTileColor(map.at(layer, x, y), x, y, map);
                }
            }
        }
    }

}

void    arcade::LibOpenGl::drawTileColor(arcade::ITile const &tile, size_t x, size_t y, arcade::IMap const &map) {

    // Set Color
    glColor4f((double)tile.getColor().r,
               (double)tile.getColor().g,
               (double)tile.getColor().b,
               (double)tile.getColor().a);

    // Adapt the coordinates for the viewport
    double  x_begin = WIDTH_RATIO * x / (this->_width / 2.0) - 1;
    double  x_end = WIDTH_RATIO * (x + 1) / (this->_width / 2.0) - 1;
    double  y_begin = (HEIGHT_RATIO * (map.getHeight() - y)) / (this->_height / 2.0) - 1;
    double  y_end = HEIGHT_RATIO * (map.getHeight() - (y + 1)) / (this->_height / 2.0) - 1;


    glBegin(GL_QUADS);

    glVertex2f(x_begin, y_end);     // Up Left
    glVertex2f(x_end, y_end);       // Up Right
    glVertex2f(x_end, y_begin);     // Bottom Right
    glVertex2f(x_begin, y_begin);   // Bottom Left

    glEnd();
}


void    arcade::LibOpenGl::drawTileSprite(arcade::ITile const &tile, size_t x, size_t y, arcade::IMap const &map) {

    return ;

    if (this->_sprites.find(tile.getSpriteId()) == this->_sprites.end()) {
        std::cout << "not found" << std::endl;
        return ;
    }

    // Adapt the coordinates for the viewport
    double  x_begin = WIDTH_RATIO * x / (this->_width / 2.0) - 1 + tile.getShiftX();
    double  x_end = WIDTH_RATIO * (x + 1) / (this->_width / 2.0) - 1 + tile.getShiftX();
    double  y_begin = HEIGHT_RATIO * (map.getHeight() - y) / (this->_height / 2.0) - 1 + tile.getShiftY();
    double  y_end = HEIGHT_RATIO * (map.getHeight() - (y + 1)) / (this->_height / 2.0) - 1 + tile.getShiftY();


    // Bind the texture (which was preloaded in loadSprites method)
    glBindTexture(GL_TEXTURE_2D, this->_sprites[tile.getSpriteId()].at(tile.getSpritePos()));
    
    glBegin(GL_QUADS);

    glTexCoord2d(0,1);  glVertex2f(x_begin, y_end); // Up Left
    glTexCoord2d(0,0);  glVertex2f(x_begin, y_begin);   // Bottom Left
    glTexCoord2d(1,0);  glVertex2f(x_end, y_begin);     // Bottom Right
    glTexCoord2d(1,1);  glVertex2f(x_end, y_end);   // Up Right

    glEnd();
}

void    arcade::LibOpenGl::updateGUI(arcade::IGUI &GUI) {
    for (size_t i = 0; i < GUI.size(); i++) {
        this->drawComponent(GUI.at(i));
    }
}

void    arcade::LibOpenGl::drawComponentSprite(const arcade::IComponent &component) {

    return ;
    double  x_begin = component.getX() - 1.0;
    double  x_end = component.getX() + component.getWidth() - 1.0;
    double  y_begin = component.getY() - 1.0;
    double  y_end = component.getY() + component.getHeight() - 1.0;

    glBindTexture(GL_TEXTURE_2D, this->_sprites[component.getBackgroundId()].at(0));
    glBegin(GL_QUADS);

    glTexCoord2d(0,1);  glVertex2f(x_begin, y_end);     // Up Left
    glTexCoord2d(0,0);  glVertex2f(x_end, y_end);       // Up Right
    glTexCoord2d(1,0);  glVertex2f(x_end, y_begin);     // Bottom Right
    glTexCoord2d(1,1);  glVertex2f(x_begin, y_begin);   // Bottom Left

    glEnd();
}

void    arcade::LibOpenGl::drawComponentColor(const arcade::IComponent &component) {

    double  x_begin = component.getX() - 1.0;
    double  x_end = component.getX() + component.getWidth() - 1.0;
    double  y_begin = component.getY() - 1.0;
    double  y_end = component.getY() + component.getHeight() - 1.0;

    arcade::Color color = component.getBackgroundColor();

    glColor4f((double)color.r,
               (double)color.g,
               (double)color.b,
               (double)color.a);
    
    glBegin(GL_QUADS);

    glTexCoord2d(0,1);  glVertex2f(x_begin, y_end);     // Up Left
    glTexCoord2d(0,0);  glVertex2f(x_end, y_end);       // Up Right
    glTexCoord2d(1,0);  glVertex2f(x_end, y_begin);     // Bottom Right
    glTexCoord2d(1,1);  glVertex2f(x_begin, y_begin);   // Bottom Left

    glEnd();

}

void    arcade::LibOpenGl::drawComponent(const arcade::IComponent &component) {

    // If component has a sprite
    if (component.hasSprite()) {
        this->drawComponentSprite(component);
    } else { // If component is juste a block of color
        this->drawComponentColor(component);
    }
}

void    arcade::LibOpenGl::loadSprites(std::vector<std::unique_ptr<arcade::ISprite>> &&sprites) {

    // Clear alls olds textures
    this->_sprites.clear();

    for (std::size_t i = 0; i < sprites.size(); i++) {

        for (std::size_t nSprite = 0; nSprite < sprites[i]->spritesCount(); nSprite++) {
         
         GLuint  textureID = this->loadGLTexture(sprites[i]->getGraphicPath(nSprite));

        if (textureID == 0)
             std::cout << "Warning : couldn't load a texture." << std::endl;
        else
            this->_sprites[i].push_back(textureID);

        }
    }
}


GLuint  arcade::LibOpenGl::loadGLTexture(const std::string &filepath) {
    return SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
		filepath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}


// Black Screen
void    arcade::LibOpenGl::clear() {
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
    if (action == GLFW_PRESS) {
        arcade::MousePos    current;
        arcade::MousePos    last;

        // Get current mouse position
        glfwGetCursorPos(window, &current.x, &current.y);
        // Get last mouse position
        last.x = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.x : current.x;
        last.y = _lastEvents.size() > 1 ? _lastEvents.end()->pos_abs.y : current.y;

        arcade::Event       newEvent;

        newEvent.type = arcade::EventType::ET_MOUSE;
        newEvent.action = arcade::ActionType::AT_PRESSED;
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

bool    arcade::LibOpenGl::pollEvent(arcade::Event &event) {   

    glfwPollEvents();

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

void    arcade::LibOpenGl::loadSounds(std::vector<std::pair<std::string, arcade::SoundType > > const &soundsToLoad)
{
    this->_soundManager.loadSounds(soundsToLoad);
}

void    arcade::LibOpenGl::soundControl(const arcade::Sound &soundToControl) {
    this->_soundManager.soundControl(soundToControl);
}


extern "C" arcade::IGfxLib *getLib()
{
    return (new arcade::LibOpenGl());
}