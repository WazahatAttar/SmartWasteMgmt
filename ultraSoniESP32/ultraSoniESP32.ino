#define TRIG_PIN 5 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 18 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#include "WiFi.h"
#define WIFI_NETWORK "Apt247"
#define WIFI_PASSWORD "kukukamagic"
#define WIFI_TIMEOUT_MS 20000
#include "config.h"
#define AWS_IOT_PUBLISH_TOPIC   "outTopic"
#define AWS_IOT_SUBSCRIBE_TOPIC "outTopic"
#include <pgmspace.h>
#define AWS_IOT_ENDPOINT "a1ivhna70vjk3a-ats.iot.us-east-1.amazonaws.com" 

#define AWS_CERT_CA "-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n"

#define AWS_CERT_PRIVATE "-----BEGIN CERTIFICATE-----\n" \
"MIIEowIBAAKCAQEAuswVdAjYJmljP5KXMNWtkknNzuXbfgxxMfPh1T/nqkz+EdbW\n" \
"omLLn25ImVz0x3nnsWqOvPVrb3dNDgBlq7ohEY9K9sUsYQPvbfvZg2fWFqpnXRnO\n" \
"gwesYFm/Tfkn1Ajh499CMCVrnWLEPjz9HfTQbDFmScUcLYzyNbPcsfOalJgLtYZc\n" \
"tNFQkrP2Fanh2X9jcejr++kWG730pdzfUIXkU//BFlE0112XCFUWkbZdtiWHTv8F\n" \
"MpMR3dCHHgOHKzNYobSZReiljwutHVFfMLfFjsgzbC+j0Md+auWXkVoyzAm7HywM\n" \
"3+jH89qQeg+PnhhVI1wIGWOeV2V4OWryh/6iVwIDAQABAoIBAG2W6AswWSeH8stM\n" \
"RFlJM1C87fqxTemQgSRuUZLbsB1wmCp9IWUZkx7RA9S9/Xm+IlkrC9z+Gu7FTjal\n" \
"swBh7Z6ws6k9GoE8Xs7mz8DRPYAErymmx0qGSPIqFRs4zs4N/ADFbb5zZcRrOnjN\n" \
"LS7S/yhKfxlOg+6RX1R0VkksgwcjfuNzgobC3DIw/PaWhJPpUitTsNXSyX84g+Gy\n" \
"m+wvgN7XTgZHDu6VVg6XftCmhnm2hz2qfhT51cFFtIF4a2dljPy0l1GqptiUlouK\n" \
"/fyNdIS7M4RMMa09KFGzw5AZ3G1p0vnbZzrk7Mvm9xWkpDJIXNRWHOFNcZXeZklq\n" \
"Zga0gtkCgYEA8kBr/+iu66A2vBSvwQJwegJl6odHhzQvNnZDFqGibqYe4IST4++r\n" \
"Vhnz39+QLvStlDIr4tZEFnXicEKtjSGCwrnhgAXLbYRqxRxz/IWqto95VKMJ7Pic\n" \
"P43y2VLJb+PA1+9sw0v0ab+T5nw2jDTb0Vii7SO/xiOpVW5Lg4oBOI0CgYEAxWX8\n" \
"fMgM4c67ytk2FYFIHkpd4qNeB2dvMGzn6CGNfS/1O23x09+oeaVc0Qm4yAnele4h\n" \
"/RXECNQAnSGFJpNZBy+b8TMoU/be8InMv/INAT2CtYj4nKlep/8cWSk0B40gQ2tP\n" \
"Bf7bbABG/YjFsvRJ3s+jHlvtZemaWfAJq/XX53MCgYAtqlsxeGlQ3Xiz56ph1dXi\n" \
"CgWwOiQPppSnzY9D+uAlv4beh99g/lLr/iRstTX2xATchMClGALpwPsYcllI22JM\n" \
"1sFdYrpAQM/nrD9pAMF3fIBApiM+2naJvHZk5Sg3wVUe33E/N1gxfv2gWxXlRCmT\n" \
"wwOjdDO4ZAyNoCb3+tHUGQKBgBLcedGac9Cnpj3tn0NSxQdP58SeA4AFnBQuc8I0\n" \
"YoaRrIbvLGooNrrY2BOJMES83K3KwSijicWmLCDXcReMgLc1D1tune3X6tlk8VFt\n" \
"2VxC+lhKLCcb79VxhM3oJ/aIv4pxmG1kOqcJJ79V8D33JY/KmzVtZzOTrJHnY6Uw\n" \
"ql6NAoGBAOqXeHfSTnWQ3opR9em+C9tI8Fv+27xRJuIIHkOeBeUd3b2fKRSuqnM7\n" \
"lw9/Wt2A6tq0x6pYABuUXSEp2UIRFQ3XVmmiQuHNW0fnbalspB/N7J9y5Bki2fk2\n" \
"d5TovxY58R+nCayWhTqxRMJvzeFzqapcdukuoIMMbbg0IzE+XuS6\n" \
"-----END CERTIFICATE-----\n"

