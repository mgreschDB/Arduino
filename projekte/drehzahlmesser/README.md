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

## Messergebnisse

| Luefter | Gemessene RPM | Bemerkung |
|---|---|---|
| Sunon MF30060V1-1000U-A99 | ~8700 RPM | MagLev-Lager, sehr schnell, leiser |
| LD3007MS (No-Name) | ~3600 RPM | Standard-Lager, deutlich langsamer |

**Fazit:** Der Sunon dreht ca. 2.5x so schnell wie der No-Name-Luefter.
Das MagLev-Lager (Magnetlager) des Sunon ermoeglicht hoehere Drehzahlen bei weniger Verschleiss.

**Status: ABGESCHLOSSEN** (2026-08-27)

---

## Zwei Display-Varianten

Dieses Projekt gibt es in zwei Versionen:

| Version | Sketch-Datei | Display | Besonderheit |
|---|---|---|---|
| **LCD-Version** | `drehzahlmesser.ino` | LCD 1602 (16 Pins) | Braucht Poti fuer Kontrast |
| **OLED-Version** | `drehzahlmesser_oled.ino` | OLED 0.96" SSD1306 (4 Pins) | Kein Poti, grosse Zahl + Balken |

Waehle die Version je nachdem welches Display du nutzen willst.

---

## OLED-Version (SSD1306) - Verkabelung

Das OLED-Display hat nur **4 Pins** und wird ueber I2C angeschlossen (2 Datenleitungen).
Viel einfacher als das LCD! Es braucht **kein Potentiometer und keinen Widerstand**.

### Benoetigte Bibliotheken (Arduino IDE)

Vor dem Hochladen in der Arduino IDE installieren:
(Sketch → Bibliothek einbinden → Bibliotheken verwalten → suchen → installieren)

- **Adafruit SSD1306**
- **Adafruit GFX Library**

> Beim Installieren von "Adafruit SSD1306" fragt die IDE evtl. ob abhaengige
> Bibliotheken mitinstalliert werden sollen → mit "Install all" bestaetigen.

### Verkabelung OLED → Arduino Mega

Die Pin-Reihenfolge auf dem Display: **GND, VCC, SCL, SDA**

| OLED-Pin | Kabelfarbe | Arduino Mega |
|---|---|---|
| **GND** | Schwarz | GND |
| **VCC** | Rot | 5V |
| **SCL** | Gelb | **Pin 21** (SCL) |
| **SDA** | Blau | **Pin 20** (SDA) |

> **Wichtig beim Mega:** I2C liegt auf Pin 20 (SDA) und Pin 21 (SCL).
> Beim Uno waeren das andere Pins (A4/A5) - aber du hast ja den Mega!

### Sensor und Luefter

Sensor und Luefter bleiben genau wie bei der LCD-Version:

| Anschluss | Nach |
|---|---|
| Sensor **VCC** | 5V (Breadboard + Leiste) |
| Sensor **GND** | GND (Breadboard - Leiste) |
| Sensor **D0/OUT** | Arduino **Pin 18** |
| Luefter **rot** | 5V |
| Luefter **schwarz** | GND |

### Was du auf dem OLED siehst

```
Drehzahlmesser
8700          <- grosse Zahl
RPM      Max:8700
[##########........]  <- Balken
```

### Fehlermeldung "OLED nicht gefunden"?

Wenn im Seriellen Monitor "FEHLER: OLED nicht gefunden" steht:
- SDA an Pin 20? SCL an Pin 21? (nicht vertauscht?)
- VCC und GND richtig?
- Falls immer noch nichts: Manche OLEDs haben die I2C-Adresse 0x3D statt 0x3C.
  Dann im Code `OLED_ADRESSE` von `0x3C` auf `0x3D` aendern.

---

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

## Verkabelung - Ausfuehrliche Anleitung

### WICHTIG - Bitte zuerst lesen!

- Den Arduino **NICHT** am USB anschliessen, solange du verkabelst
- Das 9V-Netzteil **NICHT** einstecken, solange du verkabelst
- Immer erst ALLES stecken, dann kontrollieren, DANN Strom rein
- LEDs und das Display haben eine Polaritaet (Plus/Minus beachten)

---

