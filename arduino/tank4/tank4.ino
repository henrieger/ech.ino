# include "src/sensors/temperature.h"
# include "src/sensors/water.h"
# include "src/sensors/light.h"
# include "src/comms/serial.h"
# include <string.h>
# include <LiquidCrystal_I2C.h>

# define TANK_ID 4

# define TEMPERATURE_PIN 13
# define BUTTON_PIN A0
# define WATER_PIN A1
# define BUZZER_PIN A2
# define POTENTIOMETER_PIN A3

# define LIN 4
# define COL 20
# define LCD_ADDR 0x27

SerialComms serial = SerialComms(TANK_ID);
byte waiting = true;

TemperatureSensor tempSensor(TEMPERATURE_PIN);
WaterSensor waterSensor(WATER_PIN);
LightSensor lightSensor;

float temperature, sentTemperature, light, sentLight;
long waterInput, sentWaterInput;
int tempSensorInfo, waterSensorInfo, lightSensorInfo;

LiquidCrystal_I2C lcd(LCD_ADDR, COL, LIN);
byte degreeSymbol[8] = 
{
    0b00010,
    0b00101,
    0b00010,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.createChar(0, degreeSymbol);

    randomSeed(analogRead(2));
    delay(random(0, 2000));

    serial.begin();

    tempSensor.begin();
    lightSensor.begin();

    lcd.setCursor(3, 1);
    lcd.print("ZEROING SENSOR");
    waterSensor.begin(BUTTON_PIN, POTENTIOMETER_PIN, BUZZER_PIN);
    lcd.clear();

    tempSensorInfo = TEMPERATURE | 0x8000;
    reverse((uint8_t *) &tempSensorInfo, sizeof(int));

    waterSensorInfo = WATER;
    reverse((uint8_t *) &waterSensorInfo, sizeof(int));

    lightSensorInfo = LIGHT | 0x8000;
    reverse((uint8_t *) &lightSensorInfo, sizeof(int));
}

void loop()
{
    lcd.clear();

    temperature = tempSensor.readFloatInput();            
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.write((byte)0);
    lcd.print("C");

    light = lightSensor.readFloatInput();
    lcd.setCursor(0, 1);
    lcd.print("Light: ");
    lcd.print(light);
    lcd.print(" lx");

    waterInput = waterSensor.readInput();
    lcd.setCursor(0, 2);
    lcd.print("Water: ");
    lcd.print(waterInput);

    int waterThreshold = analogRead(POTENTIOMETER_PIN) / 100;

    lcd.setCursor(0, 3);
    lcd.print("Threshold: ");
    lcd.print(waterSensor.getThreshold());
    
    if (waterSensor.getButtonInput())
    {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("RESET WATER LEVEL...");

        while(waterSensor.getButtonInput()) {}
        waterSensor.resetWaterBaseInput();
    }

    waterSensor.warnOfWaterLevel();

    if (waiting && serial.checkForTrigger())
    {
        waiting = false;
        
        sentTemperature = temperature;
        sentWaterInput = waterInput;
        sentLight = light;
    }

    if (!waiting && serial.checkForDataRequest())
    {
        waiting = true;

        uint8_t buff[18];

        memcpy(buff, &tempSensorInfo, 2);
        memcpy(buff+2, reverse((uint8_t *) &sentTemperature, 4), 4);

        memcpy(buff+6, &waterSensorInfo, 2);
        memcpy(buff+8, reverse((uint8_t *) &sentWaterInput, 4), 4);

        memcpy(buff+12, &lightSensorInfo, 2);
        memcpy(buff+14, reverse((uint8_t *) &sentLight, 4), 4);

        do
        {
            serial.sendData(buff, 18);
        } while (!serial.acknowledged());
    }

    delay(5000);
}
