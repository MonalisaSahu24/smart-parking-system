#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Servo gateServo;
#define ENTRY_SENSOR 2
#define EXIT_SENSOR 3
#define GREEN_LED 4
#define RED_LED 5
#define SERVO_PIN 6
int total_slots = 4; 
int occupied_slots = 0;
void setup() {
    pinMode(ENTRY_SENSOR, INPUT);
    pinMode(EXIT_SENSOR, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    gateServo.attach(SERVO_PIN);
    lcd.begin(16, 2);  
    delay(500); 
    lcd.setCursor(0, 0);
    lcd.print("Welcome!"); 
    delay(5000);
    updateDisplay();
    gateServo.write(0); 
}
void updateDisplay() {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (occupied_slots >= total_slots) {
        lcd.print("Sorry, Slot Full"); //Slots full
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW); 
    } else {
        lcd.print("Available Slots:");
        lcd.setCursor(0, 1);
        lcd.print(total_slots - occupied_slots);
        digitalWrite(RED_LED, LOW);  
        digitalWrite(GREEN_LED, HIGH); // Slots Available
    }
}
void loop() {
    if (digitalRead(ENTRY_SENSOR) == HIGH && occupied_slots < total_slots) {
        occupied_slots++;
        openGate();
        delay(3000);
        closeGate();
        updateDisplay();
    } else if (digitalRead(ENTRY_SENSOR) == HIGH && occupied_slots >= total_slots) {
        updateDisplay(); 
        delay(3000);  
    }
    if (digitalRead(EXIT_SENSOR) == HIGH && occupied_slots > 0) {
        occupied_slots--;
        openGate();
        delay(3000);
        closeGate();
        updateDisplay();
    }
    delay(500);
}
void openGate() {
    gateServo.write(90); 
}
void closeGate() {
    gateServo.write(20);  
}