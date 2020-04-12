/*
	MIT License

	Copyright (c) 2020 Mauro Sciancalepore

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/


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