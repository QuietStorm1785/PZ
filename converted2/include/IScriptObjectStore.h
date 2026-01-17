#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IScriptObjectStore.java
namespace zombie {
namespace scripting {
#include "IsoGameCharacter.h"
#include "Inventory.h"
#include "Item.h"
#include "QuestTaskCondition.h"
#include "Recipe.h"
#include "Room.h"
#include "Script.h"
#include "ScriptActivatable.h"
#include "ScriptCharacter.h"
#include "ScriptContainer.h"
#include "ScriptFlag.h"
#include "Waypoint.h"
#include "Zone.h"
class IScriptObjectStore {
public:
    virtual ~IScriptObjectStore() = default;
{
    public abstract Inventory getInventory(std::string s);
    public abstract ScriptCharacter getCharacter(std::string s);
    public abstract IsoGameCharacter getCharacterActual(std::string s);
    public abstract Waypoint getWaypoint(std::string s);
    public abstract ScriptContainer getScriptContainer(std::string s);
    public abstract Room getRoom(std::string s);
    public abstract ScriptActivatable getActivatable(std::string s);
    public abstract std::string getFlagValue(std::string s);
    public abstract ScriptFlag getFlag(std::string s);
    public abstract Zone getZone(std::string s);
    public abstract QuestTaskCondition getQuestCondition(std::string s);
    public abstract Item getItem(std::string s);
    public abstract Recipe getRecipe(std::string s);
    public abstract Script getScript(std::string s);
}
} // namespace
