package zombie.debug;

import java.util.ArrayList;
import javax.xml.bind.annotation.XmlRootElement;
import zombie.debug.DebugOptionsXml.OptionNode;

@XmlRootElement
final class DebugOptionsXml {
   public boolean setDebugMode = false;
   public boolean debugMode = true;
   public final ArrayList<OptionNode> options = new ArrayList<>();
}
