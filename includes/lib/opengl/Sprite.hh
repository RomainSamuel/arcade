//
// Author: Marwane Khsime 
// Date: 2017-04-04 05:51:10 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-04-04 05:51:10
//

#include <iostream>
#include <string>
#include <vector>

#include "ISprite.hh"

namespace arcade
{
    class   Sprite {
        private:
            std::vector<std::string>    _sprites;

        public:
            Sprite(const std::vector<std::string> &);
            ~Sprite();

            std::size_t spritesCount();
            std::string getGraphicPath(std::size_t pos) const;
            char getAscii(std::size_t pos) const;
    };
}