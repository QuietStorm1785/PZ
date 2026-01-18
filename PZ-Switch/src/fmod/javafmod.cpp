#include "fmod/javafmod.h"

#include <atomic>
#include <unordered_map>

#if defined(NINTENDO_SWITCH) || !defined(BUILD_FMOD_ENABLED)

namespace fmod {
namespace {
static std::atomic<long> gNextHandle{1};
static long makeHandle() { return gNextHandle.fetch_add(1); }
static long gMasterChannelGroup = 1;
}

void javafmod::init() {}

int javafmod::FMOD_System_Create() { return 0; }

int javafmod::FMOD_System_Init(int /*maxChannels*/, int /*studioInitFlags*/,
 int /*coreInitFlags*/) {
 if (gMasterChannelGroup == 1) {
 gMasterChannelGroup = makeHandle();
 }
 return 0;
}

int javafmod::FMOD_System_Update() { return 0; }

int javafmod::FMOD_System_Set3DSettings(float /*doppler*/, float /*distanceFactor*/,
 float /*rolloffScale*/) {
 return 0;
}

long javafmod::FMOD_System_CreateSound(const std::string & /*path*/, long /*mode*/) {
 return makeHandle();
}

long javafmod::FMOD_System_CreateRecordSound(long /*driverId*/, long /*channels*/,
 long /*frequency*/, long /*mode*/) {
 return makeHandle();
}

long javafmod::FMOD_System_CreateRAWPlaySound(long /*channels*/, long /*frequency*/,
 long /*mode*/) {
 return makeHandle();
}

long javafmod::FMOD_System_SetRawPlayBufferingPeriod(long /*milliseconds*/) {
 return 0;
}

int javafmod::FMOD_System_RAWPlayData(long /*channelHandle*/, const void * /*buffer*/,
 long /*bytes*/) {
 return 0;
}

int javafmod::FMOD_System_SetVADMode(int /*mode*/) { return 0; }

int javafmod::FMOD_System_SetRecordVolume(long /*percent*/) { return 0; }

int javafmod::FMOD_System_RecordStart(int /*driverId*/, long /*soundHandle*/,
 bool /*loop*/) {
 return 0;
}

int javafmod::FMOD_System_RecordStop(int /*driverId*/) { return 0; }

int javafmod::FMOD_System_GetRecordNumDrivers() { return 0; }

int javafmod::FMOD_System_GetRecordDriverInfo(int /*driverId*/, long /*infoHandle*/) {
 return 0;
}

int javafmod::FMOD_System_GetRecordPosition(int /*driverId*/, long /*positionHandle*/) {
 return 0;
}

long javafmod::FMOD_System_CreateChannelGroup(const std::string & /*name*/) {
 return makeHandle();
}

long javafmod::FMOD_System_GetMasterChannelGroup() { return gMasterChannelGroup; }

int javafmod::FMOD_System_PlaySound(long /*soundHandle*/, bool /*paused*/) {
 return static_cast<int>(makeHandle());
}

int javafmod::FMOD_System_PlayDSP() { return 0; }

int javafmod::FMOD_Channel_Stop(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetPaused(long /*channelHandle*/, bool /*paused*/) {
 return 0;
}

int javafmod::FMOD_Channel_SetVolume(long /*channelHandle*/, float /*volume*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetVolume(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_GetPaused(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_GetVolumeRamp(long /*channelHandle*/) { return 0; }

float javafmod::FMOD_Channel_GetAudibility(long /*channelHandle*/) { return 0.0f; }

int javafmod::FMOD_Channel_SetPitch(long /*channelHandle*/, float /*pitch*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetPitch(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetMute(long /*channelHandle*/, bool /*mute*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetMute(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetReverbProperties(long /*channelHandle*/, int /*instance*/,
 float /*level*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetReverbProperties(long /*channelHandle*/, int /*instance*/) {
 return 0;
}

int javafmod::FMOD_Channel_SetLowPassGain(long /*channelHandle*/, float /*gain*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetLowPassGain(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetMode(long /*channelHandle*/, long /*mode*/) { return 0; }

int javafmod::FMOD_Channel_GetMode(long /*channelHandle*/) { return 0; }

bool javafmod::FMOD_Channel_IsPlaying(long /*channelHandle*/) { return false; }

int javafmod::FMOD_Channel_SetPan(long /*channelHandle*/, float /*pan*/) { return 0; }

int javafmod::FMOD_Channel_Set3DAttributes(long /*channelHandle*/, float /*px*/, float /*py*/,
 float /*pz*/, float /*vx*/, float /*vy*/,
 float /*vz*/) {
 return 0;
}

int javafmod::FMOD_Channel_Set3DMinMaxDistance(long /*channelHandle*/, float /*minDistance*/,
 float /*maxDistance*/) {
 return 0;
}

int javafmod::FMOD_Channel_Set3DOcclusion(long /*channelHandle*/, float /*directOcclusion*/,
 float /*reverbOcclusion*/) {
 return 0;
}

int javafmod::FMOD_Channel_Set3DSpread(long /*channelHandle*/, float /*spread*/) { return 0; }

int javafmod::FMOD_Channel_Set3DLevel(long /*channelHandle*/, float /*level*/) { return 0; }

int javafmod::FMOD_Channel_Set3DDopplerLevel(long /*channelHandle*/, float /*level*/) {
 return 0;
}

int javafmod::FMOD_Channel_SetFrequency(long /*channelHandle*/, float /*frequency*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetFrequency(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetPriority(long /*channelHandle*/, int /*priority*/) {
 return 0;
}

int javafmod::FMOD_Channel_GetPriority(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_Channel_SetPosition(long /*channelHandle*/, long /*positionMs*/) {
 return 0;
}

long javafmod::FMOD_Channel_GetPosition(long /*channelHandle*/, int /*timeUnit*/) {
 return 0;
}

int javafmod::FMOD_Channel_SetChannelGroup(long /*channelHandle*/, long /*groupHandle*/) {
 return 0;
}

int javafmod::FMOD_Channel_SetLoopCount(long /*channelHandle*/, int /*loops*/) { return 0; }

int javafmod::FMOD_Channel_GetLoopCount(long /*channelHandle*/) { return 0; }

bool javafmod::FMOD_Channel_IsVirtual(long /*channelHandle*/) { return false; }

int javafmod::FMOD_Channel_GetCurrentSound(long /*channelHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_Stop(long /*groupHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_SetPaused(long /*groupHandle*/, bool /*paused*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_SetVolume(long /*groupHandle*/, float /*volume*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_SetVolumeRamp(long /*groupHandle*/, bool /*ramp*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_GetAudibility(long /*groupHandle*/, float *outAudibility) {
 if (outAudibility) {
 *outAudibility = 0.0f;
 }
 return 0;
}

int javafmod::FMOD_ChannelGroup_SetPitch(long /*groupHandle*/, float /*pitch*/) { return 0; }

int javafmod::FMOD_ChannelGroup_GetPitch(long /*groupHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_SetMute(long /*groupHandle*/, bool /*mute*/) { return 0; }

int javafmod::FMOD_ChannelGroup_GetMute(long /*groupHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_SetReverbProperties(long /*groupHandle*/, int /*instance*/,
 float /*level*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_SetLowPassGain(long /*groupHandle*/, float /*gain*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_GetLowPassGain(long /*groupHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_SetMode(long /*groupHandle*/, long /*mode*/) { return 0; }

int javafmod::FMOD_ChannelGroup_GetMode(long /*groupHandle*/) { return 0; }

int javafmod::FMOD_ChannelGroup_IsPlaying(long /*groupHandle*/, bool *outPlaying) {
 if (outPlaying) {
 *outPlaying = false;
 }
 return 0;
}

int javafmod::FMOD_ChannelGroup_SetPan(long /*groupHandle*/, float /*pan*/) { return 0; }

int javafmod::FMOD_ChannelGroup_GetVolume(long /*groupHandle*/, float *outVolume) {
 if (outVolume) {
 *outVolume = 0.0f;
 }
 return 0;
}

int javafmod::FMOD_ChannelGroup_GetVolumeRamp(long /*groupHandle*/, bool *outRamp) {
 if (outRamp) {
 *outRamp = false;
 }
 return 0;
}

int javafmod::FMOD_ChannelGroup_AddFadePoint(long /*groupHandle*/, long /*dspClock*/,
 float /*volume*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DMinMaxDistance(long /*groupHandle*/, float /*minDistance*/,
 float /*maxDistance*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DConeSettings(long /*groupHandle*/, float /*insideConeAngle*/,
 float /*outsideConeAngle*/, float /*outsideVolume*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DConeOrientation(long /*groupHandle*/, float /*x*/, float /*y*/,
 float /*z*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DCustomRolloff(long /*groupHandle*/, long /*pointsHandle*/,
 int /*numPoints*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DOcclusion(long /*groupHandle*/, float /*directOcclusion*/,
 float /*reverbOcclusion*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DSpread(long /*groupHandle*/, float /*spread*/) {
 return 0;
}

int javafmod::FMOD_ChannelGroup_Set3DLevel(long /*groupHandle*/, float /*level*/) { return 0; }

int javafmod::FMOD_ChannelGroup_Set3DDopplerLevel(long /*groupHandle*/, float /*level*/) {
 return 0;
}

int javafmod::FMOD_Sound_Release(long /*soundHandle*/) { return 0; }

int javafmod::FMOD_RAWPlaySound_Release(long /*soundHandle*/) { return 0; }

int javafmod::FMOD_RecordSound_Release(long /*soundHandle*/) { return 0; }

int javafmod::FMOD_Studio_System_Init(int /*maxChannels*/, int /*studioFlags*/, int /*flags*/) {
 return 0;
}

int javafmod::FMOD_Studio_System_Update() { return 0; }

void javafmod::FMOD_Studio_System_FlushCommands() {}

long javafmod::FMOD_Studio_System_LoadBankFile(const std::string & /*path*/) {
 return makeHandle();
}

long javafmod::FMOD_Studio_System_GetBus(const std::string & /*path*/) {
 return makeHandle();
}

long javafmod::FMOD_Studio_System_GetEvent(const std::string & /*path*/) {
 return makeHandle();
}

long javafmod::FMOD_Studio_System_CreateEventInstance(long /*eventDescriptionHandle*/) {
 return makeHandle();
}

int javafmod::FMOD_Studio_System_SetParameterByName(const std::string & /*name*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 return 0;
}

int javafmod::FMOD_Studio_System_SetParameterByID(long /*parameterIdHandle*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 return 0;
}

int javafmod::FMOD_Studio_LoadSampleData(long /*bankOrEventHandle*/) { return 0; }

void javafmod::FMOD_Studio_LoadEventSampleData(long /*eventHandle*/) {}

int javafmod::FMOD_Studio_Listener3D(int /*listener*/, float /*px*/, float /*py*/, float /*pz*/,
 float /*vx*/, float /*vy*/, float /*vz*/, float /*fx*/, float /*fy*/,
 float /*fz*/, float /*ux*/, float /*uy*/, float /*uz*/) {
 return 0;
}

int javafmod::FMOD_Studio_SetNumListeners(int /*numListeners*/) { return 0; }

void javafmod::FMOD_Studio_StartEvent(long /*eventInstanceHandle*/) {}

long javafmod::FMOD_Studio_GetTimelinePosition(long /*eventInstanceHandle*/) { return 0; }

int javafmod::FMOD_Studio_EventInstance_SetCallback(long /*eventInstanceHandle*/, long /*callback*/,
 long /*mask*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterByID(long /*eventInstanceHandle*/,
 long /*parameterIdHandle*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterByName(long /*eventInstanceHandle*/,
 const std::string & /*name*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetReverbLevel(long /*eventInstanceHandle*/, int /*index*/,
 float /*level*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterValueByIndex(long /*eventInstanceHandle*/, int /*index*/,
 float /*value*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetVolume(long /*eventInstanceHandle*/, float /*volume*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_Stop(long /*eventInstanceHandle*/, bool /*allowFadeOut*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_GetPlaybackState(long /*eventInstanceHandle*/) { return 0; }

int javafmod::FMOD_Studio_EventInstance_GetTimelinePosition(long /*eventInstanceHandle*/) { return 0; }

int javafmod::FMOD_Studio_EventInstance_Release(long /*eventInstanceHandle*/) { return 0; }

int javafmod::FMOD_Studio_EventInstance3D(long /*eventInstanceHandle*/, float /*px*/, float /*py*/,
 float /*pz*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventInstance3D(long /*eventInstanceHandle*/, float /*px*/, float /*py*/, float /*pz*/,
 float /*vx*/, float /*vy*/, float /*vz*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventDescription_GetInstanceCount(long /*eventDescriptionHandle*/) {
 return 0;
}

int javafmod::FMOD_Studio_EventDescription_GetInstanceList(long /*eventDescriptionHandle*/, long * /*handles*/,
 int /*capacity*/) {
 return 0;
}

int javafmod::FMOD_Studio_Bus_SetMute(long /*busHandle*/, bool /*mute*/) { return 0; }

int javafmod::FMOD_Studio_Bus_SetPaused(long /*busHandle*/, bool /*paused*/) { return 0; }

long javafmod::FMOD_Studio_GetPlaybackState(long /*eventInstanceHandle*/) { return 0; }

long javafmod::FMOD_Studio_GetParameterValue(long /*eventInstanceHandle*/, const std::string & /*name*/) {
 return 0;
}

long javafmod::FMOD_Studio_GetParameterValue(long /*eventInstanceHandle*/, long /*parameterIdHandle*/) {
 return 0;
}

void javafmodJNI::init() {}

} // namespace fmod

#else

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

#include <mutex>
#include <string>
#include <vector>

namespace fmod {
namespace {
static std::atomic<long> gNextHandle{1};
static long makeHandle() { return gNextHandle.fetch_add(1); }

static FMOD::System *gCore = nullptr;
static FMOD::Studio::System *gStudio = nullptr;
static long gMasterChannelGroup = 0;

static std::unordered_map<long, FMOD::Sound *> gSounds;
static std::unordered_map<long, FMOD::Channel *> gChannels;
static std::unordered_map<long, FMOD::ChannelGroup *> gChannelGroups;
static std::unordered_map<long, FMOD::Studio::Bank *> gBanks;
static std::unordered_map<long, FMOD::Studio::EventDescription *> gEventDescriptions;
static std::unordered_map<long, FMOD::Studio::EventInstance *> gEventInstances;
static std::unordered_map<long, FMOD::Studio::Bus *> gBuses;

int toInt(FMOD_RESULT r) { return static_cast<int>(r); }

template <typename T>
T *lookup(std::unordered_map<long, T *> &map, long handle) {
 auto it = map.find(handle);
 return it == map.end() ? nullptr : it->second;
}

FMOD_VECTOR vec(float x, float y, float z) {
 FMOD_VECTOR v{0};
 v.x = x;
 v.y = y;
 v.z = z;
 return v;
}

FMOD_3D_ATTRIBUTES attrs(float px, float py, float pz, float vx, float vy,
 float vz) {
 FMOD_3D_ATTRIBUTES a{};
 a.position = vec(px, py, pz);
 a.velocity = vec(vx, vy, vz);
 a.forward = vec(0, 0, 1);
 a.up = vec(0, 1, 0);
 return a;
}
} // namespace

void javafmod::init() {}

int javafmod::FMOD_System_Create() {
 if (gCore) {
 return FMOD_OK;
 }
 FMOD_RESULT r = FMOD::System_Create(&gCore);
 return toInt(r);
}

int javafmod::FMOD_System_Init(int maxChannels, int studioInitFlags,
 int coreInitFlags) {
 FMOD_RESULT r = FMOD::Studio::System::create(&gStudio);
 if (r != FMOD_OK) {
 return toInt(r);
 }
 r = gStudio->initialize(maxChannels, studioInitFlags, coreInitFlags, nullptr);
 if (r != FMOD_OK) {
 return toInt(r);
 }
 gStudio->getCoreSystem(&gCore);
 FMOD::ChannelGroup *master = nullptr;
 if (gCore && gCore->getMasterChannelGroup(&master) == FMOD_OK && master) {
 gMasterChannelGroup = makeHandle();
 gChannelGroups[gMasterChannelGroup] = master;
 }
 return FMOD_OK;
}

int javafmod::FMOD_System_Update() {
 if (gStudio) {
 return toInt(gStudio->update());
 }
 return FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_System_Set3DSettings(float doppler, float distanceFactor,
 float rolloffScale) {
 if (!gCore) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 return toInt(gCore->set3DSettings(doppler, distanceFactor, rolloffScale));
}

long javafmod::FMOD_System_CreateSound(const std::string &path, long mode) {
 if (!gCore) {
 return 0;
 }
 FMOD::Sound *sound = nullptr;
 FMOD_RESULT r = gCore->createSound(path.c_str(), static_cast<FMOD_MODE>(mode),
 nullptr, &sound);
 if (r != FMOD_OK) {
 return 0;
 }
 long handle = makeHandle();
 gSounds[handle] = sound;
 return handle;
}

long javafmod::FMOD_System_CreateRecordSound(long driverId, long channels,
 long frequency, long mode) {
 (void)driverId;
 (void)channels;
 (void)frequency;
 (void)mode;
 return 0; // not implemented
}

long javafmod::FMOD_System_CreateRAWPlaySound(long channels, long frequency,
 long mode) {
 (void)channels;
 (void)frequency;
 (void)mode;
 return 0; // not implemented
}

long javafmod::FMOD_System_SetRawPlayBufferingPeriod(long /*milliseconds*/) {
 return 0;
}

int javafmod::FMOD_System_RAWPlayData(long /*channelHandle*/, const void * /*buffer*/,
 long /*bytes*/) {
 return FMOD_OK;
}

int javafmod::FMOD_System_SetVADMode(int /*mode*/) { return FMOD_OK; }

int javafmod::FMOD_System_SetRecordVolume(long /*percent*/) { return FMOD_OK; }

int javafmod::FMOD_System_RecordStart(int /*driverId*/, long /*soundHandle*/,
 bool /*loop*/) {
 return FMOD_OK;
}

int javafmod::FMOD_System_RecordStop(int /*driverId*/) { return FMOD_OK; }

int javafmod::FMOD_System_GetRecordNumDrivers() { return 0; }

int javafmod::FMOD_System_GetRecordDriverInfo(int /*driverId*/, long /*infoHandle*/) {
 return FMOD_OK;
}

int javafmod::FMOD_System_GetRecordPosition(int /*driverId*/, long /*positionHandle*/) {
 return FMOD_OK;
}

long javafmod::FMOD_System_CreateChannelGroup(const std::string &name) {
 if (!gCore) {
 return 0;
 }
 FMOD::ChannelGroup *group = nullptr;
 FMOD_RESULT r = gCore->createChannelGroup(name.c_str(), &group);
 if (r != FMOD_OK || !group) {
 return 0;
 }
 long handle = makeHandle();
 gChannelGroups[handle] = group;
 return handle;
}

long javafmod::FMOD_System_GetMasterChannelGroup() { return gMasterChannelGroup; }

int javafmod::FMOD_System_PlaySound(long soundHandle, bool paused) {
 if (!gCore) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 FMOD::Sound *sound = lookup(gSounds, soundHandle);
 if (!sound) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 FMOD::Channel *channel = nullptr;
 FMOD_RESULT r = gCore->playSound(sound, nullptr, paused, &channel);
 if (r != FMOD_OK || !channel) {
 return toInt(r);
 }
 long handle = makeHandle();
 gChannels[handle] = channel;
 return static_cast<int>(handle);
}

int javafmod::FMOD_System_PlayDSP() { return FMOD_OK; }

int javafmod::FMOD_Channel_Stop(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->stop()) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetPaused(long channelHandle, bool paused) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setPaused(paused)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetVolume(long channelHandle, float volume) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setVolume(volume)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetVolume(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float vol = 0.0f;
 return ch ? toInt(ch->getVolume(&vol)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetPaused(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 bool paused = false;
 return ch ? toInt(ch->getPaused(&paused)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetVolumeRamp(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 bool ramp = false;
 return ch ? toInt(ch->getVolumeRamp(&ramp)) : FMOD_ERR_INVALID_HANDLE;
}

float javafmod::FMOD_Channel_GetAudibility(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float aud = 0.0f;
 if (ch) {
 ch->getAudibility(&aud);
 }
 return aud;
}

int javafmod::FMOD_Channel_SetPitch(long channelHandle, float pitch) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setPitch(pitch)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetPitch(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float pitch = 0.0f;
 return ch ? toInt(ch->getPitch(&pitch)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetMute(long channelHandle, bool mute) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setMute(mute)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetMute(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 bool mute = false;
 return ch ? toInt(ch->getMute(&mute)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetReverbProperties(long channelHandle, int instance,
 float level) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setReverbProperties(instance, level))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetReverbProperties(long channelHandle, int instance) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float level = 0.0f;
 return ch ? toInt(ch->getReverbProperties(instance, &level))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetLowPassGain(long channelHandle, float gain) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setLowPassGain(gain)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetLowPassGain(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float gain = 0.0f;
 return ch ? toInt(ch->getLowPassGain(&gain)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetMode(long channelHandle, long mode) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setMode(static_cast<FMOD_MODE>(mode)))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetMode(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 FMOD_MODE m{};
 return ch ? toInt(ch->getMode(&m)) : FMOD_ERR_INVALID_HANDLE;
}

bool javafmod::FMOD_Channel_IsPlaying(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 bool playing = false;
 if (ch) {
 ch->isPlaying(&playing);
 }
 return playing;
}

int javafmod::FMOD_Channel_SetPan(long channelHandle, float pan) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setPan(pan)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DAttributes(long channelHandle, float px, float py,
 float pz, float vx, float vy,
 float vz) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 FMOD_VECTOR pos = vec(px, py, pz);
 FMOD_VECTOR vel = vec(vx, vy, vz);
 return ch ? toInt(ch->set3DAttributes(&pos, &vel)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DMinMaxDistance(long channelHandle, float minDistance,
 float maxDistance) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->set3DMinMaxDistance(minDistance, maxDistance))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DOcclusion(long channelHandle, float directOcclusion,
 float reverbOcclusion) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->set3DOcclusion(directOcclusion, reverbOcclusion))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DSpread(long channelHandle, float spread) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->set3DSpread(spread)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DLevel(long channelHandle, float level) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->set3DLevel(level)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_Set3DDopplerLevel(long channelHandle, float level) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->set3DDopplerLevel(level)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetFrequency(long channelHandle, float frequency) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setFrequency(frequency)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetFrequency(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 float freq = 0.0f;
 return ch ? toInt(ch->getFrequency(&freq)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetPriority(long channelHandle, int priority) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setPriority(priority)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetPriority(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 int priority = 0;
 return ch ? toInt(ch->getPriority(&priority)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_SetPosition(long channelHandle, long positionMs) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setPosition(static_cast<unsigned int>(positionMs),
 FMOD_TIMEUNIT_MS))
 : FMOD_ERR_INVALID_HANDLE;
}

long javafmod::FMOD_Channel_GetPosition(long channelHandle, int timeUnit) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 unsigned int pos = 0;
 if (ch && ch->getPosition(&pos, static_cast<FMOD_TIMEUNIT>(timeUnit)) ==
 FMOD_OK) {
 return static_cast<long>(pos);
 }
 return 0;
}

int javafmod::FMOD_Channel_SetChannelGroup(long channelHandle, long groupHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 if (!ch || !grp) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 return toInt(ch->setChannelGroup(grp));
}

int javafmod::FMOD_Channel_SetLoopCount(long channelHandle, int loops) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 return ch ? toInt(ch->setLoopCount(loops)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Channel_GetLoopCount(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 int loops = 0;
 return ch ? toInt(ch->getLoopCount(&loops)) : FMOD_ERR_INVALID_HANDLE;
}

bool javafmod::FMOD_Channel_IsVirtual(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 bool isVirtual = false;
 if (ch) {
 ch->isVirtual(&isVirtual);
 }
 return isVirtual;
}

int javafmod::FMOD_Channel_GetCurrentSound(long channelHandle) {
 FMOD::Channel *ch = lookup(gChannels, channelHandle);
 FMOD::Sound *snd = nullptr;
 if (ch && ch->getCurrentSound(&snd) == FMOD_OK) {
 for (const auto &kv : gSounds) {
 if (kv.second == snd) {
 return static_cast<int>(kv.first);
 }
 }
 }
 return 0;
}

int javafmod::FMOD_ChannelGroup_Stop(long groupHandle) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->stop()) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetPaused(long groupHandle, bool paused) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setPaused(paused)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetVolume(long groupHandle, float volume) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setVolume(volume)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetVolumeRamp(long groupHandle, bool ramp) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setVolumeRamp(ramp)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetAudibility(long groupHandle, float *outAudibility) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 if (!grp) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 if (outAudibility) {
 grp->getAudibility(outAudibility);
 }
 return FMOD_OK;
}

int javafmod::FMOD_ChannelGroup_SetPitch(long groupHandle, float pitch) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setPitch(pitch)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetPitch(long groupHandle) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 float pitch = 0.0f;
 return grp ? toInt(grp->getPitch(&pitch)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetMute(long groupHandle, bool mute) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setMute(mute)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetMute(long groupHandle) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 bool mute = false;
 return grp ? toInt(grp->getMute(&mute)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetReverbProperties(long groupHandle, int instance,
 float level) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setReverbProperties(instance, level))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetLowPassGain(long groupHandle, float gain) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setLowPassGain(gain)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetLowPassGain(long groupHandle) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 float gain = 0.0f;
 return grp ? toInt(grp->getLowPassGain(&gain)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_SetMode(long groupHandle, long mode) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setMode(static_cast<FMOD_MODE>(mode)))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetMode(long groupHandle) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 FMOD_MODE mode{};
 return grp ? toInt(grp->getMode(&mode)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_IsPlaying(long groupHandle, bool *outPlaying) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 if (!grp) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 bool playing = false;
 grp->isPlaying(&playing);
 if (outPlaying) {
 *outPlaying = playing;
 }
 return FMOD_OK;
}

int javafmod::FMOD_ChannelGroup_SetPan(long groupHandle, float pan) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->setPan(pan)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_GetVolume(long groupHandle, float *outVolume) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 float volume = 0.0f;
 int r = grp ? toInt(grp->getVolume(&volume)) : FMOD_ERR_INVALID_HANDLE;
 if (grp && outVolume) {
 *outVolume = volume;
 }
 return r;
}

int javafmod::FMOD_ChannelGroup_GetVolumeRamp(long groupHandle, bool *outRamp) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 bool ramp = false;
 int r = grp ? toInt(grp->getVolumeRamp(&ramp)) : FMOD_ERR_INVALID_HANDLE;
 if (grp && outRamp) {
 *outRamp = ramp;
 }
 return r;
}

int javafmod::FMOD_ChannelGroup_AddFadePoint(long groupHandle, long dspClock,
 float volume) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->addFadePoint(static_cast<unsigned long long>(dspClock),
 volume))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DMinMaxDistance(long groupHandle, float minDistance,
 float maxDistance) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DMinMaxDistance(minDistance, maxDistance))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DConeSettings(long groupHandle, float insideConeAngle,
 float outsideConeAngle, float outsideVolume) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DConeSettings(insideConeAngle, outsideConeAngle,
 outsideVolume))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DConeOrientation(long groupHandle, float x,
 float y, float z) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 FMOD_VECTOR v = vec(x, y, z);
 return grp ? toInt(grp->set3DConeOrientation(&v)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DCustomRolloff(long groupHandle, long /*pointsHandle*/,
 int /*numPoints*/) {
 (void)groupHandle;
 return FMOD_OK;
}

int javafmod::FMOD_ChannelGroup_Set3DOcclusion(long groupHandle, float directOcclusion,
 float reverbOcclusion) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DOcclusion(directOcclusion, reverbOcclusion))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DSpread(long groupHandle, float spread) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DSpread(spread)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DLevel(long groupHandle, float level) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DLevel(level)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_ChannelGroup_Set3DDopplerLevel(long groupHandle, float level) {
 FMOD::ChannelGroup *grp = lookup(gChannelGroups, groupHandle);
 return grp ? toInt(grp->set3DDopplerLevel(level)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Sound_Release(long soundHandle) {
 FMOD::Sound *snd = lookup(gSounds, soundHandle);
 if (!snd) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 int r = toInt(snd->release());
 gSounds.erase(soundHandle);
 return r;
}

int javafmod::FMOD_RAWPlaySound_Release(long soundHandle) { return FMOD_Sound_Release(soundHandle); }

int javafmod::FMOD_RecordSound_Release(long soundHandle) { return FMOD_Sound_Release(soundHandle); }

int javafmod::FMOD_Studio_System_Init(int maxChannels, int studioFlags, int coreFlags) {
 return FMOD_System_Init(maxChannels, studioFlags, coreFlags);
}

int javafmod::FMOD_Studio_System_Update() { return FMOD_System_Update(); }

void javafmod::FMOD_Studio_System_FlushCommands() {
 if (gStudio) {
 gStudio->flushCommands();
 }
}

long javafmod::FMOD_Studio_System_LoadBankFile(const std::string &path) {
 if (!gStudio) {
 return 0;
 }
 FMOD::Studio::Bank *bank = nullptr;
 FMOD_RESULT r = gStudio->loadBankFile(path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL,
 &bank);
 if (r != FMOD_OK || !bank) {
 return 0;
 }
 long handle = makeHandle();
 gBanks[handle] = bank;
 return handle;
}

long javafmod::FMOD_Studio_System_GetBus(const std::string &path) {
 if (!gStudio) {
 return 0;
 }
 FMOD::Studio::Bus *bus = nullptr;
 FMOD_RESULT r = gStudio->getBus(path.c_str(), &bus);
 if (r != FMOD_OK || !bus) {
 return 0;
 }
 long handle = makeHandle();
 gBuses[handle] = bus;
 return handle;
}

long javafmod::FMOD_Studio_System_GetEvent(const std::string &path) {
 if (!gStudio) {
 return 0;
 }
 FMOD::Studio::EventDescription *desc = nullptr;
 FMOD_RESULT r = gStudio->getEvent(path.c_str(), &desc);
 if (r != FMOD_OK || !desc) {
 return 0;
 }
 long handle = makeHandle();
 gEventDescriptions[handle] = desc;
 return handle;
}

long javafmod::FMOD_Studio_System_CreateEventInstance(long eventDescriptionHandle) {
 FMOD::Studio::EventDescription *desc = lookup(gEventDescriptions, eventDescriptionHandle);
 if (!desc) {
 return 0;
 }
 FMOD::Studio::EventInstance *inst = nullptr;
 FMOD_RESULT r = desc->createInstance(&inst);
 if (r != FMOD_OK || !inst) {
 return 0;
 }
 long handle = makeHandle();
 gEventInstances[handle] = inst;
 return handle;
}

int javafmod::FMOD_Studio_System_SetParameterByName(const std::string &name, float value,
 bool ignoreSeekSpeed) {
 if (!gStudio) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 return toInt(gStudio->setParameterByName(name.c_str(), value, ignoreSeekSpeed));
}

int javafmod::FMOD_Studio_System_SetParameterByID(long /*parameterIdHandle*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 return FMOD_ERR_UNSUPPORTED;
}

int javafmod::FMOD_Studio_LoadSampleData(long bankOrEventHandle) {
 if (auto *bank = lookup(gBanks, bankOrEventHandle)) {
 return toInt(bank->loadSampleData());
 }
 if (auto *desc = lookup(gEventDescriptions, bankOrEventHandle)) {
 return toInt(desc->loadSampleData());
 }
 return FMOD_ERR_INVALID_HANDLE;
}

void javafmod::FMOD_Studio_LoadEventSampleData(long eventHandle) {
 if (auto *desc = lookup(gEventDescriptions, eventHandle)) {
 desc->loadSampleData();
 }
}

int javafmod::FMOD_Studio_Listener3D(int listener, float px, float py, float pz,
 float vx, float vy, float vz, float fx, float fy,
 float fz, float ux, float uy, float uz) {
 if (!gStudio) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 FMOD_3D_ATTRIBUTES a{};
 a.position = vec(px, py, pz);
 a.velocity = vec(vx, vy, vz);
 a.forward = vec(fx, fy, fz);
 a.up = vec(ux, uy, uz);
 return toInt(gStudio->setListenerAttributes(listener, &a));
}

int javafmod::FMOD_Studio_SetNumListeners(int numListeners) {
 if (!gStudio) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 return toInt(gStudio->setNumListeners(numListeners));
}

void javafmod::FMOD_Studio_StartEvent(long eventInstanceHandle) {
 if (auto *inst = lookup(gEventInstances, eventInstanceHandle)) {
 inst->start();
 }
}

long javafmod::FMOD_Studio_GetTimelinePosition(long eventInstanceHandle) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 int pos = 0;
 if (inst && inst->getTimelinePosition(&pos) == FMOD_OK) {
 return static_cast<long>(pos);
 }
 return 0;
}

int javafmod::FMOD_Studio_EventInstance_SetCallback(long /*eventInstanceHandle*/, long /*callback*/,
 long /*mask*/) {
 return FMOD_OK;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterByID(long eventInstanceHandle,
 long /*parameterIdHandle*/, float /*value*/,
 bool /*ignoreSeekSpeed*/) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? FMOD_ERR_UNSUPPORTED : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterByName(long eventInstanceHandle,
 const std::string &name, float value,
 bool ignoreSeekSpeed) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? toInt(inst->setParameterByName(name.c_str(), value, ignoreSeekSpeed))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_SetReverbLevel(long eventInstanceHandle, int index,
 float level) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? toInt(inst->setReverbLevel(index, level)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_SetParameterValueByIndex(long eventInstanceHandle,
 int index, float value) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? toInt(inst->setParameterByIndex(index, value)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_SetVolume(long eventInstanceHandle, float volume) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? toInt(inst->setVolume(volume)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_Stop(long eventInstanceHandle, bool allowFadeOut) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 return inst ? toInt(inst->stop(allowFadeOut ? FMOD_STUDIO_STOP_ALLOWFADEOUT
 : FMOD_STUDIO_STOP_IMMEDIATE))
 : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_GetPlaybackState(long eventInstanceHandle) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 FMOD_STUDIO_PLAYBACK_STATE state{};
 return inst ? toInt(inst->getPlaybackState(&state)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventInstance_GetTimelinePosition(long eventInstanceHandle) {
 return static_cast<int>(FMOD_Studio_GetTimelinePosition(eventInstanceHandle));
}

int javafmod::FMOD_Studio_EventInstance_Release(long eventInstanceHandle) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 if (!inst) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 int r = toInt(inst->release());
 gEventInstances.erase(eventInstanceHandle);
 return r;
}

int javafmod::FMOD_Studio_EventInstance3D(long eventInstanceHandle, float px, float py,
 float pz) {
 return FMOD_Studio_EventInstance3D(eventInstanceHandle, px, py, pz, 0, 0, 0);
}

int javafmod::FMOD_Studio_EventInstance3D(long eventInstanceHandle, float px, float py,
 float pz, float vx, float vy, float vz) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 if (!inst) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 FMOD_3D_ATTRIBUTES a = attrs(px, py, pz, vx, vy, vz);
 return toInt(inst->set3DAttributes(&a));
}

int javafmod::FMOD_Studio_EventDescription_GetInstanceCount(long eventDescriptionHandle) {
 FMOD::Studio::EventDescription *desc = lookup(gEventDescriptions, eventDescriptionHandle);
 int count = 0;
 return desc ? toInt(desc->getInstanceCount(&count)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_EventDescription_GetInstanceList(long eventDescriptionHandle,
 long *handles, int capacity) {
 FMOD::Studio::EventDescription *desc = lookup(gEventDescriptions, eventDescriptionHandle);
 if (!desc || !handles || capacity <= 0) {
 return FMOD_ERR_INVALID_HANDLE;
 }
 std::vector<FMOD::Studio::EventInstance *> list(capacity);
 int count = 0;
 FMOD_RESULT r = desc->getInstanceList(list.data(), capacity, &count);
 if (r != FMOD_OK) {
 return toInt(r);
 }
 for (int i = 0; i < count; ++i) {
 long h = 0;
 for (const auto &kv : gEventInstances) {
 if (kv.second == list[i]) {
 h = kv.first;
 break;
 }
 }
 if (h == 0) {
 h = makeHandle();
 gEventInstances[h] = list[i];
 }
 handles[i] = h;
 }
 return count;
}

int javafmod::FMOD_Studio_Bus_SetMute(long busHandle, bool mute) {
 FMOD::Studio::Bus *bus = lookup(gBuses, busHandle);
 return bus ? toInt(bus->setMute(mute)) : FMOD_ERR_INVALID_HANDLE;
}

int javafmod::FMOD_Studio_Bus_SetPaused(long busHandle, bool paused) {
 FMOD::Studio::Bus *bus = lookup(gBuses, busHandle);
 return bus ? toInt(bus->setPaused(paused)) : FMOD_ERR_INVALID_HANDLE;
}

long javafmod::FMOD_Studio_GetPlaybackState(long eventInstanceHandle) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 FMOD_STUDIO_PLAYBACK_STATE state{};
 if (inst && inst->getPlaybackState(&state) == FMOD_OK) {
 return static_cast<long>(state);
 }
 return 0;
}

long javafmod::FMOD_Studio_GetParameterValue(long eventInstanceHandle, const std::string &name) {
 FMOD::Studio::EventInstance *inst = lookup(gEventInstances, eventInstanceHandle);
 float value = 0.0f, finalValue = 0.0f;
 if (inst && inst->getParameterByName(name.c_str(), &value, &finalValue) == FMOD_OK) {
 return static_cast<long>(value);
 }
 return 0;
}

long javafmod::FMOD_Studio_GetParameterValue(long eventInstanceHandle, long /*parameterIdHandle*/) {
 return FMOD_Studio_GetParameterValue(eventInstanceHandle, std::string());
}

void javafmodJNI::init() {}

} // namespace fmod

#endif
