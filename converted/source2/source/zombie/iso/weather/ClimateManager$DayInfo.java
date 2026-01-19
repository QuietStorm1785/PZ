package zombie.iso.weather;

import java.util.GregorianCalendar;
import zombie.erosion.season.ErosionSeason;

public class ClimateManager$DayInfo {
   public int day;
   public int month;
   public int year;
   public int hour;
   public int minutes;
   public long dateValue;
   public GregorianCalendar calendar;
   public ErosionSeason season;

   public void set(int var1, int var2, int var3) {
      this.calendar = new GregorianCalendar(var3, var2, var1, 0, 0);
      this.dateValue = this.calendar.getTime().getTime();
      this.day = var1;
      this.month = var2;
      this.year = var3;
   }

   public int getDay() {
      return this.day;
   }

   public int getMonth() {
      return this.month;
   }

   public int getYear() {
      return this.year;
   }

   public int getHour() {
      return this.hour;
   }

   public int getMinutes() {
      return this.minutes;
   }

   public long getDateValue() {
      return this.dateValue;
   }

   public ErosionSeason getSeason() {
      return this.season;
   }
}
