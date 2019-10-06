//----------------- STORE MEAN VALUES PER HOUR (TAKE A MEASUREMENT EVERY 10 MIN)----------------------
void StoreMeanValues(Measurements *val, Measurements *mean){
    static int i = 0;
    static bool TimeFlag = false, *ptrAnHourPassed = &TimeFlag; 
   
      if((deltaTimePassed(10)) && !anHourPassed(ptrAnHourPassed)){
        mean->Temp_DS = mean->Temp_DS + val->Temp_DS;
        mean->Temp_DHT = mean->Temp_DHT + val->Temp_DHT;
        mean->Humid = mean->Humid + val->Humid;
        mean->Co = mean->Co + val->Co;
        i++;
    }
    else if ( *ptrAnHourPassed){        
        mean->Temp_DS = mean->Temp_DS / i;
        mean->Temp_DHT = mean->Temp_DHT / i;
        mean->Humid = mean->Humid / i;
        mean->Co = mean->Co / i;
        WriteInFile(mean);
        *ptrAnHourPassed = false;
        mean->Temp_DS = 0; 
        mean->Temp_DHT = 0; 
        mean->Humid = 0; 
        mean->Co = 0; 
        i = 0; 
    }  
          
}


//------------------- WRITE IN A FILE ---------------------------------------
void WriteInFile(Measurements *meanVal){
    MeanValuesPerHour = SD.open("perHour.txt",FILE_WRITE);
    if(MeanValuesPerHour){
        Serial.print("Writing to perHour.txt...");

        bool Century=false;
        bool h12;
        bool PM;
        // the hour, minute, and second
        MeanValuesPerHour.print(Clock.getHour(h12, PM), DEC);
        MeanValuesPerHour.print(':');
        MeanValuesPerHour.print(Clock.getMinute(), DEC);
        MeanValuesPerHour.print(':');
        MeanValuesPerHour.print(Clock.getSecond(), DEC);
        MeanValuesPerHour.print(" ");
        // then the date
       MeanValuesPerHour.print(Clock.getDate());
       MeanValuesPerHour.print('/');
       // then the month
        MeanValuesPerHour.print(Clock.getMonth(Century));
        MeanValuesPerHour.print('/');
        //year
        MeanValuesPerHour.print("2");
        if (Century) {      // Won't need this for 89 years.
            MeanValuesPerHour.print("1");
        } else {
            MeanValuesPerHour.print("0");
        }
        MeanValuesPerHour.print(Clock.getYear());
        MeanValuesPerHour.println(" ");
       //write mean values
        MeanValuesPerHour.print("Ds18B20 Temp : ");
        MeanValuesPerHour.println(meanVal->Temp_DS);
        MeanValuesPerHour.print("DHT Temp : ");
        MeanValuesPerHour.println(meanVal->Temp_DHT);
        MeanValuesPerHour.print("DHT Humid : ");
        MeanValuesPerHour.println(meanVal->Humid);
        MeanValuesPerHour.print("Co : ");
        MeanValuesPerHour.println(meanVal->Co);              
        MeanValuesPerHour.close();
        Serial.println("done.");
     }
     else{
         // if the file didn't open, print an error:
         Serial.println("error opening test.txt");
     }

    MeanValuesPerHour = SD.open("perHour.txt");
     if(MeanValuesPerHour) {
         Serial.println("MeanValuesPerHour.txt:");

    // read from the file until there's nothing else in it:
         while (MeanValuesPerHour.available()) {
             Serial.write(MeanValuesPerHour.read());
        }
    // close the file:
        MeanValuesPerHour.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
}

//--------------------READ FROM FUCKIN FILE --------------------------
void ReadMeasByDate(String strDate, float *DHTTemp, float *DHTHumid){
   String dataString = "", TodaysDate = "";
   float parseReaded, Temp[24], Hum[24];
   int i = 0;
   bool RightDay = false;

   TodaysDate = strDate;
   MeanValuesPerHour = SD.open("perHour.txt"); // re-open the file for reading:

  if ( MeanValuesPerHour) {
    Serial.println("perHour.txt:");    

    while ( MeanValuesPerHour.available()) {                   // Read the file line per line
      dataString =  MeanValuesPerHour.readStringUntil('\n');   //read a line from file
      if(dataString.indexOf(TodaysDate) != -1){                      //Keep Todays Measurements
        RightDay = true;        
      }

      if(RightDay){
        if(dataString.indexOf("DHT Temp") != -1){              //Check if the line containts "DHT Temp"
          //Serial.println(dataString);
          dataString = dataString.substring(11);               //Ignore the first 11 characters
          Temp[i] = dataString.toFloat();                      //Parse the Float from String
          *DHTTemp = Temp[i];                                  //Save the Float         
          DHTTemp = DHTTemp + 1;
        }
        else if(dataString.indexOf("DHT Humid") != -1){
          //Serial.println(dataString);
          dataString = dataString.substring(12);               //Ignore the first 11 characters
          Hum[i] = dataString.toFloat();                      //Parse the Float from String
          *DHTHumid = Hum[i];                                  //Save the Float          
          DHTHumid = DHTHumid + 1;       
          RightDay = false;  
        }
         i++;
      }      
        
      if(i >= 24){
          i = 0; 
      }
    }
    Serial.println("Close File");
    MeanValuesPerHour.close();  // close the file:
  } else {    
    Serial.println("error opening perHour.txt"); // if the file didn't open, print an error:
  }
}


