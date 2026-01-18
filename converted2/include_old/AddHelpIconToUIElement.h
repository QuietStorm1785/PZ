#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddHelpIconToUIElement.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Tutorial {
#include "JOptionPane.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
#include "ui.h"
class AddHelpIconToUIElement : public BaseCommand {
public:
{
    public AddHelpIconToUIElement()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Tutorial"))
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        }
        title = params[0].trim().replace("\"", "");
        title = module.getLanguage(title);
        if(title.indexOf("\"") == 0)
        {
            title = title.substring(1);
            title = title.substring(0, title.length() - 1);
        }
        message = params[1].trim().replace("\"", "");
        message = module.getLanguage(message);
        if(message.indexOf("\"") == 0)
        {
            message = message.substring(1);
            message = message.substring(0, message.length() - 1);
        }
        uielement = params[2].trim().replace("\"", "");
        x = Integer.parseInt(params[3].trim());
        y = Integer.parseInt(params[4].trim());
    }
    public void begin()
    {
        UIElement el = nullptr;
        if(uielement == "SIDEBAR_INVENTORY"))
            el = Sidebar.InventoryIcon;
        if(el != nullptr)
            UIManager.AddTutorial(el, x, y, title, message, false);
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string title;
    std::string message;
    int x;
    int y;
    std::string uielement;
}
} // namespace
