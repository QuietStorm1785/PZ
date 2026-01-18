#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoObject.java
namespace zombie {
namespace iso {
#include "THashMap.h"
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include "MessageDigest.h"
#include <algorithm>
#include "J2SEPlatform.h"
#include "KahluaTable.h"
#include "GameTime.h"
#include "GameWindow.h"
#include "LuaManager.h"
#include "SoundManager.h"
#include "WorldSoundManager.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "Core.h"
#include "Rand.h"
#include "Bucket.h"
#include "BucketManager.h"
#include "PropertyContainer.h"
#include "ColorInfo.h"
#include "Texture.h"
#include "Mouse.h"
#include "inventory.h"
#include "HandWeapon.h"
#include "IsoFlagType.h"
#include "IsoObjectType.h"
#include "IsoBarricade.h"
#include "IsoCrate.h"
#include "IsoCurtain.h"
#include "IsoDeadBody.h"
#include "IsoDoor.h"
#include "IsoJukebox.h"
#include "IsoLightSwitch.h"
#include "IsoMolotovCocktail.h"
#include "IsoRadio.h"
#include "IsoStove.h"
#include "IsoTree.h"
#include "IsoWheelieBin.h"
#include "IsoWindow.h"
#include "IsoWorldInventoryObject.h"
#include "IsoZombieGiblets.h"
#include "IsoAnim.h"
#include "IsoDirectionFrame.h"
#include "IsoSprite.h"
#include "IsoSpriteInstance.h"
#include "IsoSpriteManager.h"
#include "ui.h"
// Referenced classes of package zombie.iso:
//            IsoPushableObject, Vector2, IsoPhysicsObject, IsoMovingObject, 
//            IsoGridSquare, IsoDirections, SliceY, IsoWorld, 
//            IsoCell, IsoUtils, IsoCamera
class IsoObject {
public:
    implements Serializable
{
	/*      */   public static enum VisionResult
	/*      */   {
	/*  984 */     NoEffect, 
	/*  985 */     Blocked, 
	/*  986 */     Unblocked;
	/*      */   }
    public static bool DoChecksumCheck(std::string str, std::string expected)
    {
        std::string checksum = "";
        try
        {
            checksum = getMD5Checksum(str);
            if(!checksum == expected))
                return false;
        }
        catch(Exception ex)
        {
            checksum = "";
            try
            {
                checksum = getMD5Checksum((new StringBuilder()).append("D:/Dropbox/Zomboid/zombie/build/classes/").append(str).toString());
            }
            catch(Exception ex1)
            {
                return false;
            }
        }
        return checksum == expected);
    }
    public static bool DoChecksumCheck()
    {
        if(!DoChecksumCheck("zombie/GameWindow.class", "c4a62b8857f0fb6b9c103ff6ef127a9b"))
            return false;
        if(!DoChecksumCheck("zombie/GameWindow$1.class", "5d93dc446b2dc49092fe4ecb5edf5f17"))
            return false;
        if(!DoChecksumCheck("zombie/GameWindow$2.class", "a3e3d2c8cf6f0efaa1bf7f6ceb572073"))
            return false;
        if(!DoChecksumCheck("zombie/gameStates/MainScreenState.class", "206848ba7cb764293dd2c19780263854"))
            return false;
        if(!DoChecksumCheck("zombie/core/textures/LoginForm.class", "02b8abc1ed8fd75db69dc6e7e390db41"))
            return false;
        if(!DoChecksumCheck("zombie/FrameLoader$1.class", "0ebfcc9557cc28d53aa982a71616bf5b"))
            return false;
        if(!DoChecksumCheck("zombie/FrameLoader.class", "d5b1f7b2886a499d848c204f6a815776"))
            return false;
        return DoChecksumCheck("zombie/core/textures/AuthenticatingFrame.class", "54f57018c6405a0006ca6ea28d55aa17");
    }
    public static byte[] createChecksum(std::string filename)
        throws Exception
    {
        InputStream fis = new FileInputStream(filename);
        byte buffer[] = new byte[1024];
        MessageDigest complete = MessageDigest.getInstance("MD5");
        int numRead;
        do
        {
            numRead = fis.read(buffer);
            if(numRead > 0)
                complete.update(buffer, 0, numRead);
        } while(numRead != -1);
        fis.close();
        return complete.digest();
    }
    public static std::string getMD5Checksum(std::string filename)
        throws Exception
    {
        byte b[] = createChecksum(filename);
        std::string result = "";
        for(int i = 0; i < b.length; i++)
            result = (new StringBuilder()).append(result).append(Integer.toString((b[i] & 0xff) + 256, 16).substring(1)).toString();
        return result;
    }
    public static IsoObject getLastRendered()
    {
        return lastRendered;
    }
    public static void setLastRendered(IsoObject aLastRendered)
    {
        lastRendered = aLastRendered;
    }
    public static IsoObject getLastRenderedRendered()
    {
        return lastRenderedRendered;
    }
    public static void setLastRenderedRendered(IsoObject aLastRenderedRendered)
    {
        lastRenderedRendered = aLastRenderedRendered;
    }
    public static void setDefaultCondition(int i)
    {
        DefaultCondition = i;
    }
    public bool Serialize()
    {
        return true;
    }
    public IsoObject(IsoCell cell)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
    }
    public KahluaTable getModData()
    {
        if(table == nullptr)
            table = LuaManager.platform.newTable();
        return table;
    }
    public static IsoObject factoryFromFileInput(IsoCell cell, int classID)
    {
        if(classID == "IsoObject".hashCode())
            return new IsoObject(cell);
        if(classID == "Player".hashCode())
            return new IsoPlayer(cell);
        if(classID == "Survivor".hashCode())
            return new IsoSurvivor(cell);
        if(classID == "Zombie".hashCode())
            return new IsoZombie(cell);
        if(classID == "Pushable".hashCode())
            return new IsoPushableObject(cell);
        if(classID == "WheelieBin".hashCode())
            return new IsoWheelieBin(cell);
        if(classID == "WorldInventoryItem".hashCode())
            return new IsoWorldInventoryObject(cell);
        if(classID == "Jukebox".hashCode())
            return new IsoJukebox(cell);
        if(classID == "Curtain".hashCode())
            return new IsoCurtain(cell);
        if(classID == "Radio".hashCode())
            return new IsoRadio(cell);
        if(classID == "DeadBody".hashCode())
            return new IsoDeadBody(cell);
        if(classID == "Stove".hashCode())
            return new IsoStove(cell);
        if(classID == "Door".hashCode())
            return new IsoDoor(cell);
        if(classID == "Window".hashCode())
            return new IsoWindow(cell);
        if(classID == "Curtain".hashCode())
            return new IsoCurtain(cell);
        if(classID == "Barricade".hashCode())
            return new IsoBarricade(cell);
        if(classID == "Crate".hashCode())
            return new IsoCrate(cell);
        if(classID == "Tree".hashCode())
            return new IsoTree(cell);
        if(classID == "LightSwitch".hashCode())
            return new IsoLightSwitch(cell);
        if(classID == "ZombieGiblets".hashCode())
            return new IsoZombieGiblets(cell);
        if(classID == "MolotovCocktail".hashCode())
        {
            return new IsoMolotovCocktail(cell);
        } else
        {
            IsoObject o = new IsoObject(cell);
            return o;
        }
    }
    public static Class factoryClassFromFileInput(IsoCell cell, int classID)
    /*      */   {
    /*  320 */     if (classID == "IsoObject".hashCode())
    /*      */     {
    /*  322 */       return IsoObject.class;
    /*      */     }
    /*  324 */     if (classID == "Player".hashCode())
    /*      */     {
    /*  326 */       return IsoPlayer.class;
    /*      */     }
    /*  328 */     if (classID == "Survivor".hashCode())
    /*      */     {
    /*  330 */       return IsoSurvivor.class;
    /*      */     }
    /*  332 */     if (classID == "Zombie".hashCode())
    /*      */     {
    /*  334 */       return IsoZombie.class;
    /*      */     }
    /*  336 */     if (classID == "Pushable".hashCode())
    /*      */     {
    /*  338 */       return IsoPushableObject.class;
    /*      */     }
    /*  340 */     if (classID == "WheelieBin".hashCode())
    /*      */     {
    /*  342 */       return IsoWheelieBin.class;
    /*      */     }
    /*      */ 
    /*  345 */     if (classID == "WorldInventoryItem".hashCode())
    /*      */     {
    /*  347 */       return IsoWorldInventoryObject.class;
    /*      */     }
    /*  349 */     if (classID == "Jukebox".hashCode())
    /*      */     {
    /*  351 */       return IsoJukebox.class;
    /*      */     }
    /*  353 */     if (classID == "Curtain".hashCode())
    /*      */     {
    /*  355 */       return IsoCurtain.class;
    /*      */     }
    /*  357 */     if (classID == "Radio".hashCode())
    /*      */     {
    /*  359 */       return IsoRadio.class;
    /*      */     }
    /*  361 */     if (classID == "DeadBody".hashCode())
    /*      */     {
    /*  363 */       return IsoDeadBody.class;
    /*      */     }
    /*  365 */     if (classID == "Stove".hashCode())
    /*      */     {
    /*  367 */       return IsoStove.class;
    /*      */     }
    /*  369 */     if (classID == "Door".hashCode())
    /*      */     {
    /*  371 */       return IsoDoor.class;
    /*      */     }
    /*  373 */     if (classID == "Window".hashCode())
    /*      */     {
    /*  375 */       return IsoWindow.class;
    /*      */     }
    /*  377 */     if (classID == "Curtain".hashCode())
    /*      */     {
    /*  379 */       return IsoCurtain.class;
    /*      */     }
    /*  381 */     if (classID == "Barricade".hashCode())
    /*      */     {
    /*  383 */       return IsoBarricade.class;
    /*      */     }
    /*  385 */     if (classID == "Crate".hashCode())
    /*      */     {
    /*  387 */       return IsoCrate.class;
    /*      */     }
    /*  389 */     if (classID == "Tree".hashCode())
    /*      */     {
    /*  391 */       return IsoTree.class;
    /*      */     }
    /*  393 */     if (classID == "LightSwitch".hashCode())
    /*      */     {
    /*  395 */       return IsoLightSwitch.class;
    /*      */     }
    /*  397 */     if (classID == "ZombieGiblets".hashCode())
    /*      */     {
    /*  399 */       return IsoZombieGiblets.class;
    /*      */     }
    /*  401 */     if (classID == "MolotovCocktail".hashCode())
    /*      */     {
    /*  403 */       return IsoMolotovCocktail.class;
    /*      */     }
    /*      */ 
    /*  407 */     return IsoObject.class;
    /*      */   }
    static IsoObject factoryFromFileInput(IsoCell cell, DataInputStream input)
        throws IOException
    {
        bool serialise = input.readBoolean();
        if(!serialise)
        {
            return nullptr;
        } else
        {
            int classID = input.readInt();
            IsoObject o = factoryFromFileInput(cell, classID);
            return o;
        }
    }
    public static IsoObject factoryFromFileInput(IsoCell cell, ByteBuffer b)
        throws IOException
    {
        bool serialise = b.get() != 0;
        if(!serialise)
        {
            return nullptr;
        } else
        {
            int classID = b.getInt();
            IsoObject o = factoryFromFileInput(cell, classID);
            return o;
        }
    }
    public IsoGridSquare getSquare()
    {
        return square;
    }
    public void update()
    {
    }
    public void renderlast()
    {
    }
    public void DirtySlice()
    {
        square.getSlice().bSaveDirty = true;
    }
    public std::string getObjectName()
    {
        if(name != nullptr)
            return name;
        if(sprite != nullptr && sprite.getParentObjectName() != nullptr)
            return sprite.getParentObjectName();
        else
            return "IsoObject";
    }
    public void load(ByteBuffer input)
        throws IOException
    {
        int id = input.getInt();
        sprite = IsoSprite.getSprite(IsoWorld.instance.spriteManager, id);
        int child = input.getInt();
        for(int n = 0; n < child; n++)
        {
            if(AttachedAnimSprite == nullptr)
                AttachedAnimSprite = new NulledArrayList();
            if(child == 10000)
                AttachedAnimSprite = nullptr;
            int wtf = input.getInt();
            IsoSprite spr = IsoSprite.getSprite(IsoWorld.instance.spriteManager, wtf);
            if(spr != nullptr)
            {
                IsoSpriteInstance a = spr.newInstance();
                a.offX = input.getFloat();
                a.offY = input.getFloat();
                a.offZ = input.getFloat();
                a.tintr = input.getFloat();
                a.tintg = input.getFloat();
                a.tintb = input.getFloat();
                a.alpha = input.getFloat();
                a.targetAlpha = input.getFloat();
                a.Flip = input.get() != 0;
                a.bCopyTargetAlpha = input.get() != 0;
                AttachedAnimSprite.add(a);
            } else
            {
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.getFloat();
                input.get();
                input.get();
            }
        }
        bool ri = input.get() != 0;
        if(ri)
            name = GameWindow.ReadString(input);
        bool bContainer = input.get() != 0;
        if(bContainer)
        {
            int con = input.getInt();
            container = new ItemContainer();
            container.ID = con;
            container.parent = this;
            container.SourceGrid = square;
            if(container.ID >= ItemContainer.IDMax)
                ItemContainer.IDMax = container.ID + 1;
            IsoWorld.instance.CurrentCell.ContainerMap.put(Integer.valueOf(con), container);
        }
        if(input.get() != 0)
        {
            if(table == nullptr)
                table = LuaManager.platform.newTable();
            table.load(input);
        }
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        if(sprite == nullptr)
        {
            output.put((byte)0);
            return;
        }
        output.put(((byte)(Serialize() ? 1 : 0)));
        if(!Serialize())
            return;
        output.putInt(getObjectName().hashCode());
        output.putInt(sprite.ID);
        if(DefaultCondition == 10)
            output.putInt(DefaultCondition * 1000);
        if(AttachedAnimSprite == nullptr)
        {
            output.putInt(0);
        } else
        {
            output.putInt(AttachedAnimSprite.size());
            for(int n = 0; n < AttachedAnimSprite.size(); n++)
            {
                IsoSpriteInstance a = (IsoSpriteInstance)AttachedAnimSprite.get(n);
                output.putInt(a.getID());
                output.putFloat(a.offX);
                output.putFloat(a.offY);
                output.putFloat(a.offZ);
                output.putFloat(a.tintr);
                output.putFloat(a.tintg);
                output.putFloat(a.tintb);
                output.putFloat(a.alpha);
                output.putFloat(a.targetAlpha);
                output.put(((byte)(a.Flip ? 1 : 0)));
                output.put(((byte)(a.bCopyTargetAlpha ? 1 : 0)));
            }
        }
        if(name != nullptr)
        {
            output.put((byte)1);
            GameWindow.WriteString(output, name);
        } else
        {
            output.put((byte)0);
        }
        if(container != nullptr)
        {
            output.put((byte)1);
            output.putInt(container.ID);
        } else
        {
            output.put((byte)0);
        }
        if(table != nullptr)
        {
            output.put((byte)1);
            table.save(output);
        } else
        {
            output.put((byte)0);
        }
    }
    public void AttackObject(IsoGameCharacter owner)
    {
        Damage -= 10;
        HandWeapon weapon = (HandWeapon)owner.getPrimaryHandItem();
        SoundManager.instance.PlayWorldSound(weapon.getDoorHitSound(), square, 0.2F, 20F, 2.0F, true);
        WorldSoundManager.instance.addSound(owner, square.getX(), square.getY(), square.getZ(), 20, 20, false, 0.0F, 15F);
        if(Damage <= 0)
        {
            square.getObjects().remove(this);
            square.RecalcAllWithNeighbours(true);
            if(getType() == IsoObjectType.stairsBN || getType() == IsoObjectType.stairsMN || getType() == IsoObjectType.stairsTN || getType() == IsoObjectType.stairsBW || getType() == IsoObjectType.stairsMW || getType() == IsoObjectType.stairsTW)
                square.RemoveAllWith(IsoFlagType.attachtostairs);
            int NumPlanks = 1;
            for(int i = 0; i < NumPlanks; i++)
            {
                InventoryItem item = square.AddWorldInventoryItem("Base.Plank", Rand.Next(-1F, 1.0F), Rand.Next(-1F, 1.0F), 0.0F);
                item.setUses(1);
            }
        }
    }
    public void onMouseRightClick(int i, int j)
    {
    }
    public void onMouseRightReleased()
    {
    }
    public IsoObject getRerouteCollide()
    {
        return rerouteCollide;
    }
    public void setRerouteCollide(IsoObject rerouteCollide)
    {
        this.rerouteCollide = rerouteCollide;
    }
    public KahluaTable getTable()
    {
        return table;
    }
    public void setTable(KahluaTable table)
    {
        this.table = table;
    }
    public float getAlpha()
    {
        return alpha;
    }
    public void setAlpha(float alpha)
    {
        this.alpha = alpha;
    }
    public float getAlphaStep()
    {
        return alphaStep;
    }
    public void setAlphaStep(float alphaStep)
    {
        IsoObject _tmp = this;
        alphaStep = alphaStep;
    }
    public NulledArrayList getAttachedAnimSprite()
    {
        return AttachedAnimSprite;
    }
    public void setAttachedAnimSprite(NulledArrayList AttachedAnimSprite)
    {
        this.AttachedAnimSprite = AttachedAnimSprite;
    }
    public IsoCell getCell()
    {
        return IsoWorld.instance.CurrentCell;
    }
    public NulledArrayList getChildSprites()
    {
        return AttachedAnimSprite;
    }
    public void setChildSprites(NulledArrayList AttachedAnimSprite)
    {
        this.AttachedAnimSprite = AttachedAnimSprite;
    }
    public ItemContainer getContainer()
    {
        return container;
    }
    public void setContainer(ItemContainer container)
    {
        this.container = container;
    }
    public IsoDirections getDir()
    {
        return dir;
    }
    public void setDir(IsoDirections dir)
    {
        this.dir = dir;
    }
    public void setDir(int dir)
    {
        this.dir = IsoDirections.fromIndex(dir);
    }
    public short getDamage()
    {
        return Damage;
    }
    public void setDamage(short Damage)
    {
        this.Damage = Damage;
    }
    public bool isNoPicking()
    {
        return NoPicking;
    }
    public void setNoPicking(bool NoPicking)
    {
        this.NoPicking = NoPicking;
    }
    public void setOffsetX(float offsetX)
    {
        this.offsetX = offsetX;
    }
    public void setOffsetY(float offsetY)
    {
        this.offsetY = offsetY;
    }
    public bool isOutlineOnMouseover()
    {
        return OutlineOnMouseover;
    }
    public void setOutlineOnMouseover(bool OutlineOnMouseover)
    {
        this.OutlineOnMouseover = OutlineOnMouseover;
    }
    public IsoObject getRerouteMask()
    {
        return rerouteMask;
    }
    public void setRerouteMask(IsoObject rerouteMask)
    {
        this.rerouteMask = rerouteMask;
    }
    public IsoSprite getSprite()
    {
        return sprite;
    }
    public void setSprite(IsoSprite sprite)
    {
        this.sprite = sprite;
    }
    public void setSquare(IsoGridSquare square)
    {
        this.square = square;
    }
    public float getTargetAlpha()
    {
        return targetAlpha;
    }
    public void setTargetAlpha(float targetAlpha)
    {
        this.targetAlpha = targetAlpha;
    }
    public std::string getName()
    {
        return name;
    }
    public void setName(std::string name)
    {
        this.name = name;
    }
    public IsoObjectType getType()
    {
        if(sprite == nullptr)
            return IsoObjectType.MAX;
        else
            return sprite.getType();
    }
    public void setType(IsoObjectType type)
    {
        if(sprite != nullptr)
            sprite.setType(type);
    }
    public void addChild(IsoObject child)
    {
        Children.add(child);
    }
    public IsoObject()
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
    }
    public IsoObject(IsoCell cell, IsoGridSquare square, IsoSprite spr)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        sprite = spr;
        this.square = square;
    }
    public IsoObject(IsoCell cell, IsoGridSquare square, std::string gid)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        sprite = IsoWorld.instance.spriteManager.getSprite(gid);
        this.square = square;
        tile = gid;
    }
    public IsoObject(IsoGridSquare square, std::string tile, std::string name)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        this.name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        sprite = IsoSprite.CreateSprite(BucketManager.Shared().SpriteManager);
        sprite.LoadFramesNoDirPageSimple(tile);
        this.square = square;
        this.tile = tile;
        this.name = name;
    }
    public IsoObject(IsoGridSquare square, std::string tile, std::string name, bool bShareTilesWithMap)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        this.name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        if(bShareTilesWithMap)
        {
            sprite = IsoSprite.CreateSprite(BucketManager.Shared().SpriteManager);
            sprite.LoadFramesNoDirPageSimple(tile);
        } else
        {
            sprite = (IsoSprite)square.getCell().SpriteManager.NamedMap.get(tile);
        }
        this.tile = tile;
        this.square = square;
        this.name = name;
    }
    public IsoObject(IsoGridSquare square, std::string tile, bool bShareTilesWithMap)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        if(bShareTilesWithMap)
        {
            sprite = IsoSprite.CreateSprite(BucketManager.Shared().SpriteManager);
            sprite.LoadFramesNoDirPageSimple(tile);
        } else
        {
            sprite = (IsoSprite)square.getCell().SpriteManager.NamedMap.get(tile);
        }
        this.tile = tile;
        this.square = square;
    }
    public IsoObject(IsoGridSquare square, std::string tile)
    {
        rerouteCollide = nullptr;
        table = nullptr;
        Children = new NulledArrayList(1);
        alpha = 1.0F;
        AttachedAnimSprite = new NulledArrayList();
        container = nullptr;
        dir = IsoDirections.N;
        Damage = 100;
        NoPicking = false;
        offsetX = 0.0F;
        offsetY = -144F;
        OutlineOnMouseover = false;
        rerouteMask = nullptr;
        sprite = nullptr;
        targetAlpha = 1.0F;
        name = nullptr;
        tintr = 1.0F;
        tintg = 1.0F;
        tintb = 1.0F;
        sprite = IsoSprite.CreateSprite(BucketManager.Shared().SpriteManager);
        sprite.LoadFramesNoDirPageSimple(tile);
        this.square = square;
    }
    public void SetName(std::string name)
    {
        this.name = name;
    }
    public void AttachAnim(std::string s, std::string s1, int i, int j, int k, int l, bool flag, 
            int i1, bool flag1, float f, ColorInfo colorinfo)
    {
    }
    public void AttachExistingAnim(IsoSprite spr, int OffsetX, int OffsetY, bool Looping, int FinishHoldFrameIndex, bool DeleteWhenFinished, float zBias, 
            ColorInfo TintMod)
    {
        IsoSprite NewAnimSprite = spr;
        NewAnimSprite.TintMod.r = TintMod.r;
        NewAnimSprite.TintMod.g = TintMod.g;
        NewAnimSprite.TintMod.b = TintMod.b;
        NewAnimSprite.TintMod.a = TintMod.a;
        Integer NewOffsetX = Integer.valueOf(OffsetX);
        Integer NewOffsetY = Integer.valueOf(OffsetY);
        NewAnimSprite.soffX = (short)(-NewOffsetX.intValue());
        NewAnimSprite.soffY = (short)(-NewOffsetY.intValue());
        NewAnimSprite.Animate = true;
        NewAnimSprite.Loop = Looping;
        NewAnimSprite.DeleteWhenFinished = DeleteWhenFinished;
    }
    public void AttachExistingAnim(IsoSprite spr, int OffsetX, int OffsetY, bool Looping, int FinishHoldFrameIndex, bool DeleteWhenFinished, float zBias)
    {
        AttachExistingAnim(spr, OffsetX, OffsetY, Looping, FinishHoldFrameIndex, DeleteWhenFinished, zBias, new ColorInfo());
    }
    public void DoTooltip(ObjectTooltip objecttooltip)
    {
    }
    public ItemContainer getItemContainer()
    {
        return container;
    }
    public float getOffsetX()
    {
        return offsetX;
    }
    public float getOffsetY()
    {
        return offsetY;
    }
    public IsoObject getRerouteMaskObject()
    {
        return rerouteMask;
    }
    public bool HasTooltip()
    {
        return false;
    }
    public bool useWater(int i)
    {
        if(sprite.getProperties().Is(IsoFlagType.waterPiped) && GameTime.getInstance().getNightsSurvived() < 14)
            return true;
        if(!sprite.Properties.Is("waterAmount"))
            return false;
        Integer units = Integer.valueOf(Integer.parseInt(sprite.getProperties().Val("waterAmount")));
        if(units.intValue() > 0)
        {
            units = Integer.valueOf(units.intValue() - i);
            if(units.intValue() >= 0)
                sprite.getProperties().Set("waterAmount", units.toString());
            else
                sprite.getProperties().UnSet("waterAmount");
            return true;
        } else
        {
            return false;
        }
    }
    public bool hasWater()
    {
        if(sprite.getProperties().Is(IsoFlagType.waterPiped) && GameTime.getInstance().getNightsSurvived() < 14)
            return true;
        if(!sprite.Properties.Is("waterAmount"))
        {
            return false;
        } else
        {
            int units = Integer.parseInt(sprite.getProperties().Val("waterAmount"));
            return units > 0;
        }
    }
    public void useItemOn(InventoryItem item)
    {
        std::string replaceWith = nullptr;
        if(item != nullptr && item != nullptr)
        {
            replaceWith = item.getReplaceOnUseOn();
            if(replaceWith.split("-")[0].trim().contains(getObjectName()))
            {
                replaceWith = replaceWith.split("-")[1];
                std::string s = replaceWith;
                if(!replaceWith.contains("."))
                    replaceWith = (new StringBuilder()).append(item.getModule()).append(".").append(s).toString();
            } else
            if(replaceWith.split("-")[0].trim().contains("WaterSource"))
            {
                replaceWith = replaceWith.split("-")[1];
                std::string s = replaceWith;
                if(!replaceWith.contains("."))
                    replaceWith = (new StringBuilder()).append(item.getModule()).append(".").append(s).toString();
                useWater(10);
            } else
            {
                replaceWith = nullptr;
            }
        }
        if(replaceWith != nullptr && item != nullptr)
        {
            InventoryItem item2 = item.getContainer().AddItem(InventoryItemFactory.CreateItem(replaceWith));
            item.setUses(item.getUses() - 1);
            if(item.getUses() <= 0 && item.getContainer() != nullptr)
                item.getContainer().Items.remove(item);
        }
    }
    public bool onMouseLeftClick(int x, int y)
    {
        float dist = IsoPlayer.instance.DistTo(square.getX(), square.getY());
        std::string replaceWith = nullptr;
        if(UIManager.getDragInventory() != nullptr && square.getZ() == (int)IsoPlayer.getInstance().getZ() && UIManager.getDragInventory().getReplaceOnUseOn() != nullptr)
        {
            replaceWith = UIManager.getDragInventory().getReplaceOnUseOn();
            if(replaceWith.split("-")[0].trim().contains(getObjectName()))
            {
                replaceWith = replaceWith.split("-")[1];
                std::string s = replaceWith;
                if(!replaceWith.contains("."))
                    replaceWith = (new StringBuilder()).append(UIManager.getDragInventory().getModule()).append(".").append(s).toString();
            } else
            if(replaceWith.split("-")[0].trim().contains("WaterSource") && hasWater())
            {
                replaceWith = replaceWith.split("-")[1];
                std::string s = replaceWith;
                if(!replaceWith.contains("."))
                    replaceWith = (new StringBuilder()).append(UIManager.getDragInventory().getModule()).append(".").append(s).toString();
                useWater(10);
            } else
            {
                replaceWith = nullptr;
            }
        }
        bool bLast = false;
        if(UIManager.getDragInventory() != nullptr && square.getZ() == (int)IsoPlayer.getInstance().getZ() && UIManager.getDragInventory().getType().contains("SheetRope") && sprite != nullptr && getType() == IsoObjectType.windowN)
        {
            IsoGridSquare sq = square;
            int n = 0;
            if(sq.getProperties().Is(IsoFlagType.solidfloor))
                return false;
            do
            {
                if(sq == nullptr || UIManager.getDragInventory() == nullptr)
                    break;
                std::string d = "TileRope_1";
                if(n > 0)
                    d = "TileRope_9";
                IsoObject sheetTop = new IsoObject(getCell(), sq, d);
                sheetTop.sprite.getProperties().Set(IsoFlagType.climbSheetN);
                if(n == 0)
                {
                    sheetTop.sprite.getProperties().Set(IsoFlagType.climbSheetTopN);
                    sq.getProperties().Set(IsoFlagType.climbSheetTopN);
                }
                if(!sq.getProperties().Is(IsoFlagType.climbSheetN))
                {
                    sq.DirtySlice();
                    UIManager.getDragInventory().Use();
                }
                sq.getProperties().Set(IsoFlagType.climbSheetN);
                sq.getObjects().add(sheetTop);
                n++;
                if(bLast)
                    break;
                sq = getCell().getGridSquare(sq.getX(), sq.getY(), sq.getZ() - 1);
                if(sq != nullptr && sq.getProperties().Is(IsoFlagType.solidfloor))
                    bLast = true;
            } while(true);
        } else
        if(UIManager.getDragInventory() != nullptr && square.getZ() == (int)IsoPlayer.getInstance().getZ() && UIManager.getDragInventory().getType().contains("SheetRope") && sprite != nullptr && getType() == IsoObjectType.windowW)
        {
            IsoGridSquare sq = square;
            int n = 0;
            if(sq.getProperties().Is(IsoFlagType.solidfloor))
                return false;
            do
            {
                if(sq == nullptr || UIManager.getDragInventory() == nullptr)
                    break;
                std::string d = "TileRope_0";
                if(n > 0)
                    d = "TileRope_8";
                IsoObject sheetTop = new IsoObject(getCell(), sq, d);
                sheetTop.sprite.getProperties().Set(IsoFlagType.climbSheetW);
                if(n == 0)
                {
                    sheetTop.sprite.getProperties().Set(IsoFlagType.climbSheetTopW);
                    sq.getProperties().Set(IsoFlagType.climbSheetTopW);
                }
                if(!sq.getProperties().Is(IsoFlagType.climbSheetW))
                {
                    UIManager.getDragInventory().Use();
                    sq.DirtySlice();
                }
                sq.getProperties().Set(IsoFlagType.climbSheetW);
                sq.getObjects().add(sheetTop);
                n++;
                if(bLast)
                    break;
                sq = getCell().getGridSquare(sq.getX(), sq.getY(), sq.getZ() - 1);
                if(sq != nullptr && sq.getProperties().Is(IsoFlagType.solidfloor))
                    bLast = true;
            } while(true);
        } else
        {
            if(rerouteMask != this && rerouteMask != nullptr)
                return rerouteMask.onMouseLeftClick(x, y);
            if(UIManager.getDragInventory() != nullptr && UIManager.getDragInventory().getType().contains("Sledgehammer") && (sprite.getProperties().Is(IsoFlagType.sledgesmash) || getType() == IsoObjectType.stairsTW || getType() == IsoObjectType.stairsMW || getType() == IsoObjectType.stairsBW || getType() == IsoObjectType.stairsTN || getType() == IsoObjectType.stairsMN || getType() == IsoObjectType.stairsBN || sprite.getProperties().Is(IsoFlagType.cutW) || sprite.getProperties().Is(IsoFlagType.cutN) || sprite.getProperties().Is(IsoFlagType.windowW) || sprite.getProperties().Is(IsoFlagType.windowN)))
            {
                if(IsoUtils.DistanceTo(square.getX(), square.getY(), IsoPlayer.getInstance().getX(), IsoPlayer.getInstance().getY()) <= 2.0F && (float)square.getZ() == IsoPlayer.getInstance().getZ())
                {
                    Vector2 vec = new Vector2((float)square.getX() + 0.5F, (float)square.getY() + 0.5F);
                    vec.x -= IsoPlayer.getInstance().getX();
                    vec.y -= IsoPlayer.getInstance().getY();
                    vec.normalize();
                    IsoPlayer.getInstance().DirectionFromVector(vec);
                    IsoPlayer.getInstance().AttemptAttack();
                    IsoPlayer.instance.setFakeAttack(true);
                    IsoPlayer.instance.setFakeAttackTarget(this);
                }
            } else
            if(container != nullptr)
            {
                if(IsoUtils.DistanceTo(square.getX(), square.getY(), IsoPlayer.getInstance().getX(), IsoPlayer.getInstance().getY()) < 2.5F && (float)square.getZ() == IsoPlayer.getInstance().getZ())
                {
                    int sx = (int)IsoUtils.XToScreen(square.getX(), square.getY(), square.getZ(), 0);
                    int sy = (int)IsoUtils.YToScreen(square.getX(), square.getY(), square.getZ(), 0);
                    sx -= (int)IsoCamera.getOffX();
                    sy -= (int)IsoCamera.getOffY();
                    sy += 380;
                    sx += 24;
                    if(Core.bDoubleSize)
                    {
                        sx *= 2;
                        sy *= 2;
                    }
                    if(UIManager.getOpenContainer() == nullptr)
                        UIManager.getUI().add(new NewContainerPanel(sx, sy, 2, 3, container));
                    return true;
                }
            } else
            if(replaceWith != nullptr && UIManager.getDragInventory() != nullptr)
            {
                InventoryItem item = UIManager.getDragInventory().getContainer().AddItem(InventoryItemFactory.CreateItem(replaceWith));
                UIManager.getDragInventory().setUses(UIManager.getDragInventory().getUses() - 1);
                if(UIManager.getDragInventory().getUses() <= 0 && UIManager.getDragInventory().getContainer() != nullptr)
                {
                    UIManager.getDragInventory().getContainer().Items.remove(UIManager.getDragInventory());
                    UIManager.getDragInventory().getContainer().dirty = true;
                    UIManager.setDragInventory(nullptr);
                }
                UIManager.setDragInventory(item);
            } else
            if(sprite.getProperties().Is(IsoFlagType.bed) && IsoUtils.DistanceTo(square.getX(), square.getY(), IsoPlayer.getInstance().getX(), IsoPlayer.getInstance().getY()) < 2.0F && (float)square.getZ() == IsoPlayer.getInstance().getZ())
            {
                if(IsoPlayer.getInstance().getStats().fatigue <= 0.3F)
                    UIManager.DoModal("SleepNo", "You're not tired enough to sleep.", false);
                else
                    UIManager.DoModal("Sleep", "Do you want to sleep?", true);
                UIManager.getSpeedControls().SetCurrentGameSpeed(0);
                return true;
            }
        }
        if(sprite.getProperties().Is(IsoFlagType.solidfloor) && square.getZ() == (int)IsoPlayer.getInstance().getZ() && dist <= 3F && UIManager.getDragInventory() != nullptr)
        {
            int mx = Mouse.getX();
            int my = Mouse.getY();
            float xx = IsoUtils.XToIso(mx - 30, (float)my - 356F - 5F, IsoPlayer.instance.getZ());
            float yy = IsoUtils.YToIso(mx - 30, (float)my - 356F - 5F, IsoPlayer.instance.getZ());
            xx -= square.getX();
            yy -= square.getY();
            InventoryItem item = nullptr;
            if(UIManager.getDragInventory().getUses() > 1)
                item = InventoryItemFactory.CreateItem((new StringBuilder()).append(UIManager.getDragInventory().getModule()).append(".").append(UIManager.getDragInventory().getType()).toString());
            else
                item = UIManager.getDragInventory();
            IsoWorldInventoryObject i = new IsoWorldInventoryObject(item, square, xx, yy, 0.05F);
            i.item.setUses(1);
            square.getObjects().add(i);
            if(UIManager.getDragInventory().getUses() > 1)
            {
                UIManager.getDragInventory().Use(true);
            } else
            {
                IsoPlayer.instance.getInventory().Remove(UIManager.getDragInventory());
                UIManager.setDragInventory(nullptr);
            }
        }
        return false;
    }
    public PropertyContainer getProperties()
    {
        if(sprite == nullptr)
            return nullptr;
        else
            return sprite.getProperties();
    }
    public void RemoveAttachedAnims()
    {
        if(AttachedAnimSprite == nullptr)
            return;
        for(int i = 0; i < AttachedAnimSprite.size(); i++)
            ((IsoSpriteInstance)AttachedAnimSprite.get(i)).Dispose();
        AttachedAnimSprite.clear();
    }
    public void render(float x, float y, float z, ColorInfo col, bool bDoAttached)
    {
        stCol.r = col.r;
        stCol.g = col.g;
        stCol.b = col.b;
        stCol.a = col.a;
        if(sprite != nullptr && sprite.getProperties().Is("ForceAmbient"))
        {
            float rmod = 0.0F;
            float gmod = 0.0F;
            float bmod = 0.0F;
            rmod = GameTime.getInstance().Lerp(1.0F, 0.1F, GameTime.getInstance().getNightTint());
            gmod = GameTime.getInstance().Lerp(1.0F, 0.2F, GameTime.getInstance().getNightTint());
            bmod = GameTime.getInstance().Lerp(1.0F, 0.45F, GameTime.getInstance().getNightTint());
            rmod *= tintr;
            gmod *= tintg;
            bmod *= tintb;
            stCol.r = GameTime.getInstance().getAmbient() * rmod;
            stCol.g = GameTime.getInstance().getAmbient() * gmod;
            stCol.b = GameTime.getInstance().getAmbient() * bmod;
        }
        if(this == IsoCamera.CamCharacter && !IsoPlayer.DemoMode)
        {
            targetAlpha = 1.0F;
            alpha = 1.0F;
        }
        lastRenderedRendered = lastRendered;
        lastRendered = this;
        if(sprite != nullptr)
        {
            if(sprite.getProperties().Is(IsoFlagType.invisible))
                return;
            if(!(this instanceof IsoPhysicsObject))
                if(!(this instanceof IsoWindow) && ((float)square.getX() > IsoCamera.CamCharacter.getX() || (float)square.getY() > IsoCamera.CamCharacter.getY()) && IsoCamera.CamCharacter.getZ() <= (float)square.getZ())
                {
                    bool bCut = false;
                    if(sprite.getProperties().Is(IsoFlagType.cutW) && (float)square.getX() > IsoCamera.CamCharacter.getX() || sprite.getProperties().Is(IsoFlagType.cutN) && (float)square.getY() > IsoCamera.CamCharacter.getY())
                    {
                        if((float)square.getX() > IsoCamera.CamCharacter.getX() && (float)square.getY() > IsoCamera.CamCharacter.getY())
                            bCut = true;
                        if(sprite.getProperties().Is(IsoFlagType.cutW) && (float)square.getX() > IsoCamera.CamCharacter.getX())
                            bCut = true;
                        if(sprite.getProperties().Is(IsoFlagType.cutN) && (float)square.getY() > IsoCamera.CamCharacter.getY())
                            bCut = true;
                    }
                    if(sprite.getProperties().Is(IsoFlagType.halfheight))
                        bCut = false;
                    if(bCut)
                    {
                        targetAlpha = 0.4F;
                        if(rerouteMask == nullptr && (UIManager.getDragInventory() == nullptr || !UIManager.DragInventory.getType().contains("Sledgehammer") && !UIManager.DragInventory.getType().contains("Axe")))
                            NoPicking = true;
                        else
                            NoPicking = false;
                    } else
                    {
                        targetAlpha = 1.0F;
                        NoPicking = false;
                    }
                } else
                {
                    targetAlpha = 1.0F;
                    NoPicking = false;
                }
        }
        float mul = 2.0F;
        float div = 1.5F;
        if(IsoPlayer.getInstance().HasTrait("ShortSighted"))
            mul = 1.0F;
        if(IsoPlayer.getInstance().HasTrait("EagleEyed"))
        {
            mul = 3F;
            div = 2.0F;
        }
        if((this instanceof IsoGameCharacter) && !((IsoGameCharacter)this).isSpottedSinceAlphaZero())
            targetAlpha = 0.0F;
        if(this == IsoCamera.CamCharacter)
            targetAlpha = 1.0F;
        if(alpha < targetAlpha)
        {
            alpha += alphaStep * mul;
            if(alpha > targetAlpha)
                alpha = targetAlpha;
        } else
        if(alpha > targetAlpha)
        {
            alpha -= alphaStep / div;
            if(alpha < targetAlpha)
                alpha = targetAlpha;
        }
        if(alpha < 0.0F)
            alpha = 0.0F;
        if(alpha > 1.0F)
            alpha = 1.0F;
        if(sprite != nullptr)
        {
            if(getType() != IsoObjectType.wall);
            sprite.render(this, x, y, z, dir, offsetX, offsetY, stCol);
        }
        if(bDoAttached && AttachedAnimSprite != nullptr)
        {
            IsoSpriteInstance s;
            for(Iterator ita = AttachedAnimSprite.iterator(); ita != nullptr && ita.hasNext(); s.render(this, x, y, z, dir, offsetX, offsetY, col))
            {
                s = (IsoSpriteInstance)ita.next();
                s.update();
            }
        }
        if(bDoAttached)
        {
            Iterator it = Children.iterator();
            do
            {
                if(it == nullptr || !it.hasNext())
                    break;
                IsoObject obj = (IsoObject)it.next();
                if(obj instanceof IsoMovingObject)
                    obj.render(((IsoMovingObject)obj).x, ((IsoMovingObject)obj).y, ((IsoMovingObject)obj).z, col, bDoAttached);
            } while(true);
        }
    }
    public void renderObjectPicker(float x, float y, float z, ColorInfo lightInfo)
    {
        if(sprite == nullptr)
            return;
        if(UIManager.getDragInventory() != nullptr && "Barricade" == UIManager.getDragInventory().getType()) && !sprite.Properties.Is(IsoFlagType.solidfloor))
        {
            return;
        } else
        {
            sprite.renderObjectPicker(this, x, y, z, dir, offsetX, offsetY, lightInfo);
            return;
        }
    }
    public bool TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to)
    {
        return false;
    }
    public bool TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to)
    {
        return false;
    }
    public VisionResult TestVision(IsoGridSquare from, IsoGridSquare to)
    {
        return VisionResult.Unblocked;
    }
    Texture getCurrentFrameTex()
    {
        if(sprite == nullptr)
            return nullptr;
        if(sprite.CurrentAnim == nullptr)
            return nullptr;
        if((float)sprite.CurrentAnim.Frames.size() <= sprite.def.Frame)
            return nullptr;
        else
            return ((IsoDirectionFrame)sprite.CurrentAnim.Frames.get((int)sprite.def.Frame)).getTexture(dir);
    }
    public bool isMaskClicked(int x, int y)
    {
        if(sprite == nullptr)
            return false;
        else
            return sprite.isMaskClicked(dir, x, y);
    }
    public bool isMaskClicked(int x, int y, bool flip)
    {
        if(sprite == nullptr)
            return false;
        else
            return sprite.isMaskClicked(dir, x, y, flip);
    }
    public float getMaskClickedY(int x, int y, bool flip)
    {
        if(sprite == nullptr)
            return 10000F;
        else
            return sprite.getMaskClickedY(dir, x, y, flip);
    }
    private static int DefaultCondition = 0;
    public IsoObject rerouteCollide;
    public KahluaTable table;
    NulledArrayList Children;
    public float alpha;
    public static float alphaStep = 0.03F;
    public NulledArrayList AttachedAnimSprite;
    public ItemContainer container;
    public IsoDirections dir;
    public short Damage;
    public bool NoPicking;
    public float offsetX;
    public float offsetY;
    public bool OutlineOnMouseover;
    public IsoObject rerouteMask;
    public IsoSprite sprite;
    public IsoGridSquare square;
    public float targetAlpha;
    std::string tile;
    public std::string name;
    public static IsoObject lastRendered = nullptr;
    public static IsoObject lastRenderedRendered = nullptr;
    public float tintr;
    public float tintg;
    public float tintb;
    public static ColorInfo stCol = new ColorInfo();
}
} // namespace
