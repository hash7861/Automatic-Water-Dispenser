// Project Code Overview: We created a seamless, automatic water dispenser. While there is no object in front of
// the hrs04 sensor, the red LED stays HIGH, the serial monitor outputs the distance (cm), no object detected,
// the water pump stays OFF, and the LCD screen prints "Not Filling". As soon as the sensor senses an object within
// 8 cm, the green LED turns on, and the water pours into the object. The serial monitor only then outputs object 
// is detected and the LCD prints the message "Filling Up". Hence the water pump stays ON until the object is out of range.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// SDA->21, SCL->22
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

// Pin configuration for Ultrasonic Sensor
#define TRIG_PIN 5
#define ECHO_PIN 4

// Pin configuration for LEDs
#define RED_LED 27
#define GREEN_LED 26

// Pin configuration for Water Pump
#define MOTOR1A 25
#define MOTOR2A 33

// Define distance threshold (in cm)
#define DISTANCE_THRESHOLD 8 // Adjust based on detection range

void setup() {
  Serial.begin(115200);
  Serial.println("Ultrasonic Sensor with LEDs and Water Pump");

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Set up ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set up LEDs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Set up Water Pump
  pinMode(MOTOR1A, OUTPUT);
  pinMode(MOTOR2A, OUTPUT);

  // Turn off LEDs and Water Pump initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(MOTOR1A, LOW);
  digitalWrite(MOTOR2A, LOW);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logic for LED and Water Pump control
  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    // Object detected
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    // Turn on water pump
    digitalWrite(MOTOR1A, HIGH);
    digitalWrite(MOTOR2A, LOW);

    // Update LCD with "filling up"
    lcd.clear();
    lcd.setCursor(0, 0); // Top row
    lcd.print("   Filling Up   ");
    Serial.println("Object detected - Water Pump ON");
  } else {
    // No object detected
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // Turn off water pump
    digitalWrite(MOTOR1A, LOW);
    digitalWrite(MOTOR2A, LOW);

    // Update LCD with "not filling"
    lcd.clear();
    lcd.setCursor(0, 0); // Top row
    lcd.print("  Not Filling ");
    Serial.println("No object detected - Water Pump OFF");
  }

  // Small delay for stability
  delay(500);
}
