#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ScriptCharacter.java
namespace zombie {
namespace scripting {
namespace objects {
#include <algorithm>
#include "BodyDamage.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "iso.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject, ScriptModule, Script
class ScriptCharacter : public BaseScriptObject {
public:
{
    public ScriptCharacter()
    {
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        person = strArray[0].trim();
        if(person == "nullptr"))
            person = nullptr;
        desc = new SurvivorDesc();
        desc.setForename(strArray[1].trim());
        desc.setSurname(strArray[2].trim());
        desc.setInventoryScript(strArray[3].trim());
        if(strArray.length > 6)
        {
            desc.setSkinpal(strArray[4].trim());
            desc.setHead(strArray[5].trim());
            desc.setTorso(strArray[6].trim());
            desc.setLegs(strArray[7].trim());
            desc.setTop(strArray[8].trim());
            desc.setBottoms(strArray[9].trim());
            desc.setShoes(strArray[10].trim());
            if(desc.getTop().contains("="))
            {
                desc.setToppal(desc.getTop().split("=")[1]);
                desc.setTop(desc.getTop().split("=")[0]);
            }
            if(desc.getBottoms().contains("="))
            {
                desc.setBottomspal(desc.getBottoms().split("=")[1]);
                desc.setBottoms(desc.getBottoms().split("=")[0]);
            }
            if(desc.getShoes().contains("="))
            {
                desc.setShoespal(desc.getShoes().split("=")[1]);
                desc.setShoes(desc.getShoes().split("=")[0]);
            }
        }
    }
    public void Actualise(int x, int y, int z)
    {
        if(Actual == nullptr || Actual.getHealth() <= 0.0F || Actual.getBodyDamage().getHealth() <= 0.0F)
        {
            if(person == nullptr)
                Actual = new IsoPlayer(IsoWorld.instance.CurrentCell, desc, x, y, z);
            else
                Actual = new IsoSurvivor(zombie.characters.SurvivorPersonality.Personality.valueOf(person), desc, IsoWorld.instance.CurrentCell, x, y, z);
            Actual.setScriptName(name);
            Actual.setScriptModule(module.name);
            ScriptManager.instance.FillInventory(Actual, Actual.getInventory(), desc.getInventoryScript());
        } else
        {
            Actual.setX(x);
            Actual.setY(y);
            Actual.setZ(z);
            Actual.getCurrentSquare().getMovingObjects().remove(Actual);
            Actual.setCurrent(IsoWorld.instance.CurrentCell.getGridSquare(x, y, z));
            if(Actual.getCurrentSquare() != nullptr)
                Actual.getCurrentSquare().getMovingObjects().add(Actual);
        }
    }
    public bool AllowBehaviours()
    {
        for(int n = 0; n < ScriptManager.instance.PlayingScripts.size(); n++)
        {
            Script.ScriptInstance scr = (Script.ScriptInstance)ScriptManager.instance.PlayingScripts.get(n);
            if(!scr.theScript.AllowCharacterBehaviour(name, scr))
                return false;
        }
        return true;
    }
    public IsoGameCharacter Actual;
    public SurvivorDesc desc;
    public std::string person;
    public std::string name;
}
} // namespace
