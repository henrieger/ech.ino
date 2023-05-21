# include "water.h"

# include <Arduino.h>

WaterSensor::WaterSensor(int inputPin)
{
    setSensorType(WATER);
    setInputPin(inputPin);
}

void WaterSensor::begin(int buttonPin, int potentiometerPin, int buzzerPin)
{
    setButtonPin(buttonPin);
    setPotentiometerPin(potentiometerPin);
    setBuzzerPin(buzzerPin);

    pinMode(getInputPin(), INPUT);
    pinMode(buttonPin, INPUT);
    pinMode(potentiometerPin, INPUT);
    pinMode(buzzerPin, OUTPUT);

    noTone(buzzerPin);

    while (digitalRead(buttonPin) == LOW) {}

    waterBaseInput = (long) analogRead(getInputPin());
}

long WaterSensor::readInput()
{
    return waterBaseInput - (long) analogRead(getInputPin());
}

void WaterSensor::warnOfWaterLevel()
{
    if (abs(readInput()) > getThreshold())
    {
        tone(buzzerPin, 440);
        delay(100);
        noTone(buzzerPin);
    }
}

int WaterSensor::getThreshold()
{
    return analogRead(potentiometerPin) / 100;
}

int WaterSensor::getButtonPin() { return buttonPin; }
void WaterSensor::setButtonPin(int _buttonPin) { buttonPin = _buttonPin; }
int WaterSensor::getButtonInput() { return digitalRead(getButtonPin()); }

int WaterSensor::getPotentiometerPin() { return potentiometerPin; }
void WaterSensor::setPotentiometerPin(int _potentiometerPin) { potentiometerPin = _potentiometerPin; }

int WaterSensor::getBuzzerPin() { return buzzerPin; }
void WaterSensor::setBuzzerPin(int _buzzerPin) { buzzerPin = _buzzerPin; }

int WaterSensor::getWaterBaseInput() { return waterBaseInput; }
void WaterSensor::setWaterBaseInput(int _waterBaseInput) { waterBaseInput = _waterBaseInput; }
void WaterSensor::resetWaterBaseInput() { waterBaseInput = analogRead(getInputPin()); }
