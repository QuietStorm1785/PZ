#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CellLoader.java
namespace zombie {
namespace iso {
#include "THashMap.h"
#include "Rectangle.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "parsers.h"
#include "dom.h"
#include "SAXException.h"
#include "zombie.h"
#include "LuaEventManager.h"
#include "AStarPathMap.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "BucketManager.h"
#include "PropertyContainer.h"
#include "Texture.h"
#include "TexturePackPage.h"
#include "ItemContainer.h"
#include "ItemContainerFiller.h"
#include "IsoFlagType.h"
#include "IsoObjectType.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
#include "IsoRoomExit.h"
#include "IsoCurtain.h"
#include "IsoDoor.h"
#include "IsoJukebox.h"
#include "IsoLightSwitch.h"
#include "IsoRadio.h"
#include "IsoStove.h"
#include "IsoTree.h"
#include "IsoWheelieBin.h"
#include "IsoWindow.h"
#include "IsoAnim.h"
#include "IsoDirectionFrame.h"
#include "IsoSprite.h"
#include "IsoSpriteInstance.h"
#include "IsoSpriteManager.h"
#include "ScriptManager.h"
#include "objects.h"
// Referenced classes of package zombie.iso:
//            IsoLightSource, IsoPushableObject, IsoObject, IsoCell, 
//            IsoLot, IsoGridSquare, IsoMovingObject, BlockInfo, 
//            SliceY, IsoDirections, IsoWorld, LosUtil, 
//            IsoUtils
class CellLoader {
public:
{
    public CellLoader()
    {
    }
    public static void DoTileObjectCreation(IsoSprite spr, IsoObjectType type, IsoCell cell, int x, int y, int height, Stack BedList, bool bDoHeightOffset, 
            std::string name)
        throws NumberFormatException
    {
        IsoObject obj = nullptr;
        int times = 0;
        int n;
        if(x == 86 && y == 19 && height == 0)
            n = 0;
        if(bDoHeightOffset)
            times = 3;
        if(type == IsoObjectType.doorN)
        {
            obj = new IsoDoor(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr, true);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddSpecialTileObject(obj);
        } else
        if(type == IsoObjectType.doorW)
        {
            obj = new IsoDoor(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr, false);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddSpecialTileObject(obj);
        } else
        if(type == IsoObjectType.lightswitch)
        {
            obj = new IsoLightSwitch(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
            if(obj.sprite.getProperties().Is("lightR"))
            {
                float r = Float.parseFloat(obj.sprite.getProperties().Val("lightR"));
                float g = Float.parseFloat(obj.sprite.getProperties().Val("lightG"));
                float b = Float.parseFloat(obj.sprite.getProperties().Val("lightB"));
                IsoLightSource l = new IsoLightSource(obj.square.getX(), obj.square.getY(), obj.square.getZ(), r, g, b, 8);
                l.bActive = false;
                l.switches.add((IsoLightSwitch)obj);
                ((IsoLightSwitch)obj).lights.add(l);
                cell.getLamppostPositions().add(l);
            } else
            {
                ((IsoLightSwitch)obj).lightRoom = true;
            }
        } else
        if(type == IsoObjectType.curtainN || type == IsoObjectType.curtainS || type == IsoObjectType.curtainE || type == IsoObjectType.curtainW)
        {
            obj = new IsoCurtain(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr, type == IsoObjectType.curtainN || type == IsoObjectType.curtainS);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddSpecialTileObject(obj);
        } else
        if(spr.getProperties().Is(IsoFlagType.windowW) || spr.getProperties().Is(IsoFlagType.windowN))
        {
            obj = new IsoWindow(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr, spr.getProperties().Is(IsoFlagType.windowN));
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddSpecialTileObject(obj);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].RereouteWallMaskTo(obj);
        } else
        if(spr.getProperties().Is("container") && spr.getProperties().Val("container") == "stove"))
        {
            obj = new IsoStove(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
        } else
        if(type == IsoObjectType.jukebox)
        {
            obj = new IsoJukebox(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
            obj.OutlineOnMouseover = true;
            cell.getStaticUpdaterObjectList().add(obj);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
        } else
        if(type == IsoObjectType.radio)
        {
            obj = new IsoRadio(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
            cell.getStaticUpdaterObjectList().add(obj);
            cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
        } else
        {
            if(spr.getProperties().Is(IsoFlagType.WallOverlay))
            {
                IsoObject obj2 = cell.getSlices()[y + height * times].Squares[x + height * times][height].getWall();
                if(obj2 != nullptr)
                    obj2.AttachedAnimSprite.add(new IsoSpriteInstance(spr));
                else
                    n = 0;
                return;
            }
            if(spr.getProperties().Is(IsoFlagType.FloorOverlay))
            {
                IsoObject obj2 = cell.getSlices()[y + height * times].Squares[x + height * times][height].getFloor();
                if(obj2 != nullptr)
                    obj2.AttachedAnimSprite.add(new IsoSpriteInstance(spr));
            } else
            if(type == IsoObjectType.tree)
            {
                obj = new IsoTree(cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
                cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
            } else
            if(spr.getProperties().Is(IsoFlagType.pushable))
            {
                obj = new IsoPushableObject(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
            } else
            {
                if(spr.CurrentAnim.Frames.isEmpty() || ((IsoDirectionFrame)spr.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == nullptr)
                    return;
                std::string n1 = ((IsoDirectionFrame)spr.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N).getName();
                bool bCreate = true;
                if(n1.contains("TileObjectsExt") && (n1.contains("_5") || n1.contains("_6") || n1.contains("_7") || n1.contains("_8")))
                {
                    obj = new IsoWheelieBin(cell, x, y, height);
                    if(n1.contains("_5"))
                        obj.dir = IsoDirections.S;
                    if(n1.contains("_6"))
                        obj.dir = IsoDirections.W;
                    if(n1.contains("_7"))
                        obj.dir = IsoDirections.N;
                    if(n1.contains("_8"))
                        obj.dir = IsoDirections.E;
                    bCreate = false;
                }
                if(bCreate)
                {
                    obj = new IsoObject(cell, cell.getSlices()[y + height * times].Squares[x + height * times][height], spr);
                    cell.getSlices()[y + height * times].Squares[x + height * times][height].AddTileObject(obj);
                    if(type == IsoObjectType.stairsTN)
                        cell.getSlices()[y + height * times].Squares[x + height * times][height].setbStairsTN(true);
                    if(type == IsoObjectType.stairsTW)
                        cell.getSlices()[y + height * times].Squares[x + height * times][height].setbStairsTW(true);
                    if(obj.sprite.getProperties().Is("lightR"))
                    {
                        float r = Float.parseFloat(obj.sprite.getProperties().Val("lightR"));
                        float g = Float.parseFloat(obj.sprite.getProperties().Val("lightG"));
                        float b = Float.parseFloat(obj.sprite.getProperties().Val("lightB"));
                        cell.getLamppostPositions().add(new IsoLightSource(obj.square.getX(), obj.square.getY(), obj.square.getZ(), r, g, b, 8));
                    }
                }
            }
        }
        if(obj != nullptr)
        {
            obj.tile = name;
            if(obj.sprite.getProperties().Is("PreSeen"))
                cell.getSlices()[y + height * times].Squares[x + height * times][height].setbSeen(true);
            if(obj.sprite.getProperties().Is("container") && obj.container == nullptr)
            {
                obj.container = new ItemContainer(obj.sprite.getProperties().Val("container"), obj.square, obj, 3, 3);
                cell.getContainers().add(obj.container);
                cell.ContainerMap.put(Integer.valueOf(obj.container.ID), obj.container);
                obj.container.parent = obj;
                ItemContainerFiller.Containers.add(obj.container);
                obj.OutlineOnMouseover = true;
            }
            if(obj.sprite.getProperties().Is(IsoFlagType.vegitation))
            {
                obj.tintr = 0.7F + (float)Rand.Next(30) / 100F;
                obj.tintg = 0.7F + (float)Rand.Next(30) / 100F;
                obj.tintb = 0.7F + (float)Rand.Next(30) / 100F;
            }
            obj.square.RecalcProperties();
        }
    }
    private static IsoCell LoadCellTilesetsOnly(std::string filename)
        throws ParserConfigurationException, SAXException, IOException
    {
        InputStreamReader isr = nullptr;
        wanderX = 0;
        wanderY = 0;
        InputStream is = nullptr;
        is = new FileInputStream(filename);
        isr = new InputStreamReader(is);
        DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
        Document doc = docBuilder.parse(is);
        doc.getDocumentElement().normalize();
        System.out.println((new StringBuilder()).append("Root element of the doc is ").append(doc.getDocumentElement().getNodeName()).toString());
        Node mapNode = doc.getElementsByTagName("map").item(0);
        NamedNodeMap attr = mapNode.getAttributes();
        int width = Integer.parseInt(attr.getNamedItem("width").getNodeValue());
        int height = Integer.parseInt(attr.getNamedItem("height").getNodeValue());
        IsoCell cell = new IsoCell(width, height);
        cell.setFilename(filename.substring(filename.lastIndexOf("\\") + 1, filename.lastIndexOf(".")));
        NodeList listOfTilesets = doc.getElementsByTagName("tileset");
        int totalTilesets = listOfTilesets.getLength();
        NodeList listOfLayers = doc.getElementsByTagName("layer");
        int totalLayers = listOfLayers.getLength();
        float tilelistPercent = 30F / (float)totalTilesets;
        float layersPercent = 30F / (float)totalLayers;
        int percent = 0;
        for(int s = 0; s < totalTilesets; s++)
        {
            LoadTileset(cell, listOfTilesets.item(s));
            percent += (int)tilelistPercent;
        }
        return cell;
    }
    public static IsoCell LoadCellBinary(IsoSpriteManager spr, std::string name, std::string filename, bool mapUseJar)
        throws ParserConfigurationException, SAXException, IOException
    {
        wanderX = 0;
        wanderY = 0;
        wanderRoom = nullptr;
        wanderX = 0;
        wanderY = 0;
        filename = filename.replace(".tmx", ".lot");
        IsoLot lot = new IsoLot(filename);
        IsoCell cell = new IsoCell(spr, lot.width, lot.height);
        cell.PlaceLot(lot, 0, 0, 0, true);
        cell.setFilename(filename.substring(filename.lastIndexOf("\\") + 1, filename.lastIndexOf(".")));
        BucketManager.AddBucket("0_0", cell);
        BucketManager.ActivateBucket("0_0");
        ScriptManager.instance.Trigger("OnPostMapLoad");
        LuaEventManager.TriggerEvent("OnPostMapLoad", cell, name, Integer.valueOf(IsoWorld.instance.x), Integer.valueOf(IsoWorld.instance.y));
        ConnectMultitileObjects(cell);
        CalculateRooms(cell);
        for(int n = 0; n < cell.roomDefs.size(); n++)
        {
            IsoGridSquare sq = cell.getGridSquare(((IsoCell.Zone)cell.roomDefs.get(n)).X, ((IsoCell.Zone)cell.roomDefs.get(n)).Y, ((IsoCell.Zone)cell.roomDefs.get(n)).Z);
            if(sq != nullptr && sq.room != nullptr)
                sq.room.RoomDef = ((IsoCell.Zone)cell.roomDefs.get(n)).Name;
        }
        for(int n = 0; n < cell.getBuildingList().size(); n++)
        {
            IsoBuilding building = (IsoBuilding)cell.getBuildingList().get(n);
            building.FillContainers();
        }
        Stack disStack = ScriptManager.instance.getAllContainerDistributions();
        for(int n = 0; n < disStack.size(); n++)
            ((ContainerDistribution)disStack.get(n)).Process(cell);
        Stack floorStack = ScriptManager.instance.getAllFloorDistributions();
        for(int n = 0; n < floorStack.size(); n++)
            ((FloorDistribution)floorStack.get(n)).Process(cell);
        Stack shelfStack = ScriptManager.instance.getAllShelfDistributions();
        for(int n = 0; n < shelfStack.size(); n++)
            ((ShelfDistribution)shelfStack.get(n)).Process(cell);
        Stack it = ScriptManager.instance.getAllZones();
        for(int n = 0; n < it.size(); n++)
        {
            Zone z = (Zone)it.get(n);
            cell.getZoneStack().add(new IsoCell.Zone(z.name, z.x, z.y, z.x2 - z.x, z.y2 - z.y, z.z));
        }
        for(int x = 0; x < cell.getWidth(); x++)
        {
            for(int y = 0; y < cell.getHeight(); y++)
            {
                for(int z = 0; z < IsoCell.MaxHeight; z++)
                    if(cell.getSlices()[y].Squares[x][z] != nullptr)
                    {
                        cell.getSlices()[y].Squares[x][z].RecalcShortcutPtrs(false);
                        cell.getSlices()[y].bSaveDirty = true;
                    }
            }
        }
        cell.setPathMap(new AStarPathMap(cell));
        CalculateStairNodes(cell);
        return cell;
    }
    public static IsoCell LoadCell(std::string filename, bool mapUseJar)
        throws ParserConfigurationException, SAXException, IOException
    {
        wanderX = 0;
        wanderY = 0;
        wanderRoom = nullptr;
        wanderX = 0;
        wanderY = 0;
        InputStreamReader isr = nullptr;
        InputStream is = nullptr;
        is = new FileInputStream(filename);
        DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
        Document doc = docBuilder.parse(is);
        doc.getDocumentElement().normalize();
        System.out.println((new StringBuilder()).append("Root element of the doc is ").append(doc.getDocumentElement().getNodeName()).toString());
        Node mapNode = doc.getElementsByTagName("map").item(0);
        NamedNodeMap attr = mapNode.getAttributes();
        int width = Integer.parseInt(attr.getNamedItem("width").getNodeValue());
        int height = Integer.parseInt(attr.getNamedItem("height").getNodeValue());
        IsoCell cell = new IsoCell(width, height);
        cell.setFilename(filename.substring(filename.lastIndexOf("\\") + 1, filename.lastIndexOf(".")));
        BucketManager.AddBucket("0_0", cell);
        BucketManager.ActivateBucket("0_0");
        NodeList listOfTilesets = doc.getElementsByTagName("tileset");
        int totalTilesets = listOfTilesets.getLength();
        NodeList listOfLayers = doc.getElementsByTagName("layer");
        int totalLayers = listOfLayers.getLength();
        float tilelistPercent = 30F / (float)totalTilesets;
        float layersPercent = 30F / (float)totalLayers;
        int percent = 0;
        for(int s = 0; s < totalTilesets; s++)
        {
            LoadTileset(cell, listOfTilesets.item(s));
            percent += (int)tilelistPercent;
        }
        for(int s = 0; s < totalLayers; s++)
        {
            LoadLayer(cell, listOfLayers.item(s), s);
            percent += (int)layersPercent;
        }
        ConnectCellSquares(cell, false);
        ConnectMultitileObjects(cell);
        CalculateRooms(cell);
        listOfLayers = doc.getElementsByTagName("objectgroup");
        totalLayers = listOfLayers.getLength();
        for(int s = 0; s < totalLayers; s++)
            LoadObjectGroup(cell, listOfLayers.item(s), s);
        for(int n = 0; n < cell.getBuildingList().size(); n++)
        {
            IsoBuilding building = (IsoBuilding)cell.getBuildingList().get(n);
            building.FillContainers();
        }
        Stack disStack = ScriptManager.instance.getAllContainerDistributions();
        for(int n = 0; n < disStack.size(); n++)
            ((ContainerDistribution)disStack.get(n)).Process(cell);
        Stack floorStack = ScriptManager.instance.getAllFloorDistributions();
        for(int n = 0; n < floorStack.size(); n++)
            ((FloorDistribution)floorStack.get(n)).Process(cell);
        Stack shelfStack = ScriptManager.instance.getAllShelfDistributions();
        for(int n = 0; n < shelfStack.size(); n++)
            ((ShelfDistribution)shelfStack.get(n)).Process(cell);
        Stack it = ScriptManager.instance.getAllZones();
        for(int n = 0; n < it.size(); n++)
        {
            Zone z = (Zone)it.get(n);
            cell.getZoneStack().add(new IsoCell.Zone(z.name, z.x, z.y, z.x2 - z.x, z.y2 - z.y, z.z));
        }
        cell.setPathMap(new AStarPathMap(cell));
        CalculateStairNodes(cell);
        return cell;
    }
    public static void CalculateRooms(IsoCell cell)
    {
        IsoGridSquare wanderStart = FindNextInside(cell);
        if(wanderStart == nullptr)
            return;
        wanderRoom = new IsoRoom();
        wanderRoom.layer = wanderStart.getZ();
        IsoGridSquare square = wanderStart;
        square.setRoom(wanderRoom);
        wanderRoom.TileList.add(square);
        do
        {
            DoSquare(wanderStart);
            cell.getRoomList().add(wanderRoom);
            wanderStart = FindNextInside(cell);
            if(wanderStart != nullptr)
            {
                wanderRoom = new IsoRoom();
                wanderRoom.layer = wanderStart.getZ();
                wanderStart.setRoom(wanderRoom);
                wanderRoom.TileList.add(wanderStart);
            }
        } while(wanderStart != nullptr);
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            for(int m = 0; m < room.Exits.size(); m++)
            {
                IsoRoomExit exit = (IsoRoomExit)room.Exits.get(m);
                IsoGridSquare sq = cell.getGridSquare(exit.To.x, exit.To.y, exit.To.layer);
                if(sq.getRoom() == nullptr && !sq.getProperties().Is(IsoFlagType.exterior))
                {
                    wanderRoom = new IsoRoom();
                    wanderRoom.Exits.add(exit.To);
                    exit.To.From = wanderRoom;
                    wanderRoom.layer = sq.getZ();
                    sq.setRoom(wanderRoom);
                    DoSquare(sq);
                    cell.getRoomList().add(wanderRoom);
                }
            }
        }
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            if(room.TileList.isEmpty())
                continue;
            Rectangle rect = new Rectangle();
            rect.x = ((IsoGridSquare)room.TileList.get(0)).getX();
            rect.y = ((IsoGridSquare)room.TileList.get(0)).getY();
            rect.width = 1;
            rect.height = 1;
            for(int t = 0; t < room.TileList.size(); t++)
            {
                IsoGridSquare sq = (IsoGridSquare)room.TileList.get(t);
                if(sq.getX() < rect.x)
                {
                    rect.width += rect.x - sq.getX();
                    rect.x = sq.getX();
                }
                if(sq.getX() >= rect.x + rect.width)
                    rect.width += (sq.getX() - (rect.x + rect.width)) + 1;
                if(sq.getY() < rect.y)
                {
                    rect.height += rect.y - sq.getY();
                    rect.y = sq.getY();
                }
                if(sq.getY() >= rect.y + rect.height)
                    rect.height += (sq.getY() - (rect.y + rect.height)) + 1;
                room.layer = sq.getZ();
            }
            room.bounds = rect;
        }
label0:
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            Iterator i$;
            if(room.TileList.isEmpty())
            {
                cell.getRoomList().remove(room);
                n--;
                for(i$ = room.Exits.iterator(); i$.hasNext();)
                {
                    IsoRoomExit exit = (IsoRoomExit)i$.next();
                    exit.From = nullptr;
                }
                continue;
            }
            i$ = room.Exits.iterator();
            do
            {
                IsoRoomExit exit;
                do
                {
                    if(!i$.hasNext())
                        continue label0;
                    exit = (IsoRoomExit)i$.next();
                } while(exit.To.From == nullptr || exit.To.From.Exits.contains(exit.To));
                exit.To.From.Exits.add(exit.To);
            } while(true);
        }
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            Object arr$[] = room.Exits.toArray();
            int len$ = arr$.length;
            for(int i$ = 0; i$ < len$; i$++)
            {
                Object ex = arr$[i$];
                IsoRoomExit exit = (IsoRoomExit)ex;
                IsoGridSquare sq = cell.getGridSquare(exit.To.x, exit.To.y, exit.To.layer);
                if(sq == nullptr)
                {
                    exit.To.From = nullptr;
                    continue;
                }
                exit.To.From = sq.getRoom();
                if(sq.getRoom() != nullptr && !exit.To.From.Exits.contains(exit.To))
                    exit.To.From.Exits.add(exit.To);
            }
        }
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            if(room.building == nullptr)
            {
                IsoBuilding b = room.CreateBuilding(cell);
                cell.getBuildingList().add(b);
            }
        }
        for(int n = 0; n < cell.getBuildingList().size(); n++)
        {
            IsoBuilding building = (IsoBuilding)cell.getBuildingList().get(n);
            building.CalculateExits();
            building.CalculateWindows();
            if(building.Exits.isEmpty())
            {
                cell.getBuildingList().remove(n);
                n--;
                continue;
            }
            for(int m = 0; m < building.Exits.size(); m++)
            {
                if(Rand.Next(6) > 1)
                    continue;
                IsoDoor door = ((IsoRoomExit)building.Exits.get(m)).getDoor(cell);
                if(door != nullptr && (door.square.getX() != 87 || door.square.getY() != 107) && door.square.getX() < 69)
                    if(door.square.getY() < 30);
            }
        }
        for(int x = 0; x < cell.getWidth(); x++)
        {
            for(int y = 0; y < cell.getHeight(); y++)
            {
                for(int z = 0; z < IsoCell.MaxHeight; z++)
                {
                    IsoGridSquare g = cell.getGridSquare(x, y, z);
                    if(g != nullptr && g.room != nullptr && g.room.TileList.isEmpty())
                        g.room = nullptr;
                }
            }
        }
    }
    public static void ConnectCellSquares(IsoCell cell, bool bLoaded)
    {
        int w = cell.getWidthInTiles();
        int h = cell.getHeightInTiles();
        for(int x = 0; x < w; x++)
        {
            for(int y = 0; y < h; y++)
            {
                for(int z = 0; z < IsoCell.getMaxHeight(); z++)
                {
                    IsoGridSquare sq = cell.getGridSquare(x, y, z);
                    if(sq == nullptr)
                        continue;
                    for(int n = 0; n < sq.getObjects().size(); n++)
                        if(((IsoObject)sq.getObjects().get(n)).sprite != nullptr)
                            sq.getProperties().AddProperties(((IsoObject)sq.getObjects().get(n)).sprite.getProperties());
                }
            }
        }
        for(int x = 0; x < w; x++)
        {
            for(int y = 0; y < h; y++)
            {
                for(int z = 0; z < IsoCell.getMaxHeight(); z++)
                {
                    IsoGridSquare sq = cell.getGridSquare(x, y, z);
                    if(sq == nullptr)
                        continue;
                    if(cell.IsZone("seen", x, y))
                        sq.setbSeen(true);
                    int col = 0;
                    int path = 0;
                    int vision = 0;
                    for(int x2 = 0; x2 < 3; x2++)
                    {
                        for(int y2 = 0; y2 < 3; y2++)
                        {
                            for(int z2 = 0; z2 < 3; z2++)
                            {
                                IsoGridSquare sq2 = cell.getGridSquare(x + (x2 - 1), y + (y2 - 1), z + (z2 - 1));
                                if(sq2 != nullptr)
                                {
                                    int n;
                                    if(sq.getX() == 42 && sq.getY() == 63 && sq.getZ() == 0 && sq2.getX() == 43 && sq2.getY() == 62 && sq2.getZ() == 0)
                                        n = 0;
                                    if(!bLoaded)
                                    {
                                        col = BitMatrix.Set(col, x2 - 1, y2 - 1, z2 - 1, sq.CalculateCollide(sq2, false, false, false));
                                        path = BitMatrix.Set(path, x2 - 1, y2 - 1, z2 - 1, sq.CalculateCollide(sq2, false, true, false));
                                        vision = BitMatrix.Set(vision, x2 - 1, y2 - 1, z2 - 1, sq.CalculateVisionBlocked(sq2));
                                    }
                                    continue;
                                }
                                if(!bLoaded)
                                {
                                    col = BitMatrix.Set(col, x2 - 1, y2 - 1, z2 - 1, true);
                                    path = BitMatrix.Set(path, x2 - 1, y2 - 1, z2 - 1, true);
                                    vision = BitMatrix.Set(vision, x2 - 1, y2 - 1, z2 - 1, false);
                                }
                            }
                        }
                    }
                    if(!bLoaded)
                    {
                        sq.collideMatrix = CollisionMatrixPrototypes.instance.Add(col);
                        sq.pathMatrix = CollisionMatrixPrototypes.instance.Add(path);
                        sq.visionMatrix = CollisionMatrixPrototypes.instance.Add(vision);
                    }
                }
            }
        }
    }
    private static void DoSquare(IsoGridSquare square)
    {
        for(int x = -1; x <= 1; x++)
        {
            for(int y = -1; y <= 1; y++)
            {
                for(int z = -1; z <= 1; z++)
                {
                    if(square.getZ() == 0 && z < 0)
                        continue;
                    IsoGridSquare targ = square.getCell().getGridSquare(square.getX() + x, square.getY() + y, square.getZ() + z);
                    if(targ == nullptr)
                        continue;
                    int n;
                    if(targ.getX() == 45 && targ.getY() == 26 && targ.getZ() == 0)
                        n = 0;
                    if(targ.getProperties().Is(IsoFlagType.noStart))
                        continue;
                    bool b = targ.CalculateCollide(square, false, false, true);
                    BlockInfo lastBlockCheckInfo = targ.testAdjacentRoomTransition(-x, -y, -z);
                    if(b || targ == nullptr || targ.getRoom() != nullptr)
                        continue;
                    if(lastBlockCheckInfo.ThroughDoor || lastBlockCheckInfo.ThroughWindow || z != 0)
                    {
                        IsoRoomExit ex = new IsoRoomExit(wanderRoom, square.getX(), square.getY(), square.getZ());
                        wanderRoom.Exits.add(ex);
                        ex.To = new IsoRoomExit(ex, targ.getX(), targ.getY(), targ.getZ());
                        continue;
                    }
                    if(!targ.getProperties().Is(IsoFlagType.exterior) && targ.TreatAsSolidFloor())
                    {
                        targ.setRoom(wanderRoom);
                        wanderRoom.TileList.add(targ);
                        DoSquare(targ);
                    } else
                    {
                        n = 0;
                    }
                }
            }
        }
    }
    private static IsoGridSquare FindNextInside(IsoCell cell)
    {
        for(int x = wanderX; x < cell.getWidthInTiles(); x++)
        {
            wanderX = x;
            for(int y = 0; y < cell.getHeightInTiles(); y++)
            {
                wanderY = y;
                IsoGridSquare targ = cell.getGridSquare(x, y, 0);
                if(targ != nullptr && !targ.getProperties().Is(IsoFlagType.exterior) && targ.getRoom() == nullptr && targ.getObjects().size() > 0 && !targ.getProperties().Is(IsoFlagType.noStart))
                    return targ;
            }
        }
        return nullptr;
    }
    private static void LoadLayer(IsoCell cell, Node layerNode, int s)
    {
        Stack BedList = new Stack();
        NodeList nodes = layerNode.getChildNodes();
        bool bRender = true;
        int height = -1;
        std::string name2 = layerNode.getAttributes().getNamedItem("name").getNodeValue();
        std::string Height = name2.substring(0, name2.indexOf("_"));
        height = Integer.parseInt(Height);
label0:
        for(int i = 0; i < nodes.getLength(); i++)
        {
            Node node = nodes.item(i);
            if(node.getNodeName() == "properties"))
            {
                NodeList data = node.getChildNodes();
                for(int d = 0; d < data.getLength(); d++)
                {
                    Node prop = data.item(d);
                    if(!prop.getNodeName() == "property"))
                        continue;
                    NamedNodeMap attributes = prop.getAttributes();
                    Node namedItem = attributes.getNamedItem("name");
                    std::string propName = namedItem.getNodeValue();
                    Node namedItem2 = attributes.getNamedItem("value");
                    std::string propName2 = namedItem2.getNodeValue();
                    if(!propName == "height"));
                    if(propName == "render"))
                        bRender = propName2 == "true");
                }
            }
            if(!node.getNodeName() == "data"))
                continue;
            int x = 0;
            int y = 0;
            NodeList data = node.getChildNodes();
            int d = 0;
            do
            {
                if(d >= data.getLength())
                    continue label0;
                Node tile = data.item(d);
                std::string csv[] = tile.getNodeValue().trim().replaceAll("\n", "").split(",");
                for(int j = 0; j < csv.length; j++)
                {
                    int f = 0;
                    try
                    {
                        f = Integer.parseInt(csv[j]);
                    }
                    catch(Exception ex)
                    {
                        Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    if(f > 0)
                    {
                        int tx = x + height * 3;
                        int ty = y + height * 3;
                        int tz = height;
                        for(int ux = tx - 1; ux <= tx + 1; ux++)
                        {
                            for(int uy = ty - 1; uy <= ty + 1; uy++)
                                if(ux >= 0 && uy >= 0 && ux < cell.getWidthInTiles() && uy < cell.getHeightInTiles() && cell.getSlices()[uy].Squares[ux][tz] == nullptr)
                                    cell.getSlices()[uy].Squares[ux][tz] = new IsoGridSquare(cell, cell.getSlices()[uy], ux, uy, tz);
                        }
                        if(y + height * 3 < cell.getSlices().length)
                            if(!bRender)
                            {
                                cell.getSlices()[y + height * 3].Squares[x + height * 3][height].getProperties().Set(IsoFlagType.hidewalls, "");
                            } else
                            {
                                IsoObject obj = nullptr;
                                IsoSprite spr = IsoSprite.getSprite(cell.SpriteManager, f);
                                if(spr == nullptr)
                                    spr = IsoSprite.getSpriteForceCreate(cell.SpriteManager, f);
                                IsoObjectType type = spr.getType();
                                DoTileObjectCreation(spr, type, cell, x, y, height, BedList, true, "");
                            }
                    }
                    if(++x >= cell.getWidthInTiles())
                    {
                        x = 0;
                        y++;
                    }
                }
                d++;
            } while(true);
        }
    }
    private static void LoadObjectGroup(IsoCell cell, Node layerNode, int s)
    {
        NodeList nodes = layerNode.getChildNodes();
        int height = -1;
        bool zoning = false;
        std::string name2 = layerNode.getAttributes().getNamedItem("name").getNodeValue();
        if(name2.contains("Zoning"))
            zoning = true;
        std::string Height = name2.substring(0, name2.indexOf("_"));
        height = Integer.parseInt(Height);
        for(int i = 0; i < nodes.getLength(); i++)
        {
            Node node = nodes.item(i);
            if(node.getNodeName() == "properties"))
            {
                NodeList data = node.getChildNodes();
                for(int d = 0; d < data.getLength(); d++)
                {
                    Node prop = data.item(d);
                    if(prop.getNodeName() == "property"))
                    {
                        NamedNodeMap attributes = prop.getAttributes();
                        Node namedItem = attributes.getNamedItem("name");
                        std::string propName = namedItem.getNodeValue();
                        Node namedItem2 = attributes.getNamedItem("value");
                        std::string propName2 = namedItem2.getNodeValue();
                        if(!propName == "height"));
                    }
                }
            }
            if(!node.getNodeName() == "object"))
                continue;
            int x = 0;
            int y = 0;
            NodeList data = node.getChildNodes();
            Node name = node.getAttributes().getNamedItem("name");
            Node type = node.getAttributes().getNamedItem("type");
            Node ox = node.getAttributes().getNamedItem("x");
            Node oy = node.getAttributes().getNamedItem("y");
            Node ow = node.getAttributes().getNamedItem("width");
            Node oh = node.getAttributes().getNamedItem("height");
            if(name == nullptr)
                continue;
            if(zoning || name.getNodeValue() == "zone"))
            {
                int tileX = (int)Float.parseFloat(ox.getNodeValue()) / 32;
                int tileY = (int)Float.parseFloat(oy.getNodeValue()) / 32;
                int tileW = (int)Float.parseFloat(ow.getNodeValue()) / 32;
                int tileH = (int)Float.parseFloat(oh.getNodeValue()) / 32;
                tileX += height * 3;
                tileY += height * 3;
                ScriptManager.instance.AddZone("Map", type.getNodeValue(), new Zone(type.getNodeValue(), tileX, tileY, tileX + tileW, tileY + tileH, height));
                continue;
            }
            if(name.getNodeValue() == "roomDef"))
            {
                int tileX = (int)Float.parseFloat(ox.getNodeValue()) / 32;
                int tileY = (int)Float.parseFloat(oy.getNodeValue()) / 32;
                tileX += height * 3;
                tileY += height * 3;
                IsoGridSquare sq = cell.getGridSquare(tileX, tileY, height);
                if(sq != nullptr && sq.getRoom() != nullptr)
                {
                    sq.getRoom().RoomDef = type.getNodeValue();
                    ScriptManager.instance.AddRoom("Map", sq.getRoom().RoomDef, new Room(sq.getRoom().RoomDef, sq.getRoom()));
                    int n = 0;
                }
                continue;
            }
            if(name.getNodeValue() == "lot"))
            {
                int tileX = (int)Float.parseFloat(ox.getNodeValue()) / 32;
                int tileY = (int)Float.parseFloat(oy.getNodeValue()) / 32;
                tileX += height * 3;
                tileY += height * 3;
                IsoLot lot = new IsoLot((new StringBuilder()).append("media/lots/").append(type.getNodeValue()).append(".lot").toString());
                cell.PlaceLot(lot, tileX, tileY, height, true);
            }
        }
    }
    public static void LoadTileset(IsoCell cell, Node tilesetNode)
    {
        NodeList nodes = tilesetNode.getChildNodes();
        int firstGID = Integer.parseInt(tilesetNode.getAttributes().getNamedItem("firstgid").getNodeValue());
        std::string filename = "test";
        bool bOutside = false;
        for(int i = 0; i < nodes.getLength(); i++)
        {
            bool bWall = false;
            bool bFloor = false;
            Node node = nodes.item(i);
            if(node.getNodeName() == "image"))
            {
                filename = (new StringBuilder()).append("/media/").append(node.getAttributes().getNamedItem("source").getNodeValue()).toString();
                if(filename.contains("Wall"))
                    bWall = true;
                if(filename.contains("Floor"))
                    bFloor = true;
                std::string fn = filename.substring(filename.lastIndexOf("/") + 1);
                fn = fn.replace(".png", "");
                fn = fn.replace(".PNG", "");
                Texture tex = nullptr;
                int n = 0;
                do
                {
                    tex = TexturePackPage.getTexture((new StringBuilder()).append(fn).append("_").append(n).toString());
                    if(tex != nullptr || FrameLoader.bServer)
                    {
                        IsoSprite sprite = IsoSprite.getSprite(cell.SpriteManager, firstGID + n, tex);
                        if(bWall)
                            cell.getWallArray().add(Integer.valueOf(firstGID + n));
                        if(bWall)
                            sprite.setType(IsoObjectType.wall);
                        cell.SpriteManager.NamedMap.put((new StringBuilder()).append(fn).append("_").append(n).toString(), sprite);
                        cell.SpriteManager.ID++;
                    }
                } while(++n < 128);
            }
            if(!node.getNodeName() == "tile"))
                continue;
            NodeList data = node.getChildNodes();
            int id = Integer.parseInt(node.getAttributes().getNamedItem("id").getNodeValue());
            IsoSprite sprite = IsoSprite.getSprite(cell.SpriteManager, firstGID + id);
            if(sprite == nullptr)
                continue;
            if(bWall)
                sprite.setType(IsoObjectType.wall);
            if(bFloor)
                sprite.getProperties().Set(IsoFlagType.solidfloor, "true");
            for(int d = 0; d < data.getLength(); d++)
            {
                Node tileNode = data.item(d);
                if(!tileNode.getNodeName() == "properties"))
                    continue;
                NodeList tileChildren = tileNode.getChildNodes();
                for(int g = 0; g < tileChildren.getLength(); g++)
                {
                    Node prop = tileChildren.item(g);
                    if(!prop.getNodeName() == "property"))
                        continue;
                    NamedNodeMap attributes = prop.getAttributes();
                    Node namedItem = attributes.getNamedItem("name");
                    std::string propName = namedItem.getNodeValue();
                    Node namedItem2 = attributes.getNamedItem("value");
                    std::string propName2 = namedItem2.getNodeValue();
                    sprite.getProperties().Set(IsoFlagType.FromString(propName), propName2);
                    if(!propName.contains("stairs"));
                    if(propName == "barricadeDoorFrame"))
                        IsoCell.setBarricadeDoorFrame(firstGID + id);
                    if(propName == "sheetCurtains"))
                        IsoCell.setSheetCurtains(firstGID + id);
                    if(propName == "WallW"))
                    {
                        sprite.getProperties().Set(IsoFlagType.collideW, "true");
                        sprite.getProperties().Set(IsoFlagType.cutW, "true");
                    } else
                    if(propName == "WallN"))
                    {
                        sprite.getProperties().Set(IsoFlagType.collideN, "true");
                        sprite.getProperties().Set(IsoFlagType.cutN, "true");
                    } else
                    if(propName == "WallNW"))
                    {
                        sprite.getProperties().Set(IsoFlagType.collideN, "true");
                        sprite.getProperties().Set(IsoFlagType.cutN, "true");
                        sprite.getProperties().Set(IsoFlagType.collideW, "true");
                        sprite.getProperties().Set(IsoFlagType.cutW, "true");
                    } else
                    if(propName == "WallSE"))
                        sprite.getProperties().Set(IsoFlagType.cutW, "true");
                    else
                    if(propName == "WindowW"))
                    {
                        sprite.getProperties().Set(IsoFlagType.cutW, "true");
                        sprite.getProperties().Set(IsoFlagType.collideW, "true");
                        sprite.getProperties().Set(IsoFlagType.transparentW, "true");
                        sprite.setType(IsoObjectType.windowFW);
                    } else
                    if(propName == "WindowN"))
                    {
                        sprite.getProperties().Set(IsoFlagType.cutN, "true");
                        sprite.getProperties().Set(IsoFlagType.collideN, "true");
                        sprite.getProperties().Set(IsoFlagType.transparentN, "true");
                        sprite.setType(IsoObjectType.windowFN);
                    } else
                    if(propName == "DoorWallN"))
                        sprite.getProperties().Set(IsoFlagType.cutN, "true");
                    else
                    if(propName == "DoorWallW"))
                        sprite.getProperties().Set(IsoFlagType.cutW, "true");
                    if(!sprite.getProperties().Is(IsoFlagType.vegitation));
                    if(propName == "interior") && propName2 == "false"))
                        sprite.getProperties().Set(IsoFlagType.exterior, "");
                }
            }
        }
    }
    static IsoCell LoadCellFromData(IsoSpriteManager spr, std::string playerCell, bool mapTransferal)
        throws FileNotFoundException, IOException
    {
        File outFile = new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).append(playerCell).append("map.bin").toString());
        FileInputStream inStream = new FileInputStream(outFile);
        DataInputStream input = new DataInputStream(inStream);
        int w = input.readInt();
        int h = input.readInt();
        IsoCell.MaxHeight = input.readInt();
        IsoCell cell = new IsoCell(spr, w, h, true);
        if(cell == nullptr)
            return nullptr;
        IsoWorld.instance.CurrentCell = cell;
        cell.setFilename(playerCell);
        try
        {
            cell.load(input, !mapTransferal);
        }
        catch(ClassNotFoundException ex)
        {
            Logger.getLogger(CellLoader.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        ConnectCellSquares(cell, true);
        ConnectMultitileObjects(cell);
        CalculateRooms(cell);
        cell.setPathMap(new AStarPathMap(cell));
        CalculateStairNodes(cell);
        cell.loadCharacters();
        return cell;
    }
    private static void CalculateStairNodes(IsoCell cell)
    {
        int w = cell.getWidthInTiles();
        int h = cell.getHeightInTiles();
        for(int x = 0; x < w; x++)
        {
            for(int y = 0; y < h; y++)
            {
                for(int z = 1; z < IsoCell.getMaxHeight(); z++)
                {
                    IsoGridSquare sq = cell.getSlices()[y].Squares[x][z];
                    if(sq == nullptr || z <= 0)
                        continue;
                    IsoGridSquare a = cell.getGridSquare(x + 1, y, z - 1);
                    if(a != nullptr && a.Has(IsoObjectType.stairsTW))
                    {
                        cell.getStairsNodes().add(cell.getPathMap().nodes[x + 1][y][z - 1].ID);
                        cell.getStairsNodes().add(cell.getPathMap().nodes[x][y][z].ID);
                    }
                    a = cell.getGridSquare(x, y + 1, z - 1);
                    if(a == nullptr || !a.Has(IsoObjectType.stairsTN))
                        continue;
                    cell.getStairsNodes().add(cell.getPathMap().nodes[x][y + 1][z - 1].ID);
                    int n;
                    if(cell.getPathMap().nodes[x][y][z] == nullptr)
                        n = 0;
                    cell.getStairsNodes().add(cell.getPathMap().nodes[x][y][z].ID);
                }
            }
        }
        for(int q = 0; q < cell.getBuildingList().size(); q++)
        {
            for(int m = 0; m < ((IsoBuilding)cell.getBuildingList().get(q)).Rooms.size(); m++)
            {
                IsoRoom room = (IsoRoom)((IsoBuilding)cell.getBuildingList().get(q)).Rooms.get(m);
                int minx = 0x186a0;
                int miny = 0x186a0;
                int maxx = -10000;
                int maxy = -10000;
                Iterator i$ = room.TileList.iterator();
                do
                {
                    if(!i$.hasNext())
                        break;
                    IsoGridSquare sq = (IsoGridSquare)i$.next();
                    if(sq.getX() < minx)
                        minx = sq.getX();
                    if(sq.getX() > maxx)
                        maxx = sq.getX();
                    if(sq.getY() > maxy)
                        maxy = sq.getY();
                    if(sq.getY() < miny)
                        miny = sq.getY();
                } while(true);
                IsoGridSquare mid = nullptr;
                int dif = 0x186a0;
                bool perf = false;
                for(Iterator i$1 = room.TileList.iterator(); i$1.hasNext();)
                {
                    IsoGridSquare sq = (IsoGridSquare)i$1.next();
                    int tx = minx + (maxx - minx) / 2;
                    int ty = miny + (maxy - miny) / 2;
                    int ndif = Math.abs(sq.getX() - tx) + Math.abs(sq.getY() - ty);
                    if(ndif < dif)
                    {
                        dif = ndif;
                        mid = sq;
                    }
                    int n = 0;
                    while(n < sq.getObjects().size()) 
                    {
                        IsoObject obj = (IsoObject)sq.getObjects().get(n);
                        if((obj instanceof IsoLightSwitch) && ((IsoLightSwitch)obj).lightRoom)
                            room.lightSwitches.add((IsoLightSwitch)obj);
                        n++;
                    }
                }
                if(room.lightSwitches.isEmpty() || mid == nullptr)
                    continue;
                int rx = 0;
                int ry = 0;
                IsoLightSource s = new IsoLightSource(mid.getX(), mid.getY(), room.layer, 0.8F, 0.6F, 0.4F, 8);
                s.bActive = false;
                s.switches.addAll(room.lightSwitches);
                for(int n = 0; n < room.lightSwitches.size(); n++)
                    ((IsoLightSwitch)room.lightSwitches.get(n)).lights.add(s);
                cell.getLamppostPositions().add(s);
            }
        }
        for(int n = 0; n < cell.getLamppostPositions().size(); n++)
        {
            IsoLightSource l = (IsoLightSource)cell.getLamppostPositions().get(n);
            IsoGridSquare src = cell.getGridSquare(l.x, l.y, l.z);
            for(int x = l.x - l.radius; x <= l.x + l.radius; x++)
            {
                for(int y = l.y - l.radius; y <= l.y + l.radius; y++)
                {
                    IsoGridSquare sq = nullptr;
                    float totR = 0.0F;
                    float totG = 0.0F;
                    float totB = 0.0F;
                    for(int z = 0; z < IsoCell.getMaxHeight(); z++)
                    {
                        sq = cell.getGridSquare(x, y, z);
                        if(sq == nullptr)
                            continue;
                        int fds;
                        if(sq.getX() == 43 && sq.getY() == 28 && sq.getZ() == 0 && src.getRoom() != nullptr)
                            fds = 0;
                        if(src == nullptr || sq == nullptr)
                            continue;
                        int dd;
                        if(src.getRoom() != nullptr)
                            dd = 0;
                        LosUtil.TestResults test = LosUtil.lineClear(cell, l.x, l.y, l.z, x, y, z, true);
                        if((x != l.x || y != l.y || z != l.z) && test == LosUtil.TestResults.Blocked)
                            continue;
                        float del = 0.0F;
                        float dist = IsoUtils.DistanceTo(l.x, l.y, l.z, x, y, z);
                        if(Math.abs(z - l.z) <= 1)
                            dist = IsoUtils.DistanceTo(l.x, l.y, 0.0F, x, y, 0.0F);
                        if(dist > (float)l.radius || test == LosUtil.TestResults.ClearThroughWindow && LosUtil.DistToWindow(cell, l.x, l.y, l.z, x, y, z) == 0)
                            continue;
                        del = dist / (float)l.radius;
                        del = 1.0F - del;
                        if(del > 0.0F)
                            l.affects.add(sq);
                        sq.getLights().add(l);
                        totR = del * l.r;
                        totG = del * l.g;
                        totB = del * l.b;
                        test = LosUtil.lineClear(cell, l.x, l.y, l.z, x, y, z, false);
                        if(l.bActive && test != LosUtil.TestResults.Blocked)
                        {
                            sq.setLampostTotalR(sq.getLampostTotalR() + totR);
                            sq.setLampostTotalG(sq.getLampostTotalG() + totG);
                            sq.setLampostTotalB(sq.getLampostTotalB() + totB);
                        }
                    }
                }
            }
        }
    }
    private static void RecurseMultitileObjects(IsoCell cell, IsoGridSquare from, IsoGridSquare sq, NulledArrayList list)
    {
        Iterator it = sq.getMovingObjects().iterator();
        IsoPushableObject foundpush = nullptr;
        bool bFoundOnX = false;
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            IsoMovingObject obj = (IsoMovingObject)it.next();
            if(!(obj instanceof IsoPushableObject))
                continue;
            IsoPushableObject push = (IsoPushableObject)obj;
            int difX = from.getX() - sq.getX();
            int difY = from.getY() - sq.getY();
            if(difY != 0 && obj.sprite.getProperties().Is("connectY"))
            {
                int offY = Integer.parseInt(obj.sprite.getProperties().Val("connectY"));
                if(offY == difY)
                {
                    push.connectList = list;
                    list.add(push);
                    foundpush = push;
                    bFoundOnX = false;
                    break;
                }
            }
            if(difX == 0 || !obj.sprite.getProperties().Is("connectX"))
                continue;
            int offX = Integer.parseInt(obj.sprite.getProperties().Val("connectX"));
            if(offX != difX)
                continue;
            push.connectList = list;
            list.add(push);
            foundpush = push;
            bFoundOnX = true;
            break;
        } while(true);
        if(foundpush != nullptr)
        {
            if(foundpush.sprite.getProperties().Is("connectY") && bFoundOnX)
            {
                int offY = Integer.parseInt(foundpush.sprite.getProperties().Val("connectY"));
                IsoGridSquare other = cell.getGridSquare(foundpush.getCurrentSquare().getX(), foundpush.getCurrentSquare().getY() + offY, foundpush.getCurrentSquare().getZ());
                RecurseMultitileObjects(cell, foundpush.getCurrentSquare(), other, foundpush.connectList);
            }
            if(foundpush.sprite.getProperties().Is("connectX") && !bFoundOnX)
            {
                int offX = Integer.parseInt(foundpush.sprite.getProperties().Val("connectX"));
                IsoGridSquare other = cell.getGridSquare(foundpush.getCurrentSquare().getX() + offX, foundpush.getCurrentSquare().getY(), foundpush.getCurrentSquare().getZ());
                RecurseMultitileObjects(cell, foundpush.getCurrentSquare(), other, foundpush.connectList);
            }
        }
    }
    private static void ConnectMultitileObjects(IsoCell cell)
    {
        Iterator it = cell.getObjectList().iterator();
        do
        {
            if(it == nullptr || !it.hasNext())
                break;
            IsoMovingObject obj = (IsoMovingObject)it.next();
            if(obj instanceof IsoPushableObject)
            {
                IsoPushableObject push = (IsoPushableObject)obj;
                if((obj.sprite.getProperties().Is("connectY") || obj.sprite.getProperties().Is("connectX")) && push.connectList == nullptr)
                {
                    push.connectList = new NulledArrayList();
                    push.connectList.add(push);
                    if(obj.sprite.getProperties().Is("connectY"))
                    {
                        int offY = Integer.parseInt(obj.sprite.getProperties().Val("connectY"));
                        IsoGridSquare other = cell.getGridSquare(obj.getCurrentSquare().getX(), obj.getCurrentSquare().getY() + offY, obj.getCurrentSquare().getZ());
                        int n;
                        if(other == nullptr)
                            n = 0;
                        RecurseMultitileObjects(cell, push.getCurrentSquare(), other, push.connectList);
                    }
                    if(obj.sprite.getProperties().Is("connectX"))
                    {
                        int offX = Integer.parseInt(obj.sprite.getProperties().Val("connectX"));
                        IsoGridSquare other = cell.getGridSquare(obj.getCurrentSquare().getX() + offX, obj.getCurrentSquare().getY(), obj.getCurrentSquare().getZ());
                        RecurseMultitileObjects(cell, push.getCurrentSquare(), other, push.connectList);
                    }
                }
            }
        } while(true);
    }
    static int wanderX = 0;
    static int wanderY = 0;
    static IsoRoom wanderRoom = nullptr;
}
} // namespace
