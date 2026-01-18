#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoLot.java
namespace zombie {
namespace iso {
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include "NulledArrayList.h"
class IsoLot {
public:
{
    class Zone
    {
        public std::string name;
        public std::string val;
        public int x;
        public int y;
        public int z;
        public int w;
        public int h;
        public Zone()
        {
        }
    }
    public int getHeight()
    {
        return height;
    }
    public int getWidth()
    {
        return width;
    }
    public int getLevels()
    {
        return levels;
    }
    public static std::string readString(RandomAccessFile in)
        throws EOFException, IOException
    {
        std::string str = in.readLine();
        return str;
    }
    public static int readInt(RandomAccessFile in)
        throws EOFException, IOException
    {
        int ch1 = in.read();
        int ch2 = in.read();
        int ch3 = in.read();
        int ch4 = in.read();
        if((ch1 | ch2 | ch3 | ch4) < 0)
            throw new EOFException();
        else
            return (ch1 << 0) + (ch2 << 8) + (ch3 << 16) + (ch4 << 24);
    }
    public IsoLot(std::string filename)
    {
        tilesUsed = new NulledArrayList();
        zones = new NulledArrayList();
        data = (ArrayList[][][])nullptr;
        width = 0;
        height = 0;
        levels = 0;
        version = 0;
        try
        {
            File fo = new File(filename);
            RandomAccessFile in = new RandomAccessFile(fo.getAbsolutePath(), "r");
            version = readInt(in);
            int tilecount = readInt(in);
            for(int n = 0; n < tilecount; n++)
            {
                std::string str = readString(in);
                tilesUsed.add(str.trim());
            }
            in.read();
            width = readInt(in);
            height = readInt(in);
            levels = readInt(in);
            data = new ArrayList[width][height][levels];
            int nZones = readInt(in);
            for(int n = 0; n < nZones; n++)
            {
                Zone zone = new Zone();
                std::string str = readString(in);
                zone.name = str.trim();
                str = readString(in);
                zone.val = str.trim();
                zone.x = readInt(in);
                zone.y = readInt(in);
                zone.z = readInt(in);
                zone.w = readInt(in);
                zone.h = readInt(in);
                zones.add(zone);
            }
            int skip = 0;
            for(int z = 0; z < levels; z++)
            {
                for(int x = 0; x < width; x++)
                {
label0:
                    for(int y = 0; y < height; y++)
                    {
                        if(skip > 0)
                        {
                            skip--;
                            continue;
                        }
                        int count = readInt(in);
                        if(count == -1)
                        {
                            skip = readInt(in);
                            if(skip > 0)
                            {
                                skip--;
                                continue;
                            }
                        }
                        int n = 0;
                        do
                        {
                            if(n >= count)
                                continue label0;
                            int d = readInt(in);
                            if(data[x][y][z] == nullptr)
                                data[x][y][z] = new ArrayList();
                            data[x][y][z].add(Integer.valueOf(d));
                            n++;
                        } while(true);
                    }
                }
            }
        }
        catch(IOException ex)
        {
            Logger.getLogger(IsoLot.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
    }
    public NulledArrayList getTilesUsed()
    {
        return tilesUsed;
    }
    protected NulledArrayList tilesUsed;
    protected NulledArrayList zones;
    ArrayList data[][][];
    public int width;
    public int height;
    public int levels;
    public int version;
}
} // namespace
