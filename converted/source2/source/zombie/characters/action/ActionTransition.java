package zombie.characters.action;

import java.util.ArrayList;
import java.util.List;
import org.w3c.dom.Element;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.core.Core;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.debug.DebugType;
import zombie.network.GameClient;
import zombie.util.Lambda;
import zombie.util.PZXmlUtil;
import zombie.util.StringUtils;

public final class ActionTransition implements Cloneable {
   String transitionTo;
   boolean asSubstate;
   boolean transitionOut;
   boolean forceParent;
   final List<IActionCondition> conditions = new ArrayList<>();

   public static boolean parse(Element var0, String var1, List<ActionTransition> var2) {
      if (var0.getNodeName().equals("transitions")) {
         parseTransitions(var0, var1, var2);
         return true;
      } else if (var0.getNodeName().equals("transition")) {
         parseTransition(var0, var2);
         return true;
      } else {
         return false;
      }
   }

   public static void parseTransition(Element var0, List<ActionTransition> var1) {
      var1.clear();
      ActionTransition var2 = new ActionTransition();
      if (var2.load(var0)) {
         var1.add(var2);
      }
   }

   public static void parseTransitions(Element var0, String var1, List<ActionTransition> var2) {
      var2.clear();
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var0, var1, var2, (var0x, var1x, var2x) -> {
         if (!var0x.getNodeName().equals("transition")) {
            DebugLog.ActionSystem.warn("Warning: Unrecognised element '" + var0x.getNodeName() + "' in " + var1x);
         } else {
            ActionTransition var3 = new ActionTransition();
            if (var3.load(var0x)) {
               var2x.add(var3);
            }
         }
      });
   }

   private boolean load(Element var1) {
      try {
         PZXmlUtil.forEachElement(var1, var1x -> {
            try {
               String var2 = var1x.getNodeName();
               if ("transitionTo".equalsIgnoreCase(var2)) {
                  this.transitionTo = var1x.getTextContent();
               } else if ("transitionOut".equalsIgnoreCase(var2)) {
                  this.transitionOut = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("forceParent".equalsIgnoreCase(var2)) {
                  this.forceParent = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("asSubstate".equalsIgnoreCase(var2)) {
                  this.asSubstate = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("conditions".equalsIgnoreCase(var2)) {
                  PZXmlUtil.forEachElement(var1x, var1xx -> {
                     IActionCondition var2x = IActionCondition.createInstance(var1xx);
                     if (var2x != null) {
                        this.conditions.add(var2x);
                     }
                  });
               }
            } catch (Exception var3x) {
               DebugLog.ActionSystem.error("Error while parsing xml element: " + var1x.getNodeName());
               DebugLog.ActionSystem.error(var3x);
            }
         });
         return true;
      } catch (Exception var3) {
         DebugLog.ActionSystem.error("Error while loading an ActionTransition element");
         DebugLog.ActionSystem.error(var3);
         return false;
      }
   }

   public String getTransitionTo() {
      return this.transitionTo;
   }

   public boolean passes(ActionContext var1, int var2) {
      for (int var3 = 0; var3 < this.conditions.size(); var3++) {
         IActionCondition var4 = this.conditions.get(var3);
         if (!var4.passes(var1, var2)) {
            return false;
         }
      }

      if (Core.bDebug
         && GameClient.bClient
         && (
            DebugOptions.instance.MultiplayerShowPlayerStatus.getValue() && var1.getOwner() instanceof IsoPlayer && !((IsoPlayer)var1.getOwner()).isGodMod()
               || DebugOptions.instance.MultiplayerShowZombieStatus.getValue() && var1.getOwner() instanceof IsoZombie
         )) {
         StringBuilder var6 = new StringBuilder("Character ")
            .append(var1.getOwner().getClass().getSimpleName())
            .append(" ")
            .append("id=")
            .append(var1.getOwner().getOnlineID())
            .append(" transition to \"")
            .append(this.transitionTo)
            .append("\":");

         for (IActionCondition var5 : this.conditions) {
            var6.append(" [").append(var5.getDescription()).append("]");
         }

         DebugLog.log(DebugType.ActionSystem, var6.toString());
      }

      return true;
   }

   public ActionTransition clone() {
      ActionTransition var1 = new ActionTransition();
      var1.transitionTo = this.transitionTo;
      var1.asSubstate = this.asSubstate;
      var1.transitionOut = this.transitionOut;
      var1.forceParent = this.forceParent;

      for (IActionCondition var3 : this.conditions) {
         var1.conditions.add(var3.clone());
      }

      return var1;
   }
}
