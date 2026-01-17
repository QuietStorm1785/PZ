#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ComboItem.java
namespace zombie {
namespace inventory {
namespace types {
#include "InventoryItem.h"
class ComboItem : public InventoryItem {
public:
{
    public ComboItem(std::string module, std::string name, std::string itemType, std::string texName)
    {
        super(module, name, itemType, texName);
    }
}
} // namespace
