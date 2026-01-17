#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoLivingCharacter.java
namespace zombie {
namespace characters {
#include "GameTime.h"
#include "LuaHookManager.h"
#include "SoundManager.h"
#include "WorldSoundManager.h"
#include "StateMachine.h"
#include "SwipeState.h"
#include "BodyDamage.h"
#include "NulledArrayList.h"
#include "inventory.h"
#include "HandWeapon.h"
#include "iso.h"
#include "sprite.h"
#include "UIManager.h"
// Referenced classes of package zombie.characters:
//            IsoGameCharacter, IsoPlayer, IsoSurvivor, IsoZombie, 
//            SurvivorDesc
class IsoLivingCharacter : public IsoGameCharacter {
public:
{
    public IsoLivingCharacter(IsoCell cell, float x, float y, float z)
    {
        super(cell, x, y, z);
        bDoShove = false;
        bareHands = (HandWeapon)InventoryItemFactory.CreateItem("Base.BareHands");
    }
    public bool AttemptAttack(float ChargeDelta)
    {
        if(LuaHookManager.TriggerHook("Attack", this, Float.valueOf(ChargeDelta)))
            return false;
        else
            return DoAttack(ChargeDelta);
    }
    public bool DoAttack(float ChargeDelta)
    {
        if(this instanceof IsoPlayer)
            ((IsoPlayer)(IsoPlayer)this).FakeAttack = false;
        if(Health <= 0.0F || BodyDamage.getHealth() < 0.0F)
            return false;
        if(leftHandItem != nullptr && AttackDelay <= 0)
        {
            InventoryItem attackItem = leftHandItem;
            if(attackItem instanceof HandWeapon)
            {
                useHandWeapon = (HandWeapon)attackItem;
                if(useHandWeapon.getCondition() <= 0)
                    return false;
                if(useHandWeapon.isCantAttackWithLowestEndurance() && stats.endurance < stats.endurancedanger)
                    return false;
                int hitCount = 0;
                if((this instanceof IsoSurvivor) && useHandWeapon.isRanged() && hitCount < useHandWeapon.getMaxHitCount())
                {
                    for(int n = 0; n < getCell().getObjectList().size(); n++)
                    {
                        IsoMovingObject obj = (IsoMovingObject)getCell().getObjectList().get(n);
                        if(obj == this || !obj.isShootable() || !IsAttackRange(obj.getX(), obj.getY(), obj.getZ()) || useHandWeapon.isDirectional())
                            continue;
                        float delta = obj.getSeeValue();
                        if(!(this instanceof IsoPlayer))
                            delta = 1.0F;
                        if(delta <= 0.0F)
                            continue;
                        Vector2 oPos = new Vector2(getX(), getY());
                        Vector2 tPos = new Vector2(obj.getX(), obj.getY());
                        tPos.x -= oPos.x;
                        tPos.y -= oPos.y;
                        bool bZero = false;
                        if(tPos.x == 0.0F && tPos.y == 0.0F)
                            bZero = true;
                        Vector2 dir = angle;
                        DirectionFromVector(dir);
                        tPos.normalize();
                        float dot = tPos.dot(dir);
                        if(bZero)
                            dot = 1.0F;
                        if(dot > 1.0F)
                            dot = 1.0F;
                        if(dot < -1F)
                            dot = -1F;
                        if(dot >= useHandWeapon.getMinAngle() && dot <= useHandWeapon.getMaxAngle())
                        {
                            if(descriptor != nullptr && !(obj instanceof IsoZombie))
                            {
                                if(!descriptor.InGroupWith(obj));
                                return false;
                            }
                            hitCount++;
                        }
                        if(hitCount >= useHandWeapon.getMaxHitCount())
                            break;
                    }
                }
                if(UIManager.getPicked() != nullptr)
                {
                    attackTargetSquare = UIManager.getPicked().square;
                    if(UIManager.getPicked().tile instanceof IsoMovingObject)
                        attackTargetSquare = ((IsoMovingObject)UIManager.getPicked().tile).getCurrentSquare();
                }
                if(useHandWeapon.getAmmoType() != nullptr && !inventory.contains(useHandWeapon.getAmmoType()))
                    return false;
                if(useHandWeapon.getOtherHandRequire() != nullptr && (rightHandItem == nullptr || !rightHandItem.getType() == useHandWeapon.getOtherHandRequire())))
                    return false;
                if(attackItem.getSwingAnim() != nullptr)
                {
                    def.Finished = false;
                    PlayAnimUnlooped((new StringBuilder()).append("Attack_").append(attackItem.getSwingAnim()).toString());
                    sprite.CurrentAnim.FinishUnloopedOnFrame = 0;
                }
                float val = useHandWeapon.getSwingTime();
                if(useHandWeapon.isUseEndurance())
                    val *= 1.0F - stats.endurance;
                if(val < useHandWeapon.getMinimumSwingTime())
                    val = useHandWeapon.getMinimumSwingTime();
                if(this instanceof IsoPlayer)
                    SoundManager.instance.PlaySound(useHandWeapon.getSwingSound(), false, 0.9F);
                else
                    SoundManager.instance.PlayWorldSound(useHandWeapon.getSwingSound(), getCurrentSquare(), 0.0F, (float)useHandWeapon.getSoundRadius() * useHandWeapon.getOtherBoost(), 1.0F, true);
                WorldSoundManager.instance.addSound(this, (int)getX(), (int)getY(), (int)getZ(), useHandWeapon.getSoundRadius(), useHandWeapon.getSoundVolume());
                val *= useHandWeapon.getSpeedMod(this);
                val *= 1.0F / GameTime.instance.getMultiplier();
                AttackDelayMax = AttackDelay = (int)(val * 60F);
                AttackDelayUse = (int)((float)AttackDelayMax * useHandWeapon.getDoSwingBeforeImpact());
                AttackDelayUse = AttackDelayMax - AttackDelayUse - 2;
                AttackWasSuperAttack = superAttack;
                stateMachine.changeState(SwipeState.instance());
                if(useHandWeapon.getAmmoType() != nullptr)
                    if(this instanceof IsoPlayer)
                        IsoPlayer.instance.inventory.RemoveOneOf(useHandWeapon.getAmmoType());
                    else
                        inventory.RemoveOneOf(useHandWeapon.getAmmoType());
                if(useHandWeapon.isUseSelf() && leftHandItem != nullptr)
                    leftHandItem.Use();
                if(useHandWeapon.isOtherHandUse() && rightHandItem != nullptr)
                    rightHandItem.Use();
                return true;
            }
        }
        return false;
    }
    public HandWeapon bareHands;
    public bool bDoShove;
}
} // namespace
