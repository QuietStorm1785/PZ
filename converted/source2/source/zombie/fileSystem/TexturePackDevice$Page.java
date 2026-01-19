package zombie.fileSystem;

import java.util.ArrayList;
import zombie.core.textures.TexturePackPage.SubTextureInfo;

final class TexturePackDevice$Page {
   String m_name;
   boolean m_has_alpha = false;
   long m_png_start = -1L;
   final ArrayList<SubTextureInfo> m_sub = new ArrayList<>();
}
