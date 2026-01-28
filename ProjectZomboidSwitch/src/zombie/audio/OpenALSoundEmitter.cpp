#include "zombie/audio/OpenALSoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>

#include <stdexcept>
#include <iostream>
#include "zombie/audio/stb_vorbis.h"

namespace zombie {
namespace audio {

OpenALSoundEmitter::OpenALSoundEmitter() {
    // OpenAL context setup could go here if needed
}

OpenALSoundEmitter::~OpenALSoundEmitter() {
    stopAll();
}

void OpenALSoundEmitter::randomStart() {}
void OpenALSoundEmitter::setPos(float x, float y, float z) {
    for (auto& [id, inst] : sounds_) {
        alSource3f(inst.source, AL_POSITION, x, y, z);
    }
}
int OpenALSoundEmitter::stopSound(int64_t id) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        alSourceStop(it->second.source);
        alDeleteSources(1, &it->second.source);
        alDeleteBuffers(1, &it->second.buffer);
        sounds_.erase(it);
        return 1;
    }
    return 0;
}
void OpenALSoundEmitter::stopSoundLocal(int64_t id) { stopSound(id); }
int OpenALSoundEmitter::stopSoundByName(const std::string& name) {
    int count = 0;
    for (auto it = sounds_.begin(); it != sounds_.end();) {
        if (it->second.name == name) {
            alSourceStop(it->second.source);
            alDeleteSources(1, &it->second.source);
            alDeleteBuffers(1, &it->second.buffer);
            it = sounds_.erase(it);
            ++count;
        } else {
            ++it;
        }
    }
    return count;
}
void OpenALSoundEmitter::stopOrTriggerSound(int64_t id) { stopSound(id); }
void OpenALSoundEmitter::stopOrTriggerSoundByName(const std::string& name) { stopSoundByName(name); }
void OpenALSoundEmitter::setVolume(int64_t id, float volume) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        alSourcef(it->second.source, AL_GAIN, volume);
    }
}
void OpenALSoundEmitter::setPitch(int64_t id, float pitch) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        alSourcef(it->second.source, AL_PITCH, pitch);
    }
}
bool OpenALSoundEmitter::hasSustainPoints(int64_t /*id*/) { return false; }
void OpenALSoundEmitter::setParameterValue(int64_t /*id*/, const std::string& /*param*/, float /*value*/) {}
void OpenALSoundEmitter::setTimelinePosition(int64_t /*id*/, const std::string& /*position*/) {}
void OpenALSoundEmitter::triggerCue(int64_t /*id*/) {}
void OpenALSoundEmitter::setVolumeAll(float volume) {
    for (auto& [id, inst] : sounds_) {
        alSourcef(inst.source, AL_GAIN, volume);
    }
}
void OpenALSoundEmitter::stopAll() {
    for (auto& [id, inst] : sounds_) {
        alSourceStop(inst.source);
        alDeleteSources(1, &inst.source);
        alDeleteBuffers(1, &inst.buffer);
    }
    sounds_.clear();
}
int64_t OpenALSoundEmitter::playSound(const std::string& name) {
    int64_t id = nextId_++;
    SoundInstance inst;
    inst.name = name;


    ALuint buffer = 0;
    ALenum error = AL_NO_ERROR;
    bool loaded = false;

#ifdef ALUT_API_MAJOR_VERSION
    buffer = alutCreateBufferFromFile(name.c_str());
    error = alGetError();
    if (buffer != 0 && error == AL_NO_ERROR) {
        loaded = true;
    }
#endif

    // If not loaded, try .ogg with stb_vorbis
    if (!loaded) {
        FILE* f = fopen(name.c_str(), "rb");
        if (f) {
            fseek(f, 0, SEEK_END);
            long len = ftell(f);
            fseek(f, 0, SEEK_SET);
            std::vector<unsigned char> data(len);
            fread(data.data(), 1, len, f);
            fclose(f);

            int error = 0;
            stb_vorbis* vorbis = stb_vorbis_open_memory(data.data(), (int)data.size(), &error, nullptr);
            if (vorbis) {
                stb_vorbis_info info;
                stb_vorbis_get_info(vorbis, &info);
                int samples = stb_vorbis_stream_length_in_samples(vorbis);
                std::vector<short> pcm(samples * info.channels);
                int samples_decoded = stb_vorbis_get_samples_short_interleaved(vorbis, info.channels, pcm.data(), (int)pcm.size());
                stb_vorbis_close(vorbis);
                if (samples_decoded > 0) {
                    alGenBuffers(1, &buffer);
                    ALenum format = (info.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
                    alBufferData(buffer, format, pcm.data(), samples_decoded * info.channels * sizeof(short), info.sample_rate);
                    loaded = true;
                }
            }
        }
    }

    if (!loaded) {
        std::cerr << "OpenAL: Failed to load sound file (WAV or OGG): " << name << std::endl;
        return -1;
    }

    inst.buffer = buffer;
    ALuint source = 0;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    inst.source = source;

    sounds_[id] = inst;
    return id;
}
int64_t OpenALSoundEmitter::playSound(const std::string& name, zombie::characters::IsoGameCharacter* /*character*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSound(const std::string& name, int /*x*/, int /*y*/, int /*z*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSound(const std::string& name, zombie::iso::IsoGridSquare* /*square*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSoundImpl(const std::string& name, zombie::iso::IsoGridSquare* /*square*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSound(const std::string& name, bool /*flag*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSoundImpl(const std::string& name, bool /*flag*/, zombie::iso::IsoObject* /*obj*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSound(const std::string& name, zombie::iso::IsoObject* /*obj*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playSoundImpl(const std::string& name, zombie::iso::IsoObject* /*obj*/) { return playSound(name); }
int64_t OpenALSoundEmitter::playClip(GameSoundClip& /*clip*/, zombie::iso::IsoObject* /*obj*/) { return playSound(""); }
int64_t OpenALSoundEmitter::playAmbientSound(const std::string& name) { return playSound(name); }
int64_t OpenALSoundEmitter::playSoundLooped(const std::string& name) {
    int64_t id = playSound(name);
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        it->second.loop = true;
        alSourcei(it->second.source, AL_LOOPING, AL_TRUE);
    }
    return id;
}
int64_t OpenALSoundEmitter::playSoundLoopedImpl(const std::string& name) { return playSoundLooped(name); }
int64_t OpenALSoundEmitter::playAmbientLoopedImpl(const std::string& name) { return playSoundLooped(name); }
void OpenALSoundEmitter::set3D(int64_t id, bool is3D) {
    // OpenAL is always 3D; this can be a stub or set source spatialization
}
void OpenALSoundEmitter::tick() { cleanupStopped(); }
bool OpenALSoundEmitter::hasSoundsToStart() const { return !sounds_.empty(); }
bool OpenALSoundEmitter::isEmpty() const { return sounds_.empty(); }
bool OpenALSoundEmitter::isPlaying(int64_t id) const {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        ALint state;
        alGetSourcei(it->second.source, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }
    return false;
}
bool OpenALSoundEmitter::isPlaying(const std::string& name) const {
    for (const auto& [id, inst] : sounds_) {
        if (inst.name == name) {
            ALint state;
            alGetSourcei(inst.source, AL_SOURCE_STATE, &state);
            if (state == AL_PLAYING) return true;
        }
    }
    return false;
}
bool OpenALSoundEmitter::restart(int64_t id) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        alSourceRewind(it->second.source);
        alSourcePlay(it->second.source);
        return true;
    }
    return false;
}
void OpenALSoundEmitter::cleanupStopped() {
    for (auto it = sounds_.begin(); it != sounds_.end();) {
        ALint state;
        alGetSourcei(it->second.source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            alDeleteSources(1, &it->second.source);
            alDeleteBuffers(1, &it->second.buffer);
            it = sounds_.erase(it);
        } else {
            ++it;
        }
    }
}

