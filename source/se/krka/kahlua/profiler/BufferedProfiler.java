// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package se.krka.kahlua.profiler;

import java.util.ArrayList;
import java.util.List;

public class BufferedProfiler implements Profiler {
    private final List<Sample> buffer = new ArrayList<>();

    @Override
    public void getSample(Sample sample) {
        this.buffer.add(sample);
    }

    public void sendTo(Profiler profiler) {
        for (Sample sample : this.buffer) {
            profiler.getSample(sample);
        }
    }
}