### So ist das Breadboard aufgebaut (kurze Erklaerung)

```
       Stromleisten oben
  + (rot)  =======================================  ← hier fliesst ueberall 5V
  - (blau) =======================================  ← hier ist ueberall GND (Masse)

       Steckbereich (a-e und f-j)
  Reihe 1:  a b c d e | | f g h i j     ← a-e sind verbunden, f-j sind verbunden
  Reihe 2:  a b c d e | | f g h i j        Der Graben in der Mitte TRENNT
  Reihe 3:  a b c d e | | f g h i j
  ...                  | |
  Reihe 63: a b c d e | | f g h i j

       Stromleisten unten
  + (rot)  =======================================  ← hier fliesst ueberall 5V
  - (blau) =======================================  ← hier ist ueberall GND (Masse)
```

**Wichtig zu verstehen:**
- Alle 5 Loecher in einer Reihe (z.B. a1-b1-c1-d1-e1) sind INTERN verbunden
- Der Graben in der Mitte TRENNT die linke Seite (a-e) von der rechten (f-j)
- Die Stromleisten (+/-) am Rand laufen laengs durch - alles was du da reinsteckst
  bekommt den gleichen Strom
- Wenn du ein Bauteil ueber den Graben steckst, sind links und rechts getrennt
  zugaenglich - genau das nutzen wir beim LCD!

---

### Das Breadboard Power Supply Modul

Dein Stromversorgungsmodul steckt auf einer Seite des Breadboards
auf die + und - Leisten. Es hat:
- Einen **DC-Eingang** fuer das 9V Netzteil
- Einen **USB-Eingang** (alternativ)
- **Jumper** zum Umschalten zwischen 3.3V und 5V
- Einen **Ein/Aus-Schalter**

**WICHTIG: Stelle BEIDE Jumper auf 5V!** (nicht auf 3.3V, sonst geht das LCD nicht)

Das Modul versorgt die Stromleisten des Breadboards mit stabilen 5V.
Der Luefter und der Sensor bekommen ihren Strom von dort - nicht vom Arduino.
Der Arduino laeuft separat ueber USB vom PC.

---

### Uebersichtstabelle - Alle Verbindungen auf einen Blick

| Von | Nach | Kabelfarbe (Vorschlag) |
|---|---|---|
| **LCD Pin 1** (VSS) | Breadboard **-** Leiste (blau/GND) | Schwarz |
| **LCD Pin 2** (VDD) | Breadboard **+** Leiste (rot/5V) | Rot |
| **LCD Pin 3** (V0) | Potentiometer **mittlerer** Pin | Gelb |
| **LCD Pin 4** (RS) | Arduino **Pin 12** | Gruen |
| **LCD Pin 5** (RW) | Breadboard **-** Leiste (blau/GND) | Schwarz |
| **LCD Pin 6** (E) | Arduino **Pin 11** | Blau |
| LCD Pin 7-10 | NICHTS - frei lassen | - |
| **LCD Pin 11** (D4) | Arduino **Pin 5** | Orange |
| **LCD Pin 12** (D5) | Arduino **Pin 4** | Gelb |
| **LCD Pin 13** (D6) | Arduino **Pin 3** | Gruen |
| **LCD Pin 14** (D7) | Arduino **Pin 2** | Blau |
| **LCD Pin 15** (A) | 220-Ohm-Widerstand → dann Breadboard **+** Leiste | Rot |
| **LCD Pin 16** (K) | Breadboard **-** Leiste (blau/GND) | Schwarz |
| Poti **linker** Pin | Breadboard **+** Leiste (rot/5V) | Rot |
| Poti **rechter** Pin | Breadboard **-** Leiste (blau/GND) | Schwarz |
| Poti **mittlerer** Pin | LCD Pin 3 (siehe oben) | Gelb |
| Sensor **VCC** | Breadboard **+** Leiste (rot/5V) | Rot |
| Sensor **GND** | Breadboard **-** Leiste (blau/GND) | Schwarz |
| Sensor **D0/OUT** | Arduino **Pin 18** | Weiss |
| Luefter **rot** (+) | Breadboard **+** Leiste (rot/5V) | - |
| Luefter **schwarz** (-) | Breadboard **-** Leiste (blau/GND) | - |
| Arduino **GND** | Breadboard **-** Leiste (blau/GND) | Schwarz |

