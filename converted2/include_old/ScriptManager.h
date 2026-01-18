#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ScriptManager.java
namespace zombie {
namespace scripting {
#include "THashMap.h"
#include <fstream>
#include <iostream>
#include "URISyntaxException.h"
#include "URL.h"
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "Keyboard.h"
#include "GameWindow.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "IndieFileLoader.h"
#include "Rand.h"
#include "inventory.h"
#include "IsoCell.h"
#include "IsoWorld.h"
#include "ContainerDistribution.h"
#include "FloorDistribution.h"
#include "Inventory.h"
#include "Item.h"
#include "LanguageDefinition.h"
#include "QuestTaskCondition.h"
#include "Recipe.h"
#include "Room.h"
#include "Script.h"
#include "ScriptActivatable.h"
#include "ScriptCharacter.h"
#include "ScriptContainer.h"
#include "ScriptFlag.h"
#include "ScriptModule.h"
#include "ScriptTalker.h"
#include "ShelfDistribution.h"
#include "Trigger.h"
#include "Waypoint.h"
#include "Zone.h"
#include "PZConsole.h"
#include "TutorialManager.h"
// Referenced classes of package zombie.scripting:
//            IScriptObjectStore
class ScriptManager {
public:
    implements IScriptObjectStore
{
    public ScriptManager()
    {
        TriggerMap = new THashMap();
        CustomTriggerMap = new THashMap();
        CustomTriggerLastRan = new THashMap();
        HookMap = new THashMap();
        ModuleMap = new THashMap();
        PlayingScripts = new Stack();
        CurrentLoadingModule = nullptr;
        ModuleAliases = new THashMap();
        skipping = false;
        MapMap = new THashMap();
        toStop = new ArrayList();
        toStopInstance = new ArrayList();
        CachedModules = new HashMap();
        recipesTempList = new Stack();
        zoneTempList = new Stack();
        conTempList = new Stack();
        floorTempList = new Stack();
        shelfTempList = new Stack();
    }
    public void AddOneTime(std::string event, std::string script)
    {
        event = event.toLowerCase();
        Stack stack = nullptr;
        if(HookMap.containsKey(event))
        {
            stack = (Stack)HookMap.get(event);
        } else
        {
            stack = new Stack();
            HookMap.put(event, stack);
        }
        stack.add(script);
    }
    public void FireHook(std::string event)
    {
        if(HookMap.containsKey(event))
        {
            std::string hook;
            for(Iterator i$ = ((Stack)HookMap.get(event)).iterator(); i$.hasNext(); PlayScript(hook))
                hook = (std::string)i$.next();
            ((Stack)HookMap.get(event)).clear();
        }
    }
    public void ParseScriptPP(std::string totalFile)
    {
        bool done = false;
        Stack Tokens = new Stack();
        int depth = 0;
        int nextindexOfOpen = 0;
        int nextindexOfClosed = 0;
        do
        {
            if(done)
                break;
            depth = 0;
            nextindexOfOpen = 0;
            nextindexOfClosed = 0;
            if(totalFile.indexOf("}", nextindexOfOpen + 1) == -1)
            {
                done = true;
                break;
            }
            do
            {
                nextindexOfOpen = totalFile.indexOf("{", nextindexOfOpen + 1);
                nextindexOfClosed = totalFile.indexOf("}", nextindexOfClosed + 1);
                if(nextindexOfClosed < nextindexOfOpen && nextindexOfClosed != -1 || nextindexOfOpen == -1)
                {
                    nextindexOfOpen = nextindexOfClosed;
                    depth--;
                } else
                if(nextindexOfOpen != -1)
                {
                    nextindexOfClosed = nextindexOfOpen;
                    depth++;
                }
            } while(depth > 0);
            Tokens.add(totalFile.substring(0, nextindexOfOpen + 1));
            totalFile = totalFile.substring(nextindexOfOpen + 1);
        } while(true);
        if(totalFile.trim().length() > 0)
            Tokens.add(totalFile.trim());
        for(int n = 0; n < Tokens.size(); n++)
        {
            std::string token = (std::string)Tokens.get(n);
            CreateFromTokenPP(token);
        }
    }
    public void ParseScript(std::string totalFile)
    {
        bool done = false;
        Stack Tokens = new Stack();
        int depth = 0;
        int nextindexOfOpen = 0;
        int nextindexOfClosed = 0;
        do
        {
            if(done)
                break;
            depth = 0;
            nextindexOfOpen = 0;
            nextindexOfClosed = 0;
            if(totalFile.indexOf("}", nextindexOfOpen + 1) == -1)
            {
                done = true;
                break;
            }
            do
            {
                nextindexOfOpen = totalFile.indexOf("{", nextindexOfOpen + 1);
                nextindexOfClosed = totalFile.indexOf("}", nextindexOfClosed + 1);
                if(nextindexOfClosed < nextindexOfOpen && nextindexOfClosed != -1 || nextindexOfOpen == -1)
                {
                    nextindexOfOpen = nextindexOfClosed;
                    depth--;
                } else
                if(nextindexOfOpen != -1)
                {
                    nextindexOfClosed = nextindexOfOpen;
                    depth++;
                }
            } while(depth > 0);
            Tokens.add(totalFile.substring(0, nextindexOfOpen + 1));
            totalFile = totalFile.substring(nextindexOfOpen + 1);
        } while(true);
        if(totalFile.trim().length() > 0)
            Tokens.add(totalFile.trim());
        for(int n = 0; n < Tokens.size(); n++)
        {
            std::string token = (std::string)Tokens.get(n);
            CreateFromToken(token);
        }
    }
    public void StopScript(std::string stop)
    {
        toStop.add(stop);
    }
    public void PlayInstanceScript(std::string idname, std::string script, std::string a, IsoGameCharacter A)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(idname != nullptr && idname == ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).ID))
                return;
        zombie.scripting.objects.Script.ScriptInstance inst = new zombie.scripting.objects.Script.ScriptInstance();
        inst.ID = idname;
        Script scr = getScript(script);
        inst.theScript = scr;
        inst.CharacterAliases.put(a, A);
        inst.CharacterAliasesR.put(A, a);
        A.getActiveInInstances().add(inst);
        instance.PlayingScripts.add(inst);
        inst.begin();
    }
    public zombie.scripting.objects.Script.ScriptInstance PlayInstanceScript(std::string idname, std::string script, THashMap Aliases)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(idname != nullptr && idname == ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).ID))
                return nullptr;
        zombie.scripting.objects.Script.ScriptInstance inst = new zombie.scripting.objects.Script.ScriptInstance();
        inst.ID = idname;
        Script scr = getScript(script);
        inst.theScript = scr;
        IsoGameCharacter A;
        for(Iterator it = Aliases.entrySet().iterator(); it != nullptr && it.hasNext(); A.getActiveInInstances().add(inst))
        {
            java.util.Map.Entry entry = (java.util.Map.Entry)it.next();
            std::string a = (std::string)entry.getKey();
            A = (IsoGameCharacter)entry.getValue();
            inst.CharacterAliases.put(a, A);
            inst.CharacterAliasesR.put(A, a);
        }
        instance.PlayingScripts.add(inst);
        inst.begin();
        return inst;
    }
    public void PlayInstanceScript(std::string idname, std::string script, std::string a, IsoGameCharacter A, std::string b, IsoGameCharacter B)
    {
        zombie.scripting.objects.Script.ScriptInstance inst = new zombie.scripting.objects.Script.ScriptInstance();
        inst.ID = idname;
        Script scr = getScript(script);
        int n;
        if(scr == nullptr)
            n = 0;
        inst.theScript = scr;
        inst.CharacterAliases.put(a, A);
        inst.CharacterAliasesR.put(A, a);
        inst.CharacterAliases.put(b, B);
        inst.CharacterAliasesR.put(B, b);
        for(n = 0; n < PlayingScripts.size(); n++)
            if(idname != nullptr && idname == ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).ID))
                inst.CharactersAlreadyInScript = true;
        A.getActiveInInstances().add(inst);
        B.getActiveInInstances().add(inst);
        instance.PlayingScripts.add(inst);
        inst.begin();
    }
    public void PlayInstanceScript(std::string idname, std::string script, std::string a, IsoGameCharacter A, std::string b, IsoGameCharacter B, std::string c, 
            IsoGameCharacter C)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(idname != nullptr && idname == ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).ID))
                return;
        zombie.scripting.objects.Script.ScriptInstance inst = new zombie.scripting.objects.Script.ScriptInstance();
        inst.ID = idname;
        Script scr = getScript(script);
        inst.theScript = scr;
        inst.CharacterAliases.put(a, A);
        inst.CharacterAliasesR.put(A, a);
        inst.CharacterAliases.put(b, B);
        inst.CharacterAliasesR.put(B, b);
        inst.CharacterAliases.put(c, C);
        inst.CharacterAliasesR.put(C, c);
        A.getActiveInInstances().add(inst);
        B.getActiveInInstances().add(inst);
        C.getActiveInInstances().add(inst);
        instance.PlayingScripts.add(inst);
        inst.begin();
    }
    public void PlayScript(std::string script)
    {
        Script scr = getScript(script);
        if(scr != nullptr)
        {
            for(int n = 0; n < PlayingScripts.size(); n++)
                if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript == scr && !((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.Instancable)
                {
                    PlayingScripts.remove(n);
                    n--;
                }
            scr.module.PlayScript(scr.name);
        }
    }
    public zombie.scripting.objects.Script.ScriptInstance PlayScript(std::string script, zombie.scripting.objects.Script.ScriptInstance aliases)
    {
        Script scr = getScript(script);
        if(scr != nullptr)
        {
            for(int n = 0; n < PlayingScripts.size(); n++)
                if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript == scr && !((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.Instancable)
                {
                    PlayingScripts.remove(n);
                    n--;
                }
            return scr.module.PlayScript(scr.name, aliases);
        } else
        {
            return nullptr;
        }
    }
    public void update()
    {
        if(!PZConsole.instance.isVisible() && Keyboard.isKeyDown(1) && TutorialManager.instance.StealControl)
            skipping = true;
        for(int n = 0; n < toStopInstance.size(); n++)
        {
            for(int m = 0; m < PlayingScripts.size(); m++)
            {
                if(PlayingScripts.get(m) != toStopInstance.get(n))
                    continue;
                zombie.scripting.objects.Script.ScriptInstance s = (zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(m);
                IsoGameCharacter c;
                for(Iterator i = s.CharacterAliases.values().iterator(); i != nullptr && i.hasNext(); c.getActiveInInstances().remove(s))
                    c = (IsoGameCharacter)i.next();
                PlayingScripts.remove(m);
                m--;
            }
        }
        toStopInstance.clear();
        for(int n = 0; n < toStop.size(); n++)
        {
            for(int m = 0; m < PlayingScripts.size(); m++)
            {
                if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(m)).theScript.name == toStop.get(n)))
                {
                    zombie.scripting.objects.Script.ScriptInstance s = (zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(m);
                    IsoGameCharacter c;
                    for(Iterator i = s.CharacterAliases.values().iterator(); i != nullptr && i.hasNext(); c.getActiveInInstances().remove(s))
                        c = (IsoGameCharacter)i.next();
                    m--;
                }
                PlayingScripts.remove(m);
            }
        }
        toStop.clear();
        for(Iterator it = CustomTriggerMap.values().iterator(); it != nullptr && it.hasNext();)
        {
            Stack next = (Stack)it.next();
            int n = 0;
            while(n < next.size()) 
            {
                if(!((Trigger)next.get(n)).Locked && ((Trigger)next.get(n)).module.ValidMapCheck(IsoWorld.instance.CurrentCell.getFilename()))
                    ((Trigger)next.get(n)).Process();
                n++;
            }
        }
        Set keys = CustomTriggerLastRan.keySet();
        std::string key;
        Integer next;
        for(Iterator i$ = keys.iterator(); i$.hasNext(); CustomTriggerLastRan.put(key, next))
        {
            key = (std::string)i$.next();
            next = (Integer)CustomTriggerLastRan.get(key);
            Integer integer = next;
            Integer integer1 = next = Integer.valueOf(next.intValue() + 1);
            Integer _tmp = integer;
        }
        for(int n = 0; n < PlayingScripts.size(); n++)
        {
            if(!((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.module.ValidMapCheck(IsoWorld.instance.CurrentCell.getFilename()))
                continue;
            ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).update();
            if(!((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).finished())
                continue;
            zombie.scripting.objects.Script.ScriptInstance inst = (zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n);
            PlayingScripts.remove(n);
            IsoGameCharacter chr;
            for(Iterator it2 = inst.CharacterAliases.values().iterator(); it2 != nullptr && it2.hasNext(); chr.getActiveInInstances().remove(inst))
                chr = (IsoGameCharacter)it2.next();
            n--;
        }
    }
    public void LoadFile(std::string filename, bool bLoadJar)
        throws FileNotFoundException
    {
        if(filename.contains(".tmx"))
        {
            IsoWorld.mapPath = filename.substring(0, filename.lastIndexOf("/"));
            IsoWorld.mapUseJar = bLoadJar;
            return;
        }
        if(!filename.contains(".txt"))
            return;
        InputStreamReader isr = IndieFileLoader.getStreamReader(filename, !bLoadJar);
        BufferedReader br = new BufferedReader(isr);
        std::string inputLine = nullptr;
        std::string totalFile = "";
        int depth = 0;
        do
            try
            {
                if((inputLine = br.readLine()) == nullptr)
                    break;
                if(inputLine != nullptr)
                    totalFile = (new StringBuilder()).append(totalFile).append(inputLine).toString();
            }
            catch(Exception ex)
            {
                return;
            }
        while(true);
        int a;
        int b;
        for(; totalFile.contains("*/"); totalFile = (new StringBuilder()).append(totalFile.substring(0, a)).append("\n").append(totalFile.substring(b + 2)).toString())
        {
            a = totalFile.indexOf("/*");
            b = totalFile.indexOf("*/");
        }
        ParseScript(totalFile);
    }
    public void LoadFilePP(std::string filename, bool bLoadJar)
        throws FileNotFoundException, UnsupportedEncodingException
    {
        if(filename.contains(".tmx"))
        {
            IsoWorld.mapPath = filename.substring(0, filename.lastIndexOf("/"));
            IsoWorld.mapUseJar = bLoadJar;
            return;
        }
        if(!filename.contains(".txt"))
            return;
        InputStreamReader isr = IndieFileLoader.getStreamReader(filename, !bLoadJar);
        BufferedReader br = new BufferedReader(isr);
        std::string inputLine = nullptr;
        std::string totalFile = "";
        int lastdepth = 0;
        do
            try
            {
                if((inputLine = br.readLine()) == nullptr)
                    break;
                if(inputLine != nullptr)
                    totalFile = (new StringBuilder()).append(totalFile).append(inputLine).toString();
            }
            catch(Exception ex)
            {
                return;
            }
        while(true);
        try
        {
            int a;
            int b;
            for(; totalFile.contains("*/"); totalFile = (new StringBuilder()).append(totalFile.substring(0, a)).append("\n").append(totalFile.substring(b + 2)).toString())
            {
                a = totalFile.indexOf("/*");
                b = totalFile.indexOf("*/");
            }
        }
        catch(Exception ex)
        {
            Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        ParseScriptPP(totalFile);
    }
    private void CreateFromToken(std::string token)
    {
        token = token.trim();
        if(token.indexOf("module") == 0)
        {
            int firstopen = token.indexOf("{");
            int lastClose = token.lastIndexOf("}");
            std::string waypoint[] = token.split("[{}]");
            std::string name = waypoint[0];
            name = name.replace("module", "");
            name = name.trim();
            std::string actual = token.substring(firstopen + 1, lastClose);
            ScriptModule way = (ScriptModule)ModuleMap.get(name);
            way.Load(name, actual);
        }
    }
    private void CreateFromTokenPP(std::string token)
    {
        token = token.trim();
        if(token.indexOf("module") == 0)
        {
            std::string waypoint[] = token.split("[{}]");
            std::string name = waypoint[0];
            name = name.replace("module", "");
            name = name.trim();
            ScriptModule way = new ScriptModule();
            ModuleMap.put(name, way);
        }
    }
    public void LoadStory(std::string story)
        throws IOException, URISyntaxException
    {
        try
        {
            Enumeration en = GameWindow.class.getClassLoader().getResources((new StringBuilder()).append("stories/").append(story).append("/").toString());
            URL url = nullptr;
            if(en.hasMoreElements())
            {
                URL metaInf = (URL)en.nextElement();
                File fileMetaInf = new File(metaInf.toURI());
                std::string filenames[] = fileMetaInf.list();
                std::string arr$[] = filenames;
                int len$ = arr$.length;
                for(int i$ = 0; i$ < len$; i$++)
                {
                    std::string f = arr$[i$];
                    LoadFile((new StringBuilder()).append("stories/").append(story).append("/").append(f).toString(), true);
                }
            }
        }
        catch(IOException ex)
        {
            Logger.getLogger(ScriptManager.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
    }
    public Stack getStoryList()
        throws IOException, URISyntaxException
    {
        Stack StoryList = new Stack();
        File fo = new File("mods/stories/");
        std::string internalNames[] = fo.list();
        StoryList.addAll(Arrays.asList(internalNames));
        fo = new File("media/stories/");
        internalNames = fo.list();
        StoryList.addAll(Arrays.asList(internalNames));
        return StoryList;
    }
    public void LoadDir(std::string path, bool bUseJar)
        throws URISyntaxException
    {
        if(bUseJar)
        {
            File dir = new File((new StringBuilder()).append("media/").append(path).toString());
            std::string children[] = dir.list();
            for(int i = 0; i < children.length; i++)
            {
                std::string filename = children[i];
                File fileMetaInf = new File((new StringBuilder()).append(dir.getAbsolutePath()).append(File.separator).append(filename).toString());
                searchFolders(fileMetaInf);
            }
        } else
        {
            File fo = new File((new StringBuilder()).append("mods/").append(path).toString());
            searchFolders(fo);
        }
    }
    public void LoadDirPP(std::string path, bool bUseJar)
        throws URISyntaxException
    {
        if(bUseJar)
        {
            File dir = new File((new StringBuilder()).append("media/").append(path).toString());
            std::string children[] = dir.list();
            for(int i = 0; i < children.length; i++)
            {
                std::string filename = children[i];
                File fileMetaInf = new File((new StringBuilder()).append(dir.getAbsolutePath()).append(File.separator).append(filename).toString());
                searchFoldersPP(fileMetaInf);
            }
        } else
        {
            File fo = new File((new StringBuilder()).append("mods/").append(path).toString());
            searchFoldersPP(fo);
        }
    }
    public void searchFoldersPP(File fo)
    {
        if(fo.isDirectory())
        {
            std::string internalNames[] = fo.list();
            for(int i = 0; i < internalNames.length; i++)
                searchFoldersPP(new File((new StringBuilder()).append(fo.getAbsolutePath()).append(File.separator).append(internalNames[i]).toString()));
        } else
        {
            try
            {
                LoadFilePP(fo.getAbsolutePath(), false);
            }
            catch(Exception ex) { }
        }
    }
    public void searchFolders(File fo)
    {
        if(fo.isDirectory())
        {
            std::string internalNames[] = fo.list();
            for(int i = 0; i < internalNames.length; i++)
                searchFolders(new File((new StringBuilder()).append(fo.getAbsolutePath()).append(File.separator).append(internalNames[i]).toString()));
        } else
        if(fo.getAbsolutePath().toLowerCase().contains(".txt"))
            try
            {
                LoadFile(fo.getAbsolutePath(), false);
            }
            catch(Exception ex) { }
        else
        if(fo.getAbsolutePath().toLowerCase().contains(".lot"))
        {
            std::string name = fo.getAbsolutePath().substring(fo.getAbsolutePath().lastIndexOf("\\") + 1);
            name = name.substring(0, name.lastIndexOf("."));
            MapMap.put(name, fo.getAbsolutePath());
        }
    }
    public static std::string getItemName(std::string name)
    {
        if(!name.contains("."))
            return name;
        else
            return name.split("\\.")[1];
    }
    public void FillInventory(IsoGameCharacter chr, ItemContainer container, std::string InventoryScript)
    {
        Inventory inv = nullptr;
        std::string mod = chr.getScriptModule();
        if(InventoryScript.contains("."))
        {
            inv = getInventory(InventoryScript);
            mod = InventoryScript.split("\\.")[0];
        } else
        {
            inv = getInventory((new StringBuilder()).append(chr.getScriptModule()).append(".").append(InventoryScript).toString());
        }
        if(inv == nullptr)
            return;
        for(int n = 0; n < inv.Items.size(); n++)
            if(((zombie.scripting.objects.Inventory.Source)inv.Items.get(n)).type.trim().length() > 0)
            {
                InventoryItem item = InventoryItemFactory.CreateItem((new StringBuilder()).append(mod).append(".").append(((zombie.scripting.objects.Inventory.Source)inv.Items.get(n)).type).toString());
                item.setUses(((zombie.scripting.objects.Inventory.Source)inv.Items.get(n)).count);
                container.AddItem(item);
            }
    }
    public void Trigger(std::string type)
    {
        type = type.toLowerCase();
        FireHook(type);
        if(TriggerMap.containsKey(type))
        {
            Stack triggers = (Stack)TriggerMap.get(type);
            for(int n = 0; n < triggers.size(); n++)
                if(!((Trigger)triggers.get(n)).module.disabled && !((Trigger)triggers.get(n)).Locked)
                {
                    ((Trigger)triggers.get(n)).TriggerParam = nullptr;
                    ((Trigger)triggers.get(n)).TriggerParam2 = nullptr;
                    ((Trigger)triggers.get(n)).TriggerParam3 = nullptr;
                    ((Trigger)triggers.get(n)).Process();
                }
        }
    }
    public void Trigger(std::string type, std::string param)
    {
        type = type.toLowerCase();
        FireHook(type);
        if(TriggerMap.containsKey(type))
        {
            Stack triggers = (Stack)TriggerMap.get(type);
            for(int n = 0; n < triggers.size(); n++)
                if(!((Trigger)triggers.get(n)).module.disabled && !((Trigger)triggers.get(n)).Locked)
                {
                    ((Trigger)triggers.get(n)).TriggerParam = param;
                    ((Trigger)triggers.get(n)).Process();
                }
        }
    }
    public void Trigger(std::string type, std::string param, std::string param2)
    {
        type = type.toLowerCase();
        FireHook(type);
        if(TriggerMap.containsKey(type))
        {
            Stack triggers = (Stack)TriggerMap.get(type);
            for(int n = 0; n < triggers.size(); n++)
                if(!((Trigger)triggers.get(n)).module.disabled && !((Trigger)triggers.get(n)).Locked)
                {
                    ((Trigger)triggers.get(n)).TriggerParam = param;
                    ((Trigger)triggers.get(n)).TriggerParam2 = param2;
                    ((Trigger)triggers.get(n)).Process();
                }
        }
    }
    public void Trigger(std::string type, std::string param, std::string param2, std::string param3)
    {
        type = type.toLowerCase();
        FireHook(type);
        if(TriggerMap.containsKey(type))
        {
            Stack triggers = (Stack)TriggerMap.get(type);
            for(int n = 0; n < triggers.size(); n++)
                if(!((Trigger)triggers.get(n)).module.disabled && !((Trigger)triggers.get(n)).Locked)
                {
                    ((Trigger)triggers.get(n)).TriggerParam = param;
                    ((Trigger)triggers.get(n)).TriggerParam2 = param2;
                    ((Trigger)triggers.get(n)).TriggerParam2 = param3;
                    ((Trigger)triggers.get(n)).Process();
                }
        }
    }
    public bool IsScriptPlaying(std::string check)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.name == check))
                return true;
        return false;
    }
    public bool IsScriptPlaying(zombie.scripting.objects.Script.ScriptInstance check)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(PlayingScripts.get(n) == check)
                return true;
        return false;
    }
    public void PauseScript(std::string name)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.name == name))
                ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).Paused = true;
    }
    public void UnPauseScript(std::string name)
    {
        for(int n = 0; n < PlayingScripts.size(); n++)
            if(((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).theScript.name == name))
                ((zombie.scripting.objects.Script.ScriptInstance)PlayingScripts.get(n)).Paused = false;
    }
    public ScriptModule getModule(std::string name)
    {
        if(CachedModules.containsKey(name))
            return (ScriptModule)CachedModules.get(name);
        ScriptModule ret = nullptr;
        if(ModuleAliases.containsKey(name))
            name = (std::string)ModuleAliases.get(name);
        if(CachedModules.containsKey(name))
            return (ScriptModule)CachedModules.get(name);
        if(ModuleMap.containsKey(name))
            if(((ScriptModule)ModuleMap.get(name)).disabled)
                ret = nullptr;
            else
                ret = (ScriptModule)ModuleMap.get(name);
        if(ret != nullptr)
        {
            CachedModules.put(name, ret);
            return ret;
        }
        if(name.indexOf(".") != -1)
            ret = getModule(name.split("\\.")[0]);
        if(ret != nullptr)
        {
            CachedModules.put(name, ret);
            return ret;
        } else
        {
            return nullptr;
        }
    }
    public ScriptModule getModuleNoDisableCheck(std::string name)
    {
        if(ModuleAliases.containsKey(name))
            name = (std::string)ModuleAliases.get(name);
        if(ModuleMap.containsKey(name))
            return (ScriptModule)ModuleMap.get(name);
        if(name.indexOf(".") != -1)
            return getModule(name.split("\\.")[0]);
        else
            return nullptr;
    }
    public Inventory getInventory(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return (Inventory)module.InventoryMap.get(getItemName(name));
    }
    public ScriptCharacter getCharacter(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getCharacter(getItemName(name));
    }
    public ScriptCharacter FindCharacter(std::string name)
    {
        for(Iterator modules = ModuleMap.values().iterator(); modules != nullptr && modules.hasNext();)
        {
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell) && m.CharacterMap.containsKey(name))
                return m.getCharacter(name);
        }
        return nullptr;
    }
    public IsoGameCharacter getCharacterActual(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getCharacterActual(getItemName(name));
    }
    public int getFlagIntValue(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return 0;
        else
            return module.getFlagIntValue(getItemName(name));
    }
    public std::string getFlagValue(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return "";
        else
            return module.getFlagValue(getItemName(name));
    }
    public Waypoint getWaypoint(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getWaypoint(getItemName(name));
    }
    public ScriptContainer getScriptContainer(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getScriptContainer(getItemName(name));
    }
    public Room getRoom(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getRoom(getItemName(name));
    }
    public LanguageDefinition getLanguageDef(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getLanguageDef(getItemName(name));
    }
    public std::string getLanguage(std::string id)
    {
        if(!id.contains("@"))
        {
            return id;
        } else
        {
            std::string split[] = id.split("-");
            LanguageDefinition def = getLanguageDef(split[0]);
            return def.get(Integer.parseInt(split[1]));
        }
    }
    public ScriptTalker getTalker(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getTalker(getItemName(name));
    }
    public ScriptActivatable getActivatable(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getActivatable(getItemName(name));
    }
    public ScriptFlag getFlag(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getFlag(getItemName(name));
    }
    public Zone getZone(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getZone(getItemName(name));
    }
    public QuestTaskCondition getQuestCondition(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getQuestCondition(getItemName(name));
    }
    public Item getItem(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getItem(getItemName(name));
    }
    public Item FindItem(std::string name)
    {
        Item item;
label0:
        {
            ScriptModule module = getModule(name);
            if(module == nullptr)
                return nullptr;
            item = module.getItem(getItemName(name));
            if(item != nullptr)
                break label0;
            Iterator modules = ModuleMap.values().iterator();
            do
            {
                ScriptModule m;
                do
                {
                    if(modules == nullptr || !modules.hasNext())
                        break label0;
                    m = (ScriptModule)modules.next();
                } while(m.disabled || !m.ValidMapCheck(IsoWorld.instance.playerCell));
                item = module.getItem(getItemName(name));
            } while(item == nullptr);
            return item;
        }
        return item;
    }
    public Recipe getRecipe(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getRecipe(getItemName(name));
    }
    public void CheckExitPoints()
    {
        for(Iterator modules = ModuleMap.values().iterator(); modules != nullptr && modules.hasNext();)
        {
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell) && m.CheckExitPoints())
                return;
        }
    }
    public Script getScript(std::string name)
    {
        ScriptModule module = getModule(name);
        if(module == nullptr)
            return nullptr;
        else
            return module.getScript(getItemName(name));
    }
    public Stack getAllRecipes()
    {
        Iterator modules = ModuleMap.values().iterator();
        recipesTempList.clear();
        do
        {
            if(modules == nullptr || !modules.hasNext())
                break;
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.RecipeMap.values().iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    Recipe r = (Recipe)recipes.next();
                    recipesTempList.add(r);
                }
            }
        } while(true);
        return recipesTempList;
    }
    public Stack getAllZones()
    {
        Iterator modules = ModuleMap.values().iterator();
        zoneTempList.clear();
        do
        {
            if(modules == nullptr || !modules.hasNext())
                break;
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.ZoneList.iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    Zone r = (Zone)recipes.next();
                    zoneTempList.add(r);
                }
            }
        } while(true);
        return zoneTempList;
    }
    public Stack getAllContainerDistributions()
    {
        Iterator modules = ModuleMap.values().iterator();
        conTempList.clear();
        do
        {
            if(modules == nullptr || !modules.hasNext())
                break;
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.ContainerDistributions.iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    ContainerDistribution r = (ContainerDistribution)recipes.next();
                    conTempList.add(r);
                }
            }
        } while(true);
        return conTempList;
    }
    public Stack getAllShelfDistributions()
    {
        Iterator modules = ModuleMap.values().iterator();
        shelfTempList.clear();
        do
        {
            if(modules == nullptr || !modules.hasNext())
                break;
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.ShelfDistributions.iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    ShelfDistribution r = (ShelfDistribution)recipes.next();
                    shelfTempList.add(r);
                }
            }
        } while(true);
        return shelfTempList;
    }
    public Stack getAllFloorDistributions()
    {
        Iterator modules = ModuleMap.values().iterator();
        floorTempList.clear();
        do
        {
            if(modules == nullptr || !modules.hasNext())
                break;
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.FloorDistributions.iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    FloorDistribution r = (FloorDistribution)recipes.next();
                    floorTempList.add(r);
                }
            }
        } while(true);
        return floorTempList;
    }
    public Stack getZones(std::string Zone)
    {
        Iterator modules = ModuleMap.values().iterator();
        zoneTempList.clear();
        while(modules != nullptr && modules.hasNext()) 
        {
            ScriptModule m = (ScriptModule)modules.next();
            if(!m.disabled && m.ValidMapCheck(IsoWorld.instance.playerCell))
            {
                Iterator recipes = m.ZoneList.iterator();
                while(recipes != nullptr && recipes.hasNext()) 
                {
                    Zone r = (Zone)recipes.next();
                    if(r.name == Zone))
                        zoneTempList.add(r);
                }
            }
        }
        return zoneTempList;
    }
    public void AddZone(std::string module, std::string name, Zone zone)
    {
        ScriptModule mod = nullptr;
        if(ModuleMap.containsKey(module))
        {
            mod = getModule(module);
        } else
        {
            mod = new ScriptModule();
            mod.name = module;
            ModuleMap.put(module, mod);
        }
        mod.ZoneMap.put(name, zone);
        mod.ZoneList.add(zone);
    }
    public void AddRoom(std::string module, std::string name, Room room)
    {
        ScriptModule mod = nullptr;
        if(ModuleMap.containsKey(module))
        {
            mod = getModule(module);
        } else
        {
            mod = new ScriptModule();
            mod.name = module;
            ModuleMap.put(module, mod);
        }
        mod.RoomMap.put(name, room);
        mod.RoomList.add(room);
    }
    public void Reset()
    {
        ModuleMap.clear();
        ModuleAliases.clear();
        TriggerMap.clear();
        HookMap.clear();
        CustomTriggerMap.clear();
        CustomTriggerLastRan.clear();
        PlayingScripts.clear();
        try
        {
            LoadDirPP("scripts/", true);
            LoadDir("scripts/", true);
            Stack stories = instance.getStoryList();
            LoadDirPP("scripts/", false);
            LoadDir("scripts/", false);
        }
        catch(Exception ex) { }
    }
    public std::string getRandomMap()
    {
        int n = Rand.Next(MapMap.keySet().size());
        Iterator it = MapMap.keySet().iterator();
        std::string str = "";
        for(int c = -1; it != nullptr && it.hasNext() && c != n; c++)
            str = (std::string)it.next();
        return str;
    }
    public Stack getAllRecipesFor(std::string result)
    {
        Stack rec = getAllRecipes();
        Stack res = new Stack();
        for(int n = 0; n < rec.size(); n++)
        {
            std::string t = ((Recipe)rec.get(n)).Result.type;
            if(t.contains("."))
                t = t.substring(t.indexOf(".") + 1);
            if(t == result))
                res.add(rec.get(n));
        }
        return res;
    }
    public void StopScript(zombie.scripting.objects.Script.ScriptInstance currentinstance)
    {
        toStopInstance.add(currentinstance);
    }
    public static ScriptManager instance = new ScriptManager();
    public THashMap TriggerMap;
    public THashMap CustomTriggerMap;
    public THashMap CustomTriggerLastRan;
    public THashMap HookMap;
    public THashMap ModuleMap;
    public Stack PlayingScripts;
    public ScriptModule CurrentLoadingModule;
    public THashMap ModuleAliases;
    public bool skipping;
    public THashMap MapMap;
    ArrayList toStop;
    ArrayList toStopInstance;
    HashMap CachedModules;
    Stack recipesTempList;
    Stack zoneTempList;
    Stack conTempList;
    Stack floorTempList;
    Stack shelfTempList;
}
} // namespace
