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

    // Init OpenAl
    if (!initOpenAl())
        throw std::string("Failed to initialize OpenAl\n");

    // Run Lib
    this->runGFX();
}

/*
** DESTRUCTOR
*/
arcade::LibOpenGl::~LibOpenGl() {
    glfwDestroyWindow(this->_window);
    glfwTerminate();
    shutDownOpenAl();
}

/*
**  Run GFX
*/
void    arcade::LibOpenGl::runGFX() {
    // Game loop
    while (!glfwWindowShouldClose(this->_window)) {

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(this->_window);
    }
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
    std::cout << "does support sound (yes)" << std::endl;
    return true;
}

void    arcade::LibOpenGl::loadSound(std::vector<std::string> const &sounds) {
    std::cout << "load sound" << std::endl;

    // Remove old sounds and delete sources
    for (size_t i = 0; i < this->_sounds.size(); i++) {
        alSourcei(this->_sounds[i], AL_BUFFER, 0);
        alDeleteSources(1, &this->_sounds[i]);
    }   this->_sounds.clear();

    for (size_t i = 0; i < sounds.size(); i++) {

        // Open audio file with libsndfile
        SF_INFO     FileInfos;
        SNDFILE     *File = sf_open(sounds[i].c_str(), SFM_READ, &FileInfos);

        if (File == nullptr) {
            std::cout << "Error: failed to load '" + sounds[i] + "'\n" << std::endl;
            return ;
        }
        // Reading the number of samples and the sampling rate (number of samples to be read per second)
        ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
        ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);


        // Play audio samples in signed 16-bit integer format (the most common)
        std::vector<ALshort>    Samples(NbSamples);
        if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
            return ;

        // Close file
        sf_close(File);

        // Determining the format according to the number of channels
        ALenum Format;
        switch (FileInfos.channels) {
            case 1 :  Format = AL_FORMAT_MONO16;   break;
            case 2 :  Format = AL_FORMAT_STEREO16; break;
            default : return ;
        }

        // Create OpenAL buffer
        ALuint Buffer;

        alGenBuffers(1, &Buffer);

        // Fill with samples read
        alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
    
        // Check errors
        if (alGetError() != AL_NO_ERROR) {
            std::cout << "Error : An error has occured with file '" + sounds[i] + "'" << std::endl;
            return ;
        }

        ALuint  Source;
        alGenSources(1, &Source);
        alSourcei(Source, AL_BUFFER, Buffer);

        // push sound
        this->_sounds.insert(std::pair<size_t, ALuint>(i, Source));
    }
}

void    arcade::LibOpenGl::playSound(const Sound &sound) {
    std::cout << "play sound" << std::endl;

    if (sound.mode == Sound::SoundMode::REPEAT) {
        alSourcei(this->_sounds[sound.id], AL_LOOPING, true);
    }
    alSourcePlay(this->_sounds[sound.id]);        
    (void)sound;
}

bool    arcade::LibOpenGl::initOpenAl() const {

    // Open Device
    ALCdevice* Device = alcOpenDevice(NULL);
    if (Device == nullptr) {
        std::cout << "No sound device found" << std::endl;
        return false;
    }
 
    // Create Context
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (Context == nullptr) {
        std::cout << "Failed to create context for sound" << std::endl;
        return false;
    }
 
    // Active Context
    if (!alcMakeContextCurrent(Context)) {
        std::cout << "Failed to active context for sound" << std::endl;
        return false;
    }
 
    return true;
}

void    arcade::LibOpenGl::shutDownOpenAl() {

    // Get context and device
    ALCcontext  *Context = alcGetCurrentContext();
    ALCdevice   *Device  = alcGetContextsDevice(Context);

    // Desable context
    alcMakeContextCurrent(NULL);

    // Destroy context
    alcDestroyContext(Context);

    // Close device
    alcCloseDevice(Device);

    // Delete sources
    for (size_t i = 0; i < this->_sounds.size(); i++) {
        alSourcei(this->_sounds[i], AL_BUFFER, 0);
        alDeleteSources(1, &this->_sounds[i]);
    }
}

void    test() {
    arcade::LibOpenGl   toto(800, 600);

    (void)toto;
}

int main() {
    test();
    return 0;
}