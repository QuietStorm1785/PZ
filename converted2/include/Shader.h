#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Shader.java
namespace zombie {
namespace core {
namespace opengl {
#include <fstream>
#include <iostream>
#include "ARBShaderObjects.h"
#include "IndieFileLoader.h"
class Shader {
public:
{
    public Shader()
    {
        ShaderID = 0;
        FragID = 0;
        VertID = 0;
        ShaderID = ARBShaderObjects.glCreateProgramObjectARB();
        if(ShaderID != 0)
        {
            FragID = createFragShader("shaders/screen.frag");
            VertID = createVertShader("shaders/screen.vert");
            if(VertID != 0 && FragID != 0)
            {
                ARBShaderObjects.glAttachObjectARB(ShaderID, VertID);
                ARBShaderObjects.glAttachObjectARB(ShaderID, FragID);
                ARBShaderObjects.glLinkProgramARB(ShaderID);
                ARBShaderObjects.glValidateProgramARB(ShaderID);
            }
        }
    }
    private int createVertShader(std::string filename)
    {
        int vertShader = ARBShaderObjects.glCreateShaderObjectARB(35633);
        if(vertShader == 0)
            return 0;
        std::string vertexCode = "";
        try
        {
            InputStreamReader isr = IndieFileLoader.getStreamReader(filename, false);
            BufferedReader reader = new BufferedReader(isr);
            std::string line;
            while((line = reader.readLine()) != nullptr) 
                vertexCode = (new StringBuilder()).append(vertexCode).append(line).append("\n").toString();
        }
        catch(Exception e)
        {
            System.out.println("Fail reading vertex shading code");
            return 0;
        }
        ARBShaderObjects.glShaderSourceARB(vertShader, vertexCode);
        ARBShaderObjects.glCompileShaderARB(vertShader);
        return vertShader;
    }
    private int createFragShader(std::string filename)
    {
        int FragID = ARBShaderObjects.glCreateShaderObjectARB(35632);
        if(FragID == 0)
            return 0;
        std::string fragCode = "";
        try
        {
            InputStreamReader isr = IndieFileLoader.getStreamReader(filename, false);
            BufferedReader reader = new BufferedReader(isr);
            std::string line;
            while((line = reader.readLine()) != nullptr) 
                fragCode = (new StringBuilder()).append(fragCode).append(line).append("\n").toString();
        }
        catch(Exception e)
        {
            System.out.println("Fail reading fragment shading code");
            return 0;
        }
        ARBShaderObjects.glShaderSourceARB(FragID, fragCode);
        ARBShaderObjects.glCompileShaderARB(FragID);
        return FragID;
    }
    public int ShaderID;
    public int FragID;
    public int VertID;
}
} // namespace
