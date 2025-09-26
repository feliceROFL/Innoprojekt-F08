#include <QTRSensors.h>

// Dieses Beispiel ist für die Verwendung mit 5 RC QTR-Sensoren konzipiert.
// Diese Reflexionssensoren sollten mit den digitalen Pins 5 bis 11 verbunden werden.
// Der Steuerpin der Sensor-LEDs (CTRL oder LEDON) kann optional mit
// dem digitalen Pin 12 verbunden werden, oder Sie lassen ihn unverbunden und
// entfernen den Aufruf von setEmitterPin().
//
// Um den Sensor zu testen, decken Sie jeweils eine einzelnen Sensor mit dem Finger ab. 
// Dabei sollte der Sensorwert in den zweistelligen Bereich abfallen. Wiederholen
// Sie das mit allen Sensoren und verifizierne Sie, dass alle wie gewünscht funktionieren. 
// Optional können Sie mit schwarzem Isolierband eine Linie auf eine helle Oberfläche kleben. 
// Wenn Sie nun das Sensor Array darüber bewegen, dann sollten Sie anhand der Veränderung der Sensorwerte
// die Position der Linie erkennen können.

QTRSensors qtr;

const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

void setup()
{
  // Sensor konfigurieren
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){11, 8, 7, 6, 5}, SensorCount);
  qtr.setEmitterPin(12);

  Serial.begin(9600);
}


void loop()
{
  // Sensordaten auslesen.
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(100); // ~10 Hz
}