# Software-Setup fuer Arduino-Projekte

Diese Anleitung beschreibt alle Programme, die du auf deinem Mac brauchst, um mit dem Elegoo Mega 2560 Kit zu arbeiten.

---

## 1. Arduino IDE (Pflicht)

Die Arduino IDE ist das Hauptprogramm zum Schreiben und Hochladen von Code auf das Board.

**Download:** https://www.arduino.cc/en/software

**Installation auf macOS:**
1. Lade die macOS-Version herunter (Apple Silicon oder Intel, je nach Mac)
2. Oeffne die heruntergeladene `.dmg` Datei
3. Ziehe die Arduino IDE in den Applications-Ordner
4. Beim ersten Start: Sicherheitsabfrage mit "Oeffnen" bestaetigen

**Erste Einrichtung:**
1. Arduino IDE oeffnen
2. Menue: **Tools → Board → Arduino AVR Boards → Arduino Mega or Mega 2560**
3. Board per USB anschliessen
4. Menue: **Tools → Port → /dev/cu.usbmodemXXXX** (den Port waehlen der erscheint)
5. Test: **Datei → Beispiele → 01.Basics → Blink** oeffnen und hochladen (Pfeil-Button)

**Treiber (macOS):**
- Normalerweise werden keine zusaetzlichen Treiber benoetigt
- Falls das Board nicht erkannt wird: CH340 Treiber installieren
  (Download: https://github.com/adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver)

---

## 2. Kiro IDE (bereits installiert)

Du arbeitest bereits in Kiro! Hier schreibe ich den Code fuer dich und erklaere alles.

**Vorteile von Kiro fuer Arduino:**
- Ich schreibe den kompletten Code fuer dich
- Ich erklaere jeden Codeabschnitt verstaendlich
- Ich helfe bei Fehlern und Problemen
- Ich dokumentiere alles automatisch

**Workflow:**
1. Du beschreibst mir, was das Projekt tun soll
2. Ich erstelle den Code und die Verkabelungsanleitung
3. Du kopierst den Code in die Arduino IDE
4. Du laedt ihn auf das Board hoch
5. Bei Problemen beschreibst du mir, was passiert

---

## 3. Benoetigte Arduino-Bibliotheken

Bibliotheken sind Erweiterungen, die bestimmte Bauteile einfacher nutzbar machen.

**Installation in der Arduino IDE:**
Menue: **Sketch → Bibliothek einbinden → Bibliotheken verwalten...**

| Bibliothek | Wofuer | Projekt |
|---|---|---|
| DHT sensor library (Adafruit) | DHT11 Temperatur/Feuchtigkeit | 03, 05, 10 |
| LiquidCrystal_I2C | LCD Display ueber I2C | 05, 08, 09, 10 |
| Servo | Servo-Motor steuern | 06, 08 |
| MFRC522 | RFID-Modul | 08 |
| IRremote | IR-Fernbedienung | 09 |
| Keypad | 4x4 Tastenfeld | 13 |
| Stepper | Schrittmotor | Bonus |

**So installierst du eine Bibliothek:**
1. Arduino IDE oeffnen
2. **Sketch → Bibliothek einbinden → Bibliotheken verwalten...**
3. Im Suchfeld den Namen eingeben (z.B. "DHT sensor library")
4. Auf "Installieren" klicken
5. Fertig!

---

## 4. Optionale Software

### Fritzing (Schaltplan-Software)
Zum Visualisieren von Schaltplaenen - nicht zwingend noetig, da ich dir die Verkabelung als Text beschreibe.

**Download:** https://fritzing.org (kostenpflichtig, ca. 8 EUR)
**Kostenlose Alternative:** Tinkercad Circuits (Browser-basiert, https://www.tinkercad.com)

### Tinkercad (Browser-basiert, kostenlos)
- Schaltungen virtuell aufbauen und testen
- Arduino-Code simulieren OHNE echtes Board
- Ideal zum Vorher-Testen
- **URL:** https://www.tinkercad.com

### Serial Plotter Tools (optional)
- Die Arduino IDE hat einen eingebauten **Seriellen Monitor** und **Seriellen Plotter**
- Damit kannst du Sensordaten live als Grafik sehen

---

## 5. Git & GitHub (fuer Dokumentation)

Git ist bereits auf deinem Mac installiert (kommt mit Xcode Command Line Tools).

**Pruefen ob Git installiert ist:**
```bash
git --version
```

**GitHub Desktop (optional, einfacher als Kommandozeile):**
- Download: https://desktop.github.com
- Damit kannst du Aenderungen per Mausklick auf GitHub hochladen

**Ich uebernehme das fuer dich:**
- Ich initialisiere das Git-Repository
- Ich erstelle Commits mit sinnvollen Nachrichten
- Ich pushe auf GitHub wenn du es wuenschst

---

## 6. Zusammenfassung - Was brauchst du wirklich?

| Software | Pflicht? | Zweck |
|---|---|---|
| Arduino IDE | Ja | Code auf Board hochladen |
| Kiro | Ja (hast du) | Code schreiben lassen, Hilfe bekommen |
| Arduino-Bibliotheken | Je nach Projekt | Bauteile ansteuern |
| Git | Empfohlen (vorinstalliert) | Versionierung & Backup |
| Tinkercad | Optional | Schaltungen simulieren |
| Fritzing | Optional | Schaltplaene zeichnen |

---

## 7. Checkliste vor dem ersten Projekt

- [ ] Arduino IDE installiert
- [ ] Arduino IDE geoeffnet und Board "Arduino Mega or Mega 2560" ausgewaehlt
- [ ] Board per USB angeschlossen
- [ ] Port in Arduino IDE ausgewaehlt (unter Tools → Port)
- [ ] Test: Blink-Beispiel hochgeladen (LED auf dem Board blinkt)
- [ ] Wenn Blink funktioniert: Bereit fuer Projekt 01!

---

## Haeufige Probleme & Loesungen

| Problem | Loesung |
|---|---|
| Board wird nicht erkannt | Anderes USB-Kabel probieren (manche sind nur Ladekabel) |
| Port taucht nicht auf | CH340-Treiber installieren, Mac neustarten |
| Upload-Fehler | Richtiges Board ausgewaehlt? Richtigen Port gewaehlt? |
| "avrdude: stk500v2" Fehler | Reset-Knopf auf dem Board druecken, dann sofort Upload starten |
| Bibliothek nicht gefunden | Exakten Namen in Bibliotheksverwaltung suchen |
