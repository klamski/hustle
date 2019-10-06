void RelaysControl(){
 
  for(int i = 0; i <= 7; i++){
    pinMode(Relays[i], OUTPUT);
    if(RelaysStateFlag[i]){
      digitalWrite(Relays[i], HIGH);
    }else{
      digitalWrite(Relays[i], LOW);
    }
  }
  
}