// --- OpenAL SoundEmitter implementation ---
void OpenALSoundEmitter::initOpenAL() {
    // OpenAL: alcOpenDevice, alcCreateContext
    if (!device_) {
        device_ = alcOpenDevice(nullptr); // default device
        if (!device_) {
            std::cerr << "OpenAL: Failed to open device" << std::endl;
            return;
        }
        context_ = alcCreateContext(device_, nullptr);
        if (!context_ || !alcMakeContextCurrent(context_)) {
            std::cerr << "OpenAL: Failed to create or set context" << std::endl;
            if (context_) alcDestroyContext(context_);
            alcCloseDevice(device_);
            device_ = nullptr;
            context_ = nullptr;
        }
    }
}

void OpenALSoundEmitter::releaseOpenAL() {
    // OpenAL: alcDestroyContext, alcCloseDevice
    if (context_) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context_);
        context_ = nullptr;
    }
    if (device_) {
        alcCloseDevice(device_);
        device_ = nullptr;
    }
}

void OpenALSoundEmitter::updateOpenAL() {
    // OpenAL: No direct equivalent
    // No action needed for OpenAL
}

void OpenALSoundEmitter::set3DListenerAttributesOpenAL(float x, float y, float z, float vx, float vy, float vz, float fx, float fy, float fz, float ux, float uy, float uz) {
    // OpenAL: alListener3f, alListenerfv
    // TODO: Set listener position, velocity, orientation using OpenAL
}

