#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   IdleState.java
namespace zombie {
namespace ai {
namespace states {
#include "State.h"
class IdleState : public State {
public:
{
    public IdleState()
    {
    }
    public static IdleState instance()
    {
        return _instance;
    }
    public void execute(Character character)
    {
    }
    static IdleState _instance = new IdleState();
}} // namespace
