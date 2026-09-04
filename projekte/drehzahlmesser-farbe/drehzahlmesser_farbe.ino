/*
 * =====================================================
 * DREHZAHLMESSER FUER LUEFTER - FARBVERSION (ST7789)
 * =====================================================
 * 
 * Was macht dieses Programm?
 * - Misst die Drehzahl eines Luefters mit einer Gabellichtschranke
 * - Zeigt die RPM als grosse Zahl auf einem Farbdisplay an
 * - Zeichnet einen farbigen Tacho-Balken (gruen/gelb/rot je nach Drehzahl)
 * - Zeigt den Rekordwert an
 * 
 * Bauteile:
 * - Arduino Mega 2560
 * - Waveshare 2" LCD Modul (IPS, 240x320, ST7789V, SPI)
 * - Gabellichtschranke LM393
 * - 5V Luefter (30x30mm, 7 Blaetter)
 * 
 * Benoetigte Bibliotheken (in Arduino IDE installieren):
 * - "Adafruit ST7735 and ST7789 Library"
 * - "Adafruit GFX Library"
 * (Sketch -> Bibliothek einbinden -> Bibliotheken verwalten -> suchen -> Install all)
 * 
 * WICHTIG: Das Waveshare-Modul hat KEINEN CS-Pin am Stecker bei manchen Versionen.
 * Falls doch vorhanden, wird er angeschlossen (siehe README). Dieser Code geht
 * davon aus, dass CS angeschlossen ist.
 * 
 * Erstellt: August 2026
 */

// === BIBLIOTHEKEN EINBINDEN ===
#include <Adafruit_GFX.h>      // Grafik-Grundfunktionen
#include <Adafruit_ST7789.h>   // Treiber fuer das ST7789-Display
#include <SPI.h>               // SPI-Kommunikation (schnelle Datenverbindung)

// === PIN-DEFINITIONEN DISPLAY ===
// Diese Pins verbinden das Display mit dem Arduino Mega.
// CLK und DIN nutzen die Hardware-SPI-Pins des Mega:
//   Mega SPI: CLK = Pin 52, DIN/MOSI = Pin 51
// Die restlichen Pins koennen wir frei waehlen:
const int TFT_CS  = 10;   // Chip Select
const int TFT_DC  = 9;    // Data/Command
const int TFT_RST = 8;    // Reset
// CLK -> Pin 52 (fest, Hardware-SPI)
// DIN -> Pin 51 (fest, Hardware-SPI)
// BL (Backlight) -> direkt an 5V (immer an)

// === PIN-DEFINITION SENSOR ===
const int SENSOR_PIN = 18;  // Gabellichtschranke - Interrupt-faehiger Pin

// === EINSTELLUNGEN ===
const int ANZAHL_BLAETTER = 7;
const unsigned long MESSZEIT_MS = 1000;
const long MAX_RPM = 10000;   // Skala-Obergrenze fuer den Tacho-Balken

// === FARBEN (RGB565-Format) ===
// Die Adafruit-Bibliothek nutzt vordefinierte Farbnamen:
#define FARBE_HINTERGRUND ST77XX_BLACK
#define FARBE_TITEL       ST77XX_CYAN
#define FARBE_ZAHL        ST77XX_WHITE
#define FARBE_GRUEN       ST77XX_GREEN
#define FARBE_GELB        ST77XX_YELLOW
#define FARBE_ROT         ST77XX_RED

// === DISPLAY-OBJEKT ===
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// === VARIABLEN ===
volatile unsigned long impulsZaehler = 0;
unsigned long letzteMessung = 0;
unsigned long aktuelleRPM = 0;
unsigned long letzteRPM = 999999;   // Um zu erkennen ob sich der Wert geaendert hat
unsigned long maxRPM = 0;

// === INTERRUPT-FUNKTION ===
void impulsErkennung() {
  impulsZaehler++;
}

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(115200);
  Serial.println("=== Drehzahlmesser Farbe (ST7789) gestartet ===");

  // Sensor einrichten
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), impulsErkennung, FALLING);

  // Display starten
  // 240x320 ist die Aufloesung des 2" Moduls
  tft.init(240, 320);
  tft.setRotation(0);                    // Ausrichtung (0-3, bei Bedarf aendern)
  tft.fillScreen(FARBE_HINTERGRUND);     // Bildschirm schwarz fuellen

  // Titel oben anzeigen (bleibt stehen)
  tft.setTextColor(FARBE_TITEL);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Drehzahlmesser");

  // Statischer Text "RPM" und "Max:"
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 130);
  tft.print("RPM");

  letzteMessung = millis();
}

// ============================================
// LOOP
// ============================================
void loop() {
  unsigned long jetztMs = millis();

  if (jetztMs - letzteMessung >= MESSZEIT_MS) {

    // Impulse auslesen
    noInterrupts();
    unsigned long impulse = impulsZaehler;
    impulsZaehler = 0;
    interrupts();

    // RPM berechnen
    aktuelleRPM = (impulse * 60000UL) / (ANZAHL_BLAETTER * MESSZEIT_MS);

    if (aktuelleRPM > maxRPM) {
      maxRPM = aktuelleRPM;
    }

    // Nur neu zeichnen wenn sich der Wert geaendert hat (verhindert Flackern)
    if (aktuelleRPM != letzteRPM) {
      zeigeRPM(aktuelleRPM, maxRPM);
      letzteRPM = aktuelleRPM;
    }

    // Serieller Monitor
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
// EIGENE FUNKTION: Grosse RPM-Zahl + Tacho-Balken zeichnen
// ============================================
void zeigeRPM(unsigned long rpm, unsigned long rekord) {

  // --- Grosse Zahl in der Mitte ---
  // Erst den alten Bereich schwarz uebermalen (sonst bleiben alte Ziffern stehen)
  tft.fillRect(10, 60, 220, 50, FARBE_HINTERGRUND);
  tft.setTextColor(FARBE_ZAHL);
  tft.setTextSize(6);        // Sehr grosse Schrift
  tft.setCursor(10, 60);
  tft.print(rpm);

  // --- Tacho-Balken ---
  // Farbe je nach Drehzahl: gruen (langsam), gelb (mittel), rot (schnell)
  uint16_t balkenFarbe;
  if (rpm < MAX_RPM / 3) {
    balkenFarbe = FARBE_GRUEN;
  } else if (rpm < (2 * MAX_RPM) / 3) {
    balkenFarbe = FARBE_GELB;
  } else {
    balkenFarbe = FARBE_ROT;
  }

  // Balkenbreite berechnen (max 220 Pixel breit)
  int balkenBreite = map(rpm, 0, MAX_RPM, 0, 220);
  if (balkenBreite > 220) balkenBreite = 220;
  if (balkenBreite < 0) balkenBreite = 0;

  // Balken-Hintergrund (Rahmen) und Fuellung
  tft.drawRect(10, 165, 220, 30, ST77XX_WHITE);       // weisser Rahmen
  tft.fillRect(11, 166, 218, 28, FARBE_HINTERGRUND);  // innen erst leeren
  tft.fillRect(11, 166, balkenBreite, 28, balkenFarbe); // dann farbig fuellen

  // --- Rekordwert unten ---
  tft.fillRect(10, 210, 220, 25, FARBE_HINTERGRUND);  // alten Wert loeschen
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 210);
  tft.print("Max: ");
  tft.print(rekord);
  tft.print(" RPM");
}
