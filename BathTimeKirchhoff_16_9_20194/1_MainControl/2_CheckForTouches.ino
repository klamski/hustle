bool prevPressed = false; // TODO NA ginei POINTER GAMW TO SPITI
  
//------------- CHECK FOR TOUCHES ON SCREEN ------------------------------------------------------------
int ReadTouchScreen(MainScreenObjects *Main, ParamScreenObjects *Param, LogScreenObjects *Log, int ScreenIndex){
 uint16_t x_max = 480, y_max = 320; //Screen Borders
 uint16_t xKp_num = 100, yKp_num = 25;
 uint16_t xK_num = xKp_num, yK_num = yKp_num, wParam_num = 70, hParam_num = 40;    
 bool Green = true, White = false;
  
  //ScreenIndex: 0 MainScreen, 1 LogScreen
  // WARNING: The 0,0 of TouchScreen is Different from the 0,0 of TFT!!!
  // Retrieve a point  
  Serial.print(" ScreenIndex = ");
  Serial.println(ScreenIndex);
  TSPoint p = ts.getPoint();
  int responseMode = 0;
   
  // Scale from ~0->1000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
 // Serial.print("X = "); Serial.print(p.y);
 // Serial.print("\tY = "); Serial.print(p.x);
 // Serial.print("\tPressure = "); Serial.println(p.z); 
if( ScreenIndex == 0){
    Serial.println(" Read Main Screen's Touches");
    //----CHECK TOUCHES ON +- BUTTONS -------
    if(p.y < (tft.width()- Main->xRr) && p.y > (tft.width() - (Main->xRr+Main->wRr)) && p.x > Main->yRr && p.x < (Main->yRr + Main->hRr)){       
       Main->x0 = Main->xRr + (Main->wRr - Main->a)/2;
       Main->y0 = Main->yRr + (Main->hRr + Main->a)/2;
       Main->x1 = Main->x0 + Main->a/2;               //xRr + a/2;
       Main->y1 = Main->y0 - Main->a;                //yRr + (hRr + a)%2 + a;
       Main->x2 = Main->x0 + Main->a;                //xRr + (wRr - a);
       Main->y2 = Main->y0;                    //yRr + (hRr + a)%2;
   
       tft.fillRect(Main->xRr, Main->yRr, Main->wRr, Main->hRr, BLACK);
       tft.drawRect(Main->xRr, Main->yRr, Main->wRr, Main->hRr, WHITE);
       tft.fillTriangle( Main->x0, Main->y0, Main->x1, Main->y1, Main->x2, Main->y2, WHITE); 
       delay(200);
       tft.fillRect(Main->xRr, Main->yRr, Main->wRr, Main->hRr, WHITE);
       tft.fillTriangle( Main->x0, Main->y0, Main->x1, Main->y1, Main->x2, Main->y2, BLACK);
      responseMode = 1;
    }
    
    if(p.y < (tft.width()-Main->xRl) && p.y > (tft.width() - (Main->xRl+Main->wRl)) && p.x > Main->yRl && p.x < (Main->yRl + Main->hRl)){
       Main->x0 = Main->xRl + (Main->wRl - Main->a)/2;
       Main->y0 = Main->yRl + (Main->hRl - Main->a)/2;
       Main->x1 = Main->x0 + Main->a/2;
       Main->y1 = Main->y0 + Main->a;
       Main->x2 = Main->x0 + Main->a;
       Main->y2 = Main->y0;
       
       tft.fillRect(Main->xRl, Main->yRl, Main->wRl, Main->hRl, BLACK);
       tft.drawRect(Main->xRl, Main->yRl, Main->wRl, Main->hRl, WHITE);
       tft.fillTriangle( Main->x0, Main->y0, Main->x1, Main->y1, Main->x2, Main->y2, WHITE);
       delay(200);
       tft.fillRect(Main->xRl, Main->yRl, Main->wRl, Main->hRl, WHITE);
       tft.fillTriangle( Main->x0, Main->y0, Main->x1, Main->y1, Main->x2, Main->y2, BLACK);
       responseMode = 2;
    }
    //-----CHECK TOUCHES ON PARAM BUTTONS-----
     if(p.y < (tft.width()- Main->xParam) && p.y > (tft.width() - (Main->xParam + Main->wParam)) && p.x > Main->yParam && p.x < (Main->yParam + Main->hParam)){
      tft.fillRect(Main->xParam, Main->yParam, Main->wParam, Main->hParam, BLACK);
      tft.drawRect(Main->xParam, Main->yParam, Main->wParam, Main->hParam, WHITE);  
      tft.setCursor(Main->xParam + 1*Main->wParam/5, Main->yParam + 2*Main->hParam/6);
      tft.setTextColor(WHITE); 
      tft.setTextSize(3);
      tft.print(" PARAM");
      delay(200);
      tft.fillRect(Main->xParam, Main->yParam, Main->wParam, Main->hParam, WHITE); 
      tft.setCursor(Main->xParam + 1*(Main->wParam)/5, Main->yParam + 2*Main->hParam/6);
      tft.setTextColor(BLACK); 
      tft.setTextSize(3);
      tft.print(" PARAM");
      responseMode = 3;
    }
    //----CHECK TOUCHES ON RELAY BUTTONS------
    if(p.x < (Main->y_circle + Main->r) && p.x > (Main->y_circle - Main->r)){
      for(int i = 0; i <= 7; i++){
        if(p.y < (tft.width() - (i+1)*Main->x_circle + Main->r) && p.y > (tft.width() - (i+1)*Main->x_circle - Main->r)){
          if( !RelaysStateFlag[i]){
          tft.fillCircle((i+1)*Main->x_circle, Main->y_circle, Main->r, WHITE);
          RelaysStateFlag[i] = true;
          delay(200);        
        }else{
          tft.fillCircle((i+1)*Main->x_circle, Main->y_circle, Main->r - 1, BLACK);
          RelaysStateFlag[i] = false;
          delay(200);
          }
          responseMode = 4;
        }    
      }
    }
//-------CHECK TOUCHES ON PARAM SCREEN-----------
}else if (ScreenIndex == 1) {
  Serial.println("Read Param Screen Touches");

    //-----CHECK TOUCHES ON PIDon-off BUTTON-------
    if(p.y < (tft.width()-Param->xPID) && p.y > (tft.width() - (Param->xPID+Param->wPID)) && p.x > Param->yPID && p.x < (Param->yPID + Param->hPID)){
      if(Param->PIDstate){
      tft.fillRect(Param->xPID, Param->yPID, Param->wPID, Param->hPID, BLACK);
      tft.drawRect(Param->xPID, Param->yPID, Param->wPID, Param->hPID, WHITE);   
      tft.setCursor(Param->xPID + 2*Param->wPID/10, Param->yPID + 2*Param->hPID/6);
      tft.setTextColor(WHITE); 
      tft.setTextSize(3);
      tft.print("PID off");
      delay(200);      
      }else{
        tft.fillRect(Param->xPID, Param->yPID, Param->wPID, Param->hPID, WHITE);
        tft.drawRect(Param->xPID, Param->yPID, Param->wPID, Param->hPID, WHITE);   
        tft.setCursor(Param->xPID + 2*Param->wPID/10, Param->yPID + 2*Param->hPID/6);
        tft.setTextColor(BLACK); 
        tft.setTextSize(3);
        tft.print("PID on");
        delay(200);
      }
      Param->PIDstate = !Param->PIDstate;
      
    }
    //----CHECK TOUCHES ON EXIT/CLOSE BUTTON------
   if(p.y < (tft.width()-Param->xClose) && p.y > (tft.width() - (Param->xClose+Param->wClose)) && p.x > Param->yClose && p.x < (Param->yClose + Param->hClose)){
     
    tft.fillRect(Param->xClose, Param->yClose, Param->wClose, Param->hClose, BLACK);
    tft.drawRect(Param->xClose, Param->yClose, Param->wClose, Param->hClose, WHITE);   
    tft.setCursor(Param->xClose + 3*Param->wClose/10, Param->yClose + 2*Param->hClose/6);
    tft.setTextColor(WHITE); 
    tft.setTextSize(3);
    tft.print("EXIT"); 
    delay(200);
    tft.fillRect(Param->xClose, Param->yClose, Param->wClose, Param->hClose, WHITE);   
    tft.setCursor(Param->xClose + 3*Param->wClose/10, Param->yClose + 2*Param->hClose/6);
    tft.setTextColor(BLACK); 
    tft.setTextSize(3);
    tft.print("EXIT"); 
    
    for(int i = 0; i <= 3; i++){  // RESET NUMERICAL FIELD BEFORE EXIT
    ParamsGreenFlag[i] = &White;
    }
      responseMode = 5;
    }
       //----CHECK TOUCHES ON +- BUTTONS------
    
        if(p.y < (tft.width()-Param->xRl) && p.y > (tft.width() - (Param->xRl+Param->wRl)) && p.x > Param->yRl && p.x < (Param->yRl + Param->hRl)){
               Param->x0 = Param->xRl + (Param->wRl - Param->a)/2;
               Param->y0 = Param->yRl + (Param->hRl - Param->a)/2;
               Param->x1 = Param->x0 + Param->a/2;
               Param->y1 = Param->y0 + Param->a;
               Param->x2 = Param->x0 + Param->a;
               Param->y2 = Param->y0;
               
               tft.fillRect(Param->xRl, Param->yRl, Param->wRl, Param->hRl, BLACK);
               tft.drawRect(Param->xRl, Param->yRl, Param->wRl, Param->hRl, WHITE);
               tft.fillTriangle( Param->x0, Param->y0, Param->x1, Param->y1, Param->x2, Param->y2, WHITE);
               delay(200);
               tft.fillRect(Param->xRl, Param->yRl, Param->wRl, Param->hRl, WHITE);
               tft.fillTriangle( Param->x0, Param->y0, Param->x1, Param->y1, Param->x2, Param->y2, BLACK);
               responseMode = 6;
        }
         if(p.y < (tft.width()-Param->xRr) && p.y > (tft.width() - (Param->xRr+Param->wRr)) && p.x > Param->yRr && p.x < (Param->yRr + Param->hRr)){
               Param->x0 = Param->xRr + (Param->wRr - Param->a)/2;
               Param->y0 = Param->yRr + (Param->hRr + Param->a)/2;
               Param->x1 = Param->x0 + Param->a/2;               //xRr + a/2;
               Param->y1 = Param->y0 -  Param->a;                //yRr + (hRr + a)%2 + a;
               Param->x2 = Param->x0 + Param->a;                //xRr + (wRr - a);
               Param->y2 = Param->y0;                    //yRr + (hRr + a)%2;
           
               tft.fillRect(Param->xRr, Param->yRr, Param->wRr, Param->hRr, BLACK);
               tft.drawRect(Param->xRr, Param->yRr, Param->wRr, Param->hRr, WHITE);
               tft.fillTriangle( Param->x0, Param->y0, Param->x1, Param->y1, Param->x2, Param->y2, WHITE); 
               delay(200);
               tft.fillRect(Param->xRr, Param->yRr, Param->wRr, Param->hRr, WHITE);
               tft.fillTriangle( Param->x0, Param->y0, Param->x1, Param->y1, Param->x2, Param->y2, BLACK);
              responseMode = 7;
         }
         //------CHECK TOUCHES ON LOG BUTTON -------------------
         if(p.y < (tft.width()-Param->xLOG) && p.y > (tft.width() - (Param->xLOG+Param->wLOG)) && p.x > Param->yLOG && p.x < (Param->yLOG+ Param->hLOG)){
             
            tft.fillRect(Param->xLOG, Param->yLOG, Param->wLOG, Param->hLOG, BLACK);
            tft.drawRect(Param->xLOG, Param->yLOG, Param->wLOG, Param->hLOG, WHITE);   
            tft.setCursor(Param->xLOG + 3*Param->wLOG/10, Param->yLOG + 2*Param->hLOG/6);
            tft.setTextColor(WHITE); 
            tft.setTextSize(3);
            tft.print("LOG"); 
            delay(200);
            tft.fillRect(Param->xLOG, Param->yLOG, Param->wLOG, Param->hLOG, WHITE);   
            tft.setCursor(Param->xLOG + 3*Param->wLOG/10, Param->yLOG + 2*Param->hLOG/6);
            tft.setTextColor(BLACK); 
            tft.setTextSize(3);
            tft.print("LOG"); 
            responseMode = 8;
         }
    //-----CHECK TOUCHES ON NUMERICAL FIELDS-------
    
    
    for(int i = 0; i <= 3; i++){ 
      if(p.y < (tft.width()-xK_num) && p.y > (tft.width() - (xK_num + Param->wParam)) && p.x > yK_num && p.x < (yK_num + Param->hParam)){
        if(!(*ParamsGreenFlag[i])){
           tft.drawRect(xK_num, yK_num, wParam_num, hParam_num, GREEN);
           ParamsGreenFlag[i] = &Green;
           delay(100);
        }
        else{
           tft.drawRect(xK_num, yK_num, wParam_num, hParam_num, WHITE);
           ParamsGreenFlag[i] = &White;
           delay(100);
        } 
               
      }
      yK_num = yK_num + Param->stepParam;
        
    }
}
else{
    Serial.println("Read Log Screen Touches");
   //------------ CHECK TOUCHES ON LOG SCREEN EXIT BUTTON-----------------------
   if(p.y < (tft.width()-Log->xExit) && p.y > (tft.width() - (Log->xExit+Log->wExit)) && p.x > Log->yExit && p.x < (Log->yExit + Log->hExit)){
     
    tft.fillRect(Log->xExit, Log->yExit, Log->wExit, Log->hExit, BLACK);
    tft.drawRect(Log->xExit, Log->yExit, Log->wExit, Log->hExit, WHITE);   
    tft.setCursor(Log->xExit + 3*Log->wExit/10, Log->yExit + 2*Log->hExit/6);
    tft.setTextColor(WHITE); 
    tft.setTextSize(3);
    tft.print("EXIT"); 
    delay(200);
    tft.fillRect(Log->xExit, Log->yExit, Log->wExit, Log->hExit, WHITE);   
    tft.setCursor(Log->xExit + 3*Log->wExit/10, Log->yExit + 2*Log->hExit/6);
    tft.setTextColor(BLACK); 
    tft.setTextSize(3);
    tft.print("EXIT"); 
    responseMode = 3;  
  }

  //------------CHECK TOUCHES ON TEMP SCREEN BUTTON ---------------------------
  if(p.y < (tft.width()-Log->xTemp) && p.y > (tft.width() - (Log->xTemp+Log->wTemp)) && p.x > Log->yTemp && p.x < (Log->yTemp + Log->hTemp)){
    tft.fillRect(Log->xTemp, Log->yTemp, Log->wTemp, Log->hTemp, BLACK);
    tft.drawRect(Log->xTemp, Log->yTemp, Log->wTemp, Log->hTemp, WHITE);   
    tft.setCursor(Log->xTemp + 3*Log->wTemp/10, Log->yTemp + 2*Log->hTemp/6);
    tft.setTextColor(WHITE); 
    tft.setTextSize(3);
    tft.print("TEMP");
    delay(200);
    tft.fillRect(Log->xTemp, Log->yTemp, Log->wTemp, Log->hTemp, WHITE);  
    tft.setCursor(Log->xTemp + 3*Log->wTemp/10, Log->yTemp + 2*Log->hTemp/6);
    tft.setTextColor(BLACK); 
    tft.setTextSize(3);
    tft.print("TEMP");
    responseMode = 9;
  }

  //----------CHECK TOUCHES ON HUMID SCREEN BUTTON-----------------------------
  if(p.y < (tft.width()-Log->xHum) && p.y > (tft.width() - (Log->xHum+Log->wHum)) && p.x > Log->yHum && p.x < (Log->yHum + Log->hHum)){
    tft.fillRect(Log->xHum, Log->yHum, Log->wHum, Log->hHum, BLACK);
    tft.drawRect(Log->xHum, Log->yHum, Log->wHum, Log->hHum, WHITE);   
    tft.setCursor(Log->xHum + 1.5*Log->wHum/10, Log->yHum + 2*Log->hHum/6);
    tft.setTextColor(WHITE); 
    tft.setTextSize(3);
    tft.print("HUMID");
    delay(200);
    tft.fillRect(Log->xHum, Log->yHum, Log->wHum, Log->hHum, WHITE);  
    tft.setCursor(Log->xHum + 1.5*Log->wHum/10, Log->yHum + 2*Log->hHum/6);
    tft.setTextColor(BLACK); 
    tft.setTextSize(3);
    tft.print("HUMID");
    responseMode = 10;
  }
}
  return responseMode;
}



   
