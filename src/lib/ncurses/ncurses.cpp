//
// Author: Marwane Khsime 
// Date: 2017-04-08 17:48:59 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-04-08 17:48:59
//


#include <iostream>
#include <ncurses.h>
#include "ncurses.hh"
 
/*
 * Constructor
 */
arcade::LibNcurses::LibNcurses() : _width(200), _height(200)
{
    std::cout << "Lib Ncurses Launched" << std::endl;

    // Init NCurses Window
    initscr();

    if (!(this->_screen = newterm(NULL, stderr, stdin))) {
        throw std::string("Failed to create Ncurses Window.");
    }

    set_term(this->_screen);

    set_escdelay(1);
    cbreak();
    curs_set(0);
    noecho();


    // Init Keyboard and Mouse
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED, NULL);

    start_color();

    // Colors
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_RED);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);

    refresh();
}

/*
 * Destructor
 */
arcade::LibNcurses::~LibNcurses() {
    this->_sprites.clear();
    clrtoeol();
    refresh();
    delscreen(this->_screen);
    endwin();
}

/*
** Note: doesn't support mouse.
*/
bool    arcade::LibNcurses::pollEvent(arcade::Event &e)
{

    return 0;
    char                c;

    struct  pollfd      fds;

    fds.fd = 0;
    fds.events = POLLIN;

    if (poll(&fds, 1, 0)) {

        noecho();

        if (fds.revents & POLLIN) {

        arcade::MousePos    current;
        arcade::MousePos    last;    

        current.x = 0;
        current.y = 0;
        last.x = 0;
        last.y = 0;

        e.pos_rel = last;
        e.pos_abs = current;
 
        e.action = arcade::ActionType::AT_PRESSED;
        e.type = arcade::EventType::ET_KEYBOARD;

        c = getch();

        if (arcade::_ncursesKeyboardKeys.find(c) != arcade::_ncursesKeyboardKeys.end())
            e.kb_key = (arcade::KeyboardKey)arcade::_ncursesKeyboardKeys.find(c)->second;
        else
            e.kb_key = (arcade::KeyboardKey)-1;

        return true;

        }
    }

    return false;
}

/*
**  GRAPHIC
*/

std::size_t arcade::LibNcurses::getColorInCurses(const arcade::Color &color) {

    if (color.r > 0 && color.g > 0 && color.b > 0) {
        // WHITE
        return 1;
    }

    if (color.r > 0) {
        
        if (color.b > 0) {
            // YELLOW
            return 5;
        }

        if (color.g > 0) {
            // MAGENTA
            return 6;
        }

        // RED
        return 2;
    }

    if (color.g > 0) {

        if (color.b > 0) {
            // CYAN
            return 7;
        }

        // GREEN
        return 3;
    }

    if (color.b > 0) {
        // BLUE
        return 4;
    }

    // BLACK
    return 0;
}

void    arcade::LibNcurses::updateMap(arcade::IMap const &map)
{

    // Save Map properties
    std::size_t  nbLayers = map.getLayerNb();
    std::size_t  height = map.getHeight();
    std::size_t  width = map.getWidth();

    for (std::size_t layer = 0; layer < nbLayers; layer++) {

            for (std::size_t x = 0; x < width; x++) {

                for (std::size_t y = 0; y < height; y++) {

                    // Check if the tile is a sprite
                    if (map.at(layer, x, y).hasSprite())
                        drawTileSprite(map.at(layer, x, y), x, y, this->getColorInCurses(map.at(0, x, y).getColor()));
                    // If not, get the color
                    else {
                        drawTileColor(map.at(layer, x, y), x, y);
                    }
                }
            }
    }
}   

void    arcade::LibNcurses::drawTileColor(arcade::ITile const &tile, std::size_t x, std::size_t y) {

    std::size_t colorIndex = this->getColorInCurses(tile.getColor());

    attron(COLOR_PAIR(colorIndex));
    attron(A_REVERSE);
    mvprintw(START_Y + y, START_X + x, " ");
    attroff(COLOR_PAIR(colorIndex));
    attroff(A_NORMAL);
}

void    arcade::LibNcurses::drawTileSprite(arcade::ITile const &tile,
                                          std::size_t x,
                                          std::size_t y,
                                          std::size_t bgColorSprite) {

    if (this->_sprites.find(tile.getSpriteId()) == this->_sprites.end()) {
        return ;
    }

    std::size_t colorIndex = this->getColorInCurses(tile.getColor());

    // Modify the init_color to save the background color
    init_pair(0, colorIndex, bgColorSprite);

    attron(COLOR_PAIR(0));
 
    char    c = this->_sprites[tile.getSpriteId()].at(tile.getSpritePos());

    mvprintw(START_Y + y, START_X + x, &c);

    attroff(COLOR_PAIR(0));
}


void    arcade::LibNcurses::updateGUI(arcade::IGUI &GUI)
{
    for (std::size_t i = 0; i < GUI.size(); i++) {
        this->drawComponent(GUI.at(i));
    }
}

void    arcade::LibNcurses::drawComponent(const arcade::IComponent &component) {
    // Draw the text 
    this->drawComponentText(component);
}

void    arcade::LibNcurses::drawComponentText(const arcade::IComponent &component) {

    std::string text = component.getText();
    attron(COLOR_PAIR(1));
    mvprintw(START_Y + component.getY(), START_X + component.getX(), text.c_str());
    attroff(COLOR_PAIR(1));

}

void    arcade::LibNcurses::display()
{
    refresh();
}

void    arcade::LibNcurses::loadSprites(std::vector<std::unique_ptr<arcade::ISprite> > &&sprites)
{
    // Delete old sprites
    this->_sprites.clear();

    // Load news
    for (std::size_t i = 0; i < sprites.size(); i++) {

        for (std::size_t nSprite = 0; nSprite < sprites[i]->spritesCount(); nSprite++) {

            this->_sprites[i].push_back(sprites[i]->getAscii(nSprite));

        }
    }
}

// Clear Screen
void    arcade::LibNcurses::clear()
{
    erase();
}

/*
**  SOUND
*/
bool    arcade::LibNcurses::doesSupportSound() const
{ 
    return (true);
}

void    arcade::LibNcurses::loadSounds(std::vector<std::pair<std::string, arcade::SoundType>> const &soundsToLoad)
{
    this->_soundManager.loadSounds(soundsToLoad);
}

void    arcade::LibNcurses::soundControl(const Sound &soundToControl)
{
    this->_soundManager.soundControl(soundToControl);
}

extern "C" arcade::IGfxLib  *getLib()
{
    return (new arcade::LibNcurses());
}
