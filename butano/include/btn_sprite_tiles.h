#ifndef BTN_SPRITE_TILES_H
#define BTN_SPRITE_TILES_H

#include "btn_common.h"

namespace btn::sprite_tiles
{
    [[nodiscard]] int used_tiles_count();

    [[nodiscard]] int available_tiles_count();

    [[nodiscard]] int used_items_count();

    [[nodiscard]] int available_items_count();
}

#endif