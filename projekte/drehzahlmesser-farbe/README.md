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

### Schritt 1: Display verkabeln
Verbinde die 8 Display-Pins nach der Tabelle oben mit dem Arduino Mega.
Am besten ueber das Breadboard oder mit Female-Female-Kabeln direkt.

### Schritt 2: Bibliotheken installieren
Adafruit ST7735/ST7789 + Adafruit GFX (siehe oben).

### Schritt 3: Code hochladen
1. Datei `drehzahlmesser_farbe.ino` in der Arduino IDE oeffnen
2. Board = "Arduino Mega or Mega 2560", Port pruefen
3. Upload druecken

### Schritt 4: Erster Test
Nach dem Upload sollte das Display schwarz werden und oben "Drehzahlmesser"
in Cyan anzeigen, darunter "RPM" und "Max:".

### Schritt 5: Sensor und Luefter anschliessen
Dann den Luefter starten und die Blaetter durch die Lichtschranke laufen lassen.

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