> **Warum kein Kabel von Arduino 5V zum Breadboard?**
> Das 9V-Netzteil ueber das Stromversorgungsmodul versorgt das Breadboard mit 5V.
> Der Arduino bekommt seinen Strom ueber USB. Aber GND (Masse) muss verbunden sein,
> damit beide die gleiche "Null-Linie" haben - sonst kann der Arduino die Signale
> vom Sensor nicht richtig lesen!

---

## Aufbau Schritt fuer Schritt

### Schritt 1: Breadboard vorbereiten

1. Das Stromversorgungsmodul sollte auf einer Seite des Breadboards stecken
   (auf den + und - Leisten)
2. Pruefe: **Beide Jumper auf 5V** gestellt?
3. **Noch NICHT** das 9V-Netzteil einstecken!

---

### Schritt 2: LCD ins Breadboard stecken

Das LCD hat 16 Pins in einer Reihe. Stecke sie in das Breadboard:

```
  LCD Display (von vorne gesehen, Pins zeigen nach unten ins Breadboard)
  +----------------------------------------------------+
  |                                                    |
  |            Drehzahlmesser                          |
  |            RPM: 6420                               |
  |                                                    |
  +--|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-------------------+
     1 2 3 4 5 6 7 8 9 . . . . .16
     ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓         ↓
  Breadboard Reihe 1 bis 16
```

- Stecke LCD Pin 1 z.B. in **Reihe 1** und LCD Pin 16 in **Reihe 16**
- Die Pins sollen auf einer Seite des Grabens stecken (z.B. Seite **e**)
- Dann kannst du auf der gleichen Seite (a, b, c, d) Kabel anschliessen,
  weil a-e in jeder Reihe intern verbunden sind

```
  Breadboard-Ausschnitt (Draufsicht):
  
  Reihe:  a   b   c   d   e  ||  f   g   h   i   j
    1:    [K] [ ] [ ] [ ] [LCD1]              ← LCD Pin 1 steckt in e1
    2:    [K] [ ] [ ] [ ] [LCD2]              ← LCD Pin 2 steckt in e2
    3:    [ ] [ ] [ ] [ ] [LCD3]              ← LCD Pin 3 steckt in e3
    ...
   16:    [K] [ ] [ ] [ ] [LCD16]             ← LCD Pin 16 steckt in e16
   17:    [ ] [ ] [ ] [ ] [ ]                 ← frei (fuer Poti etc.)
   
  [K] = hier kommt spaeter ein Kabel rein
  Da a-e in einer Reihe verbunden sind, ist ein Kabel in a1 
  automatisch mit dem LCD-Pin in e1 verbunden!
```

---

### Schritt 3: LCD Masse (GND) und Strom (5V) anschliessen

Jetzt die einfachen Verbindungen - alles was an GND oder 5V muss:

**GND-Verbindungen (3 Kabel, am besten schwarze nehmen):**

| Kabel | Von (Breadboard) | Nach |
|---|---|---|
| Kabel 1 | **Reihe 1** (= LCD Pin 1 / VSS) z.B. Loch **a1** | **-** Leiste (blau) |
| Kabel 2 | **Reihe 5** (= LCD Pin 5 / RW) z.B. Loch **a5** | **-** Leiste (blau) |
| Kabel 3 | **Reihe 16** (= LCD Pin 16 / K) z.B. Loch **a16** | **-** Leiste (blau) |

**5V-Verbindung (1 Kabel, rotes nehmen):**

| Kabel | Von (Breadboard) | Nach |
|---|---|---|
| Kabel 4 | **Reihe 2** (= LCD Pin 2 / VDD) z.B. Loch **a2** | **+** Leiste (rot) |

**Hintergrundbeleuchtung (mit Widerstand!):**

| Bauteil/Kabel | Von | Nach |
|---|---|---|
| 220-Ohm-Widerstand | **Reihe 15** z.B. Loch **a15** (= LCD Pin 15 / A) | **Reihe 20** z.B. Loch **a20** (freie Reihe) |
| Kabel 5 (rot) | **Reihe 20** z.B. Loch **b20** | **+** Leiste (rot) |

