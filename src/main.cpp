#include "ServoControl.h"
#include "SensorDeteksiObjek.h"
#include "MP3Player.h"
#include "WifiControl.h"
#include "MqttClient.h"
#include "config.h"

bool isOpen = false;

HardwareSerial serial2(1);
ServoControl servoControl(SERVO_PIN);
SensorDeteksiObjek sensorDeteksiObjek(TRIGGER_PIN, ECHO_PIN);
MP3Player mp3Player;
WifiControl wifiControl(WIFI_SSID, WIFI_PASSWORD);
MqttClient mqttClient(wifiControl.getClient(), MQTT_SERVER, MQTT_PORT);

void callback(String message) {
  if (message == "open") {
    servoControl.open();
    mp3Player.playByIndex(1);
    isOpen = true;

    Serial.println("Servo terbuka");
  }
}

void setup() {
  // Serial
  Serial.begin(SERIAL_BAUDRATE);

  // Wifi
  wifiControl.connect();

  // MQTT Client
  mqttClient.setCallback(callback);
  mqttClient.setSubscribe(MQTT_TOPIC);
  mqttClient.begin();

  // MP3 Player
  serial2.begin(MP3_PLAYER_BAUDRATE, SERIAL_8N1, MP3_PLAYER_RX_PIN, MP3_PLAYER_TX_PIN);
  mp3Player.begin(serial2);
  mp3Player.setVolume(30); // Volume 0 - 30
  
  // Servo
  servoControl.begin();
  servoControl.close();

  // Sensor Deteksi Objek
  sensorDeteksiObjek.begin();
}

void loop() {
  if (!mqttClient.isConnect()) {
    mqttClient.reconnect();
  }

  if (isOpen) {
    long jarakObjek = sensorDeteksiObjek.readDistance();

    if (jarakObjek < JARAK_MAX) {
      servoControl.close();
      mp3Player.playByIndex(1);
      isOpen = false;

      Serial.println("Servo tertutup");
    }
  }

  mqttClient.loop();
}
