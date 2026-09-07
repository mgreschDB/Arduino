/*
 * =====================================================
 * LED-STREIFEN EFFEKTE (WS2812B / NeoPixel)
 * =====================================================
 * 
 * Was macht dieses Programm?
 * - Steuert einen WS2812B LED-Streifen mit 144 LEDs
 * - Zeigt nacheinander verschiedene Lichteffekte:
 *   1. Regenbogen (fliessend)
 *   2. Lauflicht (ein Punkt wandert)
 *   3. Farbwechsel (ganzer Streifen)
 *   4. Funkeln (zufaellige LEDs blitzen)
 *   5. Theater-Chase (Lauflicht-Muster)
 * 
 * Bauteile:
 * - Arduino Mega 2560
 * - WS2812B LED-Streifen (144 LEDs)
 * - 330-470 Ohm Widerstand (in der Datenleitung)
 * - Externe 5V-Stromversorgung (WICHTIG!)
 * 
 * Benoetigte Bibliothek:
 * - "FastLED" (in Arduino IDE installieren)
 * 
 * ============================================
 * !!! WICHTIG - STROMSICHERHEIT !!!
 * ============================================
 * 144 LEDs koennen bei voller Helligkeit bis zu 8.6A ziehen!
 * Das ist VIEL zu viel fuer Arduino-USB oder ein kleines Netzteil.
 * 
 * Schutzmassnahmen in diesem Code:
 * - Helligkeit auf 25% begrenzt (HELLIGKEIT)
 * - FastLED-Strombegrenzung auf 500mA gesetzt (setMaxPowerInVoltsAndMilliamps)
 *   -> FastLED dimmt automatisch runter wenn es zu viel wuerde
 * 
 * Passe MAX_STROM_MA an dein Netzteil an!
 * 
 * Erstellt: August 2026
 */

#include <FastLED.h>

// === EINSTELLUNGEN ===
const int ANZAHL_LEDS = 144;      // Anzahl LEDs auf deinem Streifen
const int DATEN_PIN = 6;          // Arduino-Pin fuer die Datenleitung (gruen)
const int HELLIGKEIT = 64;        // 0-255. 64 = 25% (sicher). Nicht hoeher ohne staerkeres Netzteil!
const int MAX_STROM_MA = 500;     // Strombegrenzung in mA - an dein Netzteil anpassen!

// Das Array das alle LED-Farben speichert
CRGB leds[ANZAHL_LEDS];

// Variablen fuer die Effekt-Steuerung
int aktuellerEffekt = 0;              // Welcher Effekt laeuft gerade?
const int ANZAHL_EFFEKTE = 5;
unsigned long effektStart = 0;
const unsigned long EFFEKT_DAUER_MS = 8000;  // Jeder Effekt laeuft 8 Sekunden

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(115200);
  Serial.println("=== LED-Streifen Effekte gestartet ===");
  Serial.print("LEDs: ");
  Serial.println(ANZAHL_LEDS);

  // FastLED einrichten: WS2812B, Datenpin, Farbreihenfolge GRB (typisch fuer WS2812B)
  FastLED.addLeds<WS2812B, DATEN_PIN, GRB>(leds, ANZAHL_LEDS);

  // Helligkeit begrenzen (Sicherheit!)
  FastLED.setBrightness(HELLIGKEIT);

  // Strombegrenzung: FastLED dimmt automatisch wenn mehr als MAX_STROM_MA noetig waere
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_STROM_MA);

  // Alle LEDs ausschalten zum Start
  FastLED.clear();
  FastLED.show();

  effektStart = millis();
}

// ============================================
// LOOP
// ============================================
void loop() {

  // Nach EFFEKT_DAUER_MS zum naechsten Effekt wechseln
  if (millis() - effektStart >= EFFEKT_DAUER_MS) {
    aktuellerEffekt++;
    if (aktuellerEffekt >= ANZAHL_EFFEKTE) {
      aktuellerEffekt = 0;  // Wieder von vorne
    }
    effektStart = millis();
    FastLED.clear();
    Serial.print("Effekt: ");
    Serial.println(aktuellerEffekt);
  }

  // Den aktuellen Effekt ausfuehren
  switch (aktuellerEffekt) {
    case 0: effektRegenbogen();   break;
    case 1: effektLauflicht();    break;
    case 2: effektFarbwechsel();  break;
    case 3: effektFunkeln();      break;
    case 4: effektTheaterChase(); break;
  }
}

// ============================================
// EFFEKT 1: REGENBOGEN
// ============================================
// Ein fliessender Regenbogen ueber den ganzen Streifen.
void effektRegenbogen() {
  static uint8_t startFarbe = 0;
  startFarbe++;  // Farbe verschiebt sich -> Regenbogen "fliesst"

  // fill_rainbow verteilt den Regenbogen ueber alle LEDs
  fill_rainbow(leds, ANZAHL_LEDS, startFarbe, 7);
  FastLED.show();
  delay(20);
}

// ============================================
// EFFEKT 2: LAUFLICHT
// ============================================
// Ein einzelner heller Punkt wandert ueber den Streifen.
void effektLauflicht() {
  static int position = 0;

  FastLED.clear();                          // Alle aus
  leds[position] = CRGB::Blue;              // Nur eine LED an (blau)
  // Ein kleiner Schweif fuer den Effekt
  if (position > 0)  leds[position - 1] = CRGB(0, 0, 80);
  if (position > 1)  leds[position - 2] = CRGB(0, 0, 30);
  FastLED.show();

  position++;
  if (position >= ANZAHL_LEDS) position = 0;
  delay(30);
}

// ============================================
// EFFEKT 3: FARBWECHSEL
// ============================================
// Der ganze Streifen wechselt langsam die Farbe.
void effektFarbwechsel() {
  static uint8_t farbton = 0;
  farbton++;

  // fill_solid faerbt alle LEDs in einer Farbe (aus dem Farbkreis HSV)
  fill_solid(leds, ANZAHL_LEDS, CHSV(farbton, 255, 255));
  FastLED.show();
  delay(30);
}

// ============================================
// EFFEKT 4: FUNKELN
// ============================================
// Zufaellige LEDs blitzen kurz weiss auf (wie Glitzern).
void effektFunkeln() {
  // Alle LEDs leicht abdunkeln (erzeugt ein Nachleuchten)
  fadeToBlackBy(leds, ANZAHL_LEDS, 40);

  // Eine zufaellige LED aufblitzen lassen
  int zufallsLED = random(ANZAHL_LEDS);
  leds[zufallsLED] = CRGB::White;

  FastLED.show();
  delay(30);
}

// ============================================
// EFFEKT 5: THEATER-CHASE
// ============================================
// Ein klassisches "Lauflicht-Muster" wie bei einer Kino-Marquise.
void effektTheaterChase() {
  static int versatz = 0;

  FastLED.clear();
  // Jede 3. LED anschalten, das Muster verschiebt sich
  for (int i = 0; i < ANZAHL_LEDS; i++) {
    if ((i + versatz) % 3 == 0) {
      leds[i] = CRGB::Red;
    }
  }
  FastLED.show();

  versatz++;
  if (versatz >= 3) versatz = 0;
  delay(100);
}
