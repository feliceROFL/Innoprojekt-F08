#include <QTRSensors.h>
#include <WiFiS3.h>

// Dieses Beispiel zeigt wie man die WiFi Funktion des Arduinos nutzen kann.
// Der Code liest die Sensordaten des IR Sensors aus, exakt wie in dem Code zum Testen des IR Sensors.
// Um zu verstehen wie das Auslesen funktioniert, schauen Sie sich bitte die Datei zum Testen des IR Sensors an.
// Der Arduino hostet lokal einen Webserver mit welchem man mit Netcat kommunizieren kann. Mehr dazu in der Mechatronikanleitung.

#define SECRET_SSID "Hotspot"  // Name des verwendeten Netzwerks
#define SECRET_PASS "Passwort"  // Passwort für das Netzwerk

QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

int status = WL_IDLE_STATUS; //Wifi Status
WiFiServer server(8080);  // ⚠️ TCP-Port 8080 für Netcat (nicht Telnet!)
char ssid[] = SECRET_SSID; // Variable für den Netzwerknamen
char pass[] = SECRET_PASS; // Variable für das Passwort

void setup() {
  Serial.begin(9600); 
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);

  if (WiFi.status() == WL_NO_MODULE) { // Prüfen ob das Wifi Modul am Arduino vorhanden ist.
    Serial.println("WiFi-Modul nicht gefunden!"); 
    while (true); 
  }

  while (status != WL_CONNECTED) { //Solange der Arduino nicht mit dem Wifi verbunden ist, versucht er eine Verbindung aufzubauen. 
    Serial.print("Verbinde mit WLAN: "); 
    Serial.println(ssid); // Netzwerknamen drucken
    status = WiFi.begin(ssid, pass); // Wifi status drucken
    delay(10000);
  }

  server.begin();  // TCP-Server starten
  digitalWrite(LED_BUILTIN, HIGH); 
  printWifiStatus(); // IP-Adresse und Netzwerknamen drucken

  // Sensoren konfigurieren
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){11, 8, 7, 6, 5}, SensorCount);
  qtr.setEmitterPin(12);
}

// Command fürs Terminal
// echo "start" | nc 172.20.10.2 8080

void loop() {
  WiFiClient client = server.available();  // Prüfen, ob ein Client verbunden ist
  qtr.read(sensorValues);

  if (client) {
    for (uint8_t i = 0; i < SensorCount; i++) {
      client.print(sensorValues[i]);
      client.print('\t');
    }
    client.println();
    delay(100);  // ca. 10 Hz
  }
}

void printWifiStatus() {
  Serial.print("Verbunden mit: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP-Adresse des Arduino: ");
  Serial.println(ip);
}