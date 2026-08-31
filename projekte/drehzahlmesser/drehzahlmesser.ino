/*
 * ============================================
 * DREHZAHLMESSER FUER LUEFTER (RPM-METER)
 * ============================================
 * 
 * Was macht dieses Programm?
 * - Misst die Drehzahl eines Luefters mit einer Gabellichtschranke
 * - Zeigt die RPM (Umdrehungen pro Minute) auf einem LCD-Display an
 * - Gibt die Werte auch im Seriellen Monitor am PC aus
 * 
 * Bauteile:
 * - Arduino Mega 2560
 * - LCD 1602A (16 Pins, 4-Bit Modus)
 * - Gabellichtschranke LM393
 * - Potentiometer 10kOhm (fuer LCD-Kontrast)
 * - 5V Luefter (30x30mm, 7 Blaetter)
 * 
 * Erstellt: August 2026
 */

// === BIBLIOTHEKEN EINBINDEN ===
// LiquidCrystal ist eine fertige Bibliothek die uns das Ansteuern
// des LCD-Displays einfach macht. Ist schon in der Arduino IDE dabei.
#include <LiquidCrystal.h>

// === PIN-DEFINITIONEN ===
// Hier legen wir fest, welcher Arduino-Pin mit welchem Bauteil verbunden ist.
// "const int" bedeutet: eine Zahl die sich nie aendert (eine Konstante).

// LCD-Pins (siehe Verkabelungstabelle in der README)
const int LCD_RS = 12;   // Register Select
const int LCD_E  = 11;   // Enable
const int LCD_D4 = 5;    // Datenpin 4
const int LCD_D5 = 4;    // Datenpin 5
const int LCD_D6 = 3;    // Datenpin 6
const int LCD_D7 = 2;    // Datenpin 7

// Sensor-Pin
const int SENSOR_PIN = 18;  // Gabellichtschranke - Interrupt-faehiger Pin

// === EINSTELLUNGEN ===
// Diese Werte kannst du anpassen:
const int ANZAHL_BLAETTER = 7;           // Dein Luefter hat 7 Blaetter
const unsigned long MESSZEIT_MS = 1000;  // Alle 1000ms (= 1 Sekunde) wird die RPM berechnet

// === VARIABLEN ===
// "volatile" ist wichtig fuer Variablen die im Interrupt veraendert werden.
// Es sagt dem Arduino: "Diese Variable kann sich jederzeit aendern, 
// schau immer nach dem aktuellen Wert!"
volatile unsigned long impulsZaehler = 0;  // Zaehlt die Impulse vom Sensor

// Variablen fuer die Zeitmessung
unsigned long letzteMessung = 0;    // Wann wurde zuletzt die RPM berechnet?
unsigned long aktuelleRPM = 0;      // Das berechnete Ergebnis

// === LCD ERSTELLEN ===
// Hier sagen wir der Bibliothek, an welchen Pins das LCD haengt.
// Die Reihenfolge ist: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// === INTERRUPT-FUNKTION ===
// Diese Funktion wird AUTOMATISCH aufgerufen, jedes Mal wenn ein 
// Luefterblatt durch die Lichtschranke faehrt.
// Wichtig: Interrupt-Funktionen muessen kurz sein! Nur zaehlen, nichts anderes.
void impulsErkennung() {
  impulsZaehler++;  // Einen Impuls dazuzaehlen
}

// ============================================
// SETUP - Wird einmal beim Start ausgefuehrt
// ============================================
void setup() {
  
  // Seriellen Monitor starten (fuer Ausgabe am PC)
  // 115200 ist die Geschwindigkeit - stelle den Seriellen Monitor 
  // in der Arduino IDE auch auf 115200 Baud ein!
  Serial.begin(115200);
  Serial.println("=== Drehzahlmesser gestartet ===");
  Serial.println("Luefter: 7 Blaetter, 30x30mm");
  Serial.println("Warte auf Impulse...");
  Serial.println();
  
  // Sensor-Pin als Eingang festlegen
  // INPUT_PULLUP bedeutet: Der Pin wird intern auf HIGH gezogen.
  // Wenn die Lichtschranke ein Blatt erkennt, zieht sie den Pin auf LOW.
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  
  // Interrupt einrichten
  // digitalPinToInterrupt(18) wandelt Pin 18 in die Interrupt-Nummer um
  // impulsErkennung = die Funktion die aufgerufen wird
  // FALLING = reagiere wenn das Signal von HIGH auf LOW faellt
  //           (= Luefterblatt unterbricht den Lichtstrahl)
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), impulsErkennung, FALLING);
  
  // LCD starten (16 Zeichen breit, 2 Zeilen hoch)
  lcd.begin(16, 2);
  
  // Startbildschirm anzeigen
  lcd.setCursor(0, 0);         // Cursor auf Zeile 1, Position 1
  lcd.print("Drehzahlmesser");
  lcd.setCursor(0, 1);         // Cursor auf Zeile 2, Position 1
  lcd.print("Warte...");
  
  // Zeitmessung starten
  letzteMessung = millis();  // millis() gibt die Zeit seit dem Start in ms zurueck
}

// ============================================
// LOOP - Wird endlos wiederholt
// ============================================
void loop() {
  
  // Aktuelle Zeit holen
  unsigned long jetztMs = millis();
  
  // Ist die Messzeit (1 Sekunde) vergangen?
  if (jetztMs - letzteMessung >= MESSZEIT_MS) {
    
    // --- Impulse auslesen und zuruecksetzen ---
    // Waehrend wir die Impulse auslesen, muessen wir kurz die Interrupts
    // deaktivieren. Sonst koennte mitten im Lesen ein neuer Impuls kommen
    // und den Zaehler veraendern.
    noInterrupts();                         // Interrupts kurz pausieren
    unsigned long impulse = impulsZaehler;  // Wert kopieren
    impulsZaehler = 0;                      // Zaehler zuruecksetzen
    interrupts();                           // Interrupts wieder aktivieren
    
    // --- RPM berechnen ---
    // Formel: RPM = (Impulse / Anzahl_Blaetter) * (60000 / Messzeit_in_ms)
    //
    // Beispiel mit 700 Impulsen in 1 Sekunde:
    //   700 / 7 Blaetter = 100 Umdrehungen pro Sekunde
    //   100 * 60 = 6000 RPM
    //
    // Die Formel hier ist mathematisch umgestellt um Rundungsfehler zu vermeiden:
    aktuelleRPM = (impulse * 60000UL) / (ANZAHL_BLAETTER * MESSZEIT_MS);
    // "UL" bedeutet "unsigned long" - damit die Zahl nicht zu gross fuer
    // den Speicher wird (impulse * 60000 kann sehr gross werden!)
    
    // --- LCD aktualisieren ---
    lcd.setCursor(0, 0);
    lcd.print("Drehzahlmesser  ");  // Leerzeichen am Ende loeschen alte Zeichen
    
    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(aktuelleRPM);
    lcd.print("      ");  // Leerzeichen loeschen alte, laengere Zahlen
    
    // --- Serieller Monitor aktualisieren ---
    Serial.print("Impulse: ");
    Serial.print(impulse);
    Serial.print("  |  RPM: ");
    Serial.println(aktuelleRPM);
    
    // --- Zeitmessung neu starten ---
    letzteMessung = jetztMs;
  }
}
