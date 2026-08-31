# Projekt-Dashboard

> Letzte Aktualisierung: 2026-08-27

---

## Gesamtfortschritt

| Metrik | Wert |
|---|---|
| Projekte gesamt | 15 |
| Abgeschlossen | 1 |
| In Arbeit | 0 |
| Geplant | 14 |
| **Fortschritt** | **7%** |

```
[#..............] 1/15 Projekte
```

---

## Projektuebersicht

| # | Projekt | Schwierigkeit | Status | Datum Start | Datum Fertig |
|---|---|---|---|---|---|
| -- | **Drehzahlmesser (Luefter RPM)** | :yellow_circle: Leicht Fortgeschritten | :green_circle: Abgeschlossen | 2026-08-27 | 2026-08-27 |
| 01 | Blinkende LED | :green_circle: Anfaenger | :white_circle: Geplant | - | - |
| 02 | Ampelschaltung | :green_circle: Anfaenger | :white_circle: Geplant | - | - |
| 03 | Temperatur-/Feuchtigkeitssensor | :green_circle: Anfaenger | :white_circle: Geplant | - | - |
| 04 | Ultraschall-Entfernungsmesser | :green_circle: Anfaenger | :white_circle: Geplant | - | - |
| 05 | LCD-Display mit Temperatur | :yellow_circle: Leicht Fortgeschritten | :white_circle: Geplant | - | - |
| 06 | Servo-Motor Steuerung | :yellow_circle: Leicht Fortgeschritten | :white_circle: Geplant | - | - |
| 07 | Bewegungsmelder mit Alarm | :yellow_circle: Leicht Fortgeschritten | :white_circle: Geplant | - | - |
| 08 | RFID-Zugangskontrolle | :orange_circle: Fortgeschritten | :white_circle: Geplant | - | - |
| 09 | IR-Fernbedienungs-Steuerung | :orange_circle: Fortgeschritten | :white_circle: Geplant | - | - |
| 10 | Wetterstation | :orange_circle: Fortgeschritten | :white_circle: Geplant | - | - |
| 11 | Smart-Home-Simulation | :red_circle: Anspruchsvoll | :white_circle: Geplant | - | - |
| 12 | Einparkhilfe | :red_circle: Anspruchsvoll | :white_circle: Geplant | - | - |
| 13 | Passwort-Tuerschloss | :red_circle: Anspruchsvoll | :white_circle: Geplant | - | - |
| 14 | Reaktionsspiel | :red_circle: Anspruchsvoll | :white_circle: Geplant | - | - |

**Status-Legende:**
- :white_circle: Geplant
- :large_blue_circle: In Arbeit
- :green_circle: Abgeschlossen
- :red_circle: Pausiert/Problem

---

## Gelernte Konzepte

| Konzept | Gelernt in Projekt | Verstanden? |
|---|---|---|
| Digitale Eingaenge (digitalRead) | Drehzahlmesser | :green_circle: |
| Interrupts (attachInterrupt) | Drehzahlmesser | :green_circle: |
| LCD 1602 ansteuern (4-Bit) | Drehzahlmesser | :green_circle: |
| Bibliotheken verwenden (LiquidCrystal) | Drehzahlmesser | :green_circle: |
| Serieller Monitor | Drehzahlmesser | :green_circle: |
| Breadboard & Verkabelung | Drehzahlmesser | :green_circle: |
| Externe Stromversorgung (Breadboard PSU) | Drehzahlmesser | :green_circle: |
| Analoge Eingaenge (analogRead) | - | - |
| PWM-Signale | - | - |
| I2C-Kommunikation | - | - |
| SPI-Kommunikation | - | - |
| Funktionen schreiben | - | - |
| Arrays und Schleifen | - | - |

---

## Naechste Schritte

1. ~~**Arduino IDE installieren**~~ ERLEDIGT
2. ~~**Board per USB anschliessen und Blink-Test**~~ ERLEDIGT
3. ~~**Drehzahlmesser aufbauen**~~ ERLEDIGT (Sunon ~8700 RPM, LD3007MS ~3600 RPM)
4. **Naechstes Projekt waehlen** - was interessiert dich?

---

## Notizen & Erkenntnisse

_Hier trage ich Notizen ein, die waehrend der Projekte entstehen._

| Datum | Notiz |
|---|---|
| 2026-08-26 | Projektrepository angelegt, Dokumentation erstellt |
| 2026-08-27 | Arduino IDE installiert, Blink-Test erfolgreich |
| 2026-08-27 | Zusatzteile bestellt: Gabellichtschranke, IR-Reflexionssensor, WLAN, Bluetooth, LED-Streifen, OLED |
| 2026-08-27 | Drehzahlmesser-Projekt gestartet (Gabellichtschranke + LCD 1602) |
| 2026-08-27 | Drehzahlmesser ABGESCHLOSSEN - Sunon ~8700 RPM, LD3007MS ~3600 RPM |
| 2026-08-27 | Erkenntnis: Trimmer-Poti (10K, 3 Beinchen) vs. Rotary Encoder (5 Pins) unterscheiden! |

---

## Statistiken

| Kategorie | Anzahl |
|---|---|
| Verschiedene Sensoren genutzt | 1 / 8 (Gabellichtschranke LM393) |
| Verschiedene Aktoren genutzt | 0 / 5 |
| Bibliotheken installiert | 1 / 7 (LiquidCrystal) |
| Code-Zeilen geschrieben | ~120 |
| Stunden investiert | ~2 |

---

## Zusaetzliche Hardware (nicht im Kit)

| Bauteil | Status | Eingesetzt in |
|---|---|---|
| Gabellichtschranke LM393 (3x) | Vorhanden | Drehzahlmesser |
| IR-Reflexionssensor FC-51 (5x) | Vorhanden | - |
| ESP8266 WiFi-Modul | Vorhanden | - |
| HC-05/HC-06 Bluetooth-Modul | Vorhanden | - |
| WS2812B LED-Streifen | Vorhanden | - |
| OLED-Display 0.96" SSD1306 | Kommt Dienstag | - |

---

## Links & Ressourcen

- [Kit-Komponenten](docs/kit-komponenten.md) - Was ist alles im Kit?
- [Hardware-Datenbank](docs/hardware/) - Alle Bauteile mit Bildern
- [Projektideen](docs/projektideen.md) - Alle Projekte mit Details
- [Software-Setup](docs/software-setup.md) - Installationsanleitung
- [Arduino Referenz](https://www.arduino.cc/reference/de/) - Offizielle Dokumentation
- [Elegoo Tutorials](https://global.elegoo.com/blogs/arduino-projects/elegoo-mega-2560-the-most-complete-starter-kit-tutorial) - Original-Tutorials vom Kit
