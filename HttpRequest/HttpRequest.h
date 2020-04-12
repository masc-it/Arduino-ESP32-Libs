#ifndef REQUEST_H
#define REQUEST_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>

#define METHOD_POST "POST"
#define METHOD_GET "GET"

class HttpRequest
{

private:
    HttpClient *httpClient;
    
    
public:
    HttpRequest(Client* client, const char* server)
    {

        this->httpClient = new HttpClient(*client, server, 80);
        
    }

    
    class RequestBuilder
    {
    private:
        String url;
        String params = "";
        HttpRequest *req;
        String method = METHOD_GET;
        int timeout = 5000;

    
    public:
        RequestBuilder(HttpRequest *req, String method)
        {
            this->req = req;
            this->method = method;
        }

        RequestBuilder &setDestination(String url)
        {
            this->url = url;
            return *this;
        }
        RequestBuilder &addParameter(String key, String value)
        {

            if (!(this->params.equals("")))
            {
                params += "&";
            }
            params += key;
            params += "=";
            value.replace(" ", "%20");
            params += value;

            return *this;
        }

        RequestBuilder& setTimeout(int timeout = 5000){
            this->timeout = timeout;
            return *this;
        }

        String send()
        {

            if ( params.equals("")){

                if ( method.equals(METHOD_GET)){
                    req->httpClient->get("/" + this->url);
                } else {
                    req->httpClient->post("/" + this->url);
                }
                
            } else {
                if ( method.equals(METHOD_GET)){
                    req->httpClient->get("/" + this->url + "?" + params);
                } else {
                    req->httpClient->post("/" + this->url, "application/x-www-form-urlencoded", params);
                }
            }
            
            int timeout = millis() + this->timeout;
            while (req->httpClient->available() == 0)
            {
                if (timeout - millis() < 0)
                    return "";
            }
            int responseStatus = req->httpClient->responseStatusCode();
            
            String res = "";

            if ( responseStatus == 200){
                res = req->httpClient->responseBody();
            }
            req->httpClient->flush();
            req->httpClient->stop();

            return res;
        }
    };

    HttpRequest::RequestBuilder buildPostRequest()
    {

        return RequestBuilder(this, METHOD_POST);
    }

    HttpRequest::RequestBuilder buildGetRequest()
    {

        return RequestBuilder(this, METHOD_GET);
    }
};

#endif