/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_HW_AUDIO_H
#define BN_HW_AUDIO_H

#include "maxmod.h"
#include "bn_dmg_music_type.h"
#include "bn_dmg_music_master_volume.h"

namespace bn::hw::audio
{
    void init();

    void enable();

    void disable();

    [[nodiscard]] bool music_playing();

    void play_music(int id, bool loop);

    void stop_music();

    void pause_music();

    void resume_music();

    [[nodiscard]] inline int music_position()
    {
        return int(mmGetPosition());
    }

    inline void set_music_position(int position)
    {
        mmSetPosition(mm_word(position));
    }

    inline void set_music_volume(int volume)
    {
        mmSetModuleVolume(mm_word(volume));
    }

    inline void set_music_tempo(int tempo)
    {
        mmSetModuleTempo(mm_word(tempo));
    }

    inline void set_music_pitch(int pitch)
    {
        mmSetModulePitch(mm_word(pitch));
    }

    [[nodiscard]] inline bool jingle_playing()
    {
        return mmActiveSub();
    }

    inline void play_jingle(int id)
    {
        mmJingle(mm_word(id));
    }

    inline void set_jingle_volume(int volume)
    {
        mmSetJingleVolume(mm_word(volume));
    }

    [[nodiscard]] bool dmg_music_playing();

    void play_dmg_music(const void* song, dmg_music_type type, int speed, bool loop);

    void stop_dmg_music();

    void pause_dmg_music();

    void resume_dmg_music();

    void dmg_music_position(int& pattern, int& row);

    void set_dmg_music_position(int pattern, int row);

    void set_dmg_music_volume(int left_volume, int right_volume);

    void set_dmg_music_master_volume(dmg_music_master_volume volume);

    [[nodiscard]] inline bool sound_active(mm_sfxhand handle)
    {
        return mmEffectActive(handle);
    }

    [[nodiscard]] mm_sfxhand play_sound(int priority, int id);

    [[nodiscard]] mm_sfxhand play_sound(int priority, int id, int volume, int speed, int panning);

    void stop_sound(mm_sfxhand handle);

    void release_sound(mm_sfxhand handle);

    inline void set_sound_speed(mm_sfxhand handle, int speed_scale)
    {
        if(mmEffectActive(handle))
        {
            mmEffectScaleRate(handle, unsigned(speed_scale));
        }
    }

    inline void set_sound_panning(mm_sfxhand handle, int panning)
    {
        if(mmEffectActive(handle))
        {
            mmEffectPanning(handle, uint8_t(panning));
        }
    }

    void stop_all_sounds();

    inline void set_sound_master_volume(int volume)
    {
        mmSetEffectsVolume(mm_word(volume));
    }

    [[nodiscard]] bool update_on_vblank();

    void set_update_on_vblank(bool update_on_vblank);

    void disable_vblank_handler();

    void update(bool dmg_sync);

    void update_sounds_queue();

    void commit();
}

#endif
