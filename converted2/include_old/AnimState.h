#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AnimState.java
namespace zombie {
namespace iso {
namespace sprite {
#include <vector>
// Referenced classes of package zombie.iso.sprite:
//            IsoSpriteInstance, IsoSprite, AnimStateMachine, IsoAnim
class AnimState {
public:
{
    public static class AnimStateEntry
    {
        public IsoAnim anim;
        public float AnimSpeedPerFrame;
        public AnimStateEntry(IsoAnim anim, float AnimSpeedPerFrame)
        {
            this.AnimSpeedPerFrame = 0.0F;
            this.anim = anim;
            this.AnimSpeedPerFrame = AnimSpeedPerFrame;
        }
    }
    public AnimState(std::string name, AnimStateMachine machine, IsoSpriteInstance inst)
    {
        entries = new ArrayList(0);
        loopEntry = 0;
        currentEntry = 0;
        lastFrame = 0.0F;
        this.inst = inst;
        this.machine = machine;
    }
    public AnimStateEntry addState(IsoAnim anim, float AnimSpeedPerFrame)
    {
        AnimStateEntry entry = new AnimStateEntry(anim, AnimSpeedPerFrame);
        entries.add(entry);
        return entry;
    }
    public void update()
    {
        if(currentEntry >= entries.size())
            return;
        AnimStateEntry e = (AnimStateEntry)entries.get(currentEntry);
        inst.parentSprite.PlayAnim(e.anim);
        inst.AnimFrameIncrease = e.AnimSpeedPerFrame;
        if(inst.Frame < lastFrame)
        {
            currentEntry++;
            if(loopEntry != -1)
                currentEntry = loopEntry;
        }
        lastFrame = inst.Frame;
    }
    public ArrayList entries;
    public AnimStateMachine machine;
    public IsoSpriteInstance inst;
    public int loopEntry;
    public int currentEntry;
    public float lastFrame;
}
} // namespace
