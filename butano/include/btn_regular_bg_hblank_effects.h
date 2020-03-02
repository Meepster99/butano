#ifndef BTN_REGULAR_BG_HBLANK_EFFECTS_H
#define BTN_REGULAR_BG_HBLANK_EFFECTS_H

#include "btn_regular_bg_ptr.h"
#include "btn_hblank_effect_ptr.h"

namespace btn
{

class regular_bg_position_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static regular_bg_position_hblank_effect_ptr create_horizontal(
            regular_bg_ptr bg_ptr, const span<const fixed>& deltas_ref);

    [[nodiscard]] static optional<regular_bg_position_hblank_effect_ptr> optional_create_horizontal(
            regular_bg_ptr bg_ptr, const span<const fixed>& deltas_ref);

    [[nodiscard]] static regular_bg_position_hblank_effect_ptr create_vertical(
            regular_bg_ptr bg_ptr, const span<const fixed>& deltas_ref);

    [[nodiscard]] static optional<regular_bg_position_hblank_effect_ptr> optional_create_vertical(
            regular_bg_ptr bg_ptr, const span<const fixed>& deltas_ref);

    [[nodiscard]] span<const fixed> deltas_ref() const;

    void set_deltas_ref(const span<const fixed>& deltas_ref);

    void reload_deltas_ref();

private:
    regular_bg_ptr _bg_ptr;

    regular_bg_position_hblank_effect_ptr(int id, regular_bg_ptr&& bg_ptr);
};

}

#endif
