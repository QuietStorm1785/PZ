#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BodyPart.java
namespace zombie {
namespace characters {
namespace BodyDamage {
#include "IsoGameCharacter.h"
#include "Rand.h"
// Referenced classes of package zombie.characters.BodyDamage:
//            BodyPartType
class BodyPart {
public:
{
    public BodyPart(BodyPartType ChosenType, IsoGameCharacter PC)
    {
        BiteDamage = 3.5F;
        BleedDamage = 2.0F;
        DamageScaler = 0.005714286F;
        ScratchDamage = 1.5F;
        WoundDamage = 6F;
        Type = ChosenType;
        ParentChar = PC;
        RestoreToFullHealth();
    }
    public void AddDamage(float Val)
    {
        Health -= Val;
        if(Health < 0.0F)
            Health = 0.0F;
    }
    public void DamageUpdate()
    {
        if(IsWounded)
            Health -= WoundDamage * DamageScaler;
        if(IsScratched)
            Health -= ScratchDamage * DamageScaler;
        if(IsBitten)
            Health -= BiteDamage * DamageScaler;
        if(IsBleeding)
            Health -= BleedDamage * DamageScaler;
        if(Health < 0.0F)
            Health = 0.0F;
    }
    public float getHealth()
    {
        return Health;
    }
    public void SetHealth(float NewHealth)
    {
        Health = NewHealth;
    }
    public void AddHealth(float Val)
    {
        Health += Val;
        if(Health > 100F)
            Health = 100F;
    }
    public void ReduceHealth(float Val)
    {
        Health -= Val;
        if(Health < 0.0F)
            Health = 0.0F;
    }
    public bool HasInjury()
    {
        return IsBitten | IsScratched | IsWounded | IsBleeding;
    }
    public bool IsBandaged()
    {
        return IsBandaged;
    }
    public bool IsBitten()
    {
        return IsBitten;
    }
    public bool IsBleeding()
    {
        return IsBleeding;
    }
    public bool IsBleedingStemmed()
    {
        return IsBleedingStemmed;
    }
    public bool IsCortorised()
    {
        return IsCortorised;
    }
    public bool IsInfected()
    {
        return IsInfected;
    }
    public void SetInfected(bool inf)
    {
        IsInfected = inf;
    }
    public void SetFakeInfected(bool inf)
    {
        IsFakeInfected = inf;
    }
    public bool IsFakeInfected()
    {
        return IsFakeInfected;
    }
    public void DisableFakeInfection()
    {
        IsFakeInfected = false;
    }
    public bool IsScratched()
    {
        return IsScratched;
    }
    public bool IsStitched()
    {
        return IsStitched;
    }
    public bool IsWounded()
    {
        return IsWounded;
    }
    public void RestoreToFullHealth()
    {
        Health = 100F;
        IsWounded = false;
        IsBleeding = false;
        IsBleedingStemmed = false;
        IsBandaged = false;
        IsCortorised = false;
        IsBitten = false;
        IsScratched = false;
        IsInfected = false;
        IsFakeInfected = false;
    }
    public void SetBandaged(bool Bandaged)
    {
        if(Bandaged)
        {
            if(IsBleeding)
                IsBleeding = false;
            IsBitten = false;
            IsScratched = false;
        }
        IsBandaged = Bandaged;
    }
    public void SetBitten(bool Bitten)
    {
        IsBitten = Bitten;
        if(Bitten)
        {
            IsBleeding = true;
            IsBleedingStemmed = false;
            IsCortorised = false;
            IsBandaged = false;
            if(ParentChar.HasTrait("ThickSkinned"))
            {
                if(Rand.Next(100) < 70)
                {
                    IsInfected = true;
                    IsFakeInfected = false;
                }
            } else
            {
                IsInfected = true;
                IsFakeInfected = false;
            }
        }
    }
    public void SetBitten(bool Bitten, bool Infected)
    {
        IsBitten = Bitten;
        if(Bitten)
        {
            IsBleeding = true;
            IsBleedingStemmed = false;
            IsCortorised = false;
            IsBandaged = false;
            if(Infected)
                IsInfected = true;
            IsFakeInfected = false;
        }
    }
    public void SetBleeding(bool Bleeding)
    {
        IsBleeding = Bleeding;
    }
    public void SetBleedingStemmed(bool BleedingStemmed)
    {
        if(IsBleeding)
        {
            IsBleeding = false;
            IsBleedingStemmed = true;
        }
    }
    public void SetCortorised(bool Cortorised)
    {
        IsCortorised = Cortorised;
        if(Cortorised)
        {
            IsBleeding = false;
            IsBleedingStemmed = false;
            IsWounded = false;
            IsBandaged = false;
        }
    }
    public void SetScratched(bool Scratched)
    {
        IsScratched = Scratched;
        if(Scratched)
        {
            IsBandaged = false;
            if(ParentChar.HasTrait("ThickSkinned"))
            {
                if(Rand.Next(100) < 12)
                    IsInfected = true;
            } else
            if(Rand.Next(100) < 25)
                IsInfected = true;
            if(!IsInfected && ParentChar.HasTrait("Hypercondriac"))
                IsFakeInfected = true;
        }
    }
    public void SetStitched(bool Stitched)
    {
        IsStitched = Stitched;
        if(IsStitched)
        {
            IsBleeding = false;
            IsBleedingStemmed = false;
            IsWounded = false;
            IsBandaged = false;
        }
    }
    public void SetWounded(bool Wounded)
    {
        IsWounded = Wounded;
        if(Wounded)
        {
            IsBleeding = true;
            IsBleedingStemmed = false;
            IsCortorised = false;
            IsBandaged = false;
        }
    }
    BodyPartType Type;
    private float BiteDamage;
    private float BleedDamage;
    private float DamageScaler;
    private float Health;
    private bool IsBandaged;
    private bool IsBitten;
    private bool IsBleeding;
    private bool IsBleedingStemmed;
    private bool IsCortorised;
    private bool IsScratched;
    private bool IsStitched;
    private bool IsWounded;
    private bool IsInfected;
    private bool IsFakeInfected;
    private IsoGameCharacter ParentChar;
    private float ScratchDamage;
    private float WoundDamage;
}
} // namespace
