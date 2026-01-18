#pragma once

#include <cstdint>
#include <string>

namespace fmod {

class javafmod {
public:
 static void init();

 static int FMOD_System_Create();
 static int FMOD_System_Init(int maxChannels, int studioInitFlags, int coreInitFlags);
 static int FMOD_System_Update();
 static int FMOD_System_Set3DSettings(float doppler, float distanceFactor, float rolloffScale);

 static long FMOD_System_CreateSound(const std::string &path, long mode);
 static long FMOD_System_CreateRecordSound(long driverId, long channels, long frequency, long mode);
 static long FMOD_System_CreateRAWPlaySound(long channels, long frequency, long mode);
 static long FMOD_System_SetRawPlayBufferingPeriod(long milliseconds);
 static int FMOD_System_RAWPlayData(long channelHandle, const void *buffer, long bytes);
 static int FMOD_System_SetVADMode(int mode);
 static int FMOD_System_SetRecordVolume(long percent);
 static int FMOD_System_RecordStart(int driverId, long soundHandle, bool loop);
 static int FMOD_System_RecordStop(int driverId);
 static int FMOD_System_GetRecordNumDrivers();
 static int FMOD_System_GetRecordDriverInfo(int driverId, long infoHandle);
 static int FMOD_System_GetRecordPosition(int driverId, long positionHandle);

 static long FMOD_System_CreateChannelGroup(const std::string &name);
 static long FMOD_System_GetMasterChannelGroup();
 static int FMOD_System_PlaySound(long soundHandle, bool paused);
 static int FMOD_System_PlayDSP();

 static int FMOD_Channel_Stop(long channelHandle);
 static int FMOD_Channel_SetPaused(long channelHandle, bool paused);
 static int FMOD_Channel_SetVolume(long channelHandle, float volume);
 static int FMOD_Channel_GetVolume(long channelHandle);
 static int FMOD_Channel_GetPaused(long channelHandle);
 static int FMOD_Channel_GetVolumeRamp(long channelHandle);
 static float FMOD_Channel_GetAudibility(long channelHandle);
 static int FMOD_Channel_SetPitch(long channelHandle, float pitch);
 static int FMOD_Channel_GetPitch(long channelHandle);
 static int FMOD_Channel_SetMute(long channelHandle, bool mute);
 static int FMOD_Channel_GetMute(long channelHandle);
 static int FMOD_Channel_SetReverbProperties(long channelHandle, int instance, float level);
 static int FMOD_Channel_GetReverbProperties(long channelHandle, int instance);
 static int FMOD_Channel_SetLowPassGain(long channelHandle, float gain);
 static int FMOD_Channel_GetLowPassGain(long channelHandle);
 static int FMOD_Channel_SetMode(long channelHandle, long mode);
 static int FMOD_Channel_GetMode(long channelHandle);
 static bool FMOD_Channel_IsPlaying(long channelHandle);
 static int FMOD_Channel_SetPan(long channelHandle, float pan);
 static int FMOD_Channel_Set3DAttributes(long channelHandle, float px, float py, float pz, float vx, float vy, float vz);
 static int FMOD_Channel_Set3DMinMaxDistance(long channelHandle, float minDistance, float maxDistance);
 static int FMOD_Channel_Set3DOcclusion(long channelHandle, float directOcclusion, float reverbOcclusion);
 static int FMOD_Channel_Set3DSpread(long channelHandle, float spread);
 static int FMOD_Channel_Set3DLevel(long channelHandle, float level);
 static int FMOD_Channel_Set3DDopplerLevel(long channelHandle, float level);
 static int FMOD_Channel_SetFrequency(long channelHandle, float frequency);
 static int FMOD_Channel_GetFrequency(long channelHandle);
 static int FMOD_Channel_SetPriority(long channelHandle, int priority);
 static int FMOD_Channel_GetPriority(long channelHandle);
 static int FMOD_Channel_SetPosition(long channelHandle, long positionMs);
 static long FMOD_Channel_GetPosition(long channelHandle, int timeUnit);
 static int FMOD_Channel_SetChannelGroup(long channelHandle, long groupHandle);
 static int FMOD_Channel_SetLoopCount(long channelHandle, int loops);
 static int FMOD_Channel_GetLoopCount(long channelHandle);
 static bool FMOD_Channel_IsVirtual(long channelHandle);
 static int FMOD_Channel_GetCurrentSound(long channelHandle);

