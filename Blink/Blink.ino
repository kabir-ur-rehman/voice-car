#define BLYNK_TEMPLATE_ID "TMPL6NcrXnVkP"
#define BLYNK_TEMPLATE_NAME "VoiceCar"
#define BLYNK_AUTH_TOKEN "-1jX90yi-D-vBdwzcMJonl88THQf92R8"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// // WiFi credentials
char ssid[] = "Redmi 12";       // Your WiFi SSID
char pass[] = "        ";       // Your WiFi Password

// char ssid[] = "sabih";       // Your WiFi SSID
// char pass[] = "rafi4420";       // Your WiFi Password



// Motor driver pins
#define IN1 14   // Right Motor IN1
#define IN2 12   // Right Motor IN2
#define IN3 26   // Left Motor IN3
#define IN4 27   // Left Motor IN4

// ----------- Motor Functions -----------
void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stopped");
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Forward");
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Backward");
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Left");
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Right");
}

void spinCar() {  // Spins in place
  digitalWrite(IN1, HIGH);  // Right motor backward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);   // Left motor forward
  digitalWrite(IN4, HIGH);
  Serial.println("Spin");
}

// ----------- Blynk Virtual Pins -----------
BLYNK_WRITE(V1) { if (param.asInt() == 1) moveForward(); else stopCar(); }
BLYNK_WRITE(V2) { if (param.asInt() == 1) moveBackward(); else stopCar(); }
BLYNK_WRITE(V3) { if (param.asInt() == 1) turnLeft(); else stopCar(); }
BLYNK_WRITE(V4) { if (param.asInt() == 1) turnRight(); else stopCar(); }
BLYNK_WRITE(V5) { if (param.asInt() == 1) spinCar(); else stopCar(); }
BLYNK_WRITE(V0) { if (param.asInt() == 1) stopCar(); }

// ----------- Setup -----------
void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connected to Blynk ✅");
}

// ----------- Loop -----------
void loop() {
  Blynk.run();
}
