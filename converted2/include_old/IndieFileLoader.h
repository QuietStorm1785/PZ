#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IndieFileLoader.java
namespace zombie {
namespace core {
#include <fstream>
#include <iostream>
#include "GameWindow.h"
class IndieFileLoader {
public:
{
    public IndieFileLoader()
    {
    }
    public static InputStreamReader getStreamReader(std::string path)
        throws FileNotFoundException
    {
        return getStreamReader(path, false);
    }
    public static InputStreamReader getStreamReader(std::string path, bool bIgnoreJar)
        throws FileNotFoundException
    {
        InputStreamReader isr = nullptr;
        InputStream is = GameWindow.class.getClassLoader().getResourceAsStream("media" + File.separator + path);
        if(is != nullptr && !bIgnoreJar)
            isr = new InputStreamReader(is);
        else
            try
            {
                FileInputStream fis = new FileInputStream(path);
                isr = new InputStreamReader(fis);
            }
            catch(FileNotFoundException ex)
            {
                FileInputStream fis = new FileInputStream((new StringBuilder()).append("mods").append(File.separator).append(path).toString());
                isr = new InputStreamReader(fis);
            }
        return isr;
    }
}
} // namespace
