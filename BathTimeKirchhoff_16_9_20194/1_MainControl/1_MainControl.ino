//------- LIBRARIES ----------------
  #include <SPI.h>
  #include <Adafruit_HX8357.h>
  #include <Adafruit_GFX.h>
  #include <TouchScreen.h>
  #include <OneWire.h>
  #include <DallasTemperature.h>
  #include <DHT.h>
  #include <PID_v1.h>
  #include "MyTypes.h"
  #include <DS3231.h>
  #include <Wire.h>
  #include <SD.h>
  

//------ SCREEN COLORS -----------
  #define LTBLUE          0xB6DF
  #define LTTEAL          0xBF5F
  #define LTGREEN         0xBFF7
  #define LTCYAN          0xC7FF
  #define LTRED           0xFD34
  #define LTMAGENTA       0xFD5F
  #define LTYELLOW        0xFFF8
  #define LTORANGE        0xFE73
  #define LTPINK          0xFDDF
  #define LTPURPLE        0xCCFF
  #define LTGREY          0xE71C
  
  #define BLUE            0x001F
  #define TEAL            0x0438
  #define GREEN           0x07E0
  #define CYAN            0x07FF
  #define RED             0xF800
  #define MAGENTA         0xF81F
  #define YELLOW          0xFFE0
  #define ORANGE          0xFD20
  // #define PINK          0xF81F
  #define PURPLE          0x801F
  #define GREY            0xC618
  #define WHITE           0xFFFF
  #define BLACK           0x0000
  
  #define DKBLUE          0x000D
  #define DKTEAL          0x020C
  #define DKGREEN         0x03E0
  #define DKCYAN          0x03EF
  #define DKRED           0x6000
  #define DKMAGENTA       0x8008
  #define DKYELLOW        0x8400
  #define DKORANGE        0x8200
  #define DKPINK          0x9009
  #define DKPURPLE        0x4010
  #define DKGREY          0x4A49

//---------- DEFINITIONS ----------------
  // DHT11 Definitions
    #define DHTPIN 23              
    #define DHTTYPE DHT11
    DHT dht(DHTPIN, DHTTYPE);
    double *TodaysMeanTemp[24];
   
  //CO Sensor
    const int AOUTpin= A7;             
    const int DOUTpin=25;
    const int Buzzer =24;
   
  //DS18B20 Temperature sensor
    #define ONE_WIRE_BUS 22                // DS18B20 Definitions .Data wire is plugged into pin 2 on the Arduino
    OneWire oneWire(ONE_WIRE_BUS);          // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
    DallasTemperature sensors(&oneWire);   // Pass our oneWire reference to Dallas Temperature. 
    unsigned long prevTimeTemp = 0;
    unsigned long measurementDelay = 600000;
    unsigned long timeTemp;

  //TFT TouchScreen
    #define TFT_CS 53
    #define TFT_DC 48
    #define SD_CS 42
    #define YP A2
    #define XM A1
    #define XP 46
    #define YM 44
    #define TS_MINX 125 // This is calibration data for the raw touch data to the screen coordinates
    #define TS_MINY 70
    #define TS_MAXX 899
    #define TS_MAXY 925
    #define MINPRESSURE 100
    #define MAXPRESSURE 1000
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 278); // For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it
    Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC);
    int ScreenIndex = 0; // 0 : MainScreen, 1: LogScreen
    bool GreenFlag[4] = {false, false, false ,false};
    bool *ParamsGreenFlag[4];
    MainScreenObjects *MainScrObj, MainScr;
    ParamScreenObjects *ParamScrObj, ParamScr;
    LogScreenObjects *LogScrObj, LogScr;
    int ChoosePlot;

  //Relays Definitions
    #define Relay_1 28
    #define Relay_2 30
    #define Relay_3 32
    #define Relay_4 34
    #define Relay_5 29
    #define Relay_6 31
    #define Relay_7 33
    #define Relay_8 35 
    bool RelaysStateFlag  [8] = {false, false, false, false, false, false, false, false};
    int  Relays[8] = {Relay_1, Relay_2, Relay_3, Relay_4, Relay_5, Relay_6, Relay_7, Relay_8};

  // PID Control 
    int NumOfFan;
    double PID_Params[4] = {2.0, 2.0, 2.0, 0.1}; // Kp, Ki, Kd, Step
    double PID_SetPoint = 0, PID_Input, PID_Output;
    PID myPID(&PID_Input, &PID_Output, &PID_SetPoint, PID_Params[0], PID_Params[1], PID_Params[2], REVERSE);

  //prev Values
    float prevTemp_DS = 0.0,  prevTemp_DHT = 0.0, prevPID = 0.0, prevHumid = 0.0 ;
    int prevCo = 0;

  //Tolerances 
    float ToleranceTemp = 0.3, ToleranceHumid = 1.0;
    int ToleranceCo = 30;

  //Clock
    DS3231 Clock;
    bool Century=false;
    bool h12;
    bool PM;
    unsigned long timeSec, prevSec = 0; 

  //Variables
     Measurements *ptrMeas, meas, *ptrMeanValues, MeanValues;
  
  // SD card
  File MeanValuesPerHour;

  //Timer
  unsigned long Timer, prevTimer = 0; 


