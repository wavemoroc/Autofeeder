#include "Countimer.h"
#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include "Countimer.h"

#define redbutt 12   //increassing
#define whitebutt 11 //decreassing
#define PUSH LOW
#define UNPUSH HIGH
#define greenbutt 10 //OK

LiquidCrystal_I2C lcd(0x3F, 20, 4); //A4 A5
Countimer tDown;

int count_m, count_h = 0; //stop valu go to 255 counter && satus  counter && satus
byte j = 1;               //Fist select colum switching &selection
String Temp, food_vol;

#define SSID "No Internet access"
#define PASSWORD "Password"
#define LINE_TOKEN "hsTPzc6TlwjFdQ4lnAENEudWSfLsvIrMeDRdluw0ZIN"
Countimer tDown;

void setup()
{
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  NodeSerial.begin(57600);
  Serial.begin(9600);
  pinMode(redbutt, INPUT);
  pinMode(whitebutt, INPUT);
  pinMode(greenbutt, INPUT);
  lcd.begin();
  Wire.begin();
  Serial.begin(9600);
  initial();
  Servo_setup();
  temp_setup();
  
  //conect wifi
  Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
  LINE.notify("อุปกรณ์เชื่อมต่ออินเตอร์เน็ตแล้วครับ ");
}

void loop()
{

  while (NodeSerial.available() > 0)
  {
    int Start = NodeSerial.parseInt();
    if (NodeSerial.read() == '\n')
    {
      Serial.print(Start);
      LINE.notify("ให้อาหารปลาแล้วครับ ! ");
      Serial.println("yes ");
    }
  tDown.run();
  satus();
  }
}

int selection()
{
  j = 1;
  Serial.println("START selection");

  while (1)
  {
    if (digitalRead(redbutt) == PUSH)
    { //move down cursor
      lcd.noBlink();
      lcd.setCursor(19, j);
      lcd.blink();
      j++;
      Serial.print("Cursor move! = ");
      Serial.print(j);
      delay(200);
    }
    if (j > 2)
    {        //endline -1
      j = 1; //WTF Zone                  //restart line
      Serial.println("Reset line ");
    }
    if (digitalRead(greenbutt) == PUSH)
    { //selected
      Serial.println("selected");
      Serial.println(j); //option Number colum =option Number -1
      lcd.noBlink();
      break;
    }
  }
}

void switching()
{
  lcd.clear();
  switch (j)
  {

  case 2: //option 2
    lcd.setCursor(0, 2);
    lcd.print("This is Optinon 2");
    delay(200);
    lcd.clear();
    Counter();
    break;

  case 1: //option 3 WTF point
    lcd.setCursor(0, 2);
    lcd.print("This is Optinon 1");
    delay(200);
    lcd.clear();
    Input_vol();
    break;
  }
  Serial.println("Break");
  lcd.clear();
  return;
}

void initial()
{
  Serial.println("Loading Screen");
  lcd.setCursor(4, 1);
  lcd.print("Auto  Feeder");
  lcd.setCursor(4, 2);
  lcd.print("version  1.0");
  delay(500);
  lcd.clear();
  return;
}

void satus()
{
  while (1)
  {

    Serial.println("Menu");
    showtemp();
    lcd.setCursor(0, 0);
    lcd.print("Temp :");
    lcd.setCursor(6, 0);
    lcd.print(Temp);
    lcd.setCursor(12, 0);
    lcd.print("C");

    //Countdown section
    lcd.setCursor(0, 1);
    lcd.print("Next :");
    lcd.setCursor(6, 1);
    lcd.print(tDown.getCurrentTime());

    //food
    lcd.setCursor(0, 2);
    lcd.print("Food : ");
    lcd.setCursor(6, 2);
    lcd.print(food_vol);

    if (digitalRead(redbutt) == PUSH)
    {
      Serial.println("PUSH");
      selection();
      switching();
      break;
    }
    delay(100);
    break;
  }
  return;
}

