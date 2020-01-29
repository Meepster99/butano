#ifndef BTN_BG_BLOCKS_MANAGER_H
#define BTN_BG_BLOCKS_MANAGER_H

#include "btn_bg_map_cell.h"
#include "btn_bg_palette_ptr.h"

namespace btn
{
    class size;
    class tile;
}

namespace btn::bg_blocks_manager
{
    void init();

    [[nodiscard]] int used_tiles_count();

    [[nodiscard]] int available_tiles_count();

    [[nodiscard]] int used_tile_blocks_count();

    [[nodiscard]] int available_tile_blocks_count();

    [[nodiscard]] int used_map_cells_count();

    [[nodiscard]] int available_map_cells_count();

    [[nodiscard]] int used_map_blocks_count();

    [[nodiscard]] int available_map_blocks_count();

    [[nodiscard]] optional<int> find_tiles(const span<const tile>& tiles_ref);

    [[nodiscard]] optional<int> find_map(const bg_map_cell& cells_ref, const size& map_dimensions,
                                         const bg_palette_ptr& palette_ptr);

    [[nodiscard]] optional<int> create_tiles(const span<const tile>& tiles_ref);

    [[nodiscard]] optional<int> create_map(const bg_map_cell& cells_ref, const size& map_dimensions,
                                           bg_palette_ptr&& palette_ptr);

    [[nodiscard]] optional<int> allocate_tiles(int tiles_count);

    [[nodiscard]] optional<int> allocate_map(const size& map_dimensions, bg_palette_ptr&& palette_ptr);

    void increase_usages(int id);

    void decrease_usages(int id);

    [[nodiscard]] int hw_tiles_id(int id);

    [[nodiscard]] int hw_map_id(int id);

    [[nodiscard]] int tiles_count(int id);

    [[nodiscard]] size map_dimensions(int id);

    [[nodiscard]] optional<span<const tile>> tiles_ref(int id);

    [[nodiscard]] const bg_map_cell* map_cells_ref(int id);

    void set_tiles_ref(int id, const span<const tile>& tiles_ref);

    void set_map_cells_ref(int id, const bg_map_cell& cells_ref, const size& map_dimensions);

    void reload(int id);

    [[nodiscard]] const bg_palette_ptr& map_palette(int id);

    void set_map_palette(int id, bg_palette_ptr&& palette_ptr);

    [[nodiscard]] optional<span<tile>> tiles_vram(int id);

    [[nodiscard]] optional<span<bg_map_cell>> map_vram(int id);

    void update();

    void commit();
}

#endif
