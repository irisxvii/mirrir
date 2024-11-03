#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin connections
const int trigPin = 9;        // Ultrasonic sensor Trigger pin
const int echoPin = 8;        // Ultrasonic sensor Echo pin
const int detectionDistance = 100;  // Detection range in cm

// Compliments list (shortened to save memory)
const char* compliments[] = {
    "Looking sharp!", "Nice to see you!", "You're amazing!", 
    "Keep smiling!", "You're a gem!", "Cool style!", 
    "Stay awesome!", "Be yourself!", "Rock on!", 
    "Top-notch!", "Always shining!", "Simply great!"
};

// Variables
int complimentIndex = -1; // -1 indicates no compliment displayed
bool personDetected = false;
unsigned long lastDisplayTime = 0;
const unsigned long displayInterval = 3000;  // Delay to hold compliment (3 seconds)

void setup() {
    Serial.begin(9600);        // Start Serial Monitor
    lcd.init();                // Initialize LCD
    lcd.backlight();           // Turn on the LCD backlight
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mirror Mirror");
}

void loop() {
    // Measure distance from ultrasonic sensor
    long distance = measureDistance();

    // Check if a person is in range
    if (distance < detectionDistance) {
        if (!personDetected) {  // Only trigger if a person was not previously detected
            personDetected = true;
            complimentIndex = random(0, sizeof(compliments) / sizeof(compliments[0])); // Select a random compliment
            displayScrollingText(compliments[complimentIndex]); // Display compliment with scrolling
            lastDisplayTime = millis();
        }
    } else {
        // Reset when person leaves range
        if (personDetected) {
            personDetected = false;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Awaiting...");
        }
    }

    delay(500); // Delay to prevent rapid looping
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2; // Convert duration to distance in cm
    return distance;
}

// Function to display a scrolling compliment on the LCD
void displayScrollingText(const char* text) {
    int textLength = strlen(text);
    
    // Scroll text if it’s longer than 16 characters
    if (textLength > 16) {
        for (int i = 0; i < textLength - 15; i++) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(text + i);
            delay(300); // Adjust scroll speed as needed
        }
    } else {
        // If text is short, display it without scrolling
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(text);
    }
}
