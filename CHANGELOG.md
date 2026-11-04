# Changelog

Alle nennenswerten Aenderungen. Format: [Keep a Changelog], SemVer.

## [Unreleased]
### Added
- LED-Streifen physisch aufbauen und testen (Code steht bereit)

## [0.4.0] - 2026-11-04
### Added
- Standard-Doku-Set ausgefuellt: PROJECT.md (Migrations-Versicherung mit
  Hardware + Library-Versionen), WORKLOG.md, CHANGELOG.md, ISSUES.md
### Changed
- Elegoo-Tutorial (25 MB Fremddaten) aus dem Git entfernt und gitignored
  (aufs NAS ausgelagert, via Elegoo-Download reproduzierbar)
- Repo-Struktur an Kiro-Standard angeglichen; .ino in IDE-konforme Unterordner
- Generischen Worklog-Reminder-Hook entfernt (laeuft jetzt global)

## [0.3.0] - 2026-09-07
### Added
- Drehzahlmesser Vergleichsversion: 2 Luefter gleichzeitig (2 Sensoren an
  Pin 18/19), zwei runde Tachos mit Nadel und Live-Vergleich
- LED-Streifen-Projekt (WS2812B, 144 LEDs) mit FastLED: 5 Effekte,
  Helligkeits- und Strombegrenzung
- Ergebnisfoto der Vergleichsversion
### Fixed
- Verkabelungsanleitung der Farbversion verstaendlicher (Schaubild, Pin-Fundorte)

## [0.2.0] - 2026-09-04
### Added
- Drehzahlmesser Farbversion fuer Waveshare 2" ST7789 (grosse Zahl + Tacho-Balken)
- Echte Kabelfarben des Waveshare-Moduls dokumentiert

## [0.1.1] - 2026-09-02
### Added
- Drehzahlmesser OLED-Version (SSD1306, I2C): Zahl, Rekordwert, Balken

## [0.1.0] - 2026-08-31
### Added
- Erstes Projekt: Luefter-Drehzahlmesser (Gabellichtschranke LM393 + LCD 1602,
  interrupt-basiert), inkl. Verkabelungsanleitung
- Hardwaredatenbank (docs/hardware/)

## [0.0.1] - 2026-08-26
### Added
- Projekt-Grundgeruest: README, DASHBOARD, Kit-Komponenten, Projektideen,
  Software-Setup, projektspezifisches Steering
- Git + privates GitHub-Repo (mgreschDB/Arduino)
