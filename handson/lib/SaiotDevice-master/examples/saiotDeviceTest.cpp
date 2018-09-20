/**
 * Exemplo de código de uma lâmpada controlada pela plataforma
 * SaIoT usando o protocolo MQTT. Nesse exemplo foi usado a
 * biblioteca para dispositivos IoT se comunicarem com a plata-
 * forma.
 * Autores:
 * Danielly Costa daniellycosta97@ufrn.edu.br
 * Patricio Oliveira patricio@bct.ect.ufrn.br
 * Ricardo Cavalcanti ricavalcanti@bct.ect.ufrn.br

  Especificações:
– Protocolo de comunicação: I2C
– Chip Acelerômetro: ADXL345 (datasheet)
– Endereço I2C: 0x53
– Faixa do Acelerômetro: ±2, ±4, ±8, ±16g
– Chip Giroscópio: L3G4200D (datasheet)
– Endereço I2C: 0x69
– Faixa do Giroscópio: ±250, 500, 2000°/s
– Chip Magnetômetro: HMC5883L (datasheet)
– Endereço I2C: 0x1E
– Chip Barômetro: BMP085 (datasheet)
– Endereço I2C: 0x77
– Tensão de operação: 3,3-5V
– Peso: 5g
– Dimensões: 25,8 x 16,8mm

  Pinagem:
  Todos os sensores são acessíveis via I2C. Para começar basta conectar apenas 4 pinos:
– GND: GND
– SCL: Clock I2C
– SCA: Dados I2C
– VCC: O sensor GY-80 é compatível com 3,3V e 5V. Se usando um Arduino Due, utilize 3,3V. Se Arduino Uno ou Arduino Mega, use 5V.

Chip Acelerômetro: ADXL345
Chip Giroscópio: L3G4200D
Chip Magnetômetro: HMC5883L
https://www.filipeflop.com/produto/modulo-bussola-eletronica-hmc5883l/
hip Barômetro: BMP085
 * */

#include <Arduino.h>
#include <SaIoTDeviceLib.h>
#define timeToSend 15

WiFiClient espClient;
SaIoTDeviceLib hidrometro("DeviceTeste","1658881hbc","ricardodev@email.com");
SaIoTController solenoide("on/off","v.Solenoide","onoff");
SaIoTSensor medidorAgua("hd01","hidrometro_01","Litros","number");
String senha = "12345678910";
void callback(char* topic, byte* payload, unsigned int length);

unsigned long tDecorrido;
String getHoraAtual();
void setup(){
  hidrometro.addController(solenoide);
  hidrometro.addSensor(medidorAgua);
  Serial.begin(115200);
  Serial.println("INICIO");
  hidrometro.preSetCom(espClient, callback);
  hidrometro.startDefault(senha);

	tDecorrido = millis();
}

void loop(){
	if( ((millis() - tDecorrido)/1000) >= timeToSend ){
		medidorAgua.sendData(random(1,30),SaIoTCom::getDateNow());
		tDecorrido = millis();
	}
	hidrometro.handleLoop();
}

void callback(char* topic, byte* payload, unsigned int length){
  String payloadS;
  Serial.print("Topic: ");
  Serial.println(topic);
  for (unsigned int i=0;i<length;i++) {
    payloadS += (char)payload[i];
  }
  if(strcmp(topic,hidrometro.getSerial().c_str()) == 0){
    Serial.println("SerialLog: " + payloadS);
  }
  if(strcmp(topic,(hidrometro.getSerial()+solenoide.getKey()).c_str()) == 0){
    Serial.println("SerialLog: " + payloadS);
    //
  }
}
