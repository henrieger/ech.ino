# include "src/sensors/temperature.h"
# include "src/sensors/water.h"
# include "src/comms/serial.h"
# include <string.h>
# include <LiquidCrystal_I2C.h>

# define TEMPERATURE_PIN 13
# define WATER_PIN A0
# define BUTTON_PIN A1
# define POTENTIOMETER_PIN A2
# define BUZZER_PIN A3

# define LIN 4
# define COL 20
# define LCD_ADDR 0x27

SerialComms serial = SerialComms(1);
byte waiting = true;

TemperatureSensor tempSensor(TEMPERATURE_PIN);
WaterSensor waterSensor(WATER_PIN);

float temperature;
long waterInput;
int tempSensorInfo, waterSensorInfo;

LiquidCrystal_I2C lcd(LCD_ADDR, COL, LIN);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();

    randomSeed(analogRead(2));
    delay(random(0, 2000));

    serial.begin();

    tempSensor.begin();

    lcd.setCursor(4, 1);
    lcd.print("ZERAR SENSOR");
    waterSensor.begin(BUTTON_PIN, POTENTIOMETER_PIN, BUZZER_PIN);
    lcd.clear();

    tempSensorInfo = TEMPERATURE | 0x8000;
    reverse((uint8_t *) &tempSensorInfo, sizeof(int));

    waterSensorInfo = WATER;
    reverse((uint8_t *) &waterSensorInfo, sizeof(int));
}

void loop()
{
    if (waiting && serial.checkForTrigger())
    {
        waiting = false;
        
        temperature = tempSensor.readFloatInput();

        lcd.clear();
            
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print(" oC");

        waterInput = waterSensor.readInput();
        // waterInput = 2;
        lcd.setCursor(0, 1);
        lcd.print("Agua: ");
        lcd.print(waterInput);
    }

    if (!waiting && serial.checkForDataRequest())
    {
        waiting = true;

        uint8_t buff[12];

        memcpy(buff, &tempSensorInfo, 2);
        memcpy(buff+2, reverse((uint8_t *) &temperature, 4), 4);

        memcpy(buff+6, &waterSensorInfo, 2);
        memcpy(buff+8, reverse((uint8_t *) &waterInput, 4), 4);

        do
        {
            serial.sendData(buff, 12);
        } while (!serial.acknowledged());
    }

    int waterThreshold = analogRead(POTENTIOMETER_PIN) / 100;

    lcd.setCursor(0, 2);
    lcd.print("Threshold: ");
    lcd.print(waterSensor.getThreshold());
    
    waterSensor.warnOfWaterLevel();

    delay(1000);
}
