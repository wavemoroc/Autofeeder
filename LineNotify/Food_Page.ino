byte vol_i = 0;
float vol = 0;
void Input_vol() {
  while(1){
  lcd.setCursor(0,0);
  lcd.print("Food Volume ");
  lcd.setCursor(0,1);
  lcd.print("Volume : ");
  lcd.setCursor(9,1);
  if(digitalRead(redbutt) == PUSH){
    vol_i++;
    if(vol_i == 1){lcd.print("S");food_vol = "S" ;vol =1;}
    if(vol_i == 2){lcd.print("M");food_vol = "M" ;vol =1.5;}
    if(vol_i == 3){lcd.print("L");food_vol = "L" ;vol =2;}
    if(vol_i == 4){ vol_i = 0 ; }  // reset 
      
      }
   lcd.setCursor(11,1);
   lcd.blink();
      
   if(digitalRead( greenbutt) == PUSH){
     lcd.noBlink();
     lcd.clear();
     satus();
    break;
    }    
    delay(200);
    
    }

}
