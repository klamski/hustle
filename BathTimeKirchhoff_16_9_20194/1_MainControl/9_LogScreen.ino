void SetUp_LogScreen(LogScreenObjects *Obj) {
 uint16_t x_max = 480, y_max = 320; //Screen Borders
 
 tft.fillScreen(BLACK);
  tft.drawRect(1, 1, x_max - 1, y_max -1, WHITE);

  //Draw Close Button
  tft.drawRect(Obj->xExit, Obj->yExit, Obj->wExit, Obj->hExit, WHITE); 
  tft.fillRect(Obj->xExit, Obj->yExit, Obj->wExit, Obj->hExit, WHITE);
  tft.setCursor(Obj->xExit + 3*Obj->wExit/10, Obj->yExit + 2*Obj->hExit/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print("EXIT"); 
 
  //Draw Temp Button
  tft.drawRect(Obj->xTemp, Obj->yTemp, Obj->wTemp, Obj->hTemp, WHITE);
  tft.fillRect(Obj->xTemp, Obj->yTemp, Obj->wTemp, Obj->hTemp, WHITE);
  tft.setCursor(Obj->xTemp + 2*Obj->wTemp/10, Obj->yTemp + 2*Obj->hTemp/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print("TEMP"); 

  //Draw Humid Button
  tft.drawRect(Obj->xHum, Obj->yHum, Obj->wHum, Obj->hHum, WHITE);
  tft.fillRect(Obj->xHum, Obj->yHum, Obj->wHum, Obj->hHum, WHITE);
  tft.setCursor(Obj->xHum + 1.5*Obj->wHum/10, Obj->yHum + 2*Obj->hHum/6);
  tft.setTextColor(BLACK); 
  tft.setTextSize(3);
  tft.print("HUMID");   
}

void PlotByDate(int ChoosePlot){
  //Plot EnvTempPerDay if ChoosePlot == 0
  //Plot EnvHumPerDay if ChoosePlot == 1
  bool display1 = true, display2 = true;
  float *plotTemp, *plotHumid, Temp[24], Hum[24];
  bool h12, PM;
  
  String MeasDate = DateInString();
  plotTemp = &Temp[0];  
  plotHumid = &Hum[0];
  int xlim = (int)Clock.getHour(h12, PM);
  for(int i = 0; i <= xlim; i++){
    if(i == 0){
        ReadMeasByDate(MeasDate, plotTemp, plotHumid);
    }
    if(ChoosePlot == 0){
      Graph(tft, (double)i, (double)*(plotTemp + i), 60, 220, 370, 150, 0, xlim, 1, 0, 50, 5,"EnvTempPerHour", "Hours", "EnvTemp", DKGREEN, WHITE, WHITE, WHITE, BLACK, display1);
    }
    else if(ChoosePlot == 1){
      Graph(tft, (double)i, (double)*(plotHumid + i), 60, 220, 370, 150, 0, xlim, 1, 0, 100, 10,"EnvHumidPerHour", "Hours", "EnvHumid", DKGREEN, WHITE, WHITE, WHITE, BLACK, display2);
    } 
  } 
}

