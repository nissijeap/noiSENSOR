//Include necessary libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
//Libraries for Timestamp
#include <NTPClient.h> 
#include <WiFiUdp.h> 

// Define network credentials
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "SugarRush_0313"

// Define Firebase project credentials
#define API_KEY "AIzaSyAXIQ1r-JR7HxOruM_h888o1wD0iNLrOLI"
#define FIREBASE_PROJECT_ID "noise-level-bc62c"

// Define user email and password
#define USER_EMAIL "test@gmail.com"
#define USER_PASSWORD "test123"

// Define Firebase objects for data and authentication
FirebaseData fbdo;  // Object to handle Firebase data
FirebaseAuth auth;  // Object to handle Firebase authentication
FirebaseConfig config;  // Object to handle Firebase configuration

// Variable to save USER UID
String uid;

//Define NTPClient to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Variables for task handling
unsigned long dataMillis = 0;
bool taskcomplete = false;

// Variables for microphone sensor
int microphonePin = A0;
int sampleWindow = 1000;
unsigned int signalMax = 0;
unsigned int signalMin = 1023;

// Initialize variables to store data needed
float Sound = 0.0;
String Level = "";
String Color = "";
char timestampStr[30];

// Define LED pins
int blueLedPin = D5;
int greenLedPin = D6;
int yellowLedPin = D7;
int redLedPin = SS;


void setup(){
  Serial.begin(115200); //Initialize serial communication
  timeClient.begin(); //Start the NTP Client

// Initialize WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();


  // Configure Firebase with user and project credentials
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Initialize the library with the Firebase auth and config
  Firebase.begin(&config, &auth);

  // Getting the user UID
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }

  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);

  // Set LED pins as output
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop(){
  // If Firebase token expired, refresh it
  if (Firebase.isTokenExpired()){
    Firebase.refreshToken(&config);
    Serial.println("Refresh token");
  }
  // Every minute or on the first loop, read sound level, set LED based on sound level, and send data to Firebase
   if (Firebase.ready() && (millis() - dataMillis > 10000 || dataMillis == 0))
    {
        dataMillis = millis();

        // Read data from the microphone sensor
        signalMax = 0;
        signalMin = 1023;

        unsigned long startMillis = millis();
        while (millis() - startMillis < sampleWindow)
    {
        int sample = analogRead(microphonePin);
        if (sample < 1024)
        {
          if (sample > signalMax)
            signalMax = sample;
          else if (sample < signalMin)
            signalMin = sample;
        }
    }

    //Calibration: Conversion from volts to decibels
    if (signalMax > signalMin)
    {
      unsigned int peakToPeak = signalMax - signalMin;
      Sound = map(peakToPeak, 0, 1023, 30, 90);
      Serial.print("Decibels: ");
      Serial.print(Sound);
      Serial.println(" Sound");

      //Determining noise level based on decibels and assigning led actuators for each level
      if (Sound >= 0 && Sound <= 35){
        Level = "Quiet";
        Color = "Blue";
        digitalWrite(blueLedPin, HIGH);    // Turn on the blue LED
        digitalWrite(greenLedPin, LOW);    // Turn off the green LED
        digitalWrite(yellowLedPin, LOW);   // Turn off the yellow LED
        digitalWrite(redLedPin, LOW);      // Turn off the red LED
      }else if (Sound > 35 && Sound <= 60){
        Level = "Normal";
        Color = "Green";
        digitalWrite(blueLedPin, LOW);     // Turn off the blue LED
        digitalWrite(greenLedPin, HIGH);   // Turn on the green LED
        digitalWrite(yellowLedPin, LOW);   // Turn off the yellow LED
        digitalWrite(redLedPin, LOW);      // Turn off the red LED
      }else if (Sound > 60 && Sound <= 80){
        Level = "Moderate";
        Color = "Yellow";
        digitalWrite(blueLedPin, LOW);     // Turn off the blue LED
        digitalWrite(greenLedPin, LOW);    // Turn off the green LED
        digitalWrite(yellowLedPin, HIGH);  // Turn on the yellow LED
        digitalWrite(redLedPin, LOW);      // Turn off the red LED
      }else{
        Level = "High";
        Color = "Red";
        digitalWrite(blueLedPin, LOW);     // Turn off the blue LED
        digitalWrite(greenLedPin, LOW);    // Turn off the green LED
        digitalWrite(yellowLedPin, LOW);   // Turn off the yellow LED
        digitalWrite(redLedPin, HIGH);     // Turn on the red LED
      }
      Serial.println("Level: " + Level);
      Serial.println("Led Color: " + Color);

      //Update the NTPClient object to get the current time and date
      timeClient.update();
      time_t now = timeClient.getEpochTime();

      if (now == 0) { //If there is an error in getting the current time
              Serial.println("Error getting current time");
            } else {
              // Set timestamp field with current time
              strftime(timestampStr, sizeof(timestampStr), "%FT%TZ", gmtime(&now));
              // send ti to firestore
            }

        // Declare an instance of FirebaseJSON to send data to Firestore
        FirebaseJson content;
        FirebaseJson timestampValue;

        // Defining the document path for data to be stored in Firestore
        String newDocumentId = String(millis());
        String documentPath = "SoundData/" + newDocumentId;

        //If the task has not yet been completed
        if (!taskcomplete)
        {
            taskcomplete = true; //Set task to complete

            content.clear(); //Clear any previous content in the JSON object

            // Set fields for Timestamp, sound, level, and LED color in the Firebase document
            content.set("fields/Timestamp/timestampValue", timestampStr);
            content.set("fields/Sound/doubleValue", String(Sound).c_str());
            content.set("fields/Level/stringValue", String(Level));
            content.set("fields/LedColor/stringValue", String(Color));
            
            Serial.print("Create a document... ");

            //Create a new document in Firebase Firestore
            if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
                Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            else
                Serial.println(fbdo.errorReason());

          // Reset the taskcomplete flag for the next cycle
          taskcomplete = false;
        }

        
    
    }
    }

}