#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   AttackState.java
namespace zombie {
namespace ai {
namespace states {
#include "SoundManager.h"
#include "State.h"
#include "StateMachine.h"
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "IsoZombie.h"
#include "Rand.h"
#include "IsoMovingObject.h"
#include "Vector2.h"
#include "IsoSpriteInstance.h"
#include "TutorialManager.h"
// Referenced classes of package zombie.ai.states:
//            WanderState
class AttackState : public State {
public:
{
    public AttackState()
    {
        temp = new Vector2();
    }
    public static AttackState instance()
    {
        return _instance;
    }
    public void enter(IsoGameCharacter owner)
    {
        if(owner instanceof IsoZombie)
        {
            IsoZombie zomb = (IsoZombie)owner;
            zomb.PlayAnim("ZombieBite");
            zomb.def.Frame = 0.0F;
        }
    }
    public void execute(IsoGameCharacter owner)
    {
        if(owner instanceof IsoZombie)
        {
            IsoZombie zomb = (IsoZombie)owner;
            if(zomb.target != nullptr)
            {
                zomb.DirectionFromVector(zomb.vectorToTarget);
                if((int)zomb.getZ() != (int)zomb.target.getZ())
                {
                    zomb.target = nullptr;
                    zomb.Wander();
                    return;
                }
            }
            float len = zomb.vectorToTarget.getLength();
            if(len > 1.0F)
            {
                zomb.Wander();
                zomb.Lunge();
                return;
            }
            if(zomb.target == nullptr)
            {
                zomb.Wander();
                return;
            }
            zomb.target.setTimeSinceZombieAttack(0);
            zomb.target.setLastTargettedBy(zomb);
            zomb.AttackAnimTime--;
            zomb.PlayAnim("ZombieBite");
            ((IsoGameCharacter)zomb.target).setLeaveBodyTimedown(((IsoGameCharacter)zomb.target).getLeaveBodyTimedown() - 1);
            if(((IsoGameCharacter)zomb.target).getLeaveBodyTimedown() <= 0 && ((IsoGameCharacter)zomb.target).getBodyDamage().getHealth() <= 0.0F)
                zomb.getStateMachine().changeState(WanderState._instance);
            if(zomb.HurtPlayerTimer <= 0 && !TutorialManager.instance.ActiveControlZombies && zomb.def.Frame >= 10F && zomb.def.Frame <= 16F)
            {
                if(zomb.target != nullptr)
                {
                    bool bAlive = false;
                    if(((IsoGameCharacter)zomb.target).getBodyDamage().getHealth() > 0.0F)
                        bAlive = true;
                    ((IsoGameCharacter)zomb.target).getBodyDamage().AddRandomDamageFromZombie();
                    if(bAlive)
                    {
                        ((IsoGameCharacter)zomb.target).getBodyDamage().Update();
                        if(((IsoGameCharacter)zomb.target).getBodyDamage().getHealth() <= 0.0F)
                        {
                            SoundManager.instance.PlayWorldSound("zombieeating", zomb.target.getCurrentSquare(), 0.0F, 15F, 1.3F, true);
                            Integer a = Integer.valueOf(Rand.Next(3) + 1);
                            SoundManager.instance.PlayWorldSound((new StringBuilder()).append("scream").append(a).toString(), zomb.target.getCurrentSquare(), 0.3F, 10F, 0.5F, true);
                            ((IsoGameCharacter)zomb.target).setLeaveBodyTimedown(1500);
                        }
                    }
                    ((IsoGameCharacter)zomb.target).setSlowTimer(30);
                    ((IsoGameCharacter)zomb.target).setSlowFactor(((IsoGameCharacter)zomb.target).getSlowFactor() + 0.05F);
                    if(((IsoGameCharacter)zomb.target).getSlowFactor() >= 0.7F)
                        ((IsoGameCharacter)zomb.target).setSlowFactor(0.7F);
                }
                zomb.HurtPlayerTimer = 20;
            } else
            {
                zomb.HurtPlayerTimer--;
            }
        }
    }
    static AttackState _instance = new AttackState();
    Vector2 temp;
}} // namespace
