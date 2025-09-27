#pragma once

#include <string>
#include <unordered_map>

#include <fmod.hpp>
#include <fmod_errors.h>

struct Vec3
{
    float x{0}, y{0}, z{0};
};

class SoundEngine
{
public:
    SoundEngine() = default;

    ~SoundEngine();

    bool init(int maxChannels = 512);

    void shutdown();

    void update();

    int load(const std::string &path, bool loop = false, bool is3D = false,
             float minDistance = 1.0f, float maxDistance = 100.0f);

    void unload(int soundId);

    int play(int soundId, float volume = 1.0f, float pitch = 1.0f, bool paused = false);

    void pause(int channelId, bool pause);

    void stop(int channelId);

    void setChannelVolume(int channelId, float volume);     // 0..1
    void setChannelPitch(int channelId, float pitch);
    void setChannelLooping(int channelId, bool loop);

    void setListener(const Vec3 &pos, const Vec3 &forward, const Vec3 &up, const Vec3 &velocity = {});

    void setChannel3DPosition(int channelId, const Vec3 &pos, const Vec3 &velocity = {});

private:
    struct SoundRec
    {
        FMOD::Sound *sound{nullptr};
        bool loop{false};
        bool is3D{false};
    };
    struct ChannelRec
    {
        FMOD::Channel *ch{nullptr};
    };

    FMOD::System *mSystem{nullptr};
    std::unordered_map<int, SoundRec> mSounds;
    std::unordered_map<int, ChannelRec> mChannels;
    int mNextSoundId{1};
    int mNextChannelId{1};

    static FMOD_VECTOR toFmod(const Vec3 &v)
    { return FMOD_VECTOR{v.x, v.y, v.z}; }

    bool ok(FMOD_RESULT r, const char *what);
};
