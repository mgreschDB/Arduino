# Projektideen - Elegoo Mega 2560 Starter Kit

Alle Projekte sind nach Schwierigkeitsgrad sortiert. Jedes Projekt baut auf dem Wissen der vorherigen auf.

## Legende Schwierigkeitsgrad

| Symbol | Stufe | Beschreibung |
|---|---|---|
| :green_circle: | Anfaenger | Keine Vorkenntnisse noetig, wenige Bauteile |
| :yellow_circle: | Leicht Fortgeschritten | Grundlagen verstanden, mehrere Bauteile |
| :orange_circle: | Fortgeschritten | Kombination mehrerer Konzepte |
| :red_circle: | Anspruchsvoll | Komplexe Logik, viele Bauteile, Zusammenspiel |

---

## :green_circle: Anfaenger-Projekte (Projekte 01-04)

### Projekt 01: Blinkende LED
**Ordner:** `projekte/01-blink-led/`
**Bauteile:** 1x LED, 1x 220-Ohm-Widerstand, Breadboard, Kabel
**Lernziele:**
- Arduino IDE kennenlernen
- Ersten Sketch hochladen
- Digitale Ausgaenge (HIGH/LOW) verstehen
- Grundlagen: Stromkreis, Widerstand, LED-Polaritaet

**Beschreibung:** Die LED blinkt im Sekundentakt. Das "Hello World" der Arduino-Welt.

---

### Projekt 02: Ampelschaltung
**Ordner:** `projekte/02-ampel/`
**Bauteile:** 3x LED (rot, gelb, gruen), 3x 220-Ohm-Widerstand, Breadboard, Kabel
**Lernziele:**
- Mehrere LEDs steuern
- Timing mit `delay()`
- Logische Ablaeufe programmieren

**Beschreibung:** Eine realistische Ampel mit korrekter Phasenfolge (Gruen → Gelb → Rot → Rot-Gelb → Gruen).

---

### Projekt 03: Temperatur- & Feuchtigkeitssensor
**Ordner:** `projekte/03-temperatur-sensor/`
**Bauteile:** DHT11 Sensor, 10kOhm Widerstand, Breadboard, Kabel
**Lernziele:**
- Bibliotheken installieren und verwenden
- Sensordaten auslesen
- Seriellen Monitor nutzen (Daten am PC anzeigen)

**Beschreibung:** Temperatur und Luftfeuchtigkeit messen und im Seriellen Monitor anzeigen.

---

### Projekt 04: Ultraschall-Entfernungsmesser
**Ordner:** `projekte/04-ultraschall-distanz/`
**Bauteile:** HC-SR04 Ultraschallsensor, Breadboard, Kabel
**Lernziele:**
- Trigger/Echo-Prinzip verstehen
- Zeitmessung mit `pulseIn()`
- Berechnungen im Code (Entfernung = Zeit × Schallgeschwindigkeit / 2)

**Beschreibung:** Entfernung zu einem Objekt messen und in cm ausgeben.

---

## :yellow_circle: Leicht Fortgeschrittene Projekte (Projekte 05-07)

### Projekt 05: LCD-Display mit Temperaturanzeige
**Ordner:** `projekte/05-lcd-display/`
**Bauteile:** LCD 1602 (I2C), DHT11, Breadboard, Kabel
**Lernziele:**
- I2C-Kommunikation verstehen
- Text auf LCD ausgeben
- Sensordaten live anzeigen

**Beschreibung:** Temperatur und Feuchtigkeit auf dem LCD-Display anzeigen statt nur am PC.

---

### Projekt 06: Servo-Motor Steuerung
**Ordner:** `projekte/06-servo-steuerung/`
**Bauteile:** Servo Motor (SG90), Potentiometer, Breadboard, Kabel
**Lernziele:**
- Analoge Eingaenge lesen (`analogRead`)
- Werte umrechnen (`map()`)
- Servo-Bibliothek verwenden
- PWM-Signale verstehen

**Beschreibung:** Den Servo-Motor mit dem Potentiometer (Drehregler) steuern - wie eine Fernsteuerung.

---

### Projekt 07: Bewegungsmelder mit Alarm
**Ordner:** `projekte/07-bewegungsmelder/`
**Bauteile:** PIR-Sensor (HC-SR501), Buzzer (aktiv), LED (rot), Widerstand, Breadboard, Kabel
**Lernziele:**
- PIR-Sensor kalibrieren
- Digitale Eingaenge lesen
- Mehrere Ausgaenge gleichzeitig steuern (LED + Buzzer)

**Beschreibung:** Bei erkannter Bewegung geht eine LED an und der Buzzer piept - wie ein einfaches Alarmsystem.

