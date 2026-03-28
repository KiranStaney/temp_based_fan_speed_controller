#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3    // DS18B20 data pin
#define ENA 7             // Enable pin for L298N (PWM)
#define IN1 8
#define IN2 9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temperatureC;

//runs once
void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  // Motor direction
}

//runs again and again
void loop() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);//arduino reads the temperature

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Map temperature (20–60°C) to PWM between 191 (≈9V) and 255 (≈12V)
  int motorSpeed = map(constrain(temperatureC, 20, 60), 20, 60, 191, 255);
  analogWrite(ENA, motorSpeed);//generates pwm signal

  Serial.print("Motor Speed (PWM): ");
  Serial.println(motorSpeed);
  
  delay(1000);
}
