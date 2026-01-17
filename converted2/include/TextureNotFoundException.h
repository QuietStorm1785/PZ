#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TextureNotFoundException.java
namespace zombie {
namespace core {
namespace textures {
class TextureNotFoundException : public RuntimeException {
public:
{
    public TextureNotFoundException(std::string name)
    {
        super((new StringBuilder()).append("Image ").append(name).append(" not found! ").toString());
    }
}
} // namespace
