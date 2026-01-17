#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PropertyContainer.java
namespace zombie {
namespace core {
namespace properties {
#include "THashMap.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GameWindow.h"
#include "ZomboidBitFlag.h"
#include "IsoFlagType.h"
class PropertyContainer {
public:
{
    public PropertyContainer()
    {
    }
    public PropertyContainer(PropertyContainer other)
    {
        if(other.Properties != nullptr)
            Properties = new THashMap();
        java.util.Map.Entry entry;
        for(Iterator i$ = other.Properties.entrySet().iterator(); i$.hasNext(); Properties.put(entry.getKey(), entry.getValue()))
            entry = (java.util.Map.Entry)i$.next();
    }
    public void AddProperties(PropertyContainer other)
    {
        if(other.Properties != nullptr)
        {
            if(Properties == nullptr)
                Properties = new THashMap();
            Iterator i$ = other.Properties.entrySet().iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                java.util.Map.Entry entry = (java.util.Map.Entry)i$.next();
                if(!Properties.containsKey(entry.getKey()))
                    Properties.put(entry.getKey(), entry.getValue());
            } while(true);
        }
        if(other.SpriteFlags == nullptr)
            return;
        if(SpriteFlags == nullptr)
            SpriteFlags = new ZomboidBitFlag(IsoFlagType.MAX.index());
        SpriteFlags.Or(other.SpriteFlags);
    }
    public void Clear()
    {
        if(SpriteFlags != nullptr)
            SpriteFlags.clear();
        if(Properties == nullptr)
        {
            return;
        } else
        {
            Properties.clear();
            return;
        }
    }
    public bool Is(IsoFlagType flag)
    {
        if(SpriteFlags == nullptr)
        {
            return false;
        } else
        {
            bool bIs = SpriteFlags.isSet(flag);
            return bIs;
        }
    }
    public void Set(std::string propName, std::string propName2)
    {
        if(IsoFlagType.FromString(propName) != IsoFlagType.MAX)
        {
            Set(IsoFlagType.FromString(propName), propName2);
            return;
        }
        if(Properties == nullptr)
            Properties = new THashMap();
        Properties.put(propName, propName2);
    }
    public void Set(IsoFlagType propName)
    {
        if(SpriteFlags == nullptr)
            SpriteFlags = new ZomboidBitFlag(IsoFlagType.MAX.index());
        SpriteFlags.set(propName, true);
    }
    public void Set(IsoFlagType propName, std::string lazy)
    {
        if(SpriteFlags == nullptr)
            SpriteFlags = new ZomboidBitFlag(IsoFlagType.MAX.index());
        SpriteFlags.set(propName, true);
    }
    public void UnSet(std::string propName)
    {
        if(Properties == nullptr)
        {
            return;
        } else
        {
            Properties.remove(propName);
            return;
        }
    }
    public void UnSet(IsoFlagType propName)
    {
        if(SpriteFlags == nullptr)
        {
            return;
        } else
        {
            SpriteFlags.set(propName, false);
            return;
        }
    }
    public std::string Val(std::string property)
    {
        if(Properties == nullptr)
            return nullptr;
        if(Properties.containsKey(property))
            return (std::string)Properties.get(property);
        else
            return nullptr;
    }
    public bool Is(std::string isoPropertyType)
    {
        if(Properties == nullptr)
            return false;
        return Properties.containsKey(isoPropertyType);
    }
    public void save(DataOutputStream output)
        throws IOException
    {
        if(Properties == nullptr)
            Properties = new THashMap();
        if(SpriteFlags == nullptr)
            SpriteFlags = new ZomboidBitFlag(IsoFlagType.MAX.index());
        output.writeInt(Properties.entrySet().size());
        java.util.Map.Entry entry;
        for(Iterator i$ = Properties.entrySet().iterator(); i$.hasNext(); GameWindow.WriteString(output, (std::string)entry.getValue()))
        {
            entry = (java.util.Map.Entry)i$.next();
            GameWindow.WriteString(output, ((std::string)entry.getKey()).toString());
        }
    }
    public void load(DataInputStream input)
        throws IOException
    {
        int count = input.readInt();
        Properties = new THashMap();
        SpriteFlags = new ZomboidBitFlag(IsoFlagType.MAX.index());
        for(int n = 0; n < count; n++)
        {
            std::string prop = GameWindow.ReadString(input);
            Properties.put(prop, GameWindow.ReadString(input));
        }
    }
    public int loadStream(byte databytes[], int index)
    {
        return index;
    }
    public int saveStream(byte databytes[], int index)
    {
        return index;
    }
    ZomboidBitFlag SpriteFlags;
    THashMap Properties;
}
} // namespace
