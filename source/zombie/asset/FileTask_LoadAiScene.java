// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.asset;

import jassimp.AiPostProcessSteps;
import jassimp.Jassimp;
import java.util.EnumSet;
import zombie.fileSystem.FileSystem;
import zombie.fileSystem.FileTask;
import zombie.fileSystem.IFileTaskCallback;

public final class FileTask_LoadAiScene extends FileTask {
    String m_filename;
    EnumSet<AiPostProcessSteps> m_post_process_step_set;

    public FileTask_LoadAiScene(String string, EnumSet<AiPostProcessSteps> enumSet, IFileTaskCallback iFileTaskCallback, FileSystem fileSystem) {
        super(fileSystem, iFileTaskCallback);
        this.m_filename = string;
        this.m_post_process_step_set = enumSet;
    }

    @Override
    public String getErrorMessage() {
        return this.m_filename;
    }

    @Override
    public void done() {
        this.m_filename = null;
        this.m_post_process_step_set = null;
    }

    @Override
    public Object call() throws Exception {
        return Jassimp.importFile(this.m_filename, this.m_post_process_step_set);
    }
}