---

## :orange_circle: Fortgeschrittene Projekte (Projekte 08-10)

### Projekt 08: RFID-Zugangskontrolle
**Ordner:** `projekte/08-rfid-zugangskontrolle/`
**Bauteile:** RFID-Modul (RC522), RFID-Karte, Servo, LEDs (rot+gruen), Buzzer, LCD, Breadboard, Kabel
**Lernziele:**
- SPI-Kommunikation
- RFID-UIDs lesen und vergleichen
- Zugangslogik programmieren (erlaubt/verweigert)
- Mehrere Komponenten zusammen steuern

**Beschreibung:** Nur mit der richtigen RFID-Karte oeffnet der Servo ein "Schloss". Gruene LED + LCD zeigen "Zugang erlaubt", rote LED + Buzzer bei falscher Karte.

---

### Projekt 09: IR-Fernbedienungs-Steuerung
**Ordner:** `projekte/09-ir-fernbedienung/`
**Bauteile:** IR-Empfaenger, IR-Fernbedienung, LEDs (mehrfarbig), Servo, LCD, Breadboard, Kabel
**Lernziele:**
- IR-Protokolle verstehen
- Tastencode auslesen und zuordnen
- Switch-Case-Anweisungen
- Mehrere Geraete mit einer Fernbedienung steuern

**Beschreibung:** Mit der mitgelieferten IR-Fernbedienung verschiedene LEDs schalten, den Servo bewegen und Text auf dem LCD anzeigen.

---

### Projekt 10: Wetterstation
**Ordner:** `projekte/10-wetter-station/`
**Bauteile:** DHT11, Fotowiderstand (LDR), LCD 1602 (I2C), Taster, LEDs, Breadboard, Kabel
**Lernziele:**
- Mehrere Sensoren gleichzeitig auswerten
- Displayseiten umschalten (mit Taster)
- Schwellwerte setzen (z.B. LED an wenn zu dunkel)
- Strukturierter Code mit Funktionen

**Beschreibung:** Eine kleine Wetterstation die Temperatur, Feuchtigkeit und Helligkeit misst. Per Tastendruck wechselt die Anzeige auf dem LCD zwischen den Werten.

---

## :red_circle: Anspruchsvolle Projekte (Bonus)

### Projekt 11: Smart-Home-Simulation
**Bauteile:** Fast alles aus dem Kit
**Beschreibung:** Raumbeleuchtung (LEDs) reagiert auf Helligkeit (LDR), Heizung (rote LED) auf Temperatur (DHT11), Tuer (Servo) oeffnet mit RFID, Alarm (PIR + Buzzer) laesst sich per Fernbedienung aktivieren.

---

### Projekt 12: Einparkhilfe
**Bauteile:** HC-SR04, Buzzer (passiv), LEDs (gruen, gelb, rot)
**Beschreibung:** Je naeher ein Objekt kommt, desto schneller piept der Buzzer und die LEDs wechseln von gruen ueber gelb zu rot.

---

### Projekt 13: Passwort-Tuerschloss mit Keypad
**Bauteile:** 4x4 Keypad, Servo, LCD, LEDs, Buzzer
**Beschreibung:** Einen PIN ueber das Tastenfeld eingeben. Bei korrektem Code oeffnet der Servo, bei falschem gibt es Alarm.

---

### Projekt 14: Reaktionsspiel
**Bauteile:** LEDs (mehrere Farben), Taster, LCD, Buzzer
**Beschreibung:** Zufaellige LEDs leuchten auf - wer am schnellsten den richtigen Taster drueckt, gewinnt. Reaktionszeit wird auf dem LCD angezeigt.

---

## Empfohlene Reihenfolge

1. Starte mit **Projekt 01** - es dauert nur 15 Minuten
2. Mache **Projekte 02-04** nacheinander - jedes baut auf dem vorherigen auf
3. Ab **Projekt 05** kannst du auch springen, je nach Interesse
4. Die **Bonus-Projekte** kombinieren alles Gelernte

## Zeitaufwand pro Projekt (geschaetzt)

| Schwierigkeit | Aufbau | Programmierung | Gesamt |
|---|---|---|---|
| :green_circle: Anfaenger | 10-20 Min | 15-30 Min | 30-60 Min |
| :yellow_circle: Leicht Fortgeschritten | 20-30 Min | 30-60 Min | 1-2 Std |
| :orange_circle: Fortgeschritten | 30-45 Min | 1-2 Std | 2-3 Std |
| :red_circle: Anspruchsvoll | 45-60 Min | 2-4 Std | 3-5 Std |
