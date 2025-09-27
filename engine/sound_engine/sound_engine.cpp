#include "sound_engine.h"
#include <iostream>

SoundEngine::~SoundEngine()
{
    shutdown();
}

bool SoundEngine::ok(FMOD_RESULT r, const char *what)
{
    if (r != FMOD_OK)
    {
        std::cerr << "[FMOD] " << what << " failed: " << FMOD_ErrorString(r) << "\n";
        return false;
    }
    return true;
}

bool SoundEngine::init(int maxChannels)
{
    if (mSystem) return true;

    FMOD_RESULT r = FMOD::System_Create(&mSystem);
    if (!ok(r, "System_Create")) return false;

    r = mSystem->init(maxChannels, FMOD_INIT_NORMAL, nullptr);
    if (!ok(r, "System::init")) return false;

    mSystem->set3DSettings(1.0f, 1.0f, 1.0f); // dopplerScale, distanceFactor, rolloffScale
    return true;
}

void SoundEngine::shutdown()
{
    if (!mSystem) return;

    for (auto &[id, rec]: mSounds)
    {
        if (rec.sound) rec.sound->release();
    }
    mSounds.clear();
    mChannels.clear();

    mSystem->close();
    mSystem->release();
    mSystem = nullptr;
}

void SoundEngine::update()
{
    if (mSystem) mSystem->update();
}

int SoundEngine::load(const std::string &path, bool loop, bool is3D,
                      float minDistance, float maxDistance)
{
    if (!mSystem)
    {
        std::cerr << "SoundEngine not initialized\n";
        return 0;
    }

    FMOD_MODE mode = FMOD_DEFAULT;
    mode |= loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    mode |= is3D ? FMOD_3D : FMOD_2D;

    FMOD::Sound *snd = nullptr;
    FMOD_RESULT r = mSystem->createSound(path.c_str(), mode, nullptr, &snd);
    if (!ok(r, "createSound")) return 0;

    if (is3D)
    {
        snd->set3DMinMaxDistance(minDistance, maxDistance);
    }

    int id = mNextSoundId++;
    mSounds[id] = SoundRec{snd, loop, is3D};
    return id;
}

void SoundEngine::unload(int soundId)
{
    auto it = mSounds.find(soundId);
    if (it == mSounds.end()) return;
    if (it->second.sound) it->second.sound->release();
    mSounds.erase(it);
}

int SoundEngine::play(int soundId, float volume, float pitch, bool paused)
{
    if (!mSystem) return 0;
    auto it = mSounds.find(soundId);
    if (it == mSounds.end()) return 0;

    FMOD::Channel *ch = nullptr;
    FMOD_RESULT r = mSystem->playSound(it->second.sound, nullptr, paused, &ch);
    if (!ok(r, "playSound") || !ch) return 0;

    ch->setVolume(volume);
    ch->setPitch(pitch);

    int cid = mNextChannelId++;
    mChannels[cid] = ChannelRec{ch};
    return cid;
}

void SoundEngine::pause(int channelId, bool pause_)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;
    it->second.ch->setPaused(pause_);
}

void SoundEngine::stop(int channelId)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;
    it->second.ch->stop();
}

void SoundEngine::setChannelVolume(int channelId, float volume)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;
    it->second.ch->setVolume(volume);
}

void SoundEngine::setChannelPitch(int channelId, float pitch)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;
    it->second.ch->setPitch(pitch);
}

void SoundEngine::setChannelLooping(int channelId, bool loop)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;

    FMOD::Sound *s = nullptr;
    it->second.ch->getCurrentSound(&s);
    if (!s) return;

    FMOD_MODE mode;
    s->getMode(&mode);
    mode &= ~(FMOD_LOOP_OFF | FMOD_LOOP_NORMAL);
    mode |= loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    s->setMode(mode);
}

void SoundEngine::setListener(const Vec3 &pos, const Vec3 &forward, const Vec3 &up, const Vec3 &velocity)
{
    if (!mSystem) return;
    FMOD_VECTOR p = toFmod(pos);
    FMOD_VECTOR v = toFmod(velocity);
    FMOD_VECTOR f = toFmod(forward);
    FMOD_VECTOR u = toFmod(up);
    mSystem->set3DListenerAttributes(0, &p, &v, &f, &u);
}

void SoundEngine::setChannel3DPosition(int channelId, const Vec3 &pos, const Vec3 &velocity)
{
    auto it = mChannels.find(channelId);
    if (it == mChannels.end() || !it->second.ch) return;
    FMOD_VECTOR p = toFmod(pos);
    FMOD_VECTOR v = toFmod(velocity);
    it->second.ch->set3DAttributes(&p, &v);
}