> **Was ist der Widerstand?** Er begrenzt den Strom fuer die Hintergrundbeleuchtung,
> damit die LED im Display nicht kaputt geht. Stell dir einen Wasserhahn vor der
> nicht ganz aufgedreht ist - genau das macht der Widerstand mit dem Strom.
>
> **Wie erkenne ich 220 Ohm?** Farbcode auf dem Widerstand: **Rot - Rot - Braun**
> (und dann Gold oder Silber fuer die Toleranz). Schau auf die Widerstandskarte
> aus dem Kit falls du unsicher bist.

---

### Schritt 4: Potentiometer anschliessen (fuer LCD-Kontrast)

Das Potentiometer (der kleine Trimmer mit 3 Beinchen) regelt den Kontrast.
Ohne ihn siehst du auf dem Display entweder nichts oder nur helle Bloecke.

1. Stecke das Poti ins Breadboard, z.B. in **Reihe 18, 19, 20** (oder wo Platz ist)
   - Es hat 3 Beinchen die in 3 verschiedene Reihen muessen

2. Verbindungen:

| Kabel | Poti-Pin | Nach |
|---|---|---|
| Kabel 6 (rot) | Linker Pin | **+** Leiste (rot/5V) |
| Kabel 7 (schwarz) | Rechter Pin | **-** Leiste (blau/GND) |
| Kabel 8 (gelb) | Mittlerer Pin | **Reihe 3** z.B. Loch **a3** (= LCD Pin 3 / V0) |

> **Wie rum stecke ich das Poti?** Egal! Wenn du es "falsch" rum steckst, dreht der
> Kontrast halt in die andere Richtung. Kaputt geht nichts.

---

### Schritt 5: LCD Datenkabel zum Arduino

Jetzt kommen die Kabel die das LCD mit dem Arduino verbinden.
Nimm am besten verschiedene Farben, damit du sie spaeter unterscheiden kannst.

| Kabel | Von (Breadboard-Reihe = LCD Pin) | Nach (Arduino Mega Pin) |
|---|---|---|
| Kabel 9 (gruen) | **Reihe 4** z.B. Loch **a4** (= LCD Pin 4 / RS) | Arduino **Digital Pin 12** |
| Kabel 10 (blau) | **Reihe 6** z.B. Loch **a6** (= LCD Pin 6 / E) | Arduino **Digital Pin 11** |
| Kabel 11 (orange) | **Reihe 11** z.B. Loch **a11** (= LCD Pin 11 / D4) | Arduino **Digital Pin 5** |
| Kabel 12 (gelb) | **Reihe 12** z.B. Loch **a12** (= LCD Pin 12 / D5) | Arduino **Digital Pin 4** |
| Kabel 13 (gruen) | **Reihe 13** z.B. Loch **a13** (= LCD Pin 13 / D6) | Arduino **Digital Pin 3** |
| Kabel 14 (blau) | **Reihe 14** z.B. Loch **a14** (= LCD Pin 14 / D7) | Arduino **Digital Pin 2** |

> **Wo finde ich die Pins am Arduino Mega?**
> Die digitalen Pins sind auf der langen Seite des Boards beschriftet.
> Pin 2-13 sind nebeneinander. Pin 18 ist im Bereich "COMMUNICATION" 
> (TX1) - da steht "18" daneben.

> **LCD Pins 7, 8, 9, 10 bleiben frei!** Da steckt KEIN Kabel rein.
> Wir nutzen den "4-Bit-Modus" - das heisst wir brauchen nur 4 Datenleitungen
> statt 8. Das spart Kabel und Arduino-Pins.

---

### Schritt 6: Arduino GND mit Breadboard verbinden

Das ist wichtig! Arduino und Breadboard muessen die gleiche Masse teilen.

| Kabel | Von | Nach |
|---|---|---|
| Kabel 15 (schwarz) | Arduino **GND** Pin | Breadboard **-** Leiste (blau) |

> Am Arduino Mega gibt es mehrere GND-Pins (neben Pin 13, neben 5V, etc.)
> Nimm irgendeinen davon - alle sind intern verbunden.

---

### Schritt 7: ERSTER TEST - Nur das LCD

