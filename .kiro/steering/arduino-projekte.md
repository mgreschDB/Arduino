# Arduino-Projekte Steering

## Kontext

Der Benutzer ist Programmier-Anfaenger und arbeitet mit dem Elegoo Mega 2560 "The Most Complete Starter Kit".
Er kann nicht programmieren - Kiro schreibt den kompletten Code und erklaert alles verstaendlich.

## Projektstruktur

- Jedes Projekt liegt in `projekte/XX-name/`
- Jedes Projekt hat eine eigene `README.md` mit:
  - Beschreibung was das Projekt tut
  - Benoetigte Bauteile
  - Verkabelungsanleitung (Pin-fuer-Pin als Tabelle)
  - Erklaerung des Codes
  - Haeufige Probleme und Loesungen
- Der Arduino-Sketch liegt als `.ino` Datei im Projektordner
- Das DASHBOARD.md wird bei jedem Projektstart/-abschluss aktualisiert

## Code-Stil

- Arduino C/C++ Code
- Ausfuehrliche Kommentare in Deutsch (jede Zeile oder Block erklaeren)
- Einfache Variablennamen auf Deutsch oder selbsterklaerend
- `setup()` und `loop()` klar getrennt mit Kommentarheadern
- Keine komplexen Konstrukte (keine Templates, kein OOP) in Anfaenger-Projekten
- Pin-Definitionen als `const int` am Dateianfang mit Erklaerung

## Verkabelungsanleitungen

- Immer als Tabelle mit: Bauteil-Pin → Arduino-Pin
- Zusaetzlich als Textbeschreibung fuer absolute Anfaenger
- Hinweis auf Polaritaet bei LEDs, Elkos etc.
- Warnung bei Bauteilen die kaputt gehen koennen (z.B. LED ohne Widerstand)

## Erklaerungen

- Fachbegriffe immer erklaeren (z.B. "PWM - das ist ein schnelles Ein- und Ausschalten")
- Analogien verwenden (z.B. "Ein Widerstand ist wie ein enger Wasserschlauch")
- Bei jedem neuen Konzept: Was ist es? Wozu braucht man es? Wie benutzt man es?

## Dashboard-Updates

Wenn ein Projekt gestartet wird:
- Status in DASHBOARD.md auf ":large_blue_circle: In Arbeit" setzen
- Startdatum eintragen

Wenn ein Projekt abgeschlossen wird:
- Status auf ":green_circle: Abgeschlossen" setzen
- Enddatum eintragen
- Gelernte Konzepte aktualisieren
- Statistiken erhoehen

## Git-Workflow

- Nach jedem abgeschlossenen Projekt: Commit und Push
- Commit-Nachricht: "Projekt XX: [Name] abgeschlossen"
- Bei Zwischenstaenden: "Projekt XX: [Name] - [was gemacht wurde]"

## Referenzen

#[[docs/kit-komponenten.md]]
#[[docs/projektideen.md]]
#[[DASHBOARD.md]]
