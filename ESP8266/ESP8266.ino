#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// This example was tested on ESP8266
// To be specific: NodeMCU 1.0 (ESP-12E Module)

const char* ssid     = " ";  // declare here your network's name
const char* password = " ";  // declare here your network's password

// This is only an example but feel free to use this configuration
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);

// VARIABLES (DIGITAL PINS FOR CONNECTION)
uint8_t LED_bagno    = D4;    // bathroom
uint8_t LED_cucina   = D5;    // kitchen
uint8_t LED_salotto  = D6;    // living room
uint8_t LED_stanza   = D7;    // bedroom
uint8_t LED_carmadio = D8;    // walk-in closet

// FLAGS FOR THE VARIABLES
bool LED_cucina_status   = LOW;
bool LED_bagno_status    = LOW;
bool LED_salotto_status  = LOW;
bool LED_stanza_status   = LOW;
bool LED_carmadio_status = LOW;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_bagno,    OUTPUT);
  pinMode(LED_cucina,   OUTPUT);
  pinMode(LED_salotto,  OUTPUT);
  pinMode(LED_stanza,   OUTPUT);
  pinMode(LED_carmadio, OUTPUT);
    
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(200);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on",  handle_led1on);  // bathroom
  server.on("/led1off", handle_led1off);
  server.on("/led2on",  handle_led2on);  // kitchen
  server.on("/led2off", handle_led2off);
  server.on("/led3on",  handle_led3on);  // living room
  server.on("/led3off", handle_led3off);
  server.on("/led4on",  handle_led4on);  // bedroom
  server.on("/led4off", handle_led4off);
  server.on("/led5on",  handle_led5on);  // walk-in closet
  server.on("/led5off", handle_led5off);
  
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("The HTTP server has started!");
}

void loop() {
  server.handleClient();

  if(LED_bagno_status) {
    digitalWrite(LED_bagno, HIGH);
  } else {
    digitalWrite(LED_bagno, LOW);
  }
  
  if(LED_cucina_status) {
    digitalWrite(LED_cucina, HIGH);
  } else {
    digitalWrite(LED_cucina, LOW);
  }

  if(LED_salotto_status) {
    digitalWrite(LED_salotto, HIGH);
  } else {
    digitalWrite(LED_salotto, LOW);
  }

  if(LED_stanza_status) {
    digitalWrite(LED_stanza, HIGH);
  } else {
    digitalWrite(LED_stanza, LOW);
  }

  if(LED_carmadio_status) {
    digitalWrite(LED_carmadio, HIGH);
  } else {
    digitalWrite(LED_carmadio, LOW);
  }
}

void handle_OnConnect() {
  LED_bagno_status    = LOW;
  LED_cucina_status   = LOW;
  LED_salotto_status  = LOW;
  LED_stanza_status   = LOW;
  LED_carmadio_status = LOW;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, LED_salotto_status, LED_stanza_status, LED_carmadio_status));
}

void handle_led1on() {
  LED_bagno_status = HIGH;
  server.send(200, "text/html", SendHTML(true, LED_cucina_status, LED_salotto_status, LED_stanza_status, LED_carmadio_status));
}

void handle_led1off() {
  LED_bagno_status = LOW;
  server.send(200, "text/html", SendHTML(false, LED_cucina_status, LED_salotto_status, LED_stanza_status, LED_carmadio_status));
}

void handle_led2on() {
  LED_cucina_status = HIGH;
  server.send(200, "text/html", SendHTML(LED_bagno_status, true, LED_salotto_status, LED_stanza_status, LED_carmadio_status));
}

void handle_led2off() {
  LED_cucina_status = LOW;
  server.send(200, "text/html", SendHTML(LED_bagno_status, false, LED_salotto_status, LED_stanza_status, LED_carmadio_status));
}

void handle_led3on() {
  LED_salotto_status = HIGH;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, true, LED_stanza_status, LED_carmadio_status));
}

void handle_led3off() {
  LED_salotto_status = LOW;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, false, LED_stanza_status, LED_carmadio_status));
}

void handle_led4on() {
  LED_stanza_status = HIGH;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, LED_salotto_status, true, LED_carmadio_status));
}

void handle_led4off() {
  LED_stanza_status = LOW;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, LED_salotto_status, false, LED_carmadio_status));
}

void handle_led5on() {
  LED_carmadio_status = HIGH;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, LED_salotto_status, LED_stanza_status, true));
}

void handle_led5off() {
  LED_carmadio_status = LOW;
  server.send(200, "text/html", SendHTML(LED_bagno_status, LED_cucina_status, LED_salotto_status, LED_stanza_status, false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "!! Page Not found !!");
}

/** PARAMETERS ORDER
  1. Status flag for the bathroom's light
  2. Status flag for the kitchen's light
  3. Status flag for the living room's light
  4. Status flag for the bedroom's light
  5. Status flag for the walk-in closet's light
*/
String SendHTML(uint8_t led1stat, uint8_t led2stat, uint8_t led3stat, uint8_t led4stat, uint8_t led5stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title> Control Panel </title>\n";
  ptr += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px; background-color: #dce3ca;} h1{color: #444444;margin: 50px auto 30px;} h3{color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block; width: 80px; background-color: #1abc9c; border: none; color: white; padding: 13px 30px; text-decoration: none; font-size: 25px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px; color: #888; margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  // ptr +="<h1> DOMOTIC HOUSE HOME PAGE </h1>\n";
  ptr += "<h1> ESP8266 LIGHT CONTROL PANEL </h1>\n";
  
  // Bathroom
  if (led1stat) {
    ptr += "<p> Bathroom status: ON </p> <a class=\"button button-off\" href=\"/led1off\"> OFF </a>\n";
  } else {
    ptr += "<p> Bathroom status: OFF </p> <a class=\"button button-on\" href=\"/led1on\"> ON </a>\n";
  }

  // kitchen
  if (led2stat) {
    ptr += "<p> Kitchen status: ON </p> <a class=\"button button-off\" href=\"/led2off\"> OFF </a>\n";
  } else {
    ptr += "<p> Kitchen status: OFF </p> <a class=\"button button-on\" href=\"/led2on\"> ON </a>\n";
  }

  // Living room
  if (led3stat) {
    ptr += "<p> Living room status: ON </p> <a class=\"button button-off\" href=\"/led3off\"> OFF </a>\n";
  } else {
    ptr += "<p> Living room status: OFF </p> <a class=\"button button-on\" href=\"/led3on\"> ON </a>\n";
  }

  // Bedroom
  if (led4stat) {
    ptr += "<p> Bedroom status: ON </p> <a class=\"button button-off\" href=\"/led4off\"> OFF </a>\n";
  } else {
    ptr += "<p> Bedroom status: OFF </p> <a class=\"button button-on\" href=\"/led4on\"> ON </a>\n";
  }

  // Walk-in closet
  if (led5stat) {
    ptr += "<p> Walk-in closet status: ON </p> <a class=\"button button-off\" href=\"/led5off\"> OFF </a>\n";
  } else {
    ptr += "<p> Walk-in closet status: OFF </p> <a class=\"button button-on\" href=\"/led5on\"> ON </a>\n";
  }
  
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}