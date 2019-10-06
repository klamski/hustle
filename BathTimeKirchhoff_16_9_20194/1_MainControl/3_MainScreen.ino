//----------------- SET UP MAIN SCREEN -------------------------------------
void SetUp_MainScreen(MainScreenObjects *Obj) {
 uint16_t x_max = 480, y_max = 320; //Screen Borders
 Obj->x_circle = x_max / 9;
  tft.fillScreen(BLACK);
  tft.drawRect(1, 1, x_max - 1, y_max -1, WHITE);
  tft.drawLine(x_max / 2, Obj->y_line, x_max / 2, y_max - Obj->y_line, WHITE); 
// Draw Texts 1st column
  tft.setCursor(Obj->x_text1,Obj->y_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("Temp_R (C):");

  tft.setCursor(Obj->x_text1, Obj->y_text1 + Obj->step_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("Temp (C):");

  tft.setCursor(Obj->x_text1, Obj->y_text1 + 2* Obj->step_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("Humid (%):");

  tft.setCursor(Obj->x_text1, Obj->y_text1 + 3* Obj->step_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("CO:");

   tft.setCursor(Obj->x_text1, Obj->y_text1 + 4* Obj->step_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("  |--PID Relays--|  |--GEN Relays--|");

  // Draw Texts 2nd column
  tft.setCursor(Obj->x_text2, Obj->y_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("PID_T (C):");

  tft.setCursor(Obj->x_text2, Obj->y_text1 + Obj->step_text1);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print("Temp_Control:");

  // Draw Numerical Fields 1st Column
  tft.drawRect(Obj->x_num1,Obj->y_num1, Obj->w_num1, Obj->h_num1, WHITE);  // tft.drawRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.drawRect(Obj->x_num1, Obj->y_num1 + Obj->step_num1, Obj->w_num1, Obj->h_num1, WHITE);
  tft.drawRect(Obj->x_num1, Obj->y_num1 + 2*Obj->step_num1, Obj->w_num1, Obj->h_num1, WHITE);
  tft.drawRect(Obj->x_num1, Obj->y_num1 + 3*Obj->step_num1, Obj->w_num1, Obj->h_num1, WHITE);

  // Draw numerical Field 2nd Column 
  tft.drawRect(Obj->xPID, Obj->yPID, Obj->wPID, Obj->hPID, WHITE); 
  
  //Draw 2nd Column Right Button
  Obj->x0 = Obj->xRr + (Obj->wRr - Obj->a)/2;
  Obj->y0 = Obj->yRr + (Obj->hRr + Obj->a)/2;
  Obj->x1 = Obj->x0 + Obj->a/2;               //Obj->xRr + a/2;
  Obj->y1 = Obj->y0 -  Obj->a;                //Obj->yRr + (Obj->hRr + a)%2 + a;
  Obj->x2 = Obj->x0 + Obj->a;                //Obj->xRr + (Obj->wRr - a);
  Obj->y2 = Obj->y0;                    //Obj->yRr + (Obj->hRr + a)%2;
  tft.drawRect(Obj->xRr, Obj->yRr, Obj->wRr, Obj->hRr, WHITE);
  tft.fillRect(Obj->xRr, Obj->yRr, Obj->wRr, Obj->hRr, WHITE);
  tft.fillTriangle( Obj->x0, Obj->y0, Obj->x1, Obj->y1, Obj->x2, Obj->y2, BLACK);
  
  //Draw 2nd Column Left Button
  Obj->x0 = Obj->xRl + (Obj->wRl - Obj->a)/2;
  Obj->y0 = Obj->yRl + (Obj->hRl - Obj->a)/2;
  Obj->x1 = Obj->x0 + Obj->a/2;
  Obj->y1 = Obj->y0 + Obj->a;
  Obj->x2 = Obj->x0 + Obj->a;
  Obj->y2 = Obj->y0;
  tft.drawRect(Obj->xRl, Obj->yRl, Obj->wRl, Obj->hRl, WHITE);
  tft.fillRect(Obj->xRl, Obj->yRl, Obj->wRl, Obj->hRl, WHITE);
  tft.fillTriangle( Obj->x0, Obj->y0, Obj->x1, Obj->y1, Obj->x2, Obj->y2, BLACK);
 
  // Draw Log Button
  tft.drawRect(Obj->xParam, Obj->yParam, Obj->wParam, Obj->hParam, WHITE); 
  tft.fillRect(Obj->xParam, Obj->yParam, Obj->wParam, Obj->hParam, WHITE); 

  tft.setCursor(Obj->xParam + 1*Obj->wParam/5, Obj->yParam + 2*Obj->hParam/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print(" PARAM");

  //Draw Relays Buttons/Indications  
  tft.drawCircle(Obj->x_circle, Obj->y_circle, Obj->r, WHITE);   //tft.drawCircle(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t r, uint16_t color); 
  tft.drawCircle(2*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(3*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(4*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(5*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(6*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(7*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
  tft.drawCircle(8*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);
          
}

//------------ REFRESH MAIN SCREEN VALUES-------------------------------------------------------------------------------
void refresh_MainScreen_Values(MainScreenObjects *Obj, Measurements *val, uint8_t Relays){
  
  tft.fillRect(Obj->x_num1 + 1, Obj->y_num1 + 1, Obj->w_num1 - 2, Obj->h_num1 - 2, BLACK); //tft.fillRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.setCursor(Obj->x_num1 + 5, Obj->y_text1);     // refresh Temp DS18B20
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(val->Temp_DS);

  tft.fillRect(Obj->x_num1 + 1, Obj->y_num1 + 1 + Obj->step_num1, Obj->w_num1 - 2, Obj->h_num1 - 2, BLACK); //tft.fillRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.setCursor(Obj->x_num1 + 5, Obj->y_text1 + Obj->step_text1);     // refresh Temp DHT11
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(val->Temp_DHT);

  tft.fillRect(Obj->x_num1 + 1, Obj->y_num1 + 1 + 2*Obj->step_num1, Obj->w_num1 - 2, Obj->h_num1 - 2, BLACK); //tft.fillRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.setCursor(Obj->x_num1 + 5, Obj->y_text1 + 2*Obj->step_text1);     // refresh Humid DHT11
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(val->Humid);

  tft.fillRect(Obj->x_num1 + 1, Obj->y_num1 + 1 + 3*Obj->step_num1, Obj->w_num1 - 2, Obj->h_num1 - 2, BLACK); //tft.fillRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.setCursor(Obj->x_num1 + 5, Obj->y_text1 + 3*Obj->step_text1);     // refresh Temp CO
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(val->Co);

  tft.fillRect(Obj->xPID + 1, Obj->yPID + 1, Obj->wPID - 2, Obj->hPID - 2, BLACK); //tft.fillRect(uint16_t Obj->x0, uint16_t Obj->y0, uint16_t w, uint16_t h, uint16_t color);
  tft.setCursor(Obj->xPID + 5, Obj->y_text1);     // refresh Temp CO
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.print(val->PID_SetPoint);
  
  //-----Refresh PID relay's state indication------------------
 for(int i = 0; i <= 7; i++){        
    if( RelaysStateFlag[i]){
      tft.fillCircle((i+1)*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);  
    }else{
      tft.fillCircle((i+1)*Obj->x_circle, Obj->y_circle, Obj->r - 1, BLACK);
    }          
   }   
}

//-----Refresh PID relay's state indication------------------
void refresh_PID_indication(MainScreenObjects *Obj){
  for(int i = 0; i <= 3; i++){        
    if( RelaysStateFlag[i]){
      tft.fillCircle((i+1)*Obj->x_circle, Obj->y_circle, Obj->r, WHITE);  
    }else{
      tft.fillCircle((i+1)*Obj->x_circle, Obj->y_circle, Obj->r - 1, BLACK);
    }          
   }   
}
   
 