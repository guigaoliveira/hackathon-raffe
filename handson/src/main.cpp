
/**
 * Exemplo de código de uma lâmpada controlada pela plataforma
 * SaIoT usando o protocolo MQTT. Nesse exemplo foi usado a
 * biblioteca para dispositivos IoT se comunicarem com a plata-
 * forma.
 * Autores:
 * Danielly Costa daniellycosta97@ufrn.edu.br
 * Patricio Oliveira patricio@bct.ect.ufrn.br
 * Ricardo Cavalcanti ricavalcanti@bct.ect.ufrn.br
 *
 * */

 #include <Wire.h>
 #include <Arduino.h>
 #include <SaIoTDeviceLib.h>
 #include <Adafruit_BMP085.h>

#define timeToSend 15
Adafruit_BMP085 bmp;
WiFiClient espClient;
void callback(char* topic, byte* payload, unsigned int length);
SaIoTDeviceLib barril("barril-raffe","barril01","apenaspatricio@gmail.com");
// SaIoTController solenoide("on/off","v.Solenoide","onoff");
SaIoTSensor barril_t("t0001","barril_01"," C","number");
String senha = "321321321321";

unsigned long tDecorrido;
String getHoraAtual();
void setup(){
  bmp.begin();
  // barril.addController(solenoide);
  barril.addSensor(barril_t);
  Serial.begin(115200);
  Serial.println("INICIO");
  barril.preSetCom(espClient, callback);
  barril.startDefault(senha);

	tDecorrido = millis();
}

void loop(){
	if( ((millis() - tDecorrido)/1000) >= timeToSend ){
		barril_t.sendData(bmp.readTemperature(),SaIoTCom::getDateNow());
		tDecorrido = millis();
	}
	barril.handleLoop();
}

void callback(char* topic, byte* payload, unsigned int length){
  String payloadS;
  Serial.print("Topic: ");
  Serial.println(topic);
  for (unsigned int i=0;i<length;i++) {
    payloadS += (char)payload[i];
  }
  if(strcmp(topic,barril.getSerial().c_str()) == 0){
    Serial.println("SerialLog: " + payloadS);
  }
  // if(strcmp(topic,(barril.getSerial()+solenoide.getKey()).c_str()) == 0){
  //   Serial.println("SerialLog: " + payloadS);
  //   //
  // }
}













































//
// Adafruit_BMP085 bmp;
// WiFiClient espClient;
// void callback(char* topic, byte* payload, unsigned int length);
// // void startSensors();
// /* TEMPERATURA PRESSAO. */
// // void BMP085UpdateValues();
//
// SaIoTDeviceLib barril("DeviceTeste","haktemp","apenaspatricio@gmail.com");
// SaIoTSensor barril_t("t","temp.barril_01","°C","number");
//
// // #include <SaIoTDeviceLib.h>
// // #define timeToSend 15
// //
// // SaIoTDeviceLib barril("barril-cerva", "raffe-bar-0001", "apenaspatricio@gmail.com");
//
// //
// //
// // // SaIoTController myController("controllerKey", "controllerTag", "onoff");
// // //SaIoTController myControllerJSON("{\"key\":\"controllerKeyJSON\",\"tag\":\"controllerTagJSON\",\"class\":\"onoff\"}");
// //
// // SaIoTSensor termometro("t","Temperatura","°C","number");
// // //SaIoTSensor mySensorJSON("{\"key\":\"on/off\",\"tag\":\"simpleToggle\",\"class\":\"onoff\"}");
// //
// String senha = "321321321321";
// //
// unsigned long tDecorrido;
// // String getHoraAtual();
// void setup(){
//   Serial.begin(115200);
//   Serial.println("INICIO");
// //   barril.addController(myController);
//   barril.addSensor(barril_t);
//   barril.preSetCom(espClient, callback);
//   barril.startDefault(senha);
//   Serial.println(SaIoTCom::getDateNow());
// }
// //
// void loop(){
//   delay(1000);
//
// // 	if( ((millis() - tDecorrido)/1000) >= timeToSend ){
//   barril_t.sendData(bmp.readTemperature(),SaIoTCom::getDateNow());
//   // BMP085UpdateValues();
//
// // 		tDecorrido = millis();
// // 	}
//   barril.handleLoop();
// }
// //
// void callback(char* topic, byte* payload, unsigned int length){
//    String payloadS;
//    Serial.print("Topic: ");
//    Serial.println(topic);
//    for (unsigned int i=0;i<length;i++) {
//      payloadS += (char)payload[i];
//    }
//    if(strcmp(topic,barril.getSerial().c_str()) == 0){
//      Serial.println("SerialLog: " + payloadS);
//    }
//    // if(strcmp(topic,(barril.getSerial()+barril_t.getKey()).c_str()) == 0){
//    //   Serial.println("SerialLog: " + payloadS);
//    //   //
//    // }
// }
//
// // void BMP085UpdateValues(){
// //   Serial.print("Temperatura = ");
// //   Serial.print(bmp.readTemperature());
// //   Serial.println(" °C");
// //   Serial.print("Pressao = ");
// //   Serial.print(bmp.readPressure());
// //   Serial.println(" Pa");
// //   Serial.print("Altitude real = ");
// //   Serial.print(bmp.readAltitude(100700));//pressão atmosferica 0m em Natal
// //   Serial.println(" metros");
// //   Serial.println();
// // }
//
// // void startSensors(){
// //   if (!bmp.begin()) {
// //   Serial.println("Sensor BMP085 não encontrado, verifique as conexões !");
// //   while (1) {}
// //   }
// // }
