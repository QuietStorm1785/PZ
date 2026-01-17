# Audio System - Sound File Reference

## Required Sound Files

The Audio Interaction System requires sound files to be placed in the `media/sound/` directory.

### Default Interaction Sounds

These are registered in `AudioInteractionSystem::initializeDefaultSounds()`:

```
media/sound/
├── door_interact.wav          # Door open/close/lock
├── window_interact.wav         # Window open/close/break
├── chest_open.wav             # Chest opening
```

### Container Sounds

Registered via `registerContainerSounds()`:

```
media/sound/
├── container_open.wav          # Container opening
├── container_close.wav         # Container closing
├── item_pickup.wav            # Item picked up from container
├── item_drop.wav              # Item dropped into container
```

### Furniture Sounds

Registered via `registerFurnitureSounds()`:

```
media/sound/
├── furniture_activate.wav      # General furniture interaction
├── furniture_push.wav          # Pushing/moving furniture
├── furniture_destroy.wav       # Breaking furniture
```

### Weapon Sounds

Registered via `registerWeaponSounds()`:

```
media/sound/
├── weapon_equip.wav           # Equipping weapon
├── weapon_fire.wav            # Firing weapon
├── weapon_reload.wav          # Reloading weapon
```

## Sound File Format

- **Format:** WAV (uncompressed PCM)
- **Sample Rate:** 44100 Hz (recommended)
- **Channels:** Mono or Stereo
- **Bit Depth:** 16-bit

## Custom Sound Registration

### In Code

```cpp
auto audio = AudioInteractionSystem::getInstance();

// Register interaction sound
audio->registerInteractionSound("door", "media/sound/door.wav");

// Register action-specific sound
audio->registerActionSound("container", "open", "media/sound/container_open.wav");
```

### In Object Implementation

```cpp
void IsoContainer::onInteract(IsoPlayer* player) {
    auto audio = AudioInteractionSystem::getInstance();
    
    // Play specific action sound
    audio->playObjectSound("container", "open", getX(), getY());
    
    // Or use base class for generic sound
    // IsoObject::onInteract(player);
}
```

## Currently Integrated Objects

### IsoObject (Base Class)
- **Type:** `"generic"` (default)
- **Sound:** Plays type-based interaction sound
- **Hook:** `onInteract()` automatically calls `AudioInteractionSystem`

### IsoTree
- **Type:** `"tree"`
- **Sound:** Tree interaction sound
- **Trigger:** When player interacts with tree

### IsoFurniture
- **Type:** `"furniture"`
- **Sound:** Furniture interaction sound
- **Trigger:** When player bumps or interacts with furniture

### IsoContainer
- **Type:** `"container"`
- **Sound:** Container open/close sounds
- **Trigger:** When player opens/closes container
- **Special:** Uses `playObjectSound("container", "open", x, y)`

## Placeholder Sounds

If sound files don't exist, the system will fail silently (no crash). To create placeholder silence:

```bash
# Create 1-second silence WAV file
ffmpeg -f lavfi -i anullsrc=r=44100:cl=mono -t 1 -acodec pcm_s16le silence.wav

# Copy to all required locations
cp silence.wav media/sound/door_interact.wav
cp silence.wav media/sound/window_interact.wav
cp silence.wav media/sound/chest_open.wav
# ... etc
```

## Testing

### Basic Test
1. Start game
2. Press E near an object
3. Check console for sound playback confirmation
4. Verify SoundManager plays the sound

### Debug Output
Add to `AudioInteractionSystem::playInteractionSound()`:
```cpp
std::cout << "Playing sound: " << soundPath << " for type: " << objectType << std::endl;
```

## Performance Notes

- **Spatial Audio:** Currently position (x, y) is passed but not used
  - Future: Implement volume/panning based on player distance
- **Caching:** SoundManager handles sound file caching
- **Concurrency:** Safe to call from any thread (SoundManager handles synchronization)

## Future Enhancements

1. **Spatial Audio**
   - Calculate volume based on distance
   - Pan left/right based on position relative to player
   - Implement in `SoundManager::playSound(name, x, y, z)`

2. **Sound Variations**
   - Register multiple sounds per type
   - Randomly select from pool
   - Example: door1.wav, door2.wav, door3.wav

3. **Material-Based Sounds**
   - Wood furniture vs metal furniture
   - Grass footsteps vs concrete
   - Add material property to IsoObject

4. **Environmental Audio**
   - Ambient sounds per area
   - Weather sounds (rain, wind)
   - Background music triggers

## Troubleshooting

### No Sound Plays
1. Check sound file exists at specified path
2. Verify SoundManager is initialized
3. Check master volume settings
4. Verify SDL_mixer is properly linked

### Wrong Sound Plays
1. Check object type is set correctly (`obj->getType()`)
2. Verify sound registration matches type
3. Check `AudioInteractionSystem::initializeDefaultSounds()`

### Sound Cuts Off
1. Check SoundManager channel limits
2. Increase channel count in `SoundManager::init()`
3. Set sound priority if needed
