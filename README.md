# hustle
BathTimeKirchhoff is an Arduino Environmental Control Project. 

The project is based on an Arduino Mega 2560 and the hardware below:
  -DS18B20 (Temperature)
  -DHT11 (Temperature & Humidity)
  -MQ-7 (Carbon Monoxide)
  -Buzzer
  -Adafruit p2050 tft 3,5" touchscreen
  -8x250V relay board
  -DS3231 Real Time Clock
  -SD card
  -DIY PCB board 
 
The aim of this project is to collect Temperature, Humidity and Carbon Monoxide measurements from the environment, 
print the measurements on the touchscreen, control 4x250V relays manually, control the room temperature by a PID controller and 4x250V 
relyas and plot the collected data. 

MainScreen: 
  On the MainScreen the data collected from the environment are printed. In addition, the user is able to set the SetPoint of the PID
  in order to control room temperature via the 4x250V relays. Using the touchscreen the rest 4x250V relays can be controlled manually.
  
ParamScreen: 
  The ParamScreen is accessed by touching the PARAM Button of the MainScreen thus the user is able to change the values of Kp, Ki and Kd
  in order to calibrate the PID's behaviour. For the calibration the user has to touch one or more numeric fields and then touch the arrow buttons.
  The chosen numeric fields will change their values by the step  written on the Stp numeric field. 
  NOTE: When a field is selected its outline turns green.

LogScreen:
  The LogScreen is accessed by touching the LOG button of the ParamScreen. On the LogScreen the time and date are printed. In addition, the system
  temperature-time or humidity-time plots can be printed. (This part is still under developement)
  NOTE: Before the first use, the user has to calibrate the real time clock on his/her local time!