#define AWS_CERT_CRT "-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUJJK/KjsZHah0yLdpgHkWxJsyc3owDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDQxNDA2MDEx\n" \
"MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALrMFXQI2CZpYz+SlzDV\n" \
"rZJJzc7l234McTHz4dU/56pM/hHW1qJiy59uSJlc9Md557Fqjrz1a293TQ4AZau6\n" \
"IRGPSvbFLGED72372YNn1haqZ10ZzoMHrGBZv035J9QI4ePfQjAla51ixD48/R30\n" \
"0GwxZknFHC2M8jWz3LHzmpSYC7WGXLTRUJKz9hWp4dl/Y3Ho6/vpFhu99KXc31CF\n" \
"5FP/wRZRNNddlwhVFpG2XbYlh07/BTKTEd3Qhx4DhyszWKG0mUXopY8LrR1RXzC3\n" \
"xY7IM2wvo9DHfmrll5FaMswJux8sDN/ox/PakHoPj54YVSNcCBljnldleDlq8of+\n" \
"olcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUhWafRJ7k4INboNCNmkWR/LQp8+owHQYD\n" \
"VR0OBBYEFAFp6u9uLIpJfgPmK9mlsqVG6N6CMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBUPDRRKE5iwVM7Gdk+u2OJSPk2\n" \
"9jeoT1twkwuA/7mG3aRapdXOEM5RueR4m+6Z5/x+K2ZSdDmU0eEksh/qENQtRg6T\n" \
"nvXYDobd+051CfOBGqO3Rk4F8mIm3O2Os4rNhmlU3YyPnSVIaeYFjvo8e0D+ko6Z\n" \
"5J3zVJziso8+vB3SY61HuyKCE0g8mR7IJkIEkqsju89Nje/bTw7uZ+udGh8WA6tj\n" \
"yVf/tdVTCMdPtvviRo/ExShw7yVxUmV7vRECkBK1wREhWsfHncPmyqkDJ9d2W0ab\n" \
"XjTTlTPWDx9CzkyFNDIz4HCtowZPG2A/bbTswPBla6W8lBt6ZLq5fOTKIEbO\n" \
"-----END CERTIFICATE-----\n"

//#define AWS_CERT_PRIVATE "-----BEGIN CERTIFICATE-----\n" \
//"MIIEpgIBAAKCAQEAyGG8aG5FKbMzHSO4k+Xws3AN4wn4gyNaHGd4D9kLu2OQNTIB\n" \
//"oMhoFfiMwGUjicZQJ/gM5CFYhK5rEHqBeSe57TkoH+B+z3nyMqq62HbKzRf7SbJu\n" \
//"pMxrrW5jVWe5A70s+zsPMrAclaiGG7laG+URQjGVEuok0sLj0USy0xjr25D8xjcW\n" \
//"urMJmSQ8nSIJblTUewN2/x4yqFIKZRbfLeTHQDru5LfoIgi+IhTCn8j+rfDo3Dzr\n" \
//"2lHjy7uiekQWaLBLpITlnTmFpytTnMrZBn+aAogeaDyMNVy8VA6w4uD+PLA6Xcq2\n" \
//"IovSMBY6zNNOFzEzsfDrgtRlUIkoBrCSMSRziQIDAQABAoIBAQCWJX36tl3GwEsV\n" \
//"k5WT5OE2Y0lUjT0UbmHwFKvHHDiJQjJlWcIUivZLOEGnTGGTs/CN8nUeX8onKVZ6\n" \
//"M4FemiDcG07wi9QZfOO5iWqWFnUhts2JTFVR0QcCHkv6S807ev4AhiF+Nq5EidFr\n" \
//"ZriZXExRUDvGv4G2F2iDfzmLqgnZK/dHVCVeRcUhCphS7MOcuDwHUQ+Zn5MLjG+f\n" \
//"w+J484ndK7tbsvhPbJ7bAjXdOaIColCL84Kv7/eeLtmqdbn9jTRoF/ZhfMA6AYNz\n" \
//"FYx2y/SfM1b0JVlp/udJ5jKS0D9jHqz0L5S3m/WPUEi9YHxMNNypi3Rz8ap++Sa+\n" \
//"rvwtCNKBAoGBAPaG1yY1x1E6LbULzT5cbFP/lU8znaMo9EX3O3d7tvm4OO86Ru8/\n" \
//"OdS/QCiQas6wpft+lItAed7AMKQRIcVxjml8WeWQiJ81C15utk0RUPBHLUbxnnJS\n" \
//"tWozWwnTeWDpnxpMBg4nSahZyWYD+ytmWgom6AL7SkQhkmmgnCQ9pVSRAoGBANAU\n" \
//"9Bj7LetZ1Fxn2vR29w7laDUtugQShkhcgqk/GCYJI3gjb481g7i5QMTqKiN6AQ56\n" \
//"ZbQffSMBB+fjcSArUzBvczcCTkph3yli2kA6+SCgWJAOkU95a5ETt/YbP/ZuILeg\n" \
//"I/pzqtDOZzA5ZOFx9YuBc9btjIvUcKoEMINjKUt5AoGBAILBMgwKKhVjDisgf1O8\n" \
//"IZjLzp2beti3OBiD8P6Gl54Ln+cCuezbVAkLBzR8pKnL971UfeT95aXHugTLMWZP\n" \
//"vIEme2fPKSeIMud7QSXPMWa/2bvvG2L3i1Ewu/CSQaatQr3n5K5NGDw6ox+ArQ9v\n" \
//"0gHgcN5j+hf41nc/wJFYQQCBAoGBAL/cUiYmk/SJ43FAoXb/qlWl2SwPeZD/s6lN\n" \
//"A30inBWWH4pKwjZ91XKh/cKTVz9W41qCKPyofC2maa+62zgaOp5SZR23lpCnJal3\n" \
//"aF4JAmS+9Gn/xKRPBIvEbr8R6SxD5w7pLcNkm3/kkOi6QvZMqWd0eWcXqZvUyf05\n" \
//"17GN4SmhAoGBAJrfaIFgw4otz3Ln5k8uRlOoMUQJuCdCEX0Cmv6dq6MOBIqA4xEP\n" \
//"zR3bEfGy3PPBpONi+LGkGuCFBvQsVpzWui9gY+y4vIKt+O+bXugjzg5JRDVSXx4b\n" \
//"PfoR9fYQVS0EzDGEZN9l2p0TnR9poMjlnhR5xliRo+qHFHaF4G30Dm5z\n"
//"-----END CERTIFICATE-----\n"

