#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoFireManager.java
namespace zombie {
namespace iso {
namespace objects {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "PropertyContainer.h"
#include "ColorInfo.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoFlagType.h"
// Referenced classes of package zombie.iso.objects:
//            IsoFire
class IsoFireManager {
public:
{
    public IsoFireManager()
    {
    }
    public static void Add(IsoFire NewFire)
    {
        if(NumActiveFires < MaxFireObjects)
        {
            FireStack.add(NewFire);
            NumActiveFires++;
        } else
        {
            IsoFire OldestFireObject = nullptr;
            int OldestAge = 0;
            for(int i = 0; i < FireStack.size(); i++)
                if(((IsoFire)FireStack.get(i)).Age > OldestAge)
                {
                    OldestAge = ((IsoFire)FireStack.get(i)).Age;
                    OldestFireObject = (IsoFire)FireStack.get(i);
                }
            OldestFireObject.square.getProperties().UnSet(IsoFlagType.burning);
            OldestFireObject.square.getProperties().Set(IsoFlagType.burntOut, "Burnt Out");
            OldestFireObject.RemoveAttachedAnims();
            Remove(OldestFireObject);
            FireStack.add(NewFire);
            NumActiveFires++;
        }
    }
    public static void AddBurningCharacter(IsoGameCharacter BurningCharacter)
    {
        for(int i = 0; i < CharactersOnFire_Stack.size(); i++)
            if(CharactersOnFire_Stack.get(i) == BurningCharacter)
                return;
        CharactersOnFire_Stack.add(BurningCharacter);
    }
    public static void Fire_LightCalc(IsoGridSquare FireSquare, IsoGridSquare TestSquare)
    {
        if(TestSquare == nullptr || FireSquare == nullptr)
            return;
        int Dist = 0;
        int FireAreaOfEffect = 8;
        Dist += Math.abs(TestSquare.getX() - FireSquare.getX());
        Dist += Math.abs(TestSquare.getY() - FireSquare.getY());
        Dist += Math.abs(TestSquare.getZ() - FireSquare.getZ());
        if(Dist <= FireAreaOfEffect)
        {
            float LightInfluence = (0.199F / (float)FireAreaOfEffect) * (float)(FireAreaOfEffect - Dist);
            float LightInfluenceR = LightInfluence;
            float LightInfluenceG = LightInfluence * 0.6F;
            float LightInfluenceB = LightInfluence * 0.4F;
            if(TestSquare.getLightInfluenceR() == nullptr)
                TestSquare.setLightInfluenceR(new NulledArrayList());
            TestSquare.getLightInfluenceR().add(Float.valueOf(LightInfluenceR));
            if(TestSquare.getLightInfluenceG() == nullptr)
                TestSquare.setLightInfluenceG(new NulledArrayList());
            TestSquare.getLightInfluenceG().add(Float.valueOf(LightInfluenceG));
            if(TestSquare.getLightInfluenceB() == nullptr)
                TestSquare.setLightInfluenceB(new NulledArrayList());
            TestSquare.getLightInfluenceB().add(Float.valueOf(LightInfluenceB));
            TestSquare.getLightInfo().r += LightInfluenceR;
            TestSquare.getLightInfo().g += LightInfluenceG;
            TestSquare.getLightInfo().b += LightInfluenceB;
            if(TestSquare.getLightInfo().r > 1.0F)
                TestSquare.getLightInfo().r = 1.0F;
            if(TestSquare.getLightInfo().g > 1.0F)
                TestSquare.getLightInfo().g = 1.0F;
            if(TestSquare.getLightInfo().b > 1.0F)
                TestSquare.getLightInfo().b = 1.0F;
        }
    }
    public static void LightTileWithFire(IsoGridSquare TestSquare)
    {
        if(TestSquare.getLightInfluenceR() != nullptr && FireRecalc > 0 && TestSquare.getLightInfluenceR().size() > 0)
        {
            for(int n = 0; n < TestSquare.getLightInfluenceR().size(); n++)
            {
                TestSquare.getLightInfo().r += (double)((Float)TestSquare.getLightInfluenceR().get(n)).floatValue() + Red_Oscilator_Val;
                TestSquare.getLightInfo().g += (double)((Float)TestSquare.getLightInfluenceG().get(n)).floatValue() + Green_Oscilator_Val;
                TestSquare.getLightInfo().b += (double)((Float)TestSquare.getLightInfluenceB().get(n)).floatValue() + Blue_Oscilator_Val;
            }
            if(TestSquare.getLightInfo().r > 1.0F)
                TestSquare.getLightInfo().r = 1.0F;
            if(TestSquare.getLightInfo().g > 1.0F)
                TestSquare.getLightInfo().g = 1.0F;
            if(TestSquare.getLightInfo().b > 1.0F)
                TestSquare.getLightInfo().b = 1.0F;
            return;
        }
        if(TestSquare.getLightInfluenceR() != nullptr)
        {
            TestSquare.getLightInfluenceR().clear();
            TestSquare.getLightInfluenceG().clear();
            TestSquare.getLightInfluenceB().clear();
        }
        LightCalcFromBurningCharacters = false;
        for(int i = 0; i < FireStack.size(); i++)
            Fire_LightCalc(((IsoFire)FireStack.get(i)).square, TestSquare);
        LightCalcFromBurningCharacters = true;
        for(int i = 0; i < CharactersOnFire_Stack.size(); i++)
            Fire_LightCalc(((IsoGameCharacter)CharactersOnFire_Stack.get(i)).getCurrentSquare(), TestSquare);
    }
    public static void MolotovSmash(IsoCell cell, IsoGridSquare gridSquare)
    {
        if(gridSquare == nullptr)
            return;
        IsoGridSquare NewSquare = nullptr;
        IsoFire NewFire = nullptr;
        FireRecalc = 1;
        NewSquare = cell.getGridSquare(gridSquare.getX(), gridSquare.getY() - 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() + 1, gridSquare.getY() - 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() + 1, gridSquare.getY(), gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() + 1, gridSquare.getY() + 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX(), gridSquare.getY() + 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() - 1, gridSquare.getY() + 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() - 1, gridSquare.getY(), gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX() - 1, gridSquare.getY() - 1, gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
        NewSquare = cell.getGridSquare(gridSquare.getX(), gridSquare.getY(), gridSquare.getZ());
        if(NewSquare != nullptr)
        {
            NewFire = new IsoFire(cell, NewSquare, true, 50);
            NewSquare.getObjects().add(NewFire);
        }
    }
    public static void Remove(IsoFire DyingFire)
    {
        FireStack.remove(DyingFire);
        NumActiveFires--;
    }
    public static void RemoveBurningCharacter(IsoGameCharacter BurningCharacter)
    {
        CharactersOnFire_Stack.remove(BurningCharacter);
    }
    public static void StartFire(IsoCell cell, IsoGridSquare gridSquare, bool IgniteOnAny, int FireStartingEnergy)
    {
        IsoFire NewFire = new IsoFire(cell, gridSquare, IgniteOnAny, FireStartingEnergy);
        gridSquare.getObjects().add(NewFire);
    }
    public static void Update()
    {
        Red_Oscilator_Val = Math.sin(Red_Oscilator += Blue_Oscilator_Rate * OscilatorSpeedScalar);
        Green_Oscilator_Val = Math.sin(Green_Oscilator += Blue_Oscilator_Rate * OscilatorSpeedScalar);
        Blue_Oscilator_Val = Math.sin(Blue_Oscilator += Blue_Oscilator_Rate * OscilatorSpeedScalar);
        Red_Oscilator_Val = (Red_Oscilator_Val + 1.0D) / 2D;
        Green_Oscilator_Val = (Green_Oscilator_Val + 1.0D) / 2D;
        Blue_Oscilator_Val = (Blue_Oscilator_Val + 1.0D) / 2D;
        Red_Oscilator_Val *= OscilatorEffectScalar;
        Green_Oscilator_Val *= OscilatorEffectScalar;
        Blue_Oscilator_Val *= OscilatorEffectScalar;
        for(int i = 0; i < FireStack.size(); i++)
            ((IsoFire)FireStack.get(i)).update();
        FireRecalc--;
        if(FireRecalc < 0)
            FireRecalc = FireRecalcDelay;
    }
    public static int NumActiveFires = 0;
    public static double Red_Oscilator = 0.0D;
    public static double Green_Oscilator = 0.0D;
    public static double Blue_Oscilator = 0.0D;
    public static double Red_Oscilator_Rate = 0.10000000149011612D;
    public static double Green_Oscilator_Rate = 0.12999999523162842D;
    public static double Blue_Oscilator_Rate = 0.087600000202655792D;
    public static double Red_Oscilator_Val = 0.0D;
    public static double Green_Oscilator_Val = 0.0D;
    public static double Blue_Oscilator_Val = 0.0D;
    public static double OscilatorSpeedScalar = 15.600000381469727D;
    public static double OscilatorEffectScalar = 0.0038999998942017555D;
    public static int MaxFireObjects = 75;
    public static int FireRecalcDelay;
    public static int FireRecalc;
    public static bool LightCalcFromBurningCharacters = false;
    public static float FireAlpha = 1.0F;
    public static float SmokeAlpha = 1.0F;
    public static int FireAnimDelay = 4;
    public static int SmokeAnimDelay = 6;
    public static ColorInfo FireTintMod = new ColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
    public static ColorInfo SmokeTintMod = new ColorInfo(0.5F, 0.5F, 0.5F, 1.0F);
    public static Stack FireStack = new Stack();
    public static Stack CharactersOnFire_Stack = new Stack();
    static 
    {
        FireRecalcDelay = 25;
        FireRecalc = FireRecalcDelay;
    }
}
} // namespace
