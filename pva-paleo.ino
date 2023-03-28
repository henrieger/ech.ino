# include <DallasTemperature.h>
# include <OneWire.h>

# define _1W_DATA 13
# define WATER_PIN A0
# define BUTTON_PIN A1
# define POTENTIOMETER_PIN A2
# define BUZZER_PIN A3

OneWire oneWire(_1W_DATA);
DallasTemperature sensors(&oneWire);

int waterBaseLevel;

void setup()
{
    Serial.begin(9600);

    sensors.begin();
    sensors.setResolution(12);

    pinMode(WATER_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT);

    Serial.println("Aperte o botao para configurar o nivel de agua");
    while (digitalRead(BUTTON_PIN) == LOW) {}
    waterBaseLevel = analogRead(WATER_PIN);
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
    Serial.println(waterBaseLevel - waterInput);

    int waterThreshold = analogRead(POTENTIOMETER_PIN) / 100;
    Serial.print("Threshold: ");
    Serial.println(waterThreshold);
    
    if (abs(waterBaseLevel - waterInput) > waterThreshold)
    {
        delay(10);
        tone(BUZZER_PIN, 440);
        delay(100);
        noTone(BUZZER_PIN);
    }

    Serial.println();
    delay(1000);
}
