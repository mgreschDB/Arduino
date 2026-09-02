/*
 * ============================================
 * DREHZAHLMESSER FUER LUEFTER - OLED VERSION
 * ============================================
 * 
 * Was macht dieses Programm?
 * - Misst die Drehzahl eines Luefters mit einer Gabellichtschranke
 * - Zeigt die RPM (Umdrehungen pro Minute) auf einem OLED-Display an
 * - Zeigt zusaetzlich eine grosse Zahl und einen Balken an
 * - Gibt die Werte auch im Seriellen Monitor am PC aus
 * 
 * Bauteile:
 * - Arduino Mega 2560
 * - OLED-Display 0.96" SSD1306 (128x64 Pixel, I2C)
 * - Gabellichtschranke LM393
 * - 5V Luefter (30x30mm, 7 Blaetter)
 * 
 * WICHTIG: Diese Version braucht KEIN Potentiometer mehr!
 * Das OLED hat keinen Kontrast der eingestellt werden muss.
 * 
 * Benoetigte Bibliotheken (in Arduino IDE installieren):
 * - "Adafruit SSD1306"
 * - "Adafruit GFX Library"
 * (Sketch -> Bibliothek einbinden -> Bibliotheken verwalten -> suchen -> installieren)
 * 
 * Erstellt: August 2026
 */

// === BIBLIOTHEKEN EINBINDEN ===
#include <Wire.h>              // Fuer die I2C-Kommunikation (2-Draht-Verbindung)
#include <Adafruit_GFX.h>      // Grafik-Grundfunktionen (Linien, Text, etc.)
#include <Adafruit_SSD1306.h>  // Steuert das OLED-Display

// === OLED-EINSTELLUNGEN ===
const int OLED_BREITE = 128;   // Displaybreite in Pixeln
const int OLED_HOEHE = 64;     // Displayhoehe in Pixeln
const int OLED_RESET = -1;     // -1 = kein separater Reset-Pin (bei I2C ueblich)
const int OLED_ADRESSE = 0x3C; // I2C-Adresse des Displays (fast immer 0x3C)

// Das Display-Objekt erstellen
Adafruit_SSD1306 display(OLED_BREITE, OLED_HOEHE, &Wire, OLED_RESET);

// === PIN-DEFINITIONEN ===
// Beim Arduino Mega ist I2C fest auf:
//   SDA = Pin 20
//   SCL = Pin 21
// Die muessen wir nicht im Code angeben, die Wire-Bibliothek weiss das.

const int SENSOR_PIN = 18;  // Gabellichtschranke - Interrupt-faehiger Pin

// === EINSTELLUNGEN ===
const int ANZAHL_BLAETTER = 7;           // Dein Luefter hat 7 Blaetter
const unsigned long MESSZEIT_MS = 1000;  // Alle 1 Sekunde wird die RPM berechnet
const long MAX_RPM_BALKEN = 10000;       // Obergrenze fuer den Balken (fuer die Skala)

// === VARIABLEN ===
volatile unsigned long impulsZaehler = 0;  // Zaehlt die Impulse vom Sensor
unsigned long letzteMessung = 0;           // Wann wurde zuletzt gerechnet?
unsigned long aktuelleRPM = 0;             // Das berechnete Ergebnis
unsigned long maxRPM = 0;                  // Hoechster gemessener Wert (Rekord)

// === INTERRUPT-FUNKTION ===
// Wird automatisch aufgerufen wenn ein Luefterblatt durchlaeuft.
void impulsErkennung() {
  impulsZaehler++;
}

