# Projekt: Drehzahlmesser fuer Luefter (RPM-Meter)

## Was macht dieses Projekt?

Dieses Projekt misst die Drehzahl (Umdrehungen pro Minute = RPM) von kleinen 5V-Lueftern
und zeigt den Wert auf einem LCD-Display an. So kannst du vergleichen, wie schnell
verschiedene Luefter drehen.

## Getestete Luefter

| Luefter | Spannung | Leistung | Groesse |
|---|---|---|---|
| Sunon MF30060V1-1000U-A99 | DC 5V | 0.72W | 30x30mm |
| LD3007MS (No-Name) | DC 5V | 0.20A (1.0W) | 30x30mm |

Beide Luefter haben **7 Blaetter** und **2 Kabel** (kein Tachosignal).

---

## Benoetigte Bauteile

| Bauteil | Anzahl | Aus dem Kit? |
|---|---|---|
| Arduino Mega 2560 | 1 | Ja |
| LCD 1602A (16 Pins, QAPASS) | 1 | Ja |
| Potentiometer (10kOhm) | 1 | Ja |
| Gabellichtschranke LM393 | 1 | Nein (bestellt) |
| Luefter (5V, 30x30mm) | 1 | Nein (vorhanden) |
| Breadboard | 1 | Ja |
| Widerstand 220 Ohm | 1 | Ja |
| Jumperkabel | diverse | Ja |
| USB-Kabel | 1 | Ja |

---

## Verkabelung

### WICHTIG - Bitte zuerst lesen!

- Den Arduino **NICHT** am USB anschliessen, solange du verkabelst
- Immer erst alles stecken, dann kontrollieren, DANN USB rein
- LEDs und das Display haben eine Polaritaet (Plus/Minus beachten)

---

### LCD 1602A (16 Pins) an Arduino Mega

Das LCD hat 16 Pins. Die sind von links nach rechts nummeriert (wenn du auf
die Vorderseite schaust, Pins oben): 1 bis 16.

Das Potentiometer regelt den **Kontrast** des Displays. Ohne Poti siehst du nichts!

| LCD Pin | Name | Verbindung | Erklaerung |
|---|---|---|---|
| 1 | VSS | GND (Arduino) | Masse/Minus |
| 2 | VDD | 5V (Arduino) | Stromversorgung Plus |
| 3 | V0 | Poti Mittelpin | Kontrast-Regelung |
| 4 | RS | Arduino Pin 12 | Register Select (Befehl oder Daten) |
| 5 | RW | GND (Arduino) | Read/Write - auf GND = nur Schreiben |
| 6 | E | Arduino Pin 11 | Enable (Freigabe) |
| 7 | D0 | nicht anschliessen | Datenpin (brauchen wir nicht) |
| 8 | D1 | nicht anschliessen | Datenpin (brauchen wir nicht) |
| 9 | D2 | nicht anschliessen | Datenpin (brauchen wir nicht) |
| 10 | D3 | nicht anschliessen | Datenpin (brauchen wir nicht) |
| 11 | D4 | Arduino Pin 5 | Datenpin (4-Bit Modus) |
| 12 | D5 | Arduino Pin 4 | Datenpin (4-Bit Modus) |
| 13 | D6 | Arduino Pin 3 | Datenpin (4-Bit Modus) |
| 14 | D7 | Arduino Pin 2 | Datenpin (4-Bit Modus) |
| 15 | A (Anode) | 5V ueber 220-Ohm-Widerstand | Hintergrundbeleuchtung Plus |
| 16 | K (Kathode) | GND (Arduino) | Hintergrundbeleuchtung Minus |

**Das Potentiometer (Kontrast):**
- Linker Pin → 5V (Arduino)
- Mittlerer Pin → LCD Pin 3 (V0)
- Rechter Pin → GND (Arduino)

> **Tipp:** Wenn du nach dem Einschalten nur helle Bloecke siehst, drehe am Poti
> bis Text sichtbar wird. Das ist voellig normal!

---

### Gabellichtschranke LM393 an Arduino Mega

Die Lichtschranke hat meistens 3 oder 4 Pins auf der Platine.

