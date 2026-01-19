package zombie.ui;

import zombie.characters.IsoSurvivor;
import zombie.characters.IsoZombie;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.areas.IsoBuilding;
import zombie.iso.objects.IsoRadio;
import zombie.iso.objects.IsoStove;
import zombie.network.GameServer;
import zombie.ui.TutorialManager.Stage;

public final class TutorialManager {
   public static boolean Debug = false;
   public boolean Active = false;
   public boolean ActiveControlZombies = false;
   public float TargetZombies = 0.0F;
   public Stage stage = Stage.getBelt;
   public IsoSurvivor wife = null;
   private IsoZombie zombie;
   public IsoStove tutorialStove;
   public IsoBuilding tutBuilding;
   public boolean DoorsLocked = true;
   public int BarricadeCount = 0;
   public String PrefMusic = null;
   public IsoSurvivor gunnut;
   public boolean StealControl = false;
   public int AlarmTime = 0;
   public boolean ProfanityFilter = false;
   public int Timer = 0;
   public int AlarmTickTime = 160;
   public boolean DoneFirstSleep = false;
   public boolean wifeKilledByEarl = false;
   public boolean warnedHammer = false;
   public boolean TriggerFire = false;
   public boolean CanDragWife = false;
   public boolean AllowSleep = false;
   public boolean skipped = false;
   private boolean bDoneDeath = false;
   boolean bDoGunnutDeadTalk = true;
   public String millingTune = "tune1.ogg";
   IsoRadio radio = null;
   public static TutorialManager instance = new TutorialManager();

   public boolean AllowUse(IsoObject var1) {
      return true;
   }

   public void CheckWake() {
   }

   public void CreateQuests() {
      try {
         for (int var1 = 0; var1 < IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().size(); var1++) {
            IsoObject var2 = (IsoObject)IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().get(var1);
            if (var2 instanceof IsoRadio) {
               this.radio = (IsoRadio)var2;
            }
         }
      } catch (Exception var3) {
         var3.printStackTrace();
         this.radio = null;
      }
   }

   public void init() {
      if (!GameServer.bServer) {
         if (this.Active) {
            ;
         }
      }
   }

   public void update() {
   }

   private void ForceKillZombies() {
      IsoWorld.instance.ForceKillAllZombies();
   }
}