**Bevor** wir Sensor und Luefter anschliessen, testen wir erst ob das LCD geht!

1. Kontrolliere nochmal alle Kabel (siehe Tabelle oben)
2. Stecke das **9V-Netzteil** in das Stromversorgungsmodul → Schalter auf **ON**
3. Stecke das **USB-Kabel** vom Arduino zum PC
4. Oeffne die **Arduino IDE**
5. Oeffne die Datei `drehzahlmesser.ino`
6. Board und Port korrekt eingestellt?
7. Druecke **Upload** (Pfeil-Button)
8. Auf dem LCD sollte jetzt stehen:

```
Drehzahlmesser
Warte...
```

**Siehst du nichts?** → Drehe am Potentiometer! Langsam in beide Richtungen.
Der Text wird irgendwann sichtbar. Manchmal muss man fast bis zum Anschlag drehen.

**Siehst du nur helle Bloecke?** → Auch am Poti drehen. Wenn das nicht hilft,
pruefe ob alle GND-Kabel (Pin 1, 5, 16) wirklich in der blauen Leiste stecken.

**Funktioniert das LCD? Dann weiter mit Schritt 8!**

---

### Schritt 8: Gabellichtschranke anschliessen

Die Gabellichtschranke (LM393) hat eine kleine Platine mit Pins und eine U-foermige
Gabel mit IR-Sender und Empfaenger.

**Die Platine hat 3 oder 4 Pins.** Schau was draufsteht:

| Sensor-Pin | Kabel | Nach |
|---|---|---|
| **VCC** (oder +) | Rot | Breadboard **+** Leiste (rot/5V) |
| **GND** (oder -) | Schwarz | Breadboard **-** Leiste (blau/GND) |
| **D0** (oder OUT oder DO) | Weiss/Gelb | Arduino **Pin 18** |
| A0 (falls vorhanden) | NICHTS | Nicht anschliessen |

> **Warum Pin 18?** Der Arduino Mega hat spezielle Pins die SOFORT reagieren wenn
> sich ein Signal aendert. Das nennt man "Interrupt" - wie eine Tuerklingel die
> dich sofort unterbricht egal was du gerade tust. Bei 9000 RPM mit 7 Blaettern
> kommen ueber 1000 Impulse pro Sekunde - da muss der Arduino blitzschnell sein!
> Pin 18 ist einer dieser speziellen Interrupt-Pins auf dem Mega.

---

### Schritt 9: Luefter anschliessen

| Luefter-Kabel | Nach |
|---|---|
| **Rot** (+) | Breadboard **+** Leiste (rot/5V) |
| **Schwarz** (-) | Breadboard **-** Leiste (blau/GND) |

> **Nur EINEN Luefter gleichzeitig anschliessen!** Das Stromversorgungsmodul
> schafft beide zusammen, aber zum Testen reicht einer.

---

### Schritt 10: Luefter an der Lichtschranke positionieren

Das ist der kniffligste Teil:

1. Die Luefterblaetter muessen **durch die U-foermige Gabel** der Lichtschranke laufen
2. Bei 30mm Lueftern: Positioniere den Sensor so, dass die **Blattspitzen**
   durch den Spalt fahren
3. Der Sensor muss **stabil stehen** - mit Blu-Tack, Klebeband oder einfach
   festhalten zum Testen

```
  Seitenansicht:

       Lichtschranke (U-Form)
       |  IR  |
       | Sender|          |Empfaenger|
       |  ↓   |          |    ↓     |
       |      |          |          |
       |   ===X==========X===      |     ← Luefterblatt faehrt durch
       |      |          |          |
       |______|          |__________|

  Die Blaetter muessen den IR-Strahl unterbrechen!
```

4. Wenn alles laeuft, sollte auf dem LCD stehen:

```
Drehzahlmesser
RPM: 6420
```

(Der Wert haengt natuerlich von deinem Luefter ab)

---

### Falls die Blaetter NICHT durch die Gabel passen

Bei 30mm Lueftern kann es sein, dass die Gabel zu eng ist. Dann:
→ Nimm stattdessen den **IR-Reflexionssensor (FC-51)**, siehe Abschnitt
  "Alternative" weiter unten in dieser Datei.

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
