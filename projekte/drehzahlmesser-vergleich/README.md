# Projekt: Drehzahlmesser Vergleich - 2 Luefter mit Tacho

## Was macht dieses Projekt?

Misst **zwei Luefter gleichzeitig** und zeigt fuer jeden einen runden Tacho
mit Nadel auf dem Farbdisplay an. Dazwischen steht welcher Luefter schneller
dreht und um wie viel.

- Oben: Tacho fuer Luefter A mit Nadel und RPM-Zahl
- Mitte: Vergleich (z.B. "B schneller (+5100)")
- Unten: Tacho fuer Luefter B mit Nadel und RPM-Zahl

---

## Benoetigte Bauteile

| Bauteil | Anzahl | Status |
|---|---|---|
| Arduino Mega 2560 | 1 | Vorhanden |
| Waveshare 2" LCD (ST7789) | 1 | Vorhanden |
| Gabellichtschranke LM393 | 2 | Vorhanden (hast 3) |
| Luefter 5V (7 Blaetter) | 2 | Vorhanden |
| Breadboard + Stromversorgungsmodul | 1 | Vorhanden |
| 9V Netzteil | 1 | Vorhanden |
| Jumperkabel | diverse | Vorhanden |

---

## Benoetigte Bibliotheken

- **Adafruit ST7735 and ST7789 Library**
- **Adafruit GFX Library**

(Bereits installiert, wenn du die Farbversion schon gemacht hast.)

---

## Verkabelung

### Display (unveraendert zur Farbversion)

| Display | Kabel | Mega |
|---|---|---|
| VCC | Lila | 5V |
| GND | Weiss | GND |
| DIN | Gruen | Pin 51 |
| CLK | Orange | Pin 52 |
| CS | Gelb | Pin 10 |
| DC | Blau | Pin 9 |
| RST | Braun | Pin 8 |
| BL | Grau | 5V |

### Sensor 1 - Luefter A

| Sensor | Mega |
|---|---|
| VCC | 5V (rote Leiste) |
| GND | GND (blaue Leiste) |
| D0/OUT | **Pin 18** |

### Sensor 2 - Luefter B (NEU)

| Sensor | Mega |
|---|---|
| VCC | 5V (rote Leiste) |
| GND | GND (blaue Leiste) |
| D0/OUT | **Pin 19** |

### Luefter

| Luefter | Kabel | Nach |
|---|---|---|
| Luefter A | rot | 5V (rote Leiste) |
| Luefter A | schwarz | GND (blaue Leiste) |
| Luefter B | rot | 5V (rote Leiste) |
| Luefter B | schwarz | GND (blaue Leiste) |

> **WICHTIG - Stromversorgung:** Zwei Luefter zusammen ziehen zu viel Strom fuer
> den USB-Anschluss. Versorge die Luefter (und Sensoren) ueber dein
> **Breadboard-Stromversorgungsmodul mit dem 9V-Netzteil** (Jumper auf 5V).
> Der Arduino haengt weiterhin am USB. Verbinde die GND von Arduino und
> Breadboard miteinander (gemeinsame Masse)!

---

## Verkabelungs-Schaubild

```
                              ARDUINO MEGA 2560
                              
  DISPLAY (8 Pins)            Digital:  8 <- RST(Braun)
    VCC (Lila) --+                      9 <- DC (Blau)
    BL  (Grau) --+--> 5V-Leiste        10 <- CS (Gelb)
                                        
    GND (Weiss)---+                     
                  +--> GND-Leiste       Communication:
                                        51 <- DIN (Gruen)
    DIN (Gruen) ------> Pin 51          52 <- CLK (Orange)
    CLK (Orange)------> Pin 52          
    CS  (Gelb) -------> Pin 10          Interrupt-Pins:
    DC  (Blau) -------> Pin 9           18 <- Sensor A OUT
    RST (Braun)------> Pin 8            19 <- Sensor B OUT

  SENSOR A                     SENSOR B
    VCC --> 5V-Leiste            VCC --> 5V-Leiste
    GND --> GND-Leiste           GND --> GND-Leiste
    OUT --> Pin 18               OUT --> Pin 19

  Stromleisten (vom 9V-Netzteil ueber PSU-Modul):
    5V-Leiste (rot):  VCC-Display, BL, Sensor-A-VCC, Sensor-B-VCC, LuefterA+, LuefterB+
    GND-Leiste(blau): GND-Display, Sensor-A-GND, Sensor-B-GND, LuefterA-, LuefterB-,
                      + Kabel zu Arduino GND (gemeinsame Masse!)
```

