// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package astar.tests;

import astar.IGoalNode;
import astar.ISearchNode;

public class GoalNodeCity implements IGoalNode {
    private String name;

    public GoalNodeCity(String string) {
        this.name = string;
    }

    @Override
    public boolean inGoal(ISearchNode iSearchNode) {
        return iSearchNode instanceof SearchNodeCity searchNodeCity ? this.name == searchNodeCity.getName() : false;
    }
}