//-----------PROGRAM-------------------------------
void setup() {
  Serial.begin(115200);
  //TFT
  tft.begin(HX8357D);
  tft.fillScreen(BLACK); 
  tft.setRotation(3);
  sensors.begin();
  Serial.println("Touch Screen!");
  MainScrObj = &MainScr;
  ParamScrObj= &ParamScr;
  LogScrObj = &LogScr;
  SetUp_MainScreen(MainScrObj);
  ScreenIndex = 0;
   for(int i = 0; i <=3; i++){
  ParamsGreenFlag[i] = &GreenFlag[i];
  }
  
   // TODO : FOROS TIMIS STON MASTORA
   ptrMeas = &meas;
   ptrMeanValues = &MeanValues;
  //DHT11
  dht.begin();
  
  //CO
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
  pinMode(Buzzer, OUTPUT);//sets the pin as an output of the arduino
  
  //Ds18B20 first meas  
  ptrMeas->Temp_DS = Temperature(); // Take Temp measurement for the first time because void loop takes temp measurements every 10min
  
  //PID SetUp
  ptrMeas->PID_SetPoint = round(dht.readTemperature()); //PID_SetPoint initialization 
  PID_SetPoint = ptrMeas->PID_SetPoint;
  PID_Input = dht.readTemperature();
  myPID.SetMode(AUTOMATIC); //Turn the PID on

  //Clock
  Wire.begin();


  //SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }
  Serial.println("SD is OK!");

  //Mean Value Struct initialization
  ptrMeanValues->Temp_DHT = 0;
  ptrMeanValues->Temp_DHT = 0;
  ptrMeanValues->PID_SetPoint = 0;
  ptrMeanValues->Humid = 0;
  ptrMeanValues->Co = 0;
}

