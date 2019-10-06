
int monoxide(int AOUTpin, int DOUTpin, int Buzzer)
{
int value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
int limit= digitalRead(DOUTpin);//reads the digital value from the CO sensor's DOUT pin
if (limit == HIGH){
  digitalWrite(Buzzer, HIGH);//if limit has been reached, LED turns on as status indicator
}
else{
  digitalWrite(Buzzer, LOW);//if threshold not reached, LED remains off
}
return value;
}
