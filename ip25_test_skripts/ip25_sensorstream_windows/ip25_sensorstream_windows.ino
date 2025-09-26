// Dieses Beispiel zeigt wie man die WiFi Funktion des Arduinos nutzen kann.
// Der Code liest die Sensordaten des IR Sensors aus, exakt wie in dem Code zum Testen des IR Sensors.
// Um zu verstehen wie das Auslesen funktioniert, schauen Sie sich bitte die Datei zum Testen des IR Sensors an.
// Der Arduino hostet lokal einen Webserver mit welchem man via Telnet kommunizieren kann. Mehr dazu in der Mechatronikanleitung.
#include <QTRSensors.h>
#include <WiFiS3.h>
#define SECRET_SSID "Netzwerk"  // Netzwerk Name (Alle ETH-Netwerke oder Eduroam funktionieren hierfür nicht)
#define SECRET_PASS "Passwort"  //WiFi Passwort

// Variablen für die Sensoren
QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

int status = WL_IDLE_STATUS;  // WIFI Status
WiFiServer server(23);  // Initialisierung des Servers am Port 23 (Default Port für Telnet Kommunikation)
char ssid[] = SECRET_SSID;  // Variable für den Netzwerknamen      
char pass[] = SECRET_PASS;  // Variable für das Passwort



void setup()
{
  Serial.begin(9600);  // Initialisierung der Serial Kommunikation 
  delay(1000);  // Warten auf die Serial Verbindung
  pinMode(LED_BUILTIN, OUTPUT);  // Pin für die LED definieren
  if (WiFi.status() == WL_NO_MODULE) {  // Prüfen ob das WiFi Modul am Arduino vorhanden ist
    Serial.println("Kommunikation mit WiFi Modul fehlgeschlagen");
    while (true);  // Falls nicht bleibt man hier stecken
  }
  while (status != WL_CONNECTED) {  // Während der Arduino nicht mit dem WiFi verbunden ist versucht er eine Verbindung herzustellen
    Serial.print("Verbindung wird aufgebaut mit: ");
    Serial.println(ssid);  // Netzwerknamen drucken
    status = WiFi.begin(ssid, pass);  // WiFi Status drucken

    delay(10000); // 10 Sekunden warten um eine Verbindung herzustellen
  }
  server.begin();  // Den Server starten
  digitalWrite(LED_BUILTIN, HIGH);
  printWifiStatus();  // IP-Adresse und Netzwerknamen drucken
  
  // Sensor konfigurieren
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){11, 8, 7, 6, 5}, SensorCount);
  qtr.setEmitterPin(12);
}

void loop()
{
  WiFiClient client = server.available();  // Gerät, welches sich mit dem Server verbunden hat. (Falls eine Verbindung existiert).
  qtr.read(sensorValues);  // Sensoren auslesen
  if (client) {  // Prüfen ob die Verbindung noch besteht  // Wichtig für die richtige Verwendung.
    for (uint8_t i = 0; i < SensorCount; i++)
    {
      client.print(sensorValues[i]);  // Sensordaten an das Verbundene Gerät übermitteln
      client.print('\t');
    }
    client.println();
  delay(100); // ~10 Hz
  }
}

void printWifiStatus() {
  Serial.print("Verbunden mit: ");
  Serial.println(WiFi.SSID());  // Netzwerknamen drucken
  IPAddress ip = WiFi.localIP();  // IP-Adresse des Arduino abfragen
  Serial.print("IP Adresse des Arduino: ");
  Serial.println(ip);  // IP-Adresse drucken
}