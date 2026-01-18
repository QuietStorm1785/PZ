#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RecipeManager.java
namespace zombie {
namespace inventory {
#include <vector>
#include <algorithm>
#include "LuaCaller.h"
#include "LuaReturn.h"
#include "KahluaTable.h"
#include "LuaManager.h"
#include "IsoPlayer.h"
#include "PerkFactory.h"
#include "Drainable.h"
#include "ScriptManager.h"
#include "Recipe.h"
// Referenced classes of package zombie.inventory:
//            InventoryItem, InventoryItemFactory
class RecipeManager {
public:
{
    public RecipeManager()
    {
    }
    public static bool DoesUseItemUp(std::string itemToUse, Recipe recipe)
    {
        for(int n = 0; n < recipe.Source.size(); n++)
            if(itemToUse == ((zombie.scripting.objects.Recipe.Source)recipe.Source.get(n)).type) && ((zombie.scripting.objects.Recipe.Source)recipe.Source.get(n)).keep)
                return false;
        return true;
    }
    public static bool DoesWipeUseDelta(std::string itemToUse, std::string itemToMake)
    {
        return "Battery" == itemToMake);
    }
    public static int UseAmount(std::string itemToUse, Recipe recipe)
    {
        for(int n = 0; n < recipe.Source.size(); n++)
            if(itemToUse == ((zombie.scripting.objects.Recipe.Source)recipe.Source.get(n)).type))
            {
                int num = ((zombie.scripting.objects.Recipe.Source)recipe.Source.get(n)).count;
                if((itemToUse.contains("Plank") || itemToUse.contains("Nails")) && IsoPlayer.getInstance().getPerkLevel(zombie.characters.skills.PerkFactory.Perks.Woodwork) == 5 && num > 1)
                    num /= 2;
                return num;
            }
        return 1;
    }
    public static Stack getRecipeItems(InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d)
    {
        RecipeList.clear();
        Stack ri = ScriptManager.instance.getAllRecipes();
        for(int m = 0; m < ri.size(); m++)
        {
            Recipe r = (Recipe)ri.get(m);
            int n = 0;
            if(((zombie.scripting.objects.Recipe.Source)r.Source.get(0)).type == nullptr)
                n++;
            else
            if(!Has(((zombie.scripting.objects.Recipe.Source)r.Source.get(0)).type, a, b, c, d, ((zombie.scripting.objects.Recipe.Source)r.Source.get(0)).count))
                continue;
            if(((zombie.scripting.objects.Recipe.Source)r.Source.get(1)).type == nullptr)
                n++;
            else
            if(!Has(((zombie.scripting.objects.Recipe.Source)r.Source.get(1)).type, a, b, c, d, ((zombie.scripting.objects.Recipe.Source)r.Source.get(1)).count))
                continue;
            if(((zombie.scripting.objects.Recipe.Source)r.Source.get(2)).type == nullptr)
                n++;
            else
            if(!Has(((zombie.scripting.objects.Recipe.Source)r.Source.get(2)).type, a, b, c, d, ((zombie.scripting.objects.Recipe.Source)r.Source.get(2)).count))
                continue;
            if(((zombie.scripting.objects.Recipe.Source)r.Source.get(3)).type == nullptr)
                n++;
            else
            if(!Has(((zombie.scripting.objects.Recipe.Source)r.Source.get(3)).type, a, b, c, d, ((zombie.scripting.objects.Recipe.Source)r.Source.get(3)).count))
                continue;
            if(!HasBlank(n, a, b, c, d))
                continue;
            if(r.LuaTest != nullptr)
            {
                InventoryItem items[] = new InventoryItem[5];
                items[r.FindIndexOf(a)] = a;
                items[r.FindIndexOf(b)] = b;
                items[r.FindIndexOf(c)] = c;
                items[r.FindIndexOf(d)] = d;
                a = items[0];
                b = items[1];
                c = items[2];
                d = items[3];
                LuaReturn ret = LuaManager.caller.protectedCall(LuaManager.thread, LuaManager.env.rawget(r.LuaTest), new Object[] {
                    a, b, c, d
                });
                if(!((Boolean)ret.getFirst()).booleanValue())
                    continue;
            }
            RecipeList.add(r);
        }
        return RecipeList;
    }
    static InventoryItem DoBatteriesCrafting(std::string itemToUse, InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d)
    {
        if(Has(itemToUse, a, b, c, d) && Has("Battery", a, b, c, d) && HasBlank(2, a, b, c, d))
        {
            float delta = UseDelta(itemToUse, a, b, c, d);
            float batDelta = UseDelta("Battery", a, b, c, d);
            if(delta == 0.0F && batDelta > 0.0F)
                return InventoryItemFactory.CreateItem(itemToUse, batDelta);
        }
        if(Has(itemToUse, a, b, c, d) && HasBlank(3, a, b, c, d))
        {
            float delta = UseDelta(itemToUse, a, b, c, d);
            if(delta > 0.0F)
                return InventoryItemFactory.CreateItem("Battery", delta);
        }
        return nullptr;
    }
    static bool Has(std::string type, InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d)
    {
        return a != nullptr && a.type == type) || b != nullptr && b.type == type) || c != nullptr && c.type == type) || d != nullptr && d.type == type);
    }
    static bool Has(std::string type, InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d, int num)
    {
        std::string typeArray[] = type.split("/");
        for(int n = 0; n < typeArray.length; n++)
        {
            type = typeArray[n];
            int oldnum = num;
            if((type.contains("Plank") || type.contains("Nails")) && IsoPlayer.getInstance().getPerkLevel(zombie.characters.skills.PerkFactory.Perks.Woodwork) == 5 && num > 1)
                num /= 2;
            if(a != nullptr && a.type == type) || b != nullptr && b.type == type) || c != nullptr && c.type == type) || d != nullptr && d.type == type))
            {
                if(a != nullptr && a.type == type) && a.uses >= num)
                    return true;
                if(b != nullptr && b.type == type) && b.uses >= num)
                    return true;
                if(c != nullptr && c.type == type) && c.uses >= num)
                    return true;
                if(d != nullptr && d.type == type) && d.uses >= num)
                    return true;
            }
            num = oldnum;
        }
        return false;
    }
    static bool HasBlank(int n, InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d)
    {
        int cn = 0;
        if(a == nullptr)
            cn++;
        if(b == nullptr)
            cn++;
        if(c == nullptr)
            cn++;
        if(d == nullptr)
            cn++;
        return cn == n;
    }
    static float UseDelta(std::string type, InventoryItem a, InventoryItem b, InventoryItem c, InventoryItem d)
    {
        if(a != nullptr && a.type == type) && (a instanceof Drainable))
            return ((Drainable)a).getUsedDelta();
        if(b != nullptr && b.type == type) && (b instanceof Drainable))
            return ((Drainable)b).getUsedDelta();
        if(c != nullptr && c.type == type) && (c instanceof Drainable))
            return ((Drainable)c).getUsedDelta();
        if(d != nullptr && d.type == type) && (d instanceof Drainable))
            return ((Drainable)d).getUsedDelta();
        else
            return 1.0F;
    }
    private static Stack RecipeList = new Stack();
}
} // namespace
