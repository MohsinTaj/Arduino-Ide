
/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2022 mobizt
 *
 */

// This example shows how to create a document in a document collection. This operation required Email/password, custom or OAUth2.0 authentication.

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#endif
#include <DHT.h>   
//#include<TimeLib.h>      
#include <Firebase_ESP_Client.h>
//#include<time.h>
#include<stdio.h>
#define DHTPIN D7                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);
//#include <NTPClient.h>
//#include <WiFiUdp.h>   
// Provide the token generation process info.
#include <addons/TokenHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Wifi"
#define WIFI_PASSWORD "WagonR2016"
const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
/* 2. Define the API Key */
#define API_KEY "AIzaSyAGRJxnjCuwMJQ0228p7t7obxq42kDPe9I"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "fir-65f4c"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "mohsintaj1111@gmail.com"
#define USER_PASSWORD "esp8266"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;

// The Firestore payload upload callback function
void fcsUploadCallback(CFS_UploadStatusInfo info)
{
    if (info.status == fb_esp_cfs_upload_status_init)
    {
        Serial.printf("\nUploading data (%d)...\n", info.size);
    }
    else if (info.status == fb_esp_cfs_upload_status_upload)
    {
        Serial.printf("Uploaded %d%s\n", (int)info.progress, "%");
    }
    else if (info.status == fb_esp_cfs_upload_status_complete)
    {
        Serial.println("Upload completed ");
    }
    else if (info.status == fb_esp_cfs_upload_status_process_response)
    {
        Serial.print("Processing the response... ");
    }
    else if (info.status == fb_esp_cfs_upload_status_error)
    {
        Serial.printf("Upload failed, %s\n", info.errorMsg.c_str());
    }
}

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
      timeClient.begin();
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
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
 dht.begin();                   
    // For sending payload callback
    // config.cfs.upload_callback = fcsUploadCallback;
}


  
//  Serial.println(ctime(&t));

void loop()

  {float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht. readTemperature();        // Read temperature as Celsius (the default)
Serial.print("Humidity: ");  Serial.print(h);
String fireHumid = String(h) + String("%");        
Serial.print("%  Temperature: ");  Serial.print(t);
String fireTemp = String(t) + String("Â°C"); 
Serial.println( "\n");
delay(2000);
timeClient.update();

Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());
long long int  a=timeClient.getHours();
String  b=daysOfTheWeek[timeClient.getDay()];
long long int c=timeClient.getMinutes();

  delay(1000);

    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
    {
        dataMillis = millis();

        // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
        FirebaseJson content;

        // We will create the nested document in the parent path "a0/b0/c0
        // a0 is the collection id, b0 is the document id in collection a0 and c0 is the collection id in the document b0.
        // and d? is the document id in the document collection id c0 which we will create.
        String documentPath = "dht/data/c/d" + String(count);

        // If the document path contains space e.g. "a b c/d e f"
        // It should encode the space as %20 then the path will be "a%20b%20c/d%20e%20f"

        // double
        content.set("fields/mytemp/doubleValue", t);
        content.set("fields/timestampday/stringValue",b);
        content.set("fields/timestamphour/doubleValue", a);
        content.set("fields/timestampmin/doubleValue", c);
        
        
         // boolean
       // content.set("fields/myBool/booleanValue", true);

        // integer
        content.set("fields/myhumidity/doubleValue", h);
        

        // null
        //content.set("fields/myNull/nullValue"); // no value set

        String doc_path = "projects/";
        doc_path += FIREBASE_PROJECT_ID;
        doc_path += "/databases/(default)/documents/coll_id/doc_id"; // coll_id and doc_id are your collection id and document id

        // reference
        //content.set("fields/myRef/referenceValue", doc_path.c_str());

        // timestamp
//       content.set("fields/myTimestamp day/timestampValue",(daysOfTheWeek[timeClient.getDay()])); // RFC3339 UTC "Zulu" format
   //  content.set("fields/hour/timestampValue",a);
//       content.set("fields/minutes/timestampValue",timeClient.getMinutes());
//         content.set("fields/seconds/timestampValue",timeClient.getSeconds());

    
        // bytes
        //content.set("fields/myBytes/bytesValue", "aGVsbG8="); // base64 encoded

        // array
        //content.set("fields/myArray/arrayValue/values/[0]/stringValue", "test");
        //content.set("fields/myArray/arrayValue/values/[1]/integerValue", "20");
        //content.set("fields/myArray/arrayValue/values/[2]/booleanValue", true);

        // map
        //content.set("fields/myMap/mapValue/fields/name/stringValue", "wrench");
        //content.set("fields/myMap/mapValue/fields/mass/stringValue", "1.3kg");
        //content.set("fields/myMap/mapValue/fields/count/integerValue", "3");

        // lat long
        //content.set("fields/myLatLng/geoPointValue/latitude", 1.486284);
        //content.set("fields/myLatLng/geoPointValue/longitude", 23.678198);

        count++;

        Serial.print("Create a document... ");

        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        else
            Serial.println(fbdo.errorReason());
    }
//    Firebase.createDocument("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
//  Firebase.createDocumen("/DHT11/Temperature", fireTemp);                                //setup path and send readings
}
