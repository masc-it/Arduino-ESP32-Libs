# HttpRequest

An ArduinoHTTPClient header-only wrapper that wants to make HTTP requests an easier job.

## Features
- Make complete GET or POST requests with a single method call (Builder pattern and chaining)
- Add parameters/payload to your requests
- Set timeouts
- Set endpoint to contact with
- Default Content-Type: "application/x-www-form-urlencoded"


## Dependencies
- Arduino.h
- ArduinoHTTPClient.h

## Usage
- Just Copy & Paste HttpRequest.h in your project and you're good to go!

## Examples

- Simple POST request

```
    WiFiEspClient* client = new WiFiEspClient(); // or any other class that extends Client
    HttpRequest server1(client, "your_server.com");
    
    String response = server1->buildPostRequest()
        .setDestination("your/post/endpoint/path")  // mandatory, NO starting slash!
        .setTimeout(5000)                      // optional
        .addParameter("param1", "value1")      // if any payload
        .addParameter("param2", "value2")
        .addParameter("param3", "value3")
        .send();

    Serial.println(response);
``` 
- Simple GET request
```
WiFiEspClient* client = new WiFiEspClient(); // or any other class that extends Client
HttpRequest server1(client, "your_server.com");
    
String response = server1->buildGetRequest()
   .setDestination("your/get/endpoint/path")  // mandatory
   .setTimeout(5000)                      // optional
   .addParameter("param1", "value1")      // if any payload
   .addParameter("param2", "value2")
   .addParameter("param3", "value3")
   .send();
        
Serial.println(response);
    
String response_2 = server1->buildGetRequest()
   .setDestination("your/get/endpoint/path")  // mandatory
   .send();
        
Serial.println(response_2);
```
