#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TraitFactory.java
namespace zombie {
namespace characters {
namespace traits {
#include "THashMap.h"
#include "NulledArrayList.h"
#include "IListBoxItem.h"
class TraitFactory {
public:
{
    public static class Trait : public IListBoxItem
    {
        public std::string getLabel()
        {
            return name;
        }
        public std::string getLeftLabel()
        {
            return name;
        }
        public std::string getRightLabel()
        {
            int cost = this.cost;
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
        public std::string traitID;
        public std::string name;
        public int cost;
        public std::string description;
        public bool prof;
        public NulledArrayList MutuallyExclusive;
        public Trait(std::string tr, std::string name, int cost, std::string desc, bool prof)
        {
            MutuallyExclusive = new NulledArrayList(0);
            traitID = tr;
            this.name = name;
            this.cost = cost;
            description = desc;
            this.prof = prof;
        }
    }
    public TraitFactory()
    {
    }
    public static void init()
    {
    }
    public static void setMutualExclusive(std::string a, std::string b)
    {
        ((Trait)TraitMap.get(a)).MutuallyExclusive.add(b);
        ((Trait)TraitMap.get(b)).MutuallyExclusive.add(a);
    }
    public static void addTrait(std::string type, std::string name, int cost, std::string desc, bool profession)
    {
        TraitMap.put(type, new Trait(type, name, cost, desc, profession));
    }
    public static Trait getTrait(std::string name)
    {
        if(TraitMap.containsKey(name))
            return (Trait)TraitMap.get(name);
        else
            return nullptr;
    }
    public static THashMap TraitMap = new THashMap();
}
} // namespace
