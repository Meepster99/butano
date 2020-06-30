#ifndef BTN_SPRITE_HBLANK_EFFECTS_H
#define BTN_SPRITE_HBLANK_EFFECTS_H

#include "btn_sprite_ptr.h"
#include "btn_hblank_effect_ptr.h"

namespace btn
{

class sprite_position_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_position_hblank_effect_ptr create_horizontal(
            sprite_ptr sprite, const span<const fixed>& deltas_ref);

    [[nodiscard]] static optional<sprite_position_hblank_effect_ptr> create_horizontal_optional(
            sprite_ptr sprite, const span<const fixed>& deltas_ref);

    [[nodiscard]] static sprite_position_hblank_effect_ptr create_vertical(
            sprite_ptr sprite, const span<const fixed>& deltas_ref);

    [[nodiscard]] static optional<sprite_position_hblank_effect_ptr> create_vertical_optional(
            sprite_ptr sprite, const span<const fixed>& deltas_ref);

    sprite_position_hblank_effect_ptr(const sprite_position_hblank_effect_ptr& other) = default;

    sprite_position_hblank_effect_ptr& operator=(const sprite_position_hblank_effect_ptr& other) = default;

    sprite_position_hblank_effect_ptr(sprite_position_hblank_effect_ptr&& other) noexcept;

    sprite_position_hblank_effect_ptr& operator=(sprite_position_hblank_effect_ptr&& other) noexcept;

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] span<const fixed> deltas_ref() const;

    void set_deltas_ref(const span<const fixed>& deltas_ref);

    void reload_deltas_ref();

    void swap(sprite_position_hblank_effect_ptr& other);

    friend void swap(sprite_position_hblank_effect_ptr& a, sprite_position_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    sprite_ptr _sprite;

    sprite_position_hblank_effect_ptr(int id, sprite_ptr&& sprite);
};

class sprite_first_attributes_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_first_attributes_hblank_effect_ptr create(
            sprite_ptr sprite, const span<const sprite_first_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_first_attributes_hblank_effect_ptr> create_optional(
            sprite_ptr sprite, const span<const sprite_first_attributes>& attributes_ref);

    sprite_first_attributes_hblank_effect_ptr(const sprite_first_attributes_hblank_effect_ptr& other) = default;

    sprite_first_attributes_hblank_effect_ptr& operator=(
            const sprite_first_attributes_hblank_effect_ptr& other) = default;

    sprite_first_attributes_hblank_effect_ptr(sprite_first_attributes_hblank_effect_ptr&& other) noexcept;

    sprite_first_attributes_hblank_effect_ptr& operator=(sprite_first_attributes_hblank_effect_ptr&& other) noexcept;

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] span<const sprite_first_attributes> attributes_ref() const;

    void set_attributes_ref(const span<const sprite_first_attributes>& attributes_ref);

    void reload_attributes_ref();

    void swap(sprite_first_attributes_hblank_effect_ptr& other);

    friend void swap(sprite_first_attributes_hblank_effect_ptr& a, sprite_first_attributes_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    sprite_ptr _sprite;

    sprite_first_attributes_hblank_effect_ptr(int id, sprite_ptr&& sprite);
};


class sprite_regular_second_attributes_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_regular_second_attributes_hblank_effect_ptr create(
            sprite_ptr sprite, const span<const sprite_regular_second_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_regular_second_attributes_hblank_effect_ptr> create_optional(
            sprite_ptr sprite, const span<const sprite_regular_second_attributes>& attributes_ref);

    sprite_regular_second_attributes_hblank_effect_ptr(
            const sprite_regular_second_attributes_hblank_effect_ptr& other) = default;

    sprite_regular_second_attributes_hblank_effect_ptr& operator=(
            const sprite_regular_second_attributes_hblank_effect_ptr& other) = default;

    sprite_regular_second_attributes_hblank_effect_ptr(
            sprite_regular_second_attributes_hblank_effect_ptr&& other) noexcept;

    sprite_regular_second_attributes_hblank_effect_ptr& operator=(
            sprite_regular_second_attributes_hblank_effect_ptr&& other) noexcept;

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] span<const sprite_regular_second_attributes> attributes_ref() const;

    void set_attributes_ref(const span<const sprite_regular_second_attributes>& attributes_ref);

    void reload_attributes_ref();

    void swap(sprite_regular_second_attributes_hblank_effect_ptr& other);

    friend void swap(sprite_regular_second_attributes_hblank_effect_ptr& a,
                     sprite_regular_second_attributes_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    sprite_ptr _sprite;

    sprite_regular_second_attributes_hblank_effect_ptr(int id, sprite_ptr&& sprite);
};


class sprite_affine_second_attributes_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_second_attributes_hblank_effect_ptr create(
            sprite_ptr sprite, const span<const sprite_affine_second_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_second_attributes_hblank_effect_ptr> create_optional(
            sprite_ptr sprite, const span<const sprite_affine_second_attributes>& attributes_ref);

    sprite_affine_second_attributes_hblank_effect_ptr(
            const sprite_affine_second_attributes_hblank_effect_ptr& other) = default;

    sprite_affine_second_attributes_hblank_effect_ptr& operator=(
            const sprite_affine_second_attributes_hblank_effect_ptr& other) = default;

    sprite_affine_second_attributes_hblank_effect_ptr(
            sprite_affine_second_attributes_hblank_effect_ptr&& other) noexcept;

    sprite_affine_second_attributes_hblank_effect_ptr& operator=(
            sprite_affine_second_attributes_hblank_effect_ptr&& other) noexcept;

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] span<const sprite_affine_second_attributes> attributes_ref() const;

    void set_attributes_ref(const span<const sprite_affine_second_attributes>& attributes_ref);

    void reload_attributes_ref();

    void swap(sprite_affine_second_attributes_hblank_effect_ptr& other);

    friend void swap(sprite_affine_second_attributes_hblank_effect_ptr& a,
                     sprite_affine_second_attributes_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    sprite_ptr _sprite;

    sprite_affine_second_attributes_hblank_effect_ptr(int id, sprite_ptr&& sprite);
};


class sprite_third_attributes_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_third_attributes_hblank_effect_ptr create(
            sprite_ptr sprite, const span<const sprite_third_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_third_attributes_hblank_effect_ptr> create_optional(
            sprite_ptr sprite, const span<const sprite_third_attributes>& attributes_ref);

    sprite_third_attributes_hblank_effect_ptr(const sprite_third_attributes_hblank_effect_ptr& other) = default;

    sprite_third_attributes_hblank_effect_ptr& operator=(
            const sprite_third_attributes_hblank_effect_ptr& other) = default;

    sprite_third_attributes_hblank_effect_ptr(sprite_third_attributes_hblank_effect_ptr&& other) noexcept;

    sprite_third_attributes_hblank_effect_ptr& operator=(sprite_third_attributes_hblank_effect_ptr&& other) noexcept;

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] span<const sprite_third_attributes> attributes_ref() const;

    void set_attributes_ref(const span<const sprite_third_attributes>& attributes_ref);

    void reload_attributes_ref();

    void swap(sprite_third_attributes_hblank_effect_ptr& other);

    friend void swap(sprite_third_attributes_hblank_effect_ptr& a, sprite_third_attributes_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    sprite_ptr _sprite;

    sprite_third_attributes_hblank_effect_ptr(int id, sprite_ptr&& sprite);
};

}

#endif
