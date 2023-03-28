# include "temperature.h"
# include "water.h"

# define TEMPERATURE_PIN 13
# define WATER_PIN A0
# define BUTTON_PIN A1
# define POTENTIOMETER_PIN A2
# define BUZZER_PIN A3

TemperatureSensor tempSensor(TEMPERATURE_PIN);
WaterSensor waterSensor(WATER_PIN);

void setup()
{
    Serial.begin(9600);

    tempSensor.begin();
    waterSensor.begin(BUTTON_PIN, POTENTIOMETER_PIN, BUZZER_PIN);
}

void loop()
{
    float temp = tempSensor.readFloatInput();

    Serial.print("Temperatura atual: ");
    Serial.print(temp);
    Serial.println(" ºC");

    int waterInput = waterSensor.readInput();
    Serial.print("Nível da água: ");
    Serial.println(waterInput);

    int waterThreshold = analogRead(POTENTIOMETER_PIN) / 100;
    Serial.print("Threshold: ");
    Serial.println(waterSensor.getThreshold());
    
    waterSensor.warnOfWaterLevel();

    Serial.println();
    delay(1000);
}
