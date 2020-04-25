#ifndef BF_TITLE_H
#define BF_TITLE_H

#include "btn_fixed.h"
#include "btn_vector.h"
#include "btn_display.h"
#include "btn_sprite_actions.h"
#include "btn_sprite_hblank_effects.h"
#include "btn_third_sprite_attributes.h"
#include "bf_scene.h"

namespace btn
{
    class sprite_text_generator;
}

namespace bf
{

class title : public scene
{

public:
    title(btn::sprite_text_generator& text_generator);

    title(const title& other) = delete;

    title& operator=(const title& other) = delete;

    [[nodiscard]] btn::optional<scene_type> update() final;

private:
    btn::sprite_ptr _butano_up_sprite;
    btn::sprite_ptr _butano_down_sprite;
    btn::vector<btn::sprite_ptr, 6> _butano_characters;
    btn::vector<btn::sprite_ptr, 7> _fighter_characters;
    btn::vector<btn::sprite_ptr, 4> _high_score_text_sprites;
    btn::vector<btn::sprite_ptr, 2> _start_text_sprites;
    btn::vector<btn::sprite_ptr, 2> _credits_text_sprites;
    btn::sprite_ptr _cursor_sprite;
    btn::fixed _butano_y_inc = -4.05;
    btn::vector<btn::third_sprite_attributes, btn::display::height()> _butano_up_hblank_effect_attributes;
    btn::third_sprite_attributes_hblank_effect_ptr _butano_up_hblank_effect;
    btn::vector<btn::third_sprite_attributes, btn::display::height()> _butano_down_hblank_effect_attributes;
    btn::third_sprite_attributes_hblank_effect_ptr _butano_down_hblank_effect;
    btn::optional<btn::sprite_move_to_action> _cursor_move_action;
    bool _start_selected = true;
    bool _butano_y_up = true;

    void _animate_butano();
};

}

#endif