| Sensor-Pin | Verbindung | Erklaerung |
|---|---|---|
| VCC | 5V (Arduino) | Stromversorgung Plus |
| GND | GND (Arduino) | Masse/Minus |
| D0 (oder OUT) | Arduino Pin 18 (Interrupt) | Digitales Signal - wird LOW wenn ein Blatt durchlaeuft |
| A0 (falls vorhanden) | nicht anschliessen | Analoges Signal (brauchen wir nicht) |

> **Warum Pin 18?** Der Arduino Mega hat spezielle Pins die sofort reagieren koennen
> wenn sich ein Signal aendert. Das nennt man "Interrupt". Pin 18 ist Interrupt 5 auf
> dem Mega. Bei hohen Drehzahlen (bis 9000 RPM) ist das wichtig, damit kein Impuls
> verloren geht.

---

### Luefter an Strom

Die Luefter brauchen 5V und ziehen zu viel Strom fuer einen Arduino-Digitalpin.
Deshalb schliessen wir sie direkt an die Stromversorgung an:

| Luefter-Kabel | Verbindung | Erklaerung |
|---|---|---|
| Rot (+) | 5V Pin am Arduino | Plus/Strom |
| Schwarz (-) | GND am Arduino | Masse/Minus |

> **Hinweis:** Beide Luefter ziehen zusammen zu viel Strom fuer USB allein.
> Schliesse immer nur EINEN Luefter gleichzeitig an. Wenn du beide gleichzeitig
> betreiben willst, brauchst du eine externe 5V-Stromversorgung.

---

## Aufbau Schritt fuer Schritt

### Schritt 1: LCD auf das Breadboard stecken
- Stecke das LCD mit den 16 Pins in das Breadboard
- Die Pins sollen in verschiedene Reihen stecken (jeder Pin eine eigene Reihe)

### Schritt 2: LCD Stromversorgung
- LCD Pin 1 (VSS) → blauer Streifen (GND-Leiste) auf dem Breadboard
- LCD Pin 2 (VDD) → roter Streifen (5V-Leiste) auf dem Breadboard
- LCD Pin 5 (RW) → blauer Streifen (GND-Leiste)
- LCD Pin 16 (K) → blauer Streifen (GND-Leiste)
- LCD Pin 15 (A) → ueber 220-Ohm-Widerstand → roter Streifen (5V-Leiste)

### Schritt 3: Potentiometer
- Stecke das Potentiometer ins Breadboard
- Linker Pin → roter Streifen (5V)
- Rechter Pin → blauer Streifen (GND)
- Mittlerer Pin → Kabel zu LCD Pin 3 (V0)

### Schritt 4: LCD Datenkabel zum Arduino
- LCD Pin 4 (RS) → Arduino Pin 12
- LCD Pin 6 (E) → Arduino Pin 11
- LCD Pin 11 (D4) → Arduino Pin 5
- LCD Pin 12 (D5) → Arduino Pin 4
- LCD Pin 13 (D6) → Arduino Pin 3
- LCD Pin 14 (D7) → Arduino Pin 2

### Schritt 5: Breadboard-Stromleisten mit Arduino verbinden
- Roter Streifen → Arduino 5V
- Blauer Streifen → Arduino GND

### Schritt 6: Gabellichtschranke
- VCC → roter Streifen (5V)
- GND → blauer Streifen (GND)
- D0/OUT → Arduino Pin 18

### Schritt 7: Luefter
- Rotes Kabel → roter Streifen (5V)
- Schwarzes Kabel → blauer Streifen (GND)

### Schritt 8: Positionierung der Lichtschranke
- Die Luefterblaetter muessen durch die Gabel der Lichtschranke laufen
- Bei 30mm Lueftern: Positioniere den Sensor so, dass die Blattspitzen
  durch den Spalt der Gabel fahren
- Der Sensor muss stabil stehen/liegen, sonst zittern die Werte

---

## Den Code hochladen

1. Oeffne die Arduino IDE
2. Oeffne die Datei `drehzahlmesser.ino` aus diesem Ordner
3. Stelle sicher: Board = "Arduino Mega or Mega 2560", Port korrekt
4. Druecke den Upload-Button (Pfeil)
5. Warte bis "Hochladen abgeschlossen" erscheint

---

## Was du auf dem Display siehst

```
Drehzahlmesser
RPM: 6420
```

Die Anzeige aktualisiert sich jede Sekunde.

---

## Bedienung

- **Poti drehen:** Kontrast des Displays einstellen (wenn nichts zu sehen ist)
- **Luefter wechseln:** Arduino per USB trennen, Luefter tauschen, wieder anschliessen
- **Serieller Monitor:** In der Arduino IDE unter Tools → Serieller Monitor (115200 Baud)
  siehst du die RPM-Werte auch am PC

---

## Erklaerung: Wie funktioniert die Messung?

### Das Prinzip
Die Gabellichtschranke hat auf einer Seite eine Infrarot-LED (unsichtbares Licht)
und auf der anderen Seite einen Empfaenger. Wenn nichts dazwischen ist, empfaengt
der Empfaenger das Licht → Signal ist HIGH (1).

Wenn ein Luefterblatt durchfaehrt, wird das Licht unterbrochen → Signal wird LOW (0).

### Die Berechnung
- Der Luefter hat 7 Blaetter
- Bei einer Umdrehung gibt es also 7 Unterbrechungen (Impulse)
- Der Arduino zaehlt die Impulse pro Sekunde
- Formel: **RPM = (Impulse pro Sekunde / 7) × 60**

Beispiel:
- 700 Impulse pro Sekunde → 700 / 7 = 100 Umdrehungen pro Sekunde → 100 × 60 = 6000 RPM

### Was ist ein Interrupt?
Normalerweise arbeitet der Arduino seinen Code Zeile fuer Zeile ab (in `loop()`).
Ein Interrupt ist wie ein Tuerklingeln: Egal was der Arduino gerade tut, er unterbricht
sofort seine Arbeit, zaehlt den Impuls, und macht dann weiter wo er war. So geht kein
Impuls verloren, selbst bei 9000 RPM.

---

## Haeufige Probleme und Loesungen

| Problem | Ursache | Loesung |
|---|---|---|
| Display zeigt nichts | Kontrast falsch | Am Poti drehen bis Text erscheint |
| Display zeigt nur helle Bloecke | Kontrast zu hoch oder Verkabelung falsch | Poti drehen, alle LCD-Kabel pruefen |
| RPM zeigt 0 | Sensor erkennt Blaetter nicht | Sensor naeher an die Blaetter, Ausrichtung pruefen |
| RPM springt wild | Sensor steht nicht stabil | Sensor fixieren (z.B. mit Klebeband/Blu-Tack) |
| RPM viel zu hoch | Anzahl Blaetter falsch eingestellt | Im Code ANZAHL_BLAETTER pruefen |
| Luefter dreht nicht | Kein Strom | Kabel pruefen, richtiger Anschluss? |
| Arduino startet neu | Luefter zieht zu viel Strom ueber USB | Nur EINEN Luefter anschliessen |
| Blaetter passen nicht durch Gabel | Luefter zu gross fuer Gabellichtschranke | IR-Reflexionssensor verwenden (siehe Alternative) |

---

## Alternative: IR-Reflexionssensor (FC-51) statt Gabellichtschranke

Falls die Luefterblaetter nicht durch die Gabel passen, verwende den
IR-Reflexionssensor. Dafuer:

1. Klebe einen kleinen weissen Streifen (Papier/Klebeband) auf EIN Blatt
2. Richte den FC-51-Sensor auf die Blaetter (Abstand ca. 1-2cm)
3. Aendere im Code die Zeile `ANZAHL_BLAETTER` von 7 auf 1
   (weil nur EIN Blatt den Streifen hat → 1 Impuls pro Umdrehung)
4. Empfindlichkeit am Poti des FC-51-Sensors einstellen bis die LED
   auf dem Sensormodul beim Vorbeidrehen des Streifens blinkt

Der Anschluss ist identisch:
- VCC → 5V
- GND → GND
- OUT → Arduino Pin 18
