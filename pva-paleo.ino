# include <DallasTemperature.h>
# include <OneWire.h>

# define _1W_DATA 13

OneWire oneWire(_1W_DATA);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(9600);

    sensors.begin();
    sensors.setResolution(12);
}

void loop()
{
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);

    Serial.print("Temperatura atual: ");
    Serial.print(temp);
    Serial.println(" ºC");

    delay(1000);
}
