#ifndef MyTypes_h
#define MyTypes_h

#include <Arduino.h>

//----------- TOUCHSCREEN -----------------
typedef struct MainScreenObjects {
 uint16_t x_num1 = 150, y_num1 = 25, step_num1 = 50, h_num1 = 40, w_num1 = 70; //1st Column Numerical Fields
 uint16_t y_line = 50;
 uint16_t x_text1 = 10, y_text1 = 40, step_text1 = 50;                  // 1st Column Text Fields
 uint16_t x_text2 = 250;  // 2nd Column Text Field
 uint16_t xPID = 390, yPID = 25, wPID = 80, hPID = 40;                  // PID Field
 uint16_t xRr = 270, yRr = 125, wRr = 85, hRr = 50;                     //2nd Column RIGHT Button (Rect Buttons xRr -> x Rect Right, xRl -> x Rect left)
 uint16_t xRl = 365, yRl = 125, wRl = 85, hRl = 50;                     // 2nd columnd LEFT Button
 uint16_t xParam = 270, yParam = 180, wParam = 180, hParam = 50;        // PARAM Button
 uint16_t x_circle, r = 20, y_circle = 290;                             //Circles for Relays Visualization ( x_circle = = x_max / 9)
 uint16_t x0, y0, x1, y1, x2, y2;                                       // Triangle Edges Coordinants
 int a = 20;                                                            // Pleura Trigwnou  
} MainScreenObjects;

typedef struct ParamScreenObjects {
   
  uint16_t xClose = 290, yClose = 250 , wClose = 170, hClose = 50; // Close Button on Param Screen
  uint16_t  hParam = 40, wParam = 70, stepParam = 50;
  uint16_t xKp_txt = 10, yKp_txt = 40, xKi_txt = xKp_txt, yKi_txt = yKp_txt + stepParam, xKd_txt = xKi_txt, yKd_txt = yKi_txt + stepParam;  
  uint16_t xKp_num = 100, yKp_num = 25, xKi_num = xKp_num, yKi_num = yKp_num + stepParam, xKd_num = xKi_num, yKd_num = yKi_num + stepParam;
  uint16_t xRr = 290, yRr = 190, wRr = 80, hRr = 50; //2nd Column RIGHT Button (Rect Buttons xRr -> x Rect Right, xRl -> x Rect left)
  uint16_t xRl = 380, yRl = 190, wRl = 80, hRl = 50; // 2nd columnd LEFT Button
  uint16_t xStep_txt = xKd_txt, yStep_txt = yKd_txt + stepParam;
  uint16_t xStep_num = xKd_num, yStep_num = yKd_num + stepParam; 
  uint16_t x0, y0, x1, y1, x2, y2; // Triangle Edges Coordinants
  int a = 20; // Pleura Trigwnou
  uint16_t xLOG = xClose, yLOG = 130, wLOG = wClose, hLOG = hClose;
  uint16_t xPID = xLOG, yPID = 70, wPID = wLOG, hPID = hLOG;
  bool PIDstate = false;
} ParamScreenObject;

typedef struct Measurements {
  float Temp_DHT; // in C
  float Humid;
  int Co;
  float Temp_DS;
  double PID_SetPoint; 
} Measurements;

typedef struct LogScreenObjects{
  uint16_t xExit = 290, yExit = 250 , wExit = 170, hExit = 50; // Close Button on Log Screen
  uint16_t xTemp = 20, yTemp = 250, wTemp = 125, hTemp = 50;
  uint16_t xHum = 155, yHum = 250, wHum = 125, hHum = 50;
} LogScreenObjects;  

#endif
