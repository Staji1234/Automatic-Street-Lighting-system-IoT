#include<ESP8266WiFi.h>
WiFiClient iotclient; //globally declaring client
#include "ThingSpeak.h"//including things speak

#define led 13
#define ldr A0
int level;
int threshold=200;

void setup() 
{ 
  Serial.begin(9600);
  
  pinMode(led,OUTPUT);
  pinMode(ldr,INPUT);
  
  ThingSpeak.begin(iotclient);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Hit Girl!","Amalu@1998");
  while (WiFi.status()!=WL_CONNECTED)
  {
    delay(100);
  }
  Serial.print(WiFi.localIP());
}

void loop() 
{

   int a; 
   int level;
   level=analogRead(ldr);
   Serial.println(level);
   if(level<threshold)
   { 
      digitalWrite(led,HIGH);
   }
   else
   {  
      digitalWrite(led,LOW);
   }

   ThingSpeak.writeField(370050,2,level,"39RTG1MQTGGST9BJ");// writes 'level' to thingspeak
   Serial.println(level);
   a= digitalRead(led);
   ThingSpeak.writeField( 371221,1,a,"D3M1K8A23YY6MF6T");
   Serial.println(a);
   delay(20000);//for free users there will be a a delay of 20 sec ie, 20*1000 millisec..ie why we give delay of 20000 sec 
}
