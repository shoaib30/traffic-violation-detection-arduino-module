#include <SoftwareSerial.h>
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_PIN 8
#define SIGNAL_PIN 4
SoftwareSerial traffic(5, 6);// setting RX and TX
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int input;
int output;
int dist;
int range = 10;
int signalState;
void setup() {
  // put your setup code here, to run once:
  //traffic.begin(9600); // starting serial communication over bluetooth
  Serial.begin(9600);
  //Serial.println("Initializing Board");
//  while(range<0){
//    Serial.println("Enter Range");
//    range = Serial.read();
//    delay(1000);
//  }
  
  //Serial.println("Range: " + range);
  dist = 0;
  pinMode(LED_PIN, OUTPUT);
  pinMode(SIGNAL_PIN, INPUT);
}

void loop() {
  //if (traffic.available())  {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //    Serial.print("Ping: ");
  //    Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  //    Serial.println("cm");
  dist = sonar.ping_cm();
  signalState = digitalRead(SIGNAL_PIN);
//  Serial.print("Signal: ");
//  Serial.println(signalState);
  if(signalState){
    if (dist < range) {
      delay(5);
      dist = sonar.ping_cm();
      if (dist < range) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("1");
        delay(1000);
      }
    }
    else  {
      digitalWrite(LED_PIN, LOW);
    }
  }
  else  {
    digitalWrite(LED_PIN, LOW);
  }
  //}
}