 static int FMOD_ChannelGroup_Stop(long groupHandle);
 static int FMOD_ChannelGroup_SetPaused(long groupHandle, bool paused);
 static int FMOD_ChannelGroup_SetVolume(long groupHandle, float volume);
 static int FMOD_ChannelGroup_SetVolumeRamp(long groupHandle, bool ramp);
 static int FMOD_ChannelGroup_GetAudibility(long groupHandle, float *outAudibility);
 static int FMOD_ChannelGroup_SetPitch(long groupHandle, float pitch);
 static int FMOD_ChannelGroup_GetPitch(long groupHandle);
 static int FMOD_ChannelGroup_SetMute(long groupHandle, bool mute);
 static int FMOD_ChannelGroup_GetMute(long groupHandle);
 static int FMOD_ChannelGroup_SetReverbProperties(long groupHandle, int instance, float level);
 static int FMOD_ChannelGroup_SetLowPassGain(long groupHandle, float gain);
 static int FMOD_ChannelGroup_GetLowPassGain(long groupHandle);
 static int FMOD_ChannelGroup_SetMode(long groupHandle, long mode);
 static int FMOD_ChannelGroup_GetMode(long groupHandle);
 static int FMOD_ChannelGroup_IsPlaying(long groupHandle, bool *outPlaying);
 static int FMOD_ChannelGroup_SetPan(long groupHandle, float pan);
 static int FMOD_ChannelGroup_GetVolume(long groupHandle, float *outVolume);
 static int FMOD_ChannelGroup_GetVolumeRamp(long groupHandle, bool *outRamp);
 static int FMOD_ChannelGroup_AddFadePoint(long groupHandle, long dspClock, float volume);
 static int FMOD_ChannelGroup_Set3DMinMaxDistance(long groupHandle, float minDistance, float maxDistance);
 static int FMOD_ChannelGroup_Set3DConeSettings(long groupHandle, float insideConeAngle, float outsideConeAngle, float outsideVolume);
 static int FMOD_ChannelGroup_Set3DConeOrientation(long groupHandle, float x, float y, float z);
 static int FMOD_ChannelGroup_Set3DCustomRolloff(long groupHandle, long pointsHandle, int numPoints);
 static int FMOD_ChannelGroup_Set3DOcclusion(long groupHandle, float directOcclusion, float reverbOcclusion);
 static int FMOD_ChannelGroup_Set3DSpread(long groupHandle, float spread);
 static int FMOD_ChannelGroup_Set3DLevel(long groupHandle, float level);
 static int FMOD_ChannelGroup_Set3DDopplerLevel(long groupHandle, float level);

 static int FMOD_Sound_Release(long soundHandle);
 static int FMOD_RAWPlaySound_Release(long soundHandle);
 static int FMOD_RecordSound_Release(long soundHandle);

 static int FMOD_Studio_System_Init(int maxChannels, int studioFlags, int flags);
 static int FMOD_Studio_System_Update();
 static void FMOD_Studio_System_FlushCommands();
 static long FMOD_Studio_System_LoadBankFile(const std::string &path);
 static long FMOD_Studio_System_GetBus(const std::string &path);
 static long FMOD_Studio_System_GetEvent(const std::string &path);
 static long FMOD_Studio_System_CreateEventInstance(long eventDescriptionHandle);
 static int FMOD_Studio_System_SetParameterByName(const std::string &name, float value, bool ignoreSeekSpeed);
 static int FMOD_Studio_System_SetParameterByID(long parameterIdHandle, float value, bool ignoreSeekSpeed);
 static int FMOD_Studio_LoadSampleData(long bankOrEventHandle);
 static void FMOD_Studio_LoadEventSampleData(long eventHandle);

 static int FMOD_Studio_Listener3D(int listener, float px, float py, float pz, float vx, float vy, float vz, float fx, float fy, float fz, float ux, float uy, float uz);
 static int FMOD_Studio_SetNumListeners(int numListeners);

 static void FMOD_Studio_StartEvent(long eventInstanceHandle);
 static long FMOD_Studio_GetTimelinePosition(long eventInstanceHandle);
 static int FMOD_Studio_EventInstance_SetCallback(long eventInstanceHandle, long callback, long mask);
 static int FMOD_Studio_EventInstance_SetParameterByID(long eventInstanceHandle, long parameterIdHandle, float value, bool ignoreSeekSpeed);
 static int FMOD_Studio_EventInstance_SetParameterByName(long eventInstanceHandle, const std::string &name, float value, bool ignoreSeekSpeed);
 static int FMOD_Studio_EventInstance_SetReverbLevel(long eventInstanceHandle, int index, float level);
 static int FMOD_Studio_EventInstance_SetParameterValueByIndex(long eventInstanceHandle, int index, float value);
 static int FMOD_Studio_EventInstance_SetVolume(long eventInstanceHandle, float volume);
 static int FMOD_Studio_EventInstance_Stop(long eventInstanceHandle, bool allowFadeOut);
 static int FMOD_Studio_EventInstance_GetPlaybackState(long eventInstanceHandle);
 static int FMOD_Studio_EventInstance_GetTimelinePosition(long eventInstanceHandle);
 static int FMOD_Studio_EventInstance_Release(long eventInstanceHandle);
 static int FMOD_Studio_EventInstance3D(long eventInstanceHandle, float px, float py, float pz);
 static int FMOD_Studio_EventInstance3D(long eventInstanceHandle, float px, float py, float pz, float vx, float vy, float vz);

 static int FMOD_Studio_EventDescription_GetInstanceCount(long eventDescriptionHandle);
 static int FMOD_Studio_EventDescription_GetInstanceList(long eventDescriptionHandle, long *handles, int capacity);

 static int FMOD_Studio_Bus_SetMute(long busHandle, bool mute);
 static int FMOD_Studio_Bus_SetPaused(long busHandle, bool paused);

 static long FMOD_Studio_GetPlaybackState(long eventInstanceHandle);
 static long FMOD_Studio_GetParameterValue(long eventInstanceHandle, const std::string &name);
 static long FMOD_Studio_GetParameterValue(long eventInstanceHandle, long parameterIdHandle);
};

class javafmodJNI {
public:
 static void init();
};

} // namespace fmod