// ============================================
// SETUP - Wird einmal beim Start ausgefuehrt
// ============================================
void setup() {
  
  // Seriellen Monitor starten (115200 Baud)
  Serial.begin(115200);
  Serial.println("=== Drehzahlmesser OLED gestartet ===");
  
  // Sensor-Pin als Eingang mit internem Pullup
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  
  // Interrupt einrichten: reagiere wenn Signal von HIGH auf LOW faellt
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), impulsErkennung, FALLING);
  
  // OLED-Display starten
  // Wenn das Display nicht antwortet, bleiben wir hier haengen (mit Fehlermeldung)
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADRESSE)) {
    Serial.println("FEHLER: OLED nicht gefunden! Verkabelung pruefen.");
    Serial.println("Ist SDA an Pin 20 und SCL an Pin 21? Adresse 0x3C?");
    while (true) {
      // Endlosschleife - hier kommen wir nicht mehr raus.
      // Wenn das passiert: Verkabelung und I2C-Adresse pruefen.
    }
  }
  
  // Startbildschirm zeigen
  display.clearDisplay();              // Bildschirm leeren
  display.setTextColor(SSD1306_WHITE); // Textfarbe weiss (OLED ist einfarbig)
  display.setTextSize(1);              // Textgroesse 1 (klein)
  display.setCursor(0, 0);             // Cursor oben links
  display.println("Drehzahlmesser");
  display.println("");
  display.println("Warte auf Luefter...");
  display.display();                   // WICHTIG: erst mit display() wird alles sichtbar!
  
  letzteMessung = millis();
}

// ============================================
// LOOP - Wird endlos wiederholt
// ============================================
void loop() {
  
  unsigned long jetztMs = millis();
  
  // Ist die Messzeit (1 Sekunde) vergangen?
  if (jetztMs - letzteMessung >= MESSZEIT_MS) {
    
    // --- Impulse auslesen und zuruecksetzen (Interrupts kurz pausieren) ---
    noInterrupts();
    unsigned long impulse = impulsZaehler;
    impulsZaehler = 0;
    interrupts();
    
    // --- RPM berechnen ---
    // RPM = (Impulse / Blaetter) * (60000ms / Messzeit)
    aktuelleRPM = (impulse * 60000UL) / (ANZAHL_BLAETTER * MESSZEIT_MS);
    
    // Rekord merken
    if (aktuelleRPM > maxRPM) {
      maxRPM = aktuelleRPM;
    }
    
    // --- OLED aktualisieren ---
    zeigeAnzeige(aktuelleRPM, maxRPM);
    
    // --- Serieller Monitor ---
    Serial.print("Impulse: ");
    Serial.print(impulse);
    Serial.print("  |  RPM: ");
    Serial.print(aktuelleRPM);
    Serial.print("  |  Max: ");
    Serial.println(maxRPM);
    
    letzteMessung = jetztMs;
  }
}

// ============================================
// EIGENE FUNKTION: Anzeige auf dem OLED zeichnen
// ============================================
// Diese Funktion baut das komplette Displaybild auf.
// Wir lagern das in eine eigene Funktion aus, damit loop() uebersichtlich bleibt.
void zeigeAnzeige(unsigned long rpm, unsigned long rekord) {
  
  display.clearDisplay();  // Alten Inhalt loeschen
  
  // --- Ueberschrift (kleiner Text oben) ---
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Drehzahlmesser");
  
  // --- Grosse RPM-Zahl in der Mitte ---
  display.setTextSize(3);       // Textgroesse 3 (gross)
  display.setCursor(0, 16);
  display.print(rpm);
  
  // "RPM" klein daneben
  display.setTextSize(1);
  display.setCursor(0, 42);
  display.print("RPM");
  
  // --- Rekordwert rechts ---
  display.setTextSize(1);
  display.setCursor(70, 42);
  display.print("Max:");
  display.print(rekord);
  
  // --- Balkenanzeige unten ---
  // Der Balken zeigt visuell wie hoch die Drehzahl im Verhaeltnis zum Maximum ist.
  // map() rechnet die RPM auf eine Balkenbreite von 0 bis 124 Pixel um.
  int balkenBreite = map(rpm, 0, MAX_RPM_BALKEN, 0, 124);
  if (balkenBreite > 124) balkenBreite = 124;  // Nicht ueber den Rand hinaus
  if (balkenBreite < 0) balkenBreite = 0;
  
  // Rahmen des Balkens (leeres Rechteck)
  display.drawRect(0, 54, 128, 10, SSD1306_WHITE);
  // Gefuellter Teil des Balkens
  display.fillRect(2, 56, balkenBreite, 6, SSD1306_WHITE);
  
  // --- Alles auf einmal anzeigen ---
  display.display();
}
