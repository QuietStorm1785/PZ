// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.model.jassimp;

import jassimp.AiMesh;

public class ImportedSkeletonParams extends ProcessedAiSceneParams {
    AiMesh mesh = null;

    ImportedSkeletonParams() {
    }

    public static ImportedSkeletonParams create(ProcessedAiSceneParams processedAiSceneParams, AiMesh aiMesh) {
        ImportedSkeletonParams importedSkeletonParams = new ImportedSkeletonParams();
        importedSkeletonParams.set(processedAiSceneParams);
        importedSkeletonParams.mesh = aiMesh;
        return importedSkeletonParams;
    }
}
