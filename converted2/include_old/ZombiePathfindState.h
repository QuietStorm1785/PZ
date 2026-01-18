#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ZombiePathfindState.java
namespace zombie {
namespace ai {
namespace states {
#include "State.h"
#include "IsoGameCharacter.h"
#include "IsoZombie.h"
#include "Vector2.h"
class ZombiePathfindState : public State {
public:
{
    public ZombiePathfindState()
    {
        a = new Vector2();
    }
    public static ZombiePathfindState instance()
    {
        return _instance;
    }
    public void enter(IsoGameCharacter owner)
    {
        owner.setPath(nullptr);
        owner.setPathIndex(0);
    }
    public void execute(IsoGameCharacter owner)
    {
        owner.MoveForward(((IsoZombie)owner).getPathSpeed() * owner.getSpeedMod());
    }
    public void exit(IsoGameCharacter isogamecharacter)
    {
    }
    private void Finished(IsoGameCharacter owner)
    {
        owner.pathFinished();
    }
    private void getBestDirection(IsoZombie isozombie)
    {
    }
    private void TraceWall(IsoZombie isozombie)
    {
    }
    static ZombiePathfindState _instance = new ZombiePathfindState();
    Vector2 a;
}
} // namespace
