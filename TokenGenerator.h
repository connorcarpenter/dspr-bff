#pragma once

//
// Created by connor on 8/3/18.
//

#include <string>

namespace DsprBff
{
    class TokenGenerator
    {
    public:
        std::string generate_playertoken();
    private:
        const int playerTokenLength = 16;
    };
}