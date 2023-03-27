# include <DallasTemperature.h>
# include <OneWire.h>

# define _1W_DATA 13
# define WATER_PIN A0

OneWire oneWire(_1W_DATA);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(9600);

    sensors.begin();
    sensors.setResolution(12);

    pinMode(WATER_PIN, INPUT);
}

void loop()
{
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);

    Serial.print("Temperatura atual: ");
    Serial.print(temp);
    Serial.println(" ºC");

    int waterInput = analogRead(WATER_PIN);
    Serial.print("Nível da água: ");
    Serial.println(waterInput);

    Serial.println();

    delay(1000);
}
