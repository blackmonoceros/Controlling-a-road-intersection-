// Traffic light control system with pedestrian display
// Displays messages for pedestrians: STOP, GET READY, GO... 
// Synchronized with traffic lights, according to traffic rules.
// 

#include <Wire.h>                 // I2C library – required for LCD
#include <LiquidCrystal_I2C.h>    // LCD 2x16 with I2C interface

LiquidCrystal_I2C lcd(0x20, 16, 2); // Create LCD at address 0x20

// Constants – pin assignments for lights and button
#define zielone_samochody 1
#define zolte_samochody 2
#define czerwone_samochody 3
#define zielone_piesi 4
#define czerwone_piesi 5
#define przycisk 6

// Phase durations (in milliseconds)
#define czas_zolte 5000           // Yellow light for cars before stopping
#define czas_zielone_piesi 6000   // Green for pedestrians – crossing
#define czas_czerwono_zolte 2000  // Cars transition from red to green

void setup() {
    Wire.begin();                 // Start I2C communication
    lcd.init();                   // Initialize LCD
    lcd.backlight();              // Turn on backlight

    // Set pin modes
    pinMode(przycisk, INPUT_PULLUP); // Button as input with pull-up resistor
    pinMode(czerwone_piesi, OUTPUT);
    pinMode(zielone_piesi, OUTPUT);
    pinMode(czerwone_samochody, OUTPUT);
    pinMode(zolte_samochody, OUTPUT);
    pinMode(zielone_samochody, OUTPUT);

    ustaw_poczatkowy_stan();      // Initial state of lights and display
}

void loop() {
    // Check if pedestrian pressed the button
    if (digitalRead(przycisk) == LOW) {
        delay(50); // Debounce – short pause to avoid accidental detection
        if (digitalRead(przycisk) == LOW) {
            przygotowanie_dla_pieszych(); // Warning phase – yellow for cars
            piesi_moga_przejsc();         // Pedestrians can cross
            przejscie_do_samochodow();    // Pedestrians finish crossing
            samochody_moga_jechac();      // Cars go
        }
    }
}

// Initial setup: cars have green, pedestrians red
void ustaw_poczatkowy_stan() {
    digitalWrite(zielone_samochody, HIGH);
    digitalWrite(zolte_samochody, LOW);
    digitalWrite(czerwone_samochody, LOW);
    digitalWrite(czerwone_piesi, HIGH);
    digitalWrite(zielone_piesi, LOW);

    lcd.clear();
    lcd.setCursor(4, 0);      // Centered header
    lcd.print("PIESZY:");
    lcd.setCursor(5, 1);      // STOP centered on bottom line
    lcd.print("STOP");
}

// Cars get yellow light – pedestrians still wait
void przygotowanie_dla_pieszych() {
    digitalWrite(zielone_samochody, LOW);
    digitalWrite(zolte_samochody, HIGH);
    digitalWrite(czerwone_samochody, LOW);
    digitalWrite(czerwone_piesi, HIGH);
    digitalWrite(zielone_piesi, LOW);

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("PIESZY:");
    lcd.setCursor(1, 1);      // "PRZYGOTUJ SIE" is 13 characters
    lcd.print("PRZYGOTUJ SIE");
    delay(czas_zolte);        // Yellow light duration

    digitalWrite(zolte_samochody, LOW);
}

// Pedestrians get green – can cross
void piesi_moga_przejsc() {
    digitalWrite(czerwone_samochody, HIGH);
    digitalWrite(czerwone_piesi, LOW);
    digitalWrite(zielone_piesi, HIGH);

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("PIESZY:");
    lcd.setCursor(6, 1);      // "IDZ" centered
    lcd.print("IDZ");
    delay(czas_zielone_piesi); // Crossing time
}

// Pedestrians finished crossing – cars prepare to go
void przejscie_do_samochodow() {
    digitalWrite(zielone_piesi, LOW);
    digitalWrite(czerwone_piesi, HIGH);
    digitalWrite(zolte_samochody, HIGH);

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("PIESZY:");
    lcd.setCursor(5, 1);
    lcd.print("STOP");
    delay(czas_czerwono_zolte);

    digitalWrite(zolte_samochody, LOW);
}

// Cars go again, pedestrians wait
void samochody_moga_jechac() {
    digitalWrite(czerwone_samochody, LOW);
    digitalWrite(zielone_samochody, HIGH);

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("PIESZY:");
    lcd.setCursor(5, 1);
    lcd.print("STOP");
    delay(czas_zolte);
}
