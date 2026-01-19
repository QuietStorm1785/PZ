package zombie.core.skinnedmodel.advancedanimation;

import javax.xml.bind.annotation.XmlTransient;
import zombie.core.skinnedmodel.advancedanimation.AnimEvent.AnimEventTime;

public final class AnimEvent {
   public String m_EventName;
   public AnimEventTime m_Time = AnimEventTime.Percentage;
   public float m_TimePc;
   public String m_ParameterValue;
   @XmlTransient
   public String m_SetVariable1;
   @XmlTransient
   public String m_SetVariable2;

   @Override
   public String toString() {
      return String.format("%s { %s }", this.getClass().getName(), this.toDetailsString());
   }

   public String toDetailsString() {
      return String.format(
         "Details: %s %s, time: %s",
         this.m_EventName,
         this.m_ParameterValue,
         this.m_Time == AnimEventTime.Percentage ? Float.toString(this.m_TimePc) : this.m_Time.name()
      );
   }
}
