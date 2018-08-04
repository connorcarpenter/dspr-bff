//
// Created by connor on 8/3/18.
//

#include <sstream>
#include "TokenGenerator.h"

namespace DsprBff
{
    std::string TokenGenerator::generate_playertoken()
    {
        std::stringstream output;
        for(int i=0;i<playerTokenLength;i++)
        {
            char c = 'a' + rand() % 26;
            output << c;
        }
        return output.str();
    }
}