#define THINGNAME "esp_32"

#include <WiFiClientSecure.h>
#include <MQTTClient.h> //MQTT Library Source: https://github.com/256dpi/arduino-mqtt

#include <ArduinoJson.h>

float duration_us, distance_cm;
WiFiClientSecure wifi_client = WiFiClientSecure();
MQTTClient mqtt_client = MQTTClient(256); //256 indicates the maximum size for packets being published and received.

uint32_t t1;





void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  unsigned long startAttempt = millis();
  
  while (WiFi.status() != WL_CONNECTED && millis()- startAttempt < WIFI_TIMEOUT_MS ) {
    Serial.print('.');
    delay(100);
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Failed");  
  }else{
    Serial.println("Connected") ;   
    Serial.println(WiFi.localIP());
  }
  
}

void connectAWS()
{
  //Begin WiFi in station mode
//  WiFi.mode(WIFI_STA); 
//  WiFi.begin("Apt247", "kukukamagic");
  initWiFi();
  Serial.println("Connecting to Wi-Fi");
  unsigned long startAttempt = millis();
  
  //Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED && millis()- startAttempt < 20000){
    delay(500);
    Serial.print("Inside while");
    Serial.print(".");
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Failed");  
  }else{
    Serial.println("Connected") ;   
    Serial.println(WiFi.localIP());
  }
 
  Serial.println("Wifi Connected");

  // Configure wifi_client with the correct certificates and keys
  wifi_client.setCACert(AWS_CERT_CA);
  wifi_client.setCertificate(AWS_CERT_CRT);
  wifi_client.setPrivateKey(AWS_CERT_PRIVATE);

  //Connect to AWS IOT Broker. 8883 is the port used for MQTT
  mqtt_client.begin(AWS_IOT_ENDPOINT, 8883, wifi_client);

  //Set action to be taken on incoming messages
  mqtt_client.onMessage(incomingMessageHandler);

  Serial.print("Connecting to AWS IOT");

  //Wait for connection to AWS IoT
  while (!mqtt_client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if(!mqtt_client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  //Subscribe to a topic
  mqtt_client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  //Create a JSON document of size 200 bytes, and populate it
  //See https://arduinojson.org/
  StaticJsonDocument<200> doc;
  doc["elapsed_time"] = millis() - t1;
  doc["value"] = random(1000);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to mqtt_client

  //Publish to the topic
  mqtt_client.publish("ouTopic", jsonBuffer);
  Serial.println("Sent a message");
}

void incomingMessageHandler(String &topic, String &payload) {
  Serial.println("Message received!");
  Serial.println("Topic: " + topic);
  Serial.println("Payload: " + payload);
}

void setup() {
  // begin serial port
//  Serial.begin(9600);
//  initWiFi();
//  Serial.print("RRSI: ");
//  Serial.println(WiFi.RSSI());
Serial.begin(115200);
  t1 = millis();
  connectAWS();
  
  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
//  Serial.println("scan start");
//
//  // WiFi.scanNetworks will return the number of networks found
//  int n = WiFi.scanNetworks();
//  Serial.println("scan done");
//  if (n == 0) {
//      Serial.println("no networks found");
//  } else {
//    Serial.print(n);
//    Serial.println(" networks found");
//    for (int i = 0; i < n; ++i) {
//      // Print SSID and RSSI for each network found
//      Serial.print(i + 1);
//      Serial.print(": ");
//      Serial.print(WiFi.SSID(i));
//      Serial.print(" (");
//      Serial.print(WiFi.RSSI(i));
//      Serial.print(")");
//      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
//      delay(10);
//    }
//  }
//  Serial.println("");
//
//  // Wait a bit before scanning again
//  delay(5000);  
  // generate 10-microsecond pulse to TRIG pin
  publishMessage();
  mqtt_client.loop();
  delay(4000);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
