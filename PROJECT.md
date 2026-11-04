# Arduino — Lernprojekte mit dem Elegoo Mega 2560 Starter Kit

> Steckbrief — immer aktuell halten, besonders die Versionen (Migrations-Versicherung).

## Zweck
Sammlung von Arduino-Lernprojekten rund um das **Elegoo Mega 2560 "The Most
Complete Starter Kit"**. Marco ist Programmier-Anfaenger; Kiro schreibt den Code,
erklaert ihn verstaendlich und dokumentiert alles. Jedes Projekt liegt in
`projekte/<name>/` mit eigener README (Beschreibung, Verkabelung, Code-Erklaerung,
Troubleshooting). Fortschritt wird im `DASHBOARD.md` getrackt, alle Bauteile in
`docs/hardware/` dokumentiert.

Reines Hardware-/Lern-Repo — **kein Deployment**, der Code laeuft direkt auf dem Board.

## Status
- Version: v0.4.0
- Stand: 2026-11-04
- Kurz: Drehzahlmesser in 4 Display-Varianten fertig und getestet; LED-Streifen-Projekt angelegt (Aufbau steht aus). Doku-Set und Struktur nach Standard vereinheitlicht.

## Tech-Stack (mit exakten Versionen)
| Komponente | Version | Hinweis |
|---|---|---|
| Arduino IDE | 2.x | Entwicklungsumgebung auf dem Mac (Apple Silicon) |
| Board-Paket | Arduino AVR Boards | Board: "Arduino Mega or Mega 2560" (ATmega2560) |
| Adafruit GFX Library | 1.12.6 | Grafik-Grundlagen (OLED + ST7789) |
| Adafruit ST7735/ST7789 Library | 1.11.0 | Treiber fuer Waveshare 2" Farbdisplay |
| Adafruit BusIO | installiert | Abhaengigkeit der Adafruit-Libs |
| Adafruit SSD1306 | installiert (Version bei Einsatz pruefen) | OLED 0.96" (I2C) |
| LiquidCrystal | IDE-Bordmittel | LCD 1602 (4-Bit) |
| FastLED | fuer LED-Streifen noch zu installieren | WS2812B-Ansteuerung |

> Serielle Baudrate in allen Sketches: **115200**.

## Hardware
**Hauptplatine:** Elegoo Mega 2560 R3 (ATmega2560), USB Typ B, 5V.

**Verwendete Bauteile (bisher):**
- LCD 1602A (16-Pin, QAPASS) + 10K Trimmer-Poti (Kontrast)
- OLED 0.96" SSD1306 (I2C, Adresse 0x3C) — SDA=Pin 20, SCL=Pin 21
- Waveshare 2" LCD (ST7789V, IPS, 240x320, SPI) — DIN=51, CLK=52, CS=10, DC=9, RST=8, BL+VCC=5V
- Gabellichtschranke LM393 (2 Stk. im Einsatz) — Interrupt-Pins 18 und 19
- WS2812B LED-Streifen, 144 LEDs — Datenpin 6, Farbreihenfolge GRB
- Breadboard 830 + Stromversorgungsmodul (3.3V/5V) + 9V-Netzteil

**Zusatzhardware vorhanden (noch ungenutzt):** IR-Reflexionssensor FC-51 (5x),
ESP8266 WiFi, HC-05/HC-06 Bluetooth.

Vollstaendige Bauteilliste mit Erkennungsmerkmalen: siehe `docs/hardware/README.md`.

## Start / Betrieb
```
# Kein Build-/Startbefehl auf dem Mac — Ablauf:
# 1. Projekt-Sketch in der Arduino IDE oeffnen (projekte/<name>/<name>/<name>.ino)
# 2. Board "Arduino Mega or Mega 2560" + richtigen Port waehlen
# 3. Upload-Button druecken
# 4. Ergebnis am Display bzw. im Seriellen Monitor (115200 Baud)
```
- Ports: entfaellt (laeuft auf dem Board)
- Env/Secrets: keine

## Deployment
- Ziel: — (kein Deployment, Code laeuft auf dem Mikrocontroller)

## Besonderheiten / Fallstricke
- **Mega-SPI-Pins:** DIN/MOSI=51, CLK/SCK=52 (anders als beim Uno 11/13).
- **Mega-I2C-Pins:** SDA=20, SCL=21 (anders als beim Uno A4/A5).
- **Interrupt-Pins am Mega:** 2, 3, 18, 19, 20, 21. Drehzahlmesser nutzt 18 + 19;
  20/21 bleiben fuer I2C frei.
- **Waveshare-Display an 5V** betreiben (VCC und BL), sonst bleibt es dunkel.
- **WS2812B-Strom:** 144 LEDs koennen bis ~8,6 A ziehen. Helligkeit im Code
  begrenzt + FastLED-Strombegrenzung; Streifen NICHT ueber den Arduino-5V-Pin
  versorgen, sondern externes 5V-Netzteil. Gemeinsame Masse (GND) nicht vergessen.
- **Arduino-IDE-Ordnerkonvention:** Jede `.ino` liegt in einem gleichnamigen
  Unterordner (z.B. `drehzahlmesser_farbe/drehzahlmesser_farbe.ino`).
- **Elegoo-Tutorial liegt NICHT mehr im Git** (25 MB Fremddaten). Es ist
  gitignored und wurde aufs NAS ausgelagert — jederzeit reproduzierbar ueber den
  Elegoo-Download ("Mega 2560 The Most Complete Starter Kit" Tutorial).
- Kontrast beim LCD 1602 ueber das Trimmer-Poti einstellen; bei nur hellen
  Bloecken am Poti drehen.
