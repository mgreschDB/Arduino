# Arbeitslog

> Taeglicher Log. Neueste Eintraege oben.

## 2026-11-04
### Ziele
- Standard-Doku-Set des Repos ausfuellen (war noch Vorlage/Geruest)
### Erledigt
- PROJECT.md mit echten Werten befuellt (Zweck, Hardware, Tech-Stack mit Versionen, Besonderheiten)
- WORKLOG.md und CHANGELOG.md rueckwirkend mit dem realen Verlauf gefuellt
- ISSUES.md mit offenen Punkten angelegt
- Elegoo-Tutorial (25 MB Fremddaten) aus dem Git entfernt und gitignored (aufs NAS ausgelagert, via Elegoo-Download reproduzierbar)
### Probleme & Loesungen
- Problem: Elegoo-Ordner blaehte das Repo/Backup um 25 MB auf.
  Loesung: Aus Git-Tracking entfernt, in .gitignore aufgenommen, Original aufs NAS.
### Offen (-> ISSUES.md)
- LED-Streifen physisch aufbauen und testen
- FastLED-Version nach Installation in PROJECT.md nachtragen

## 2026-11-03
### Ziele
- Repo-Struktur an den Kiro-Standard angleichen
### Erledigt
- Alle .ino in IDE-konforme gleichnamige Unterordner verschoben
- Standard-Doku-Dateien (PROJECT/WORKLOG/ISSUES/CHANGELOG) als Geruest angelegt
- Generischen Worklog-Reminder-Hook entfernt (laeuft jetzt global in ~/.kiro/hooks)

## 2026-09-07
### Ziele
- Drehzahlmesser auf Farbdisplay und auf Zwei-Luefter-Vergleich erweitern
- Neues Projekt LED-Streifen starten
### Erledigt
- Farbversion (Waveshare 2" ST7789) fertig: grosse Zahl + farbiger Tacho-Balken, erfolgreich getestet
- Verkabelung der Farbversion anschaulicher dokumentiert (Schaubild, Pin-Fundorte)
- Vergleichsversion: 2 Gabellichtschranken (Pin 18 + 19), zwei runde Tachos mit Nadel + Live-Vergleich
- Vergleichsversion erfolgreich getestet (Luefter A 3214 RPM, Luefter B 7740 RPM), Ergebnisfoto abgelegt
- LED-Streifen-Projekt (WS2812B, 144 LEDs) mit FastLED angelegt: 5 Effekte, Helligkeits-/Strombegrenzung
### Probleme & Loesungen
- Problem: Zwei Luefter + evtl. voller LED-Streifen ueberlasten den USB-Strom.
  Loesung: Versorgung ueber Breadboard-Netzteil (9V->5V); bei LEDs zusaetzlich Helligkeit im Code begrenzt.

## 2026-09-04
### Ziele
- Groesseres/schoeneres Display fuer den Drehzahlmesser
### Erledigt
- Waveshare 2" Farbdisplay (ST7789) ausgewaehlt und angeschlossen
- Farbversion des Sketches erstellt; echte Kabelfarben des Moduls dokumentiert

## 2026-09-02
### Ziele
- Drehzahlmesser vom LCD aufs OLED umstellen
### Erledigt
- OLED-Version (SSD1306, I2C) erstellt: grosse Zahl, Rekordwert und Balken
- Bibliotheken Adafruit SSD1306 + GFX eingebunden

## 2026-08-31
### Ziele
- Erstes richtiges Projekt: Luefter-Drehzahlmesser
### Erledigt
- Drehzahlmesser mit Gabellichtschranke (LM393) + LCD 1602 gebaut, interrupt-basiert
- Ausfuehrliche Verkabelungsanleitung erstellt und erweitert
- Projekt abgeschlossen; Hardwaredatenbank (docs/hardware/) angelegt
- Messung: Sunon MF30060V1 ~8700 RPM, LD3007MS ~3600 RPM
### Probleme & Loesungen
- Problem: Trimmer-Poti (3 Pins) mit Rotary Encoder (5 Pins) verwechselt.
  Loesung: Fuer LCD-Kontrast das 10K-Trimmer-Poti verwendet.

## 2026-08-26
### Ziele
- Projekt-Repository und Grundstruktur aufsetzen
### Erledigt
- README, DASHBOARD, Kit-Komponentenliste, Projektideen, Software-Setup angelegt
- Git initialisiert, privates GitHub-Repo (mgreschDB/Arduino) erstellt und gepusht
- Projektspezifische Steering-Datei (.kiro/steering/arduino-projekte.md) angelegt
