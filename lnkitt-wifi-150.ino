// 08/08/2018 - 14/10/2018
// K.I.T.T. Lights Effects by Luca Nicolini V 1.50 WiFi
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
"<h1>K.I.T.T. Sequential lights<br> by Luca Nicolini<br> V1.50 WiFi</h1>"

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

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT); // onboard blue led
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
 }

void effetto1() {
  digitalWrite(D0, HIGH);
  delay(delaytime);
  digitalWrite(D0, LOW);
  delay(offtime);
  digitalWrite(D1, HIGH);
  delay(delaytime);
  digitalWrite(D1, LOW);
  delay(offtime); 
  digitalWrite(D2, HIGH);
  delay(delaytime);
  digitalWrite(D2, LOW);
  delay(offtime);  
  digitalWrite(D3, HIGH);
  delay(delaytime);
  digitalWrite(D3, LOW);
  delay(offtime);
  digitalWrite(D5, HIGH);
  delay(delaytime);
  digitalWrite(D5, LOW);
  delay(offtime);
  digitalWrite(D6, HIGH);
  delay(delaytime);
  digitalWrite(D6, LOW);
  delay(offtime);
  digitalWrite(D7, HIGH);
  delay(delaytime);
  digitalWrite(D7, LOW);
  delay(offtime);
  digitalWrite(D8, HIGH);
  delay(delaytime);
  digitalWrite(D8, LOW);
  delay(offtime);
  // led indietro
  digitalWrite(D7, HIGH);
  delay(delaytime);
  digitalWrite(D7, LOW);
  delay(offtime);
  digitalWrite(D6, HIGH);
  delay(delaytime);
  digitalWrite(D6, LOW);
  delay(offtime);
  digitalWrite(D5, HIGH);
  delay(delaytime);
  digitalWrite(D5, LOW);
  delay(offtime);
  digitalWrite(D3, HIGH);
  delay(delaytime);
  digitalWrite(D3, LOW);
  delay(offtime);
  digitalWrite(D2, HIGH);
  delay(delaytime);
  digitalWrite(D2, LOW);
  delay(offtime);
  digitalWrite(D1, HIGH);
  delay(delaytime);
  digitalWrite(D1, LOW);
  delay(offtime);
  }
  
void effetto2() {
  digitalWrite(D0, HIGH);
  digitalWrite(D8, HIGH);
  delay(delaytime);
  digitalWrite(D0, LOW);
  digitalWrite(D8, LOW);   
  digitalWrite(D1, HIGH);
  digitalWrite(D7, HIGH);
  delay(delaytime);
  digitalWrite(D1, LOW);
  digitalWrite(D7, LOW);  
  digitalWrite(D2, HIGH);
  digitalWrite(D6, HIGH);
  delay(delaytime);
  digitalWrite(D2, LOW);
  digitalWrite(D6, LOW);  
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  delay(delaytime);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);  

// back

  digitalWrite(D2, HIGH);
  digitalWrite(D6, HIGH);
  delay(delaytime);
  digitalWrite(D2, LOW);
  digitalWrite(D6, LOW);   
  digitalWrite(D1, HIGH);
  digitalWrite(D7, HIGH);
  delay(delaytime);
  digitalWrite(D1, LOW);
  digitalWrite(D7, LOW);  
  //digitalWrite(D0, HIGH);
  //digitalWrite(D8, HIGH);
  //delay(delaytime);
  //digitalWrite(D0, LOW);
  //digitalWrite(D8, LOW);  
  //delay(delaytime);  
  
}
void effetto3() {
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  delay(45);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  delay(45);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  delay(45);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  delay(45);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  delay(45);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  delay(45);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  delay(45);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
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


