# Projekt: LED-Streifen Effekte (WS2812B)

## Was macht dieses Projekt?

Steuert einen WS2812B LED-Streifen mit 144 adressierbaren RGB-LEDs.
Das Programm zeigt nacheinander 5 verschiedene Lichteffekte, jeder laeuft 8 Sekunden:

1. **Regenbogen** - fliessender Farbverlauf ueber den ganzen Streifen
2. **Lauflicht** - ein blauer Punkt mit Schweif wandert
3. **Farbwechsel** - der ganze Streifen wechselt langsam die Farbe
4. **Funkeln** - zufaellige LEDs blitzen weiss auf
5. **Theater-Chase** - klassisches Lauflicht-Muster

---

## !!! WICHTIG: STROMSICHERHEIT ZUERST LESEN !!!

**144 LEDs koennen bei voller Helligkeit bis zu 8,6 Ampere ziehen.**

Das ist weit mehr als der Arduino-USB (500mA) oder dein Breadboard-Netzteil liefern kann.
Wenn du das ignorierst, koennen folgende Dinge passieren:
- Der Arduino startet staendig neu (Unterspannung)
- Das Netzteil ueberhitzt
- Im schlimmsten Fall Kabelbrand bei zu duennen Kabeln

### Schutzmassnahmen in diesem Projekt

Der Code schuetzt dich mehrfach:
- **Helligkeit auf 25% begrenzt** (`HELLIGKEIT = 64`)
- **FastLED-Strombegrenzung auf 500mA** (`MAX_STROM_MA` - FastLED dimmt automatisch runter)
- Die Effekte lassen **nie alle 144 LEDs gleichzeitig voll weiss** leuchten

Mit diesen Einstellungen ist es sicher, auch am Breadboard-Netzteil.

### Fuer volle Helligkeit spaeter

Wenn du irgendwann alle LEDs hell leuchten lassen willst, brauchst du ein
**separates 5V-Netzteil mit mindestens 5-10 Ampere** (z.B. ein 5V/10A Netzteil).
Dann kannst du `HELLIGKEIT` und `MAX_STROM_MA` hochsetzen.

---

## Benoetigte Bauteile

| Bauteil | Anzahl | Status |
|---|---|---|
| Arduino Mega 2560 | 1 | Vorhanden |
| WS2812B Streifen (144 LEDs) | 1 | Vorhanden |
| Widerstand 330-470 Ohm | 1 | Aus dem Kit (330 Ohm: orange-orange-braun) |
| Breadboard-Netzteil (9V→5V) oder 5V-Netzteil | 1 | Vorhanden |
| Jumperkabel | einige | Vorhanden |

---

## Benoetigte Bibliothek

- **FastLED** (Sketch → Bibliothek einbinden → Bibliotheken verwalten → "FastLED" suchen → installieren)

---

## Dein Streifen - Kabelbelegung

Dein WS2812B-Streifen hat folgende Anschluesse:

| Kabel | Bedeutung | Wohin |
|---|---|---|
| **Rot** (duenn) | 5V (Plus) | 5V vom Netzteil |
| **Weiss** | GND (Minus) | GND (Netzteil UND Arduino) |
| **Gruen** | DIN (Dateneingang) | ueber 330-Ohm-Widerstand an Arduino Pin 6 |
| **Rot** (dick, extra) | Zusaetzliche 5V-Einspeisung | ebenfalls an 5V vom Netzteil |

> **Pfeilrichtung beachten!** Die Pfeile auf dem Streifen zeigen die Datenrichtung.
> Du musst am ANFANG des Streifens anschliessen - dort wo die Pfeile WEG zeigen
> (in den Streifen hinein). Das ist die Seite mit dem 3-Pin-Stecker (rot/gruen/weiss).

---

## Verkabelung

### Schaubild

```
   NETZTEIL (5V, ueber Breadboard-Modul)
     |
     +-- 5V  ---> rote Leiste (+) am Breadboard
     +-- GND ---> blaue Leiste (-) am Breadboard

   LED-STREIFEN (Anfang, wo Pfeile hineinzeigen)
     Rot (duenn) -----> rote Leiste (+)      [5V]
     Rot (dick)  -----> rote Leiste (+)      [5V, zusaetzlich]
     Weiss       -----> blaue Leiste (-)     [GND]
     Gruen (DIN) --[330 Ohm]--> Arduino Pin 6

   ARDUINO MEGA
     Pin 6  ---> (ueber Widerstand) zum gruenen Datenkabel
     GND    ---> blaue Leiste (-)            [gemeinsame Masse!]
     USB    ---> PC (nur fuer Programm + Steuerung)
```