void OpenALSoundEmitter::setLoopCountOpenAL(int64_t id, int loopCount) {
    // OpenAL: alSourcei(AL_LOOPING, ...)
    // TODO: Set looping on source; OpenAL only supports infinite or no looping
}

float OpenALSoundEmitter::getPositionOpenAL(int64_t id) {
    // OpenAL: alGetSourcef(AL_SEC_OFFSET, ...)
    // TODO: Query playback position
    return 0.0f;
}

void OpenALSoundEmitter::setPositionOpenAL(int64_t id, float seconds) {
    // OpenAL: alSourcef(AL_SEC_OFFSET, ...)
    // TODO: Set playback position
}

void OpenALSoundEmitter::setMuteOpenAL(int64_t id, bool mute) {
    // OpenAL: alSourcef(AL_GAIN, 0.0f) for mute
    // TODO: Implement mute logic
}

bool OpenALSoundEmitter::getMuteOpenAL(int64_t id) const {
    // OpenAL: Query AL_GAIN == 0.0f
    // TODO: Implement mute query
    return false;
}

void OpenALSoundEmitter::setPanOpenAL(int64_t id, float pan) {
    // OpenAL: alSource3f(AL_POSITION, ...)
    // TODO: Implement panning logic
}

void OpenALSoundEmitter::addGroupOpenAL(int64_t id) {
    // OpenAL: No direct equivalent
    // Stub for compatibility
}

void OpenALSoundEmitter::setGroupVolumeOpenAL(int64_t id, float volume) {
    // OpenAL: No direct equivalent
    // Stub for compatibility
}

void OpenALSoundEmitter::stopGroupOpenAL(int64_t id) {
    // OpenAL: No direct equivalent
    // Stub for compatibility
}

void OpenALSoundEmitter::createChannelGroupOpenAL(const std::string& groupName) {
    // OpenAL: No direct equivalent
    // Stub for compatibility
}

void OpenALSoundEmitter::setReverbPropertiesOpenAL(float decayTime, float density, float diffusion) {
    // OpenAL: alEffect/alAuxiliaryEffectSlot (EAX extensions)
    // TODO: Implement reverb properties if EFX is available
}

void OpenALSoundEmitter::setChannelReverbPropertiesOpenAL(int64_t id, float reverbLevel) {
    // OpenAL: alSourcef/alSourcei with EFX extensions
    // TODO: Implement per-channel reverb if EFX is available
}

void OpenALSoundEmitter::playSoundOpenAL(const std::string& soundName) {
    // OpenAL: alSourcePlay
    // TODO: Implement actual OpenAL playback if needed
}

void OpenALSoundEmitter::setPausedOpenAL(int64_t id, bool paused) {
    // OpenAL: alSourcePause/alSourcePlay
    // TODO: Implement pause/resume logic using OpenAL
}

void OpenALSoundEmitter::set3DAttributesOpenAL(int64_t id, float x, float y, float z) {
    // OpenAL: alSource3f(AL_POSITION, ...)
    // TODO: Set 3D position using OpenAL
}

void OpenALSoundEmitter::setVolumeOpenAL(int64_t id, float volume) {
    // OpenAL: alSourcef(AL_GAIN, ...)
    setVolume(id, volume);
}

// All FMOD-style methods removed; use OpenAL methods directly.

} // namespace audio
} // namespace zombie
