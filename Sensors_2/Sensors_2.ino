#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE);
#define FIREBASE_HOST "fir-65f4c-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "ungFuaFAmOX6pt2cKqEClP7rWYDv2JPODov3vztu"

#define WIFI_SSID "Wifi"

#define WIFI_PASSWORD "WagonR2016"
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Abdallah Agha"
#define WIFI_PASSWORD "abdallah123"

/* 2. Define the API Key */
#define API_KEY "AIzaS***************"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "sm**********"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "a@a.com"
#define USER_PASSWORD "123456"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

String uid;

String path;

String firebaseStatus = "on";

void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    
    Firebase.reconnectWiFi(true);
     //----------
    //LED LIGHT
    //-----------
    pinMode(D1, OUTPUT); 

    //----------------------------------------------
   // Getting the user UID might take a few seconds
   //-----------------------------------------------
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
    //-----------------
   // Print user UID
   //------------------
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
           
}
          

void loop()
{      
          //-------------------
            //Create Document
            //-------------------
            FirebaseJson content;

            content.set("fields/pump/stringValue", firebaseStatus);
           
            //esp is the collection id, user uid is the document id in collection info.
            path = "esp/"+uid+"";
            
            Serial.print("Create document... ");

            if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, path.c_str(), content.raw()))
                Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            else
                Serial.println(fbdo.errorReason());

         //-------------------
         //Get Document
        //--------------------
        path = "esp/"+uid+"";
//        String mask = "pump";
        Serial.print("Get a document... ");
        if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), mask.c_str())){
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            
            if(mask == "on"){
              digitalWrite(D1, HIGH);
              }
            
            if(mask == "off"){
              digitalWrite(D1, LOW);
              }
              
          }
           else{
            Serial.println(fbdo.errorReason());
        } 
            
    }
void setup() {
Serial.begin(9600);

// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
float h = dht.readHumidity();

float t = dht.readTemperature();
Firebase.setFloat("Temperature", t);
Firebase.setFloat("Humidity", h);

Serial.println(t);
Serial.println(h);
delay(50);

}
