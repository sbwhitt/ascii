#include <string>

#include "sprite.h"

sprite::sprite(const char* sprite) {
    this->raw = sprite;
}

sprite::sprite(std::string sprite) {
    this->raw = sprite;
}

const char* sprite::get_sprite() {
    return this->raw.c_str();
}
