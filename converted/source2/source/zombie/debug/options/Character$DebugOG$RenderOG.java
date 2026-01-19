package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Character$DebugOG$RenderOG extends OptionGroup {
   public final BooleanDebugOption AimCone = newDebugOnlyOption(this.Group, "AimCone", false);
   public final BooleanDebugOption Angle = newDebugOnlyOption(this.Group, "Angle", false);
   public final BooleanDebugOption TestDotSide = newDebugOnlyOption(this.Group, "TestDotSide", false);
   public final BooleanDebugOption DeferredMovement = newDebugOnlyOption(this.Group, "DeferredMovement", false);
   public final BooleanDebugOption DeferredAngles = newDebugOnlyOption(this.Group, "DeferredRotation", false);
   public final BooleanDebugOption TranslationData = newDebugOnlyOption(this.Group, "Translation_Data", false);
   public final BooleanDebugOption Bip01 = newDebugOnlyOption(this.Group, "Bip01", false);
   public final BooleanDebugOption PrimaryHandBone = newDebugOnlyOption(this.Group, "HandBones.Primary", false);
   public final BooleanDebugOption SecondaryHandBone = newDebugOnlyOption(this.Group, "HandBones.Secondary", false);
   public final BooleanDebugOption SkipCharacters = newDebugOnlyOption(this.Group, "SkipCharacters", false);
   public final BooleanDebugOption Vision = newDebugOnlyOption(this.Group, "Vision", false);
   public final BooleanDebugOption DisplayRoomAndZombiesZone = newDebugOnlyOption(this.Group, "DisplayRoomAndZombiesZone", false);
   public final BooleanDebugOption FMODRoomType = newDebugOnlyOption(this.Group, "FMODRoomType", false);

   public Character$DebugOG$RenderOG(IDebugOptionGroup var1) {
      super(var1, "Render");
   }
}
