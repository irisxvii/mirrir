#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin connections
const int trigPin = 9;        // Ultrasonic sensor Trigger pin
const int echoPin = 8;        // Ultrasonic sensor Echo pin
const int detectionDistance = 100;  // Distance threshold in cm for detecting presence

// Compliment list
const char* compliments[50] = {
    "You're amazing!", "Looking great!", "You're unstoppable!", 
    "You're a genius!", "You shine bright!", "Awesome style!", 
    "You got this!", "Simply the best!", "You inspire others!", 
    "Keep it up!", "You're so talented!", "Wow, just wow!", 
    "You are enough!", "Breathtaking!", "Simply radiant!", 
    "Superb attitude!", "You rock!", "Impressive!", 
    "A true gem!", "You look fantastic!", "Never stop dreaming!", 
    "You're so unique!", "Keep shining!", "Fabulous!", 
    "Marvelous mind!", "Radiant smile!", "Such charm!", 
    "Purely brilliant!", "Unstoppable!", "Incredible!", 
    "You're courageous!", "Stand tall!", "Exceptional!", 
    "Amazing energy!", "You’re so cool!", "Magnificent!", 
    "What a star!", "Radiating positivity!", "You are loved!", 
    "True inspiration!", "Remarkable!", "Bright mind!", 
    "Epic presence!", "You're terrific!", "Superb confidence!", 
    "So charismatic!", "Simply gorgeous!", "Extraordinary!", 
    "Always be you!", "Wonderful person!"
};

// Variables for compliment display
int complimentIndex = -1; // -1 indicates no compliment displayed
bool personDetected = false;

void setup() {
    Serial.begin(9600);        // Start Serial Monitor for debugging
    lcd.init();                // Initialize the LCD
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
            complimentIndex = random(0, 50);  // Select a random compliment
            displayCompliment(compliments[complimentIndex]); // Display compliment
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

// Function to display a compliment on the LCD
void displayCompliment(const char* compliment) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(compliment); // Display compliment on LCD
}
