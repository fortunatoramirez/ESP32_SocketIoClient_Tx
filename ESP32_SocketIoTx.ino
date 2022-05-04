#include <WiFi.h>
#include <SocketIoClient.h>

#define INPUT_PIN 4

const char*       ssid     = "NOMBRE_DE_LA_RED"; 
const char*       password = "CONTRASENA";
const char*       server   = "IP.DEL.SER.VIDOR";
const uint16_t    port     = 5001; //Puerto del servidor

int       entrada;
String    mensaje;
uint64_t  now       = 0;
uint64_t  timestamp = 0;

SocketIoClient socketIO;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
  conectar_WiFiSTA();
  socketIO.begin(server, port);
}

void loop() {
  now = millis();
  if(now - timestamp > 300)
  {
    timestamp = now;
    if(entrada = digitalRead(INPUT_PIN))
    {
      mensaje = "\""+String(entrada)+"\"";
      socketIO.emit("desde_esp32",mensaje.c_str());
    }
  }
  socketIO.loop();
}

void conectar_WiFiSTA()
{
   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Conectado a STA:\t");
   Serial.println(ssid);
   Serial.print("My IP Address:\t");
   Serial.println(WiFi.localIP());
}
