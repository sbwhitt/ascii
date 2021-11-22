#pragma once

#include <string>

class sprite {
    public:
        std::string raw;

        sprite(const char* sprite);
        sprite(std::string sprite);
        const char* get_sprite();
};
