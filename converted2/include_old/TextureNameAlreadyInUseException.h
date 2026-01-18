#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TextureNameAlreadyInUseException.java
namespace zombie {
namespace core {
namespace textures {
class TextureNameAlreadyInUseException : public RuntimeException {
public:
{
    public TextureNameAlreadyInUseException(std::string name)
    {
        super((new StringBuilder()).append("Texture Name ").append(name).append(" is already in use").toString());
    }
}
} // namespace
