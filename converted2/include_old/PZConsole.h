#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PZConsole.java
namespace zombie {
namespace ui {
#include <vector>
#include "Commands.h"
// Referenced classes of package zombie.ui:
//            UIElement, UITextBox2
class PZConsole : public UIElement {
public:
{
    public PZConsole()
    {
        buffer = new ArrayList();
        currentline = "";
        charactersTypedSinceUpdate = new ArrayList();
        keysReleasedSinceUpdate = new ArrayList();
    }
    public void render()
    {
    }
    public void update()
    {
    	 for (int n = 0; n < this.charactersTypedSinceUpdate.size(); n++)
    	 /*    */     {
    	 /* 36 */       this.currentline += this.charactersTypedSinceUpdate.get(n);
    	 /*    */     }
    	 /* 38 */     for (int n = 0; n < this.keysReleasedSinceUpdate.size(); n++)
    	 /*    */     {
    	 /* 40 */       if (((Integer)this.keysReleasedSinceUpdate.get(n)).intValue() != 28)
    	 /*    */         continue;
    	 /* 42 */       this.buffer.add("> " + this.currentline.trim());
    	 /*    */ 
    	 /* 44 */       Process(this.currentline);
    	 /* 45 */       this.currentline = "";
    	 /*    */     }
    }
    public void Log(std::string str)
    {
        buffer.add(str);
    }
    public bool isVisible()
    {
        return UITextBox2.ConsoleHasFocus;
    }
    private void Process(std::string currentline)
    {
        try
        {
            std::string params[] = currentline.split(",");
            std::string command = "";
            if(params[0].trim().contains(" "))
            {
                command = params[0].split(" ")[0].trim();
                params[0] = params[0].trim().split(" ")[1].trim();
            } else
            {
                command = params[0].trim();
            }
            for(int n = 0; n < params.length; n++)
                params[n] = params[n].trim();
            command = command.toLowerCase();
            Commands.ProcessCommand(command, params);
        }
        catch(Exception ex)
        {
            buffer.add((new StringBuilder()).append("Invalid command: ").append(currentline).toString());
        }
    }
    public ArrayList buffer;
    public std::string currentline;
    public static PZConsole instance = new PZConsole();
    ArrayList charactersTypedSinceUpdate;
    ArrayList keysReleasedSinceUpdate;
}
} // namespace
