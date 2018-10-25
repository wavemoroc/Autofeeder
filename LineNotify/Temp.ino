#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void temp_setup(void)
{
  Serial.println("Set up Temp");
  sensors.begin();
}

void showtemp(void)
{ 

  sensors.requestTemperatures(); // Send the command to get temperatures
  Temp = sensors.getTempCByIndex(0);
  return;  
}
