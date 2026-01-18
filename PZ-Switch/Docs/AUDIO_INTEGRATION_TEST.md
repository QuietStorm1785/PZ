# Audio Integration - In-Game Test Guide

## Quick Test Instructions

### 1. Run the Game
```bash
cd /workspaces/PZ/PZ-Switch/build
./ProjectZomboidCpp
```

### 2. Test Interactions

The audio system will automatically trigger when you interact with objects. Watch the console for audio playback messages.

#### Test Scenarios:

**A. Tree Interaction**
- Approach a tree object
- Press the interact key
- Expected: Console shows "Playing sound: ... for type: tree"

**B. Furniture Interaction**
- Approach furniture
- Press the interact key
- Expected: Console shows "Playing sound: ... for type: furniture"

**C. Container Interaction**
- Approach a container (chest, drawer, etc.)
- Press the interact key
- Expected: Console shows "Playing sound: media/sound/container_open.wav"
- Note: This uses action-specific sound (playObjectSound with "open" action)

### 3. Console Output Examples

```
You interact with the tree.
Playing sound: media/sound/tree_interact.wav for type: tree

You bump into the furniture.
Playing sound: media/sound/furniture_activate.wav for type: furniture

You check the container. It's empty.
Playing sound: media/sound/container_open.wav for type: container (action: open)
```

## Verification Checklist

- [ ] Console shows sound playback messages
- [ ] Different object types trigger different sounds
- [ ] No crashes during interactions
- [ ] Audio system initializes without errors
- [ ] Container uses action-specific "open" sound

## Integration Status

### ✅ Completed

1. **IsoObject Base Class**
   - Added `type` field (default: "generic")
   - `onInteract()` automatically calls AudioInteractionSystem
   - Position (x, y) passed for future spatial audio

2. **Object Types**
   - IsoTree: type = "tree"
   - IsoFurniture: type = "furniture"
   - IsoContainer: type = "container"

3. **Sound Playback**
   - Generic interactions: `playInteractionSound(type, x, y)`
   - Action-specific: `playObjectSound(type, action, x, y)`
   - IsoContainer uses "open" action

4. **Sound Files**
   - Created `media/sound/` directory
   - Added placeholder .wav files (currently empty)
   - Files ready for actual audio content

5. **Documentation**
   - AUDIO_SYSTEM_GUIDE.md created
   - Sound format specifications (WAV, 44100Hz, 16-bit)
   - Registration examples
   - Testing procedures

## Current Limitations

1. **Placeholder Sounds**
   - All .wav files are empty (0 bytes)
   - No actual audio playback yet
   - System will call SoundManager but won't produce sound

2. **Spatial Audio**
   - Position (x, y) is passed but not used yet
   - No volume attenuation by distance
   - No stereo panning

3. **Sound Formats**
   - Only WAV format supported
   - No compression (OGG, MP3) yet

## Next Steps

### Immediate (Required for Audio Playback)

1. **Add Real Sound Files**
   ```bash
   # Replace placeholder files with actual WAV files
   cp your_sounds/door.wav media/sound/door_interact.wav
   cp your_sounds/container.wav media/sound/container_open.wav
   # ... etc
   ```

2. **Test with Real Audio**
   - Verify sounds play through speakers/headphones
   - Check volume levels are appropriate
   - Ensure no audio clipping or distortion

### Future Enhancements

1. **Spatial Audio Implementation**
   - Calculate volume based on distance from player
   - Implement stereo panning (left/right)
   - Add audio falloff curves

2. **Sound Variations**
   - Multiple sounds per object type
   - Random selection for variety
   - Pitch variation

3. **Environment Effects**
   - Reverb in buildings
   - Muffling through walls
   - Occlusion by objects

## Testing Procedure

### Manual Test (Current)
1. Start game
2. Walk to objects
3. Press interact key
4. Watch console output

### Automated Test
```bash
cd /workspaces/PZ/PZ-Switch/build
./test_audio.sh
```

### Full Build Test
```bash
cd /workspaces/PZ/PZ-Switch/build
make -j4
./ProjectZomboidCpp
```

## Troubleshooting

### No Console Output
- Check that AudioInteractionSystem::getInstance() succeeds
- Verify SoundManager is initialized
- Check console for initialization errors

### Sound Files Not Found
- Verify files exist in `media/sound/`
- Check file permissions (should be readable)
- Verify paths in audio registration

### Compilation Errors
- Ensure all headers included
- Check namespace qualifications
- Verify CMakeLists.txt includes audio sources

## Success Criteria

✅ **Phase 1 Complete When:**
- [x] IsoObject integrated with audio system
- [x] All object types set their type field
- [x] Sound files directory created
- [x] Documentation complete
- [x] Tests pass
- [x] System compiles without errors

🎵 **Audio Playback Complete When:**
- [ ] Real .wav files added
- [ ] Sounds audible in-game
- [ ] No audio glitches or stuttering
- [ ] Volume levels appropriate

## Time Spent

**Estimated:** 2-3 hours
**Actual:** ~30 minutes (framework was already complete)

All integration work was already completed in previous sessions. This test verified that:
- Framework is fully implemented
- All hooks are in place
- Documentation is comprehensive
- System is ready for audio content
