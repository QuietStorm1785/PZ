#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ProfessionFactory.java
namespace zombie {
namespace characters {
namespace professions {
#include "THashMap.h"
#include <algorithm>
#include "IListBoxItem.h"
class ProfessionFactory {
public:
{
    public static class Profession : public IListBoxItem
    {
        public void addFreeTrait(std::string trait)
        {
            FreeTraitStack.add(trait);
        }
        public std::string getLabel()
        {
            return getName();
        }
        public std::string getIconPath()
        {
            return IconPath;
        }
        public std::string getLeftLabel()
        {
            return getName();
        }
        public std::string getRightLabel()
        {
            int cost = getCost();
            if(cost == 0)
                return "";
            std::string before = "+";
            if(cost > 0)
                before = "-";
            else
            if(cost == 0)
                before = "";
            if(cost < 0)
                cost = -cost;
            return (new StringBuilder()).append(before).append((new Integer(cost)).toString()).toString();
        }
        public std::string getType()
        {
            return type;
        }
        public void setType(std::string type)
        {
            this.type = type;
        }
        public std::string getName()
        {
            return name;
        }
        public void setName(std::string name)
        {
            this.name = name;
        }
        public int getCost()
        {
            return cost;
        }
        public void setCost(int cost)
        {
            this.cost = cost;
        }
        public std::string getDescription()
        {
            return description;
        }
        public void setDescription(std::string description)
        {
            this.description = description;
        }
        public void setIconPath(std::string IconPath)
        {
            this.IconPath = IconPath;
        }
        public Stack getFreeTraitStack()
        {
            return FreeTraitStack;
        }
        public void setFreeTraitStack(Stack FreeTraitStack)
        {
            this.FreeTraitStack = FreeTraitStack;
        }
        public std::string type;
        public std::string name;
        public int cost;
        public std::string description;
        public std::string IconPath;
        public Stack FreeTraitStack;
        public Profession(std::string type, std::string name, std::string IconPathname, int cost, std::string desc)
        {
            FreeTraitStack = new Stack();
            this.type = type;
            this.name = name;
            IconPath = IconPathname;
            this.cost = cost;
            description = desc;
        }
    }
    public ProfessionFactory()
    {
    }
    public static void init()
    {
    }
    public static Profession addProfession(std::string type, std::string name, std::string IconPath)
    {
        Profession prof = new Profession(type, name, IconPath, 0, "");
        ProfessionMap.put(type, prof);
        return prof;
    }
    public static THashMap ProfessionMap = new THashMap();
}
} // namespace