//---------LOOP--------------------------------
  void loop(){
  //Check for pressure on the screen
  // WARNING: The 0,0 of TouchScreen is Different from the 0,0 of TFT!!!
  // Retrieve a point  
    TSPoint p = ts.getPoint();
    
    
  if(p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    Serial.println("Pressure Detected");
     int tftAction = ReadTouchScreen(MainScrObj, ParamScrObj, LogScrObj, ScreenIndex);          
          switch(tftAction){
             case 1:
              ptrMeas->PID_SetPoint++;
               break;
             case 2:
               ptrMeas->PID_SetPoint--;
               break;
             case 3:
               SetUp_ParamScreen(ParamScrObj);
               refresh_ParamScreen_Values( ParamScrObj, PID_Params[0], PID_Params[1], PID_Params[2], PID_Params[3]);
               ScreenIndex = 1;
               break;  
             case 4:
               RelaysControl(); // Yparxei kapoio Kuklomatiko Problima me ta Relay, i prokaloun braxykukloma i mia ptosi tasis pou kanei restart stin othoni
               break;
             case 5:
              SetUp_MainScreen(MainScrObj);
              refresh_MainScreen_Values(MainScrObj, ptrMeas, 0);
              ScreenIndex = 0;
              break;
             case 6:
              for(int i = 0; i <= 3; i++){
                if(*ParamsGreenFlag[i]){
                if(i != 3){
                     PID_Params[i] = PID_Params[i] - PID_Params[3];        
                  }else{
                     PID_Params[i] = PID_Params[i] - 0.01;
                  }
                }
              }
              refresh_ParamScreen_Values(ParamScrObj, PID_Params[0], PID_Params[1], PID_Params[2], PID_Params[3]);
              myPID.SetTunings(PID_Params[0], PID_Params[1], PID_Params[2]); 
              break;
             case 7:
              for(int i = 0; i <= 3; i++){
                if(*ParamsGreenFlag[i]){
                  if(i != 3){
                     PID_Params[i] = PID_Params[i] + PID_Params[3];        
                  }else{
                     PID_Params[i] = PID_Params[i] + 0.01;
                  }
                }
              }
              refresh_ParamScreen_Values(ParamScrObj, PID_Params[0], PID_Params[1], PID_Params[2], PID_Params[3]);
              myPID.SetTunings(PID_Params[0], PID_Params[1], PID_Params[2]);
              break;
            case 8:
              SetUp_LogScreen(LogScrObj);
              Refresh_Clock();
              ScreenIndex = 2;
              break;
            case 9:
              ChoosePlot = 0;
              SetUp_LogScreen(LogScrObj);
              PlotByDate(ChoosePlot);
              break;
            case 10:
              ChoosePlot = 1;
              SetUp_LogScreen(LogScrObj);
              PlotByDate(ChoosePlot);
              break;
         }              
   

  }else{
        // Read Sensors
         timeTemp = millis();                          //Chose to take measurements from DS18B20 every 10 minites as it inserts latency on TouchScreen response if we take measurements on every loop
         if(timeTemp > (prevTimeTemp + measurementDelay)){
               ptrMeas->Temp_DS = Temperature();
               prevTimeTemp = millis();
         }
         
         ptrMeas->Temp_DHT = dht.readTemperature(); // in C
         ptrMeas->Humid = dht.readHumidity();
         ptrMeas->Co = monoxide(AOUTpin, DOUTpin, Buzzer);  

           
         
         //Serial.print("PID bool state: ");
         //Serial.println(ParamScrObj->PIDstate);
         //TODO control fans according to PID_Output  
        
         if(ParamScrObj->PIDstate){
           PID_SetPoint = ptrMeas->PID_SetPoint;
           PID_Input = ptrMeas->Temp_DHT;
           myPID.Compute();

           if(PID_Output == 0){
              NumOfFan = 0;             //Do not turn on any fan
           }else if(PID_Output < 63){           
              NumOfFan = 1;             //turn on 1 fan
           }else if(PID_Output <120){            
              NumOfFan = 2;              //turn on 2 fan           
           }else if(PID_Output < 180){            
              NumOfFan = 3;              //turn on 3 fan            
           }else{            
              NumOfFan = 4;              //turn on 4 fan                
           }
            Serial.print("ScreenIndex: "); //delete it
            Serial.println(ScreenIndex); //delete it
           if(ScreenIndex == 0){
             for(int i = 0; i <= (NumOfFan - 1); i++){
                RelaysStateFlag[i] = true;             
              }
              for(int i = NumOfFan; i <= 3; i++){
                RelaysStateFlag[i] = false;             
              }
              refresh_PID_indication(MainScrObj);                
           }
           RelaysControl();
           //refresh_PID_indication(MainScrObj);            
         }

         Serial.print("PID_OUTPUT: "); //delete it
         Serial.println(PID_Output); //delete it
         Serial.print("NumOfFan: "); //delete it
         Serial.println(NumOfFan); //delete it
         
             
      }

   //refresh tft if you read different measurements
    if((ScreenIndex == 0)&&(abs(ptrMeas->Temp_DS - prevTemp_DS) > ToleranceTemp || abs(ptrMeas->Temp_DHT - prevTemp_DHT) > ToleranceTemp || abs(ptrMeas->Humid - prevHumid) > ToleranceHumid || abs(ptrMeas->Co - prevCo) > ToleranceCo || abs(ptrMeas->PID_SetPoint - prevPID) > 0)){
         Serial.println("refresh_Main_Screen_Values");
         refresh_MainScreen_Values(MainScrObj, ptrMeas, 0);
    }
   
    //Set previous values
    prevTemp_DS = ptrMeas->Temp_DS;
    prevTemp_DHT = ptrMeas->Temp_DHT;
    prevHumid = ptrMeas->Humid;
    prevCo = ptrMeas->Co;
    prevPID = ptrMeas->PID_SetPoint; 

    //refresh clock if you are on LogScreen
    timeSec = millis();
    if((ScreenIndex == 2) && (timeSec >= prevSec + 1000)){
      Refresh_Clock();
      prevSec = timeSec;
    }

    //StoreValues
     StoreMeanValues(ptrMeas, ptrMeanValues);
                 
}

  
