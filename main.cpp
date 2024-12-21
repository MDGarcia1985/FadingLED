#include <Arduino.h>

// Define Arduino pins independently
#define LED1_PIN 6  // PWM-capable pin for fading (PD6)
#define LED2_PIN 5  // PWM-capable pin for fading (PD5)
#define LED3_PIN 4  // Software PWM (PD4)
#define LED4_PIN 3  // Software PWM (PD3)
#define LED5_PIN 2  // Software PWM (PD2)
#define LED6_PIN 7  // Software PWM (PD7)
#define LEDB1_PIN 8 // Blinking LED (PB0)
#define LEDB2_PIN 9 // Blinking LED (PB1)
#define POT_PIN A0  // Potentiometer input

// Variables for fading
int brightness = 0;         // Current brightness
unsigned long previousMillis = 0; // Timing for fading
const unsigned long fadeInterval = 30; // Interval for fading updates (ms)

// Variables for blinking
volatile bool blinkState = false; // State of blinking LED

void setup() {
    // Set up pins as OUTPUT
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    pinMode(LED6_PIN, OUTPUT);
    pinMode(LEDB1_PIN, OUTPUT);
    pinMode(LEDB2_PIN, OUTPUT);

    // Set up the potentiometer pin
    pinMode(POT_PIN, INPUT);

    // Set up timer interrupt for blinking LEDs
    cli(); // Disable global interrupts
    TCCR1A = 0; // Clear Timer/Counter Control Registers
    TCCR1B = 0;
    TCNT1 = 0;  // Initialize counter value
    OCR1A = 15624;  // Compare Match Register for 1 Hz
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    sei(); // Enable global interrupts
}

void loop() {
    unsigned long currentMillis = millis();

    // Handle fading LEDs
    if (currentMillis - previousMillis >= fadeInterval) {
        previousMillis = currentMillis;

        // Read potentiometer and map to brightness range
        int potValue = analogRead(POT_PIN);
        brightness = map(potValue, 0, 1023, 0, 255);

        // Write brightness to PWM-capable LEDs
        analogWrite(LED1_PIN, brightness);
        analogWrite(LED2_PIN, brightness);

        // Software PWM for non-PWM pins
        softwarePWM(LED3_PIN, brightness);
        softwarePWM(LED4_PIN, brightness);
        softwarePWM(LED5_PIN, brightness);
        softwarePWM(LED6_PIN, brightness);
    }

    // Blinking LEDs are handled in the ISR
}

// Interrupt Service Routine for blinking LEDs
ISR(TIMER1_COMPA_vect) {
    blinkState = !blinkState; // Toggle blink state
    digitalWrite(LEDB1_PIN, blinkState ? HIGH : LOW);
    digitalWrite(LEDB2_PIN, blinkState ? HIGH : LOW);
}

// Software PWM function for non-PWM pins
void softwarePWM(int pin, int brightness) {
    // Create a simple PWM cycle
    for (int i = 0; i < 256; i++) {
        if (i < brightness) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
        delayMicroseconds(40); // Add small delay to control cycle speed
    }
}
