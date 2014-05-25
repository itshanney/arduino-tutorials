
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x14, 0x72};
IPAddress ip(10, 0, 1, 42);

EthernetServer server(8080);

void setup() {
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Arduino IP: "); Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if(client) {
    Serial.println(" -- New Client Connection -- ");
   
    boolean currentLineIsBlank = true;
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);
       
        if(c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.println("{\"message\": \"Hello, World!\"}");
          break;
        } 
        
        if(c == '\n') {
          currentLineIsBlank = true; 
        } else if (c != '\r') {
          currentLineIsBlank = false; 
        }
      }
    }
   
    delay(1);
    client.stop();
    Serial.println(" -- Client Disconnected -- "); 
  }
}
