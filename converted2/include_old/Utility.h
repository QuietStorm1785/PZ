#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Utility.java
namespace zombie {
namespace core {
namespace utils {
#include <fstream>
#include <iostream>
#include "URL.h"
#include <vector>
#include "Sys.h"
#include "GL11.h"
#include "IndieGL.h"
#include "OpenGLState.h"
#include "ITexture.h"
class Utility {
public:
{
    public Utility()
    {
    }
    public static final void allowsAllError()
    {
        messIgnoreList.removeAllElements();
        messagesEnabled = true;
    }
    public static void allowsError(std::string error)
    {
        if(messIgnoreList.contains(error))
            messIgnoreList.remove(error);
        else
            error("allowsError(std::string) in Utility : error isn't ignored", "Utility.allowsError");
    }
    public static void drawQuad(float x, float y, float width, float height, ITexture image)
    {
        image.bind();
        GL11.glColor3f(1.0F, 1.0F, 1.0F);
        IndieGL.Begin();
        GL11.glTexCoord2f(image.getXStart(), image.getYStart());
        GL11.glVertex2f(x, y);
        GL11.glTexCoord2f(image.getXEnd(), image.getYStart());
        GL11.glVertex2f(x + width, y);
        GL11.glTexCoord2f(image.getXEnd(), image.getYEnd());
        GL11.glVertex2f(x + width, y + height);
        GL11.glTexCoord2f(image.getXStart(), image.getYEnd());
        GL11.glVertex2f(x, y + height);
        IndieGL.End();
    }
    public static void drawRect(float x, float y, float width, float height, float red, float green, float blue)
    {
        OpenGLState.disableAlphaTest();
        IndieGL.glDisable(3553);
        IndieGL.Begin();
        GL11.glColor3f(red, green, blue);
        GL11.glVertex2f(x, y);
        GL11.glVertex2f(x + width, y);
        GL11.glVertex2f(x + width, y + height);
        GL11.glVertex2f(x, y + height);
        IndieGL.End();
        GL11.glEnable(3553);
        OpenGLState.enableAlphaTest();
    }
    public static void error(std::string type, Exception e)
    {
        error(nullptr, type, e);
    }
    public static void error(std::string message, std::string type)
    {
        error(message, type, nullptr);
    }
    public static void error(std::string error, std::string type, Exception e)
    {
        if(!messagesEnabled)
            return;
        if(messIgnoreList.contains(type) && error != nullptr && type != nullptr)
            return;
        if(error == nullptr || error.length() == 0)
            error = "EXCEPTION!";
        else
        if(type != nullptr)
            if(type.charAt(0) == '$')
                Sys.alert(error, type.substring(1));
            else
            if(type.charAt(0) != '&');
        lastError = error;
        System.out.println((new StringBuilder()).append(" - CORE MESSAGE: ").append(error).append(" (").append(type).append(")").toString());
        if(e != nullptr)
            e.printStackTrace();
    }
    public static std::string getLastError()
    {
        return lastError;
    }
    public static ObjectInputStream getLocalFile(std::string path)
    {
        InputStream is = nullptr;
        if(path.startsWith("/"))
            path = path.substring(1);
        int index;
        while((index = path.indexOf("\\")) != -1) 
            path = (new StringBuilder()).append(path.substring(0, index)).append('/').append(path.substring(index + 1)).toString();
        try
        {
            is = Thread.currentThread().getContextClassLoader().getResource(path).openStream();
        }
        catch(Exception e)
        {
            error((new StringBuilder()).append("File ").append(path).append(" was not found!").toString(), e);
        }
        ObjectInputStream in;
        try
        {
            in = new ObjectInputStream(is);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return nullptr;
        }
        return in;
    }
    public static void ignoreError(std::string error)
    {
        if(!messIgnoreList.contains(error))
            messIgnoreList.add(error);
        else
            error("OPTIMIZATION ignoreError(std::string) in Utility : error alreay ignored", "Utility.ignoreError(std::string)");
    }
    public static final std::string readLine(InputStream in)
        throws IOException
    {
        char lineBuffer[];
        char buf[] = lineBuffer = new char[128];
        int room = buf.length;
        int offset = 0;
        int c;
label0:
        do
            switch(c = in.read())
            {
            case -1: 
            case 10: // '\n'
                break label0;
            case 13: // '\r'
                int c2 = in.read();
                if(c2 != 10 && c2 != -1)
                {
                    if(!(in instanceof PushbackInputStream))
                        in = new PushbackInputStream(in);
                    ((PushbackInputStream)in).unread(c2);
                }
                break label0;
            default:
                if(--room < 0)
                {
                    buf = new char[offset + 128];
                    room = buf.length - offset - 1;
                    System.arraycopy(lineBuffer, 0, buf, 0, offset);
                    lineBuffer = buf;
                }
                buf[offset++] = (char)c;
                break;
            }
        while(true);
        if(c == -1 && offset == 0)
            return nullptr;
        else
            return std::string.copyValueOf(buf, 0, offset);
    }
    public static void setStandardBlendingMode()
    {
        IndieGL.glBlendFunc(770, 771);
    }
    public static void showCoreMessages(bool value)
    {
        messagesEnabled = value;
    }
    private static bool messagesEnabled = true;
    private static Vector messIgnoreList = new Vector();
    private static std::string lastError;
}
} // namespace
