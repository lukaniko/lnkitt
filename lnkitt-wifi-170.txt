// 08/08/2018 - 25/05/2019
// K.I.T.T. Lights Effects by Luca Nicolini V 1.70 WiFi
// For nodeMCU, programmed and compiled through Arduino IDE
//

// Include Librerie
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Definizione parametri WiFi AP

ESP8266WebServer server(80);
IPAddress    apIP(192, 168, 4, 1);
const char *ssid = "lnkitt";
const char *password = "lnkitt";
MDNSResponder mdns;

// Inizializza Variabili
// int sensorPin = A0;  // set pin input analogico
int delaytime = 90;  // variabile dati sensore
int offtime = 0;  // variabile dati sensore
String MODE = "1"; // variabile tipo effetto

// WEB HTML

String INDEX_HTML = 
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>K.I.T.T. Sequential lights by luca nicolini</title>"
"<style>"
"body { background-color: #0099ff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }"
"h1   {color: #e6f5ff; font-size: 24px}"
"P    {color: #002e4d; font-size: 18px} "
"</style>"
"</head>"
"<body>"
"<center>"
"<h1>K.I.T.T. Sequential lights<br> by Luca Nicolini<br> V1.70 WiFi</h1>"

"<FORM action=\"/\" method=\"GET\">"  
   "<legend>Select Effect</legend>"
   "<BR>"
   "<select name=\"MODE\" >"
   "<option value=\"1\" selected=\"selected\">KITT  </option>"
   "<option value=\"2\">In And Out  </option>"
   "<option value=\"3\">Emergency  </option>"
  "</select>"
 "<INPUT type=\"submit\" value=\"Select\">"
"</form>"
"<BR>"
"Select speed"
"<FORM action=\"/\" method=\"GET\">"
"<INPUT type=\"hidden\" name=\"SPEED\" value=\"1\">"
"<BR>"
"<INPUT type=\"submit\" value=\"Slower\">"
"</FORM>"
"<FORM action=\"/\" method=\"GET\">"
"<INPUT type=\"hidden\" name=\"SPEED\" value=\"0\">"
"<BR>"
"<INPUT type=\"submit\" value=\"Faster\">"
"</FORM>"
"<BR>"
"Current Speed = ";

String INDEX_HTML2 =
"</center>"
"<!DOCTYPE HTML>"
"</body>"
"</html>";

void handleRoot()
{
  if (server.hasArg("SPEED")) {
    handleSubmit();
  }
  else {
     if (server.hasArg("MODE")) {
       MODE = server.arg("MODE");
       server.send(200, "text/html", INDEX_HTML+String(delaytime)+INDEX_HTML2);
      }
      else
      {
       server.send(200, "text/html",INDEX_HTML+String(delaytime)+INDEX_HTML2);  
      } 
     }
}

void returnFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void handleSubmit()
{
  String SPEEDvalue;

  if (!server.hasArg("SPEED")) return returnFail("BAD ARGS");
  SPEEDvalue = server.arg("SPEED");
  if (SPEEDvalue == "0") {
    writeSPEED(0);
    server.send(200, "text/html",INDEX_HTML+String(delaytime)+INDEX_HTML2);
  }
  else if (SPEEDvalue == "1") {
    writeSPEED(1);
    server.send(200, "text/html",INDEX_HTML+String(delaytime)+INDEX_HTML2);
  }
  else {
    returnFail("Bad SPEED value");
  }
}
void returnOK()
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK\r\n");
}
void handleSPEEDon()
{
  writeSPEED("up");
  returnOK();
}
void handleSPEEDoff()
{
  writeSPEED("down");
  returnOK();
}
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void writeSPEED(bool SPEEDon)
{
  int caso;
  
  if (SPEEDon)
    { 
      caso=delaytime;
      caso += 10;
      delaytime=caso; 
    } // low
  else
    { 
      caso=delaytime;
      caso -= 10;
      delaytime=caso; 
    } // hi
}

void setup() 
{

// WiFi setup
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);  
  WiFi.hostname("lnkitt");
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());
  Serial.println("Server listening");
  writeSPEED(true);

// server web
  server.on("/", handleRoot);
  server.on("/speedon", handleSPEEDon);
  server.on("/speedoff", handleSPEEDoff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());

// Dichiarazione dei pin come Output
// Utilizzabili : 1.3.4.5.12.13.14.16 (3.1 sono RX e TX ridichiarati dopo il boot)
// 0.2.15 reserved

  pinMode(16, OUTPUT); 
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);  
  pinMode(15, OUTPUT); 
 }

void effetto1() {
  digitalWrite(16, HIGH);
  delay(delaytime);
  digitalWrite(16, LOW);
  delay(offtime);
  digitalWrite(5, HIGH);
  delay(delaytime);
  digitalWrite(5, LOW);
  delay(offtime); 
  digitalWrite(4, HIGH);
  delay(delaytime);
  digitalWrite(4, LOW);
  delay(offtime);  
  digitalWrite(2, HIGH);
  delay(delaytime);
  digitalWrite(2, LOW);
  delay(offtime);
  digitalWrite(14, HIGH);
  delay(delaytime);
  digitalWrite(14, LOW);
  delay(offtime);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(12, LOW);
  delay(offtime);
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(13, LOW);
  delay(offtime);
  digitalWrite(15, HIGH);
  delay(delaytime);
  digitalWrite(15, LOW);
  delay(offtime);
  // led indietro
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(13, LOW);
  delay(offtime);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(12, LOW);
  delay(offtime);
  digitalWrite(14, HIGH);
  delay(delaytime);
  digitalWrite(14, LOW);
  delay(offtime);
  digitalWrite(2, HIGH);
  delay(delaytime);
  digitalWrite(2, LOW);
  delay(offtime);
  digitalWrite(4, HIGH);
  delay(delaytime);
  digitalWrite(4, LOW);
  delay(offtime);
  digitalWrite(5, HIGH);
  delay(delaytime);
  digitalWrite(5, LOW);
  delay(offtime);
  }
  
void effetto2() {
  digitalWrite(16, HIGH);
  digitalWrite(15, HIGH);
  delay(delaytime);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);   
  digitalWrite(5, HIGH);
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);  
  digitalWrite(4, HIGH);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(4, LOW);
  digitalWrite(12, LOW);  
  digitalWrite(2, HIGH);
  digitalWrite(14, HIGH);
  delay(delaytime);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);  

// back

  digitalWrite(4, HIGH);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(4, LOW);
  digitalWrite(12, LOW);   
  digitalWrite(5, HIGH);
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);  
  //digitalWrite(16, HIGH);
  //digitalWrite(1, HIGH);
  //delay(delaytime);
  //digitalWrite(16, LOW);
  //digitalWrite(1, LOW);  
  //delay(delaytime);  
  
}
void effetto3() {
  digitalWrite(16, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);
  delay(45);
  digitalWrite(16, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  delay(45);
  digitalWrite(16, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);
  delay(45);
  digitalWrite(16, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  delay(45);
  digitalWrite(16, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);
  delay(45);
  digitalWrite(16, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  delay(delaytime);
}

void loop() {

  server.handleClient();

// Inizio sequenza led  
// delaytime = analogRead(sensorPin);  // Lettura valore potenziometro analogico,commentare se non utilizzato. max 1volt ?
// led avanti

 if (MODE == "1"){
  effetto1();
 }
 if (MODE == "2"){
  effetto2();
 }
if (MODE == "3"){
  effetto3();
 }  
}
