#include "HttpRequest.h"

// HTTP server URL
char serverAddress[] = "your_server.com";

HttpRequest* server1;


void setup()
{
   // your setup stuff
   // ...
   
  // your client, in this case I'm going to use a 8266 client
  WiFiEspClient* client = new WiFiEspClient();
  server1 = new HttpRequest(client, serverAddress);
  
}


int status = 0;
static long currentMillisLoop;

unsigned int loopTimeout = 1000;
void loop()
{
   
  if (millis() - currentMillisLoop >= loopTimeout)
  {
	
	// Handy builder to send the post request
    String response = server1->buildPostRequest()
        .setDestination("your/endpoint/path")
        .addParameter("param1", "value1")
        .addParameter("param2", "value2")
        .addParameter("param3", "value3")
        .send();

    Serial.println(response);

    currentMillisLoop = millis();
  } 

}