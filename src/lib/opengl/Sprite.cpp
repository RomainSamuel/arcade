//
// Author: Marwane Khsime 
// Date: 2017-04-04 05:59:58 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-04-04 05:59:58
//

#include "Sprite.hpp"

arcade::Sprite::Sprite(const std::vector<std::string> &sprites)
    : _sprites(sprites) {
}

arcade::Sprite::~Sprite() {
}

std::size_t arcade::Sprite::spritesCount() {
    return this->_sprites.size();
}

std::string arcade::Sprite::getGraphicPath(std::size_t pos) const {
    return pos >= this->_sprites.size() ? "" : this->_sprites[pos];
}

char    arcade::Sprite::getAscii(std::size_t pos) const {
    return pos >= this->_sprites.size() ? '\0' : this->_sprites[pos].at(0);
}