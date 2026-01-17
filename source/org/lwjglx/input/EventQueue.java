// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package org.lwjglx.input;

class EventQueue {
    private int maxEvents = 32;
    private int currentEventPos = -1;
    private int nextEventPos = 0;

    EventQueue(int int0) {
        this.maxEvents = int0;
    }

    void add() {
        this.nextEventPos++;
        if (this.nextEventPos == this.maxEvents) {
            this.nextEventPos = 0;
        }

        if (this.nextEventPos == this.currentEventPos) {
            this.currentEventPos++;
            if (this.currentEventPos == this.maxEvents) {
                this.currentEventPos = 0;
            }
        }
    }

    boolean next() {
        if (this.currentEventPos == this.nextEventPos - 1) {
            return false;
        } else if (this.nextEventPos == 0 && this.currentEventPos == this.maxEvents - 1) {
            return false;
        } else {
            this.currentEventPos++;
            if (this.currentEventPos == this.maxEvents) {
                this.currentEventPos = 0;
            }

            return true;
        }
    }

    int getMaxEvents() {
        return this.maxEvents;
    }

    int getCurrentPos() {
        return this.currentEventPos;
    }

    int getNextPos() {
        return this.nextEventPos;
    }
}