---

## Aufbau Schritt fuer Schritt

1. **Display** wie in der Farbversion verkabeln (8 Verbindungen)
2. **Arduino GND** mit der blauen Breadboard-Leiste verbinden (gemeinsame Masse)
3. **Sensor A:** VCC→5V-Leiste, GND→GND-Leiste, OUT→Pin 18
4. **Sensor B:** VCC→5V-Leiste, GND→GND-Leiste, OUT→**Pin 19**
5. **Luefter A + B:** rot→5V-Leiste, schwarz→GND-Leiste
6. **9V-Netzteil** ins Stromversorgungsmodul, Schalter auf ON
7. **USB** vom Arduino zum PC
8. Sketch `drehzahlmesser_vergleich.ino` hochladen
9. Beide Luefterblaetter durch die jeweilige Gabel positionieren

---

## Was du auf dem Display siehst

```
        Luefter A
      .-''''''''-.
     /   \  |  /   \      <- Halbkreis-Tacho mit Nadel
    |     \ | /     |
         ( o )
        8700              <- RPM-Zahl

    B schneller (+700)    <- Vergleich in der Mitte

        Luefter B
      .-''''''''-.
     /   \  |  /   \
    |     \ | /     |
         ( o )
        9400
```

---

## Erklaerung: Wie funktioniert der Tacho?

### Die Nadel
Die Nadel ist eine Linie vom Mittelpunkt nach aussen. Der Winkel haengt von der
Drehzahl ab:
- 0 RPM → Nadel zeigt nach links (180 Grad)
- MAX_RPM (10000) → Nadel zeigt nach rechts (360 Grad)

Berechnet wird das mit **Sinus und Cosinus** (aus der Mathematik). Die geben zu
einem Winkel die X- und Y-Position auf dem Kreis. Keine Sorge, das macht der Code
fuer dich - du musst es nicht selbst rechnen.

### Warum zwei Interrupt-Pins?
Jeder Sensor braucht einen eigenen "sofort-reagier-Pin" (Interrupt). Der Mega hat
mehrere davon: Pin 2, 3, 18, 19, 20, 21. Wir nutzen 18 (Sensor A) und 19 (Sensor B).
Pin 20 und 21 sind fuer I2C reserviert (falls du spaeter das OLED zusaetzlich willst).

---

## Haeufige Probleme und Loesungen

| Problem | Ursache | Loesung |
|---|---|---|
| Ein Tacho bleibt auf 0 | Sensor falsch verkabelt | OUT-Pin pruefen (18 bzw. 19) |
| Arduino startet neu / haengt | Luefter ueberlasten USB | Luefter ueber 9V-Netzteil + PSU-Modul versorgen |
| Beide Tachos zeigen gleiche Zahl | Sensoren verwechselt/gleicher Pin | Jeder Sensor eigener Pin (18 und 19) |
| Nadel zittert | Sensor nicht stabil | Sensor fixieren |
| Werte unrealistisch | Blattzahl falsch | ANZAHL_BLAETTER im Code pruefen (7) |

---

## Unterschied zu den anderen Versionen

| Version | Luefter | Anzeige |
|---|---|---|
| `drehzahlmesser.ino` | 1 | LCD Text |
| `drehzahlmesser_oled.ino` | 1 | OLED Text + Balken |
| `drehzahlmesser_farbe.ino` | 1 | Farbe, Zahl + Balken |
| `drehzahlmesser_vergleich.ino` | **2** | **2 runde Tachos + Vergleich** |

---

## Ergebnis

**Status: ERFOLGREICH GETESTET** (2026-08-27)

Beide Tachos zeigen die Drehzahl mit roter Nadel, RPM-Zahl und Live-Vergleich.
Beispielmessung: Luefter A = 3214 RPM, Luefter B = 7740 RPM.

<!-- Ergebnisfoto: lege ein Foto als ergebnis.jpg in diesen Ordner -->
<!-- ![Ergebnis](ergebnis.jpg) -->