### Warum der Widerstand in der Datenleitung?

Der 330-Ohm-Widerstand zwischen Arduino Pin 6 und dem gruenen Datenkabel schuetzt
die erste LED vor Spannungsspitzen. Er ist nicht zwingend noetig, aber empfohlen -
und du hast passende Widerstaende im Kit.

### Warum GND von Arduino UND Netzteil verbinden?

Der Arduino sendet die Daten, das Netzteil liefert den Strom. Damit die LEDs die
Datensignale richtig "verstehen", muessen Arduino und Netzteil die gleiche Masse
(GND) teilen. Deshalb: Arduino-GND MIT der blauen Leiste verbinden.

> **WICHTIG:** Verbinde den 5V-Anschluss des Streifens NICHT mit dem Arduino-5V-Pin!
> Der Arduino kann den Strom nicht liefern. Nur das externe Netzteil versorgt die LEDs.

---

## Aufbau Schritt fuer Schritt

1. **Netzteil-Modul** auf das Breadboard, Jumper auf **5V**, noch AUS
2. **Streifen-Strom:** Rot (duenn) + Rot (dick) → rote Leiste, Weiss → blaue Leiste
3. **Widerstand** (330 Ohm) ins Breadboard, ein Ende zu einer freien Reihe
4. **Gruen (DIN)** an das eine Ende des Widerstands
5. **Arduino Pin 6** an das andere Ende des Widerstands
6. **Arduino GND** → blaue Leiste (gemeinsame Masse)
7. **FastLED-Bibliothek** installieren (falls noch nicht)
8. Sketch `led_streifen.ino` hochladen
9. **9V-Netzteil einstecken**, Modul auf ON
10. Die Effekte sollten starten (Regenbogen zuerst)

---

## Einstellungen im Code anpassen

Ganz oben im Sketch findest du diese Zeilen:

```cpp
const int ANZAHL_LEDS = 144;    // Anzahl LEDs
const int DATEN_PIN = 6;        // Datenpin (gruenes Kabel)
const int HELLIGKEIT = 64;      // 0-255 (64 = 25%, sicher)
const int MAX_STROM_MA = 500;   // Strombegrenzung in mA
```

- **HELLIGKEIT:** Hoeher = heller, aber mehr Strom. Bei 64 sicher. Nicht ueber 100
  gehen ohne staerkeres Netzteil!
- **MAX_STROM_MA:** An dein Netzteil anpassen. Beim Breadboard-Modul lieber bei
  500 lassen.

---

## Was du siehst

Die Effekte laufen automatisch nacheinander (je 8 Sekunden), dann von vorne.
Im Seriellen Monitor (115200 Baud) siehst du welcher Effekt gerade laeuft.

---

## Haeufige Probleme und Loesungen

| Problem | Ursache | Loesung |
|---|---|---|
| Nichts leuchtet | Falsche Streifen-Seite | Am Anfang anschliessen (Pfeile zeigen hinein) |
| Nichts leuchtet | GND nicht gemeinsam | Arduino-GND mit Netzteil-GND verbinden |
| Nur erste LED leuchtet weiss/bunt | Datenleitung Problem | Pin 6, Widerstand und gruenes Kabel pruefen |
| Farben falsch (rot=gruen) | Farbreihenfolge | Im Code `GRB` auf `RGB` aendern (frag mich) |
| Arduino startet neu | Streifen zieht zu viel Strom | HELLIGKEIT runter, externes Netzteil nutzen |
| Flackern | Masse-Problem oder Netzteil schwach | GND pruefen, Helligkeit senken |
| Erste LEDs dunkler als Rest | Spannungsabfall | dickes rotes Kabel auch anschliessen |

> Falls die Farben vertauscht sind (z.B. Rot zeigt Gruen): sag mir Bescheid,
> dann aendere ich eine Zeile im Code (GRB → RGB oder aehnlich).

---

## Ideen zum Erweitern

- Effekt per Taster oder IR-Fernbedienung umschalten
- Streifen als VU-Meter (reagiert auf Geraeusche mit dem Schalldetektor)
- Streifen zeigt die Luefter-Drehzahl an (Kombi mit dem Drehzahlmesser)
- Farben per Bluetooth-App vom Handy steuern
