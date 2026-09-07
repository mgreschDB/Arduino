/*
 * =========================================================
 * DREHZAHLMESSER VERGLEICH - 2 LUEFTER MIT TACHO (ST7789)
 * =========================================================
 * 
 * Was macht dieses Programm?
 * - Misst die Drehzahl von ZWEI Lueftern gleichzeitig
 * - Zeigt fuer jeden Luefter einen runden Tacho mit Nadel an
 * - Zeigt die RPM-Zahl und einen Vergleich (welcher ist schneller)
 * 
 * Bauteile:
 * - Arduino Mega 2560
 * - Waveshare 2" LCD Modul (IPS, 240x320, ST7789V, SPI)
 * - 2x Gabellichtschranke LM393
 * - 2x 5V Luefter (30x30mm, 7 Blaetter)
 * 
 * Benoetigte Bibliotheken:
 * - "Adafruit ST7735 and ST7789 Library"
 * - "Adafruit GFX Library"
 * 
 * Erstellt: August 2026
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h>   // fuer sin() und cos() (Tacho-Nadel berechnen)

// === DISPLAY-PINS ===
const int TFT_CS  = 10;
const int TFT_DC  = 9;
const int TFT_RST = 8;
// CLK -> Pin 52, DIN -> Pin 51 (Hardware-SPI, fest)

// === SENSOR-PINS ===
const int SENSOR_A_PIN = 18;  // Luefter A - Interrupt-Pin
const int SENSOR_B_PIN = 19;  // Luefter B - Interrupt-Pin (NEU)

// === EINSTELLUNGEN ===
const int ANZAHL_BLAETTER = 7;
const unsigned long MESSZEIT_MS = 1000;
const long MAX_RPM = 10000;   // Skala-Endwert der Tachos

// === FARBEN ===
#define C_BG      ST77XX_BLACK
#define C_TITEL   ST77XX_CYAN
#define C_TEXT    ST77XX_WHITE
#define C_NADEL   ST77XX_RED
#define C_SKALA   ST77XX_WHITE
#define C_GRUEN   ST77XX_GREEN
#define C_GELB    ST77XX_YELLOW
#define C_ROT     ST77XX_RED

// === DISPLAY-OBJEKT ===
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// === VARIABLEN fuer beide Sensoren ===
volatile unsigned long impulseA = 0;
volatile unsigned long impulseB = 0;
unsigned long letzteMessung = 0;
unsigned long rpmA = 0, rpmB = 0;
unsigned long letzteRpmA = 999999, letzteRpmB = 999999;

// Tacho-Geometrie (wird in setup berechnet)
// Tacho A: obere Bildhaelfte, Tacho B: untere Bildhaelfte
const int TACHO_A_X = 120, TACHO_A_Y = 95,  TACHO_RADIUS = 70;
const int TACHO_B_X = 120, TACHO_B_Y = 250;

// === INTERRUPT-FUNKTIONEN ===
void impulsA() { impulseA++; }
void impulsB() { impulseB++; }

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(115200);
  Serial.println("=== Drehzahlmesser Vergleich (2 Luefter) ===");

  // Beide Sensoren einrichten
  pinMode(SENSOR_A_PIN, INPUT_PULLUP);
  pinMode(SENSOR_B_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_A_PIN), impulsA, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_B_PIN), impulsB, FALLING);

  // Display starten
  tft.init(240, 320);
  tft.setRotation(0);
  tft.fillScreen(C_BG);

  // Statische Skalen einmal zeichnen (die aendern sich nie)
  zeichneTachoSkala(TACHO_A_X, TACHO_A_Y, "Luefter A");
  zeichneTachoSkala(TACHO_B_X, TACHO_B_Y, "Luefter B");

  letzteMessung = millis();
}

// ============================================
// LOOP
// ============================================
void loop() {
  unsigned long jetztMs = millis();

  if (jetztMs - letzteMessung >= MESSZEIT_MS) {

    // Impulse beider Sensoren auslesen
    noInterrupts();
    unsigned long iA = impulseA;
    unsigned long iB = impulseB;
    impulseA = 0;
    impulseB = 0;
    interrupts();

    // RPM berechnen
    rpmA = (iA * 60000UL) / (ANZAHL_BLAETTER * MESSZEIT_MS);
    rpmB = (iB * 60000UL) / (ANZAHL_BLAETTER * MESSZEIT_MS);

    // Tachos nur neu zeichnen wenn sich was geaendert hat
    if (rpmA != letzteRpmA) {
      zeichneNadelUndWert(TACHO_A_X, TACHO_A_Y, rpmA, letzteRpmA);
      letzteRpmA = rpmA;
    }
    if (rpmB != letzteRpmB) {
      zeichneNadelUndWert(TACHO_B_X, TACHO_B_Y, rpmB, letzteRpmB);
      letzteRpmB = rpmB;
    }

    // Vergleich in der Mitte anzeigen
    zeigeVergleich(rpmA, rpmB);

    // Serieller Monitor
    Serial.print("Luefter A: ");
    Serial.print(rpmA);
    Serial.print(" RPM  |  Luefter B: ");
    Serial.print(rpmB);
    Serial.println(" RPM");

    letzteMessung = jetztMs;
  }
}

// ============================================
// TACHO-SKALA zeichnen (einmalig, aendert sich nie)
// ============================================
// Zeichnet den Halbkreis-Bogen mit Skalenstrichen und dem Namen darunter.
void zeichneTachoSkala(int mx, int my, const char* name) {
  // Halbkreis-Bogen von 180 Grad (links) bis 0 Grad (rechts), oben herum
  // Wir zeichnen ihn aus vielen kurzen Linien zusammen.
  for (int winkel = 180; winkel <= 360; winkel += 5) {
    float rad1 = winkel * PI / 180.0;
    float rad2 = (winkel + 5) * PI / 180.0;
    int x1 = mx + cos(rad1) * TACHO_RADIUS;
    int y1 = my + sin(rad1) * TACHO_RADIUS;
    int x2 = mx + cos(rad2) * TACHO_RADIUS;
    int y2 = my + sin(rad2) * TACHO_RADIUS;
    tft.drawLine(x1, y1, x2, y2, C_SKALA);
  }

  // Skalenstriche: alle 25% ein laengerer Strich, dazwischen kurze
  for (int i = 0; i <= 10; i++) {
    // Winkel von 180 (=0 RPM) bis 360 (=MAX_RPM)
    float winkel = 180 + (i * 18);   // 10 Abschnitte a 18 Grad = 180 Grad
    float rad = winkel * PI / 180.0;
    int laenge = (i % 5 == 0) ? 10 : 5;  // jeder 5. Strich laenger
    int xa = mx + cos(rad) * TACHO_RADIUS;
    int ya = my + sin(rad) * TACHO_RADIUS;
    int xi = mx + cos(rad) * (TACHO_RADIUS - laenge);
    int yi = my + sin(rad) * (TACHO_RADIUS - laenge);
    tft.drawLine(xa, ya, xi, yi, C_SKALA);
  }

  // Name unter dem Tacho
  tft.setTextColor(C_TITEL);
  tft.setTextSize(1);
  tft.setCursor(mx - 30, my + 18);
  tft.print(name);
}

// ============================================
// NADEL + RPM-WERT zeichnen
// ============================================
// Loescht die alte Nadel (uebermalen mit Hintergrund) und zeichnet die neue.
void zeichneNadelUndWert(int mx, int my, unsigned long rpm, unsigned long alteRpm) {

  // --- Alte Nadel loeschen (mit Hintergrundfarbe uebermalen) ---
  zeichneNadel(mx, my, alteRpm, C_BG);

  // --- Neue Nadel zeichnen ---
  zeichneNadel(mx, my, rpm, C_NADEL);

  // --- Mittelpunkt (kleiner Kreis) ---
  tft.fillCircle(mx, my, 4, C_TEXT);

  // --- RPM-Zahl unter dem Namen ---
  // Erst alten Wert-Bereich loeschen
  tft.fillRect(mx - 45, my + 30, 90, 20, C_BG);
  tft.setTextColor(C_TEXT);
  tft.setTextSize(2);
  // Zahl zentriert ausgeben
  int ziffern = String(rpm).length();
  tft.setCursor(mx - (ziffern * 6), my + 30);
  tft.print(rpm);
}

// Hilfsfunktion: zeichnet eine Nadel in der angegebenen Farbe
void zeichneNadel(int mx, int my, unsigned long rpm, uint16_t farbe) {
  // RPM auf Winkel umrechnen: 0 RPM = 180 Grad (links), MAX_RPM = 360 Grad (rechts)
  long begrenzt = rpm;
  if (begrenzt > MAX_RPM) begrenzt = MAX_RPM;
  float winkel = 180 + ((float)begrenzt / MAX_RPM) * 180.0;
  float rad = winkel * PI / 180.0;
  int spitzeX = mx + cos(rad) * (TACHO_RADIUS - 12);
  int spitzeY = my + sin(rad) * (TACHO_RADIUS - 12);
  tft.drawLine(mx, my, spitzeX, spitzeY, farbe);
  // Nadel etwas dicker: zwei zusaetzliche Linien daneben
  tft.drawLine(mx + 1, my, spitzeX, spitzeY, farbe);
  tft.drawLine(mx - 1, my, spitzeX, spitzeY, farbe);
}

// ============================================
// VERGLEICH anzeigen (welcher Luefter schneller ist)
// ============================================
void zeigeVergleich(unsigned long a, unsigned long b) {
  // Bereich zwischen den Tachos leeren
  tft.fillRect(0, 158, 240, 20, C_BG);
  tft.setTextSize(1);

  if (a == 0 && b == 0) {
    return;  // Nichts anzeigen wenn beide still stehen
  }

  tft.setCursor(60, 162);
  if (a > b) {
    tft.setTextColor(C_GRUEN);
    long diff = a - b;
    tft.print("A schneller (+");
    tft.print(diff);
    tft.print(")");
  } else if (b > a) {
    tft.setTextColor(C_GRUEN);
    long diff = b - a;
    tft.print("B schneller (+");
    tft.print(diff);
    tft.print(")");
  } else {
    tft.setTextColor(C_GELB);
    tft.print("Gleich schnell");
  }
}
