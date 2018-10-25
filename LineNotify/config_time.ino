/*
void preconfig() {
  
  byte j = 1 ;
  Serial.print("Preconfig Time ");
  lcd.setCursor(0,0);
  lcd.print("Time "); 
  lcd.setCursor(0,1);
  lcd.print("By Counter");
  lcd.setCursor(0,2);
  lcd.print("By Date ");
  
while(1){
    delay(200);
    if(digitalRead(redbutt) == PUSH ){j++;}
    if(j == 3) {j =1;}
    lcd.setCursor(11,j);
    lcd.blink();
    Serial.println("Sel ");
    if(digitalRead(greenbutt)== PUSH){lcd.noBlink(); break; }
      }  
     Serial.println(j);
     lcd.clear();  
  switch (j){
    case 1 :
    delay(200);
    Counter ();
    satus(); //home
    break;
    case 2 :
    delay(200);
    bydate ();
    satus(); //home 
    break;
    }
  
  
  }
*/

   
void Counter (){
    Serial.println("load Counter");
    byte i = 0 ;  //Template
    byte cursor_x = 17; // 17 12
    lcd.setCursor(0,0);
    lcd.print("Counter = HH : MM");
    lcd.setCursor(0,1);
    lcd.print("Set =");
    while(1){
      lcd.setCursor(15,1);
      lcd.print(count_m);
      lcd.setCursor(10,1);
      lcd.print(count_h);
      lcd.setCursor(cursor_x,1);
      lcd.blink();
      
     switch(i){ //move row
      case 0 : //input min 
      if(digitalRead(redbutt) == PUSH){count_m++ ;;}
      if(digitalRead(whitebutt) == PUSH){
        --count_m;
        if(count_m < 0 ){count_m = 0;}        //stop go to 255 
        }
      if(count_m ==60){count_m=0;count_h++; }
      
      if(digitalRead(greenbutt) == PUSH){ // go set Hour
        i++;
        cursor_x=12;
        }
        delay(200);
        break ;
        
      case 1: // input Hour
      if(digitalRead(redbutt) == PUSH){
        ++count_h;
        }
      if(digitalRead(whitebutt) == PUSH){
        --count_h;
        if(count_h <0){
          count_h = 0 ;}
        }
      if(digitalRead(greenbutt) == PUSH){ //set hour 
        i++;
        lcd.noBlink();
        break ; 
        }  
      delay(200);
      
      }
      
      if(i == 2){i=0;break;}
    }
    
    lcd.clear();
    Serial.println("SENT COUNTTIME");
    countdown();
    return;
}
void countdown() {
    tDown.setCounter(0, 0, 5, tDown.COUNT_DOWN, Sent);
    tDown.setInterval(counter, 1000);
    tDown.start();
  }
void counter () {
  Serial.print("tDown : ");
  Serial.print (tDown.getCurrentTime() );
  Serial.println("");
  return;
  }


