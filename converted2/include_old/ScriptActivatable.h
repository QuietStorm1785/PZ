#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ScriptActivatable.java
namespace zombie {
namespace scripting {
namespace objects {
#include "NulledArrayList.h"
#include "iso.h"
#include "Activatable.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class ScriptActivatable : public BaseScriptObject {
public:
{
    public ScriptActivatable()
    {
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        type = strArray[0].trim();
        x = Integer.parseInt(strArray[1].trim());
        y = Integer.parseInt(strArray[2].trim());
        z = Integer.parseInt(strArray[3].trim());
    }
    public bool IsActivated()
    {
        Activatable ac = getActual();
        if(ac == nullptr)
            return false;
        else
            return ac.Activated();
    }
    public void Toggle()
    {
        Activatable ac = getActual();
        if(ac == nullptr)
        {
            return;
        } else
        {
            ac.Toggle();
            return;
        }
    }
    public Activatable getActual()
    {
        if(ac != nullptr)
            return ac;
        IsoGridSquare sq = IsoWorld.instance.CurrentCell.getGridSquare(this.x, y, z);
        for(int x = 0; x < sq.getObjects().size(); x++)
        {
            IsoObject ob = (IsoObject)sq.getObjects().get(x);
            if((ob instanceof Activatable) && ((Activatable)ob).getActivatableType() == type))
            {
                ac = (Activatable)ob;
                return (Activatable)ob;
            }
        }
        return nullptr;
    }
    public int x;
    public int y;
    public int z;
    public std::string name;
    public std::string type;
    Activatable ac;
}
} // namespace
