/*
* based on https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/html-buttons
* the aim is to controll 2 relays that close the cirquit to a shutter controller
* feel free to suggest improvement
*/




#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "WiFi Name";
const char* password = "Password";

const int pin_up = 14;
const int pin_down = 12;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output_up = "stop";
String output_down = "stop";

void setup() {
pinMode(pin_up, OUTPUT);
pinMode(pin_down, OUTPUT);

Serial.begin(115200);

  // Set outputs to LOW
  digitalWrite(pin_up, LOW);
  digitalWrite(pin_down, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /up") >= 0) {
              Serial.println("shutters moving up");
              output_up = "up";
              digitalWrite(pin_up, HIGH);
              delay(0.2*1000);
              output_up = "stop";
              digitalWrite(pin_up, LOW);
            } else if (header.indexOf("GET /down") >= 0) {
              Serial.println("shutters moving down");
              output_down = "down";
              digitalWrite(pin_down, HIGH);
              delay(0.2*1000);
               output_down = "stop";
              digitalWrite(pin_down, LOW);
            }

            // Hier wird nun die HTML Seite angezeigt:
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // Es folgen der CSS-Code um die Ein/Aus Buttons zu gestalten
            // Hier können Sie die Hintergrundfarge (background-color) und Schriftgröße (font-size) anpassen
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #333344; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #888899;}</style></head>");
            client.println("<body><h1>Open window shutters</h1>");


            // Display current state of the up button
            client.println("<p>moving " + output_up + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output_down=="up") {
              client.println("<p><a href=\"/up\"><button class=\"button\">UP</button></a></p>");
            }else if(output_down=="stop") {
              client.println("<p><a href=\"/up\"><button class=\"button\">UP</button></a></p>");
            }


            // Display current state of down button  
            client.println("<p>moving " + output_down + "</p>");
            if (output_down=="down") {
              client.println("<p><a href=\"/down\"><button class=\"button\">DOWN</button></a></p>");
            }else if (output_down=="stop"){
              client.println("<p><a href=\"/down\"><button class=\"button\">DOWN</button></a></p>");
            }

          

            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}