#include <Arduino.h>
#include <SaIoTDeviceLib.h>
#include <DHT.h>

#define DHTPIN D1     // pino dht
#define DHTTYPE DHT11 // DHT 11
#define timeToSend 5

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;

SaIoTDeviceLib hackathon("Hackathon Device", "40402", "gm@email.com");
SaIoTSensor temperature("temp1", "temp1", "°C", "number");
SaIoTSensor humidity("humi1", "humi1", "%", "number");
String senha = "12345678910";

void callback(char *topic, byte *payload, unsigned int length);

unsigned long tDecorrido;

String getHoraAtual();

void setup()
{
    hackathon.addSensor(temperature);
    hackathon.addSensor(humidity);
    Serial.begin(115200);
    Serial.println("INICIO");
    hackathon.preSetCom(espClient, callback);
    hackathon.startDefault(senha);
    dht.begin();
    tDecorrido = millis();
}

void loop()
{
    if (((millis() - tDecorrido) / 1000) >= timeToSend)
    {
        String date = SaIoTCom::getDateNow();
        double humiData = dht.readHumidity();
        double tempData = dht.readTemperature();
        if (isnan(tempData) || isnan(humiData))
        {
            Serial.println("Falhou ao ler o DHT");
        }
        else
        {
            Serial.println(date);
            Serial.print("Umidade: ");
            Serial.print(dht.readHumidity(), 2);
            Serial.print("%");
            Serial.print(" Temperatura: ");
            Serial.print(tempData, 2);
            Serial.println(" °C");
            temperature.sendData(tempData, date);
            humidity.sendData(humiData, date);
        }
        tDecorrido = millis();
    }
    hackathon.handleLoop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String payloadS;
    Serial.print("Topic: ");
    Serial.println(topic);
    for (unsigned int i = 0; i < length; i++)
    {
        payloadS += (char)payload[i];
    }
    if (strcmp(topic, hackathon.getSerial().c_str()) == 0)
    {
        Serial.println("SerialLog: " + payloadS);
    }
}
