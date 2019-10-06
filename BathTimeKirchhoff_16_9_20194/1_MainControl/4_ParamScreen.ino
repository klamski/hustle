//----------------------------- SET UP PARAM SCREEN ------------------------------------------------
void SetUp_ParamScreen(ParamScreenObjects *Obj){
  uint16_t x_max = 480, y_max = 320; //Screen Borders
  
  tft.fillScreen(BLACK);
  tft.drawRect(1, 1, x_max - 1, y_max -1, WHITE);

  //Draw PID on-off Button
  if(Obj->PIDstate){
    tft.drawRect(Obj->xPID, Obj->yPID, Obj->wPID, Obj->hPID, WHITE); 
    tft.fillRect(Obj->xPID, Obj->yPID, Obj->wPID, Obj->hPID, WHITE); 

    tft.setCursor(Obj->xPID + 2*Obj->wPID/10, Obj->yPID + 2*Obj->hPID/6);
    tft.setTextColor(BLACK); 
    tft.setTextSize(3);
    tft.print("PID on");
  }else{
    tft.fillRect(Obj->xPID, Obj->yPID, Obj->wPID, Obj->hPID, BLACK); 
    tft.drawRect(Obj->xPID, Obj->yPID, Obj->wPID, Obj->hPID, WHITE);     

    tft.setCursor(Obj->xPID + 2*Obj->wPID/10, Obj->yPID + 2*Obj->hPID/6);
    tft.setTextColor(WHITE); 
    tft.setTextSize(3);
    tft.print("PID off");
  }
  
  
  //Draw Close Button
  tft.drawRect(Obj->xClose, Obj->yClose, Obj->wClose, Obj->hClose, WHITE); 
  tft.fillRect(Obj->xClose, Obj->yClose, Obj->wClose, Obj->hClose, WHITE); 

  tft.setCursor(Obj->xClose + 3*Obj->wClose/10, Obj->yClose + 2*Obj->hClose/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print("EXIT"); 

  //Draw LOG Button
  tft.drawRect(Obj->xLOG, Obj->yLOG, Obj->wLOG, Obj->hLOG, WHITE); 
  tft.fillRect(Obj->xLOG, Obj->yLOG, Obj->wLOG, Obj->hLOG, WHITE); 

  tft.setCursor(Obj->xLOG + 3*Obj->wLOG/10, Obj->yLOG + 2*Obj->hLOG/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print("LOG"); 
  

  // Set Up Kp, Ki, Kd
  tft.setCursor(Obj->xKp_txt, Obj->yKp_txt);
  tft.setTextColor(WHITE); 
  tft.setTextSize(3);
  tft.print("Kp :"); 

  tft.setCursor(Obj->xKi_txt, Obj->yKi_txt);
  tft.setTextColor(WHITE); 
  tft.setTextSize(3);
  tft.print("Ki :"); 

  tft.setCursor(Obj->xKd_txt, Obj->yKd_txt);
  tft.setTextColor(WHITE); 
  tft.setTextSize(3);
  tft.print("Kd :"); 

  tft.setCursor(Obj->xStep_txt, Obj->yStep_txt);
  tft.setTextColor(WHITE); 
  tft.setTextSize(3);
  tft.print("Stp:"); 

  tft.drawRect(Obj->xKp_num, Obj->yKp_num, Obj->wParam, Obj->hParam, WHITE);
  tft.drawRect(Obj->xKi_num, Obj->yKi_num, Obj->wParam, Obj->hParam, WHITE);
  tft.drawRect(Obj->xKd_num, Obj->yKd_num, Obj->wParam, Obj->hParam, WHITE);
  tft.drawRect(Obj->xStep_num, Obj->yStep_num, Obj->wParam, Obj->hParam, WHITE);

  // draw Buttons 
  //Draw Kp  Right Button
  Obj->x0 = Obj->xRr + (Obj->wRr - Obj->a)/2;
  Obj->y0 = Obj->yRr + (Obj->hRr + Obj->a)/2;
  Obj->x1 = Obj->x0 + Obj->a/2;               //Obj->xRr + a/2;
  Obj->y1 = Obj->y0 -  Obj->a;                //Obj->yRr + (Obj->hRr + a)%2 + a;
  Obj->x2 = Obj->x0 + Obj->a;                //Obj->xRr + (Obj->wRr - a);
  Obj->y2 = Obj->y0;                    //Obj->yRr + (Obj->hRr + a)%2;
  tft.drawRect(Obj->xRr, Obj->yRr, Obj->wRr, Obj->hRr, WHITE);
  tft.fillRect(Obj->xRr, Obj->yRr, Obj->wRr, Obj->hRr, WHITE);
  tft.fillTriangle( Obj->x0, Obj->y0, Obj->x1, Obj->y1, Obj->x2, Obj->y2, BLACK);
  
  //Draw Kp Left Button
  Obj->x0 = Obj->xRl + (Obj->wRl - Obj->a)/2;
  Obj->y0 = Obj->yRl + (Obj->hRl - Obj->a)/2;
  Obj->x1 = Obj->x0 + Obj->a/2;
  Obj->y1 = Obj->y0 + Obj->a;
  Obj->x2 = Obj->x0 + Obj->a;
  Obj->y2 = Obj->y0;
  tft.drawRect(Obj->xRl, Obj->yRl, Obj->wRl, Obj->hRl, WHITE);
  tft.fillRect(Obj->xRl, Obj->yRl, Obj->wRl, Obj->hRl, WHITE);
  tft.fillTriangle( Obj->x0, Obj->y0, Obj->x1, Obj->y1, Obj->x2, Obj->y2, BLACK);


}

//------------REFRESH PARAM SCREEN VALUES----------------------------------------------------
void refresh_ParamScreen_Values(ParamScreenObjects *Obj, double Kp, double Ki, double Kd, double Stp){
  uint16_t x_max = 480, y_max = 320; //Screen Borders

  
  Serial.println("Refresh ParamScreen Values");
  tft.fillRect(Obj->xKp_num + 1, Obj->yKp_num + 1, Obj->wParam - 2, Obj->hParam - 2, BLACK);
  tft.setCursor(Obj->xKp_num + 5, Obj->yKp_txt+ 1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(Kp); 

  tft.fillRect(Obj->xKi_num + 1, Obj->yKi_num + 1, Obj->wParam - 2, Obj->hParam - 2, BLACK);
  tft.setCursor(Obj->xKi_num + 5, Obj->yKi_txt + 1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(Ki); 

  tft.fillRect(Obj->xKd_num + 1, Obj->yKd_num + 1, Obj->wParam - 2, Obj->hParam - 2, BLACK);
  tft.setCursor(Obj->xKd_num + 5, Obj->yKd_txt + 1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(Kd); 

  tft.fillRect(Obj->xStep_num + 1, Obj->yStep_num + 1, Obj->wParam - 2, Obj->hParam - 2, BLACK);
  tft.setCursor(Obj->xStep_num + 5, Obj->yStep_txt + 1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(Stp);
}
