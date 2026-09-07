# Projekt: Drehzahlmesser Farbversion (Waveshare 2" ST7789)

## Was macht dieses Projekt?

Wie der normale Drehzahlmesser, aber mit einem **Farbdisplay** statt LCD/OLED:
- Grosse weisse RPM-Zahl
- Farbiger Tacho-Balken (gruen = langsam, gelb = mittel, rot = schnell)
- Rekordwert-Anzeige

## Display

**Waveshare 2" LCD Modul**
- IPS-Panel, 240x320 Pixel, Farbe
- Treiber-Chip: ST7789V
- Anschluss: SPI (4-Draht)
- Betriebsspannung: 3.3V oder 5V (Modul hat einen Spannungsregler an Bord)

---

## Benoetigte Bibliotheken (Arduino IDE)

Vor dem Hochladen installieren:
(Sketch → Bibliothek einbinden → Bibliotheken verwalten → suchen → installieren)

- **Adafruit ST7735 and ST7789 Library**
- **Adafruit GFX Library**

> Beim Installieren bietet die IDE evtl. an, abhaengige Bibliotheken mitzuinstallieren
> → mit "Install all" bestaetigen.

---

## Verkabelung Waveshare 2" → Arduino Mega

Das Modul hat 8 Pins: **VCC, GND, DIN, CLK, CS, DC, RST, BL**

Wichtig: Beim Arduino **Mega** liegen die Hardware-SPI-Pins auf 51 (MOSI/DIN) und
52 (SCK/CLK) - anders als beim Uno! Deshalb weicht diese Anleitung von der
offiziellen Waveshare-Uno-Anleitung ab.

| Display-Pin | Bedeutung | Arduino Mega | Kabelfarbe (dein Modul) |
|---|---|---|---|
| **VCC** | Stromversorgung | **5V** | Lila |
| **GND** | Masse | **GND** | Weiss |
| **DIN** | Daten (MOSI) | **Pin 51** | Gruen |
| **CLK** | Takt (SCK) | **Pin 52** | Orange |
| **CS** | Chip Select | **Pin 10** | Gelb |
| **DC** | Data/Command | **Pin 9** | Blau |
| **RST** | Reset | **Pin 8** | Braun |
| **BL** | Hintergrundbeleuchtung | **5V** | Grau |

> **Hinweis zu den Kabelfarben:** Diese Farben gelten fuer das mitgelieferte
> Kabel dieses Moduls. Verlass dich im Zweifel immer auf die **Beschriftung
> auf der Platine** (VCC, GND, DIN, ...) - die Farbe ist nur eine Hilfe.

> **BL (Backlight):** Direkt an 5V anschliessen = Beleuchtung immer an.
> (Man koennte BL auch an einen PWM-Pin haengen um zu dimmen, brauchen wir aber nicht.)

> **Wichtiger Hinweis von Waveshare:** Beim Betrieb mit Arduino muss das Modul
> an **5V** haengen (nicht 3.3V), sonst bleibt das Display evtl. schwarz.

---

## Verkabelungs-Schaubild

So sieht die Verbindung aus. Links das Display (8 Pins von oben nach unten),
rechts der Arduino Mega:

```
   WAVESHARE 2" DISPLAY                    ARDUINO MEGA 2560
   +------------------+
   |                  |
   |   2inch LCD      |
   |   ST7789V        |
   |   240x320        |
   |                  |
   +------------------+
     |                                    
     | Pin      Kabel                     Anschluss am Mega
     |
     +-- VCC ... Lila  ------------------> 5V         (Power-Leiste)
     +-- GND ... Weiss ------------------> GND        (Power-Leiste)
     +-- DIN ... Gruen ------------------> Pin 51     (MOSI, im Block "COMMUNICATION")
     +-- CLK ... Orange -----------------> Pin 52     (SCK,  daneben)
     +-- CS  ... Gelb  ------------------> Pin 10     (Digital-Leiste PWM)
     +-- DC  ... Blau  ------------------> Pin 9      (Digital-Leiste PWM)
     +-- RST ... Braun ------------------> Pin 8      (Digital-Leiste PWM)
     +-- BL  ... Grau  ------------------> 5V         (Power-Leiste, immer an)
```

### Wo finde ich die Pins am Arduino Mega?

Der Arduino Mega hat mehrere Pin-Bloecke. Hier die Fundorte:

```
                 ARDUINO MEGA 2560 (Draufsicht)
   +-----------------------------------------------------------+
   |  [USB]                                        [Power-Jack]|
   |                                                           |
   |  DIGITAL (PWM)                                            |
   |  22 23 24 ... (viele Pins)                                |
   |                                                           |
   |         Pin 13 12 11 10  9  8  7 ...                      |  <- CS=10, DC=9, RST=8
   |                                                           |     hier oben rechts
   |                                                           |
   |  [ Mega-Chip ]                     COMMUNICATION          |
   |                                    50 51 52 53            |  <- DIN=51, CLK=52
   |                                                           |     Block unten
   |  POWER          ANALOG IN                                 |
   |  5V GND GND Vin  A0 A1 A2 ...                             |  <- 5V und GND hier
   +-----------------------------------------------------------+
```

- **5V und GND:** Im "POWER"-Block an der unteren Kante. Es gibt mehrere GND-Pins,
  nimm irgendeinen. Fuer VCC und BL (beide an 5V) brauchst du 2x 5V - nutze dafuer
  die 5V-Leiste am Breadboard, dann kannst du beide anschliessen.
- **Pin 8, 9, 10:** Im "DIGITAL"-Block, oben rechts, in der Zahlenreihe.
- **Pin 51, 52:** Im "COMMUNICATION"-Block (die kurze Doppelreihe neben dem Chip).
  Dort sind die Pins 50-53. Pin 51 = MOSI, Pin 52 = SCK.

### Tipp: 5V zweimal gebraucht (VCC + BL)

Da sowohl VCC als auch BL an 5V muessen, aber der Mega nur begrenzt 5V-Pins hat:
- Verbinde ein Kabel von Arduino **5V** zur **roten Leiste (+)** deines Breadboards
- Stecke dann VCC (Lila) UND BL (Grau) beide in die rote Leiste
- Genauso mit GND: ein Kabel von Arduino **GND** zur **blauen Leiste (-)**,
  dann GND (Weiss) und spaeter den Sensor-GND dort anschliessen

```
  Arduino 5V  ----> [ rote Leiste + ] <---- VCC (Lila)
                                      <---- BL  (Grau)
                                      <---- Sensor VCC
                                      <---- Luefter rot

  Arduino GND ----> [ blaue Leiste - ] <--- GND (Weiss)
                                       <--- Sensor GND
                                       <--- Luefter schwarz
```

---

## Sensor und Luefter

Wie beim normalen Drehzahlmesser:

| Anschluss | Nach |
|---|---|
| Sensor **VCC** | 5V |
| Sensor **GND** | GND |
| Sensor **D0/OUT** | Arduino **Pin 18** |
| Luefter **rot** | 5V |
| Luefter **schwarz** | GND |

---

## Aufbau Schritt fuer Schritt

> Arbeite immer OHNE Strom (USB abgezogen, Netzteil aus). Erst alles stecken,
> kontrollieren, DANN Strom rein.

### Schritt 1: Stromleisten vorbereiten
1. Kabel von Arduino **5V** → **rote Leiste (+)** am Breadboard
2. Kabel von Arduino **GND** → **blaue Leiste (-)** am Breadboard

### Schritt 2: Display-Strom anschliessen
3. **VCC** (Lila) → rote Leiste (+)
4. **BL** (Grau) → rote Leiste (+)
5. **GND** (Weiss) → blaue Leiste (-)

### Schritt 3: Display-Datenleitungen zum Arduino
6. **DIN** (Gruen) → Pin 51
7. **CLK** (Orange) → Pin 52
8. **CS** (Gelb) → Pin 10
9. **DC** (Blau) → Pin 9
10. **RST** (Braun) → Pin 8

### Schritt 4: Kontrolle
Geh die 10 Verbindungen nochmal durch. Sitzt jedes Kabel fest?
Steckt nichts schief oder in der falschen Reihe?

### Schritt 5: Bibliotheken installieren
Adafruit ST7735/ST7789 + Adafruit GFX (siehe oben), falls noch nicht geschehen.

### Schritt 6: Code hochladen
1. USB-Kabel Arduino → PC einstecken
2. Datei `drehzahlmesser_farbe.ino` in der Arduino IDE oeffnen
3. Board = "Arduino Mega or Mega 2560", Port pruefen
4. Upload druecken

### Schritt 7: Erster Test (nur Display)
Nach dem Upload sollte das Display schwarz werden und oben "Drehzahlmesser"
in Cyan anzeigen, darunter "RPM" und "Max:". Die grosse Zahl zeigt erstmal 0.

### Schritt 8: Sensor und Luefter anschliessen
1. Sensor **VCC** → rote Leiste, **GND** → blaue Leiste, **D0/OUT** → Pin 18
2. Luefter **rot** → rote Leiste, **schwarz** → blaue Leiste
3. Luefterblaetter durch die Gabel der Lichtschranke positionieren
4. Strom an - die Zahl sollte jetzt die Drehzahl anzeigen

---

## Was du auf dem Display siehst

```
Drehzahlmesser          <- Cyan, oben

8700                    <- grosse weisse Zahl
RPM

[=================   ]  <- Tacho-Balken (Farbe je nach Drehzahl)

Max: 8700 RPM           <- Rekordwert
```

---

## Haeufige Probleme und Loesungen

| Problem | Ursache | Loesung |
|---|---|---|
| Display bleibt schwarz | Falsche Spannung | VCC und BL an 5V (nicht 3.3V) |
| Display bleibt schwarz | Verkabelung | DIN→51, CLK→52 (Mega-SPI-Pins!) pruefen |
| Nur weisser/bunter Rauschbildschirm | RST/DC vertauscht | RST→8, DC→9 pruefen |
| Farben vertauscht (rot/blau) | Display-Variante | Im Code testen: tft.init mit SPI_MODE anpassen (frag mich) |
| Bild steht auf dem Kopf/seitlich | Rotation | Im Code `tft.setRotation(0)` auf 1, 2 oder 3 aendern |
| RPM zeigt 0 | Sensor | Ausrichtung der Lichtschranke pruefen |

> Falls die Farben rot und blau vertauscht sind (ein bekanntes Phaenomen bei
> manchen ST7789-Modulen), sag mir Bescheid - dann passe ich eine Zeile im Code an.

---

## Unterschied zu den anderen Versionen

| Version | Display | Anzeige | Verkabelung |
|---|---|---|---|
| `drehzahlmesser.ino` | LCD 1602 | Text | Viele Kabel + Poti |
| `drehzahlmesser_oled.ino` | OLED 0.96" | Text + Balken | 4 Kabel |
| `drehzahlmesser_farbe.ino` | Waveshare 2" | Farbe + Tacho | 8 Kabel |
