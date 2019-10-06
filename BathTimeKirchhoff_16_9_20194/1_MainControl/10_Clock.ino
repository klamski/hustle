//--------------------- REFRESH CLOCK ON SCREEN -----------------------------------
void Refresh_Clock(){
  bool Century=false;
  bool h12;
  bool PM;
  tft.fillRect( 9, 9, 250, 20, BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(WHITE); 
  tft.setTextSize(1);
  
  tft.print("2");
  if (Century) {      // Won't need this for 89 years.
    tft.print("1");
  } else {
    tft.print("0");
  }
 
  tft.print(Clock.getYear());
  tft.print('/');
  // then the month
  tft.print(Clock.getMonth(Century));
  tft.print('/');
  // then the date
  tft.print(Clock.getDate());
  tft.print(' ');
  // and the day of the week
  tft.print(Clock.getDoW());
  tft.print(' ');
  // Finally the hour, minute, and second
  tft.print(Clock.getHour(h12, PM), DEC);
  tft.print(':');
  tft.print(Clock.getMinute(), DEC);
  tft.print(':');
  tft.print(Clock.getSecond(), DEC);
  // Add AM/PM indicator
  if (h12) {
    if (PM) {
      tft.print(" PM ");
    } else {
      tft.print(" AM ");
    }
  } else {
    tft.print(" 24h ");
  }
  // Display the temperature
  tft.print("T=");
  tft.print(Clock.getTemperature(), 2);
  // Tell whether the time is (likely to be) valid
  if (Clock.oscillatorCheck()) {
    tft.print(" O+");
  } else {
    tft.print(" O-");
  }
} 

//----------------- 10 MINUTES PASSED ----------------------------------------------
bool deltaTimePassed(byte deltaTime){
   static byte targetMin = Clock.getMinute();
   bool output;
   if(Clock.getMinute() == targetMin){
     Serial.print("----Perasan deka lepta-----");
     Serial.println(targetMin);
     targetMin = Clock.getMinute() + deltaTime;
     if(targetMin >= 60){
       targetMin = targetMin - 60;
     }
      output = true;
   }
   else{
    output = false;
   }
   return output;
}
 //-----------------AN HOUR PASSED -------------------------------------------------
bool anHourPassed(bool *TimeFlag){
    bool Century=false;
    bool h12;
    bool PM;
    static byte currentHour = Clock.getHour(h12, PM);
   // Serial.println("current hour from ten aHourPassed");
   // Serial.println(currentHour);
    if( Clock.getHour(h12, PM) != currentHour){        
       currentHour = Clock.getHour(h12, PM);
       *TimeFlag = true;
       return true;
    }
    else{
        return false;
    }

}

//---------------A DAY PASSED ----------------------------------------------------
bool aDayPassed(){
    static byte currentDate = Clock.getDate();

    if( Clock.getDate() != currentDate){
        currentDate = Clock.getDate();
        return true;
    }
    else{
        return false;
    }

}

//------------------------ A MIN PASSED ------------------------------------
bool aMinPassed(){
    static byte currentMin = Clock.getMinute();
    bool output;
    if(Clock.getMinute() != currentMin){
        currentMin = Clock.getMinute();
        output = true;
    }
    else{
        output = false;
    }
    return output;
}

//-----------FIND DATE----------------------
String DateInString(){
  String DDMMYY = "";
  bool century = false;
  DDMMYY = Clock.getDate();
  DDMMYY += "/";
  DDMMYY += Clock.getMonth(century);
  DDMMYY += "/";
  DDMMYY += "20";
  DDMMYY += Clock.getYear();
  return DDMMYY;
}