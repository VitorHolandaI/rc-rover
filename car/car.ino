#include <WiFi.h>
#include <WiFiAP.h>

// Motor A (left)
#define enA D0
#define in1 D1
#define in2 D2

// Motor B (right)
#define enB D3
#define in3 D4
#define in4 D5

const char *ssid = "carAp";
const char *password = "334166";

WiFiServer server(80);

void setup() {
  //Serial.begin(115200);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Default all off
  stopMotors();

  //Serial.println("Setting up Access Point...");
  WiFi.softAP(ssid, password);
 // Serial.print("AP IP address: ");
  //Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  //Serial.println("Client connected.");
  String req = client.readStringUntil('\r');
  //Serial.println(req);
  client.flush();

  // Handle movement commands
  if (req.indexOf("/forward") != -1) moveForward();
  else if (req.indexOf("/backward") != -1) moveBackward();
  else if (req.indexOf("/left") != -1) turnLeft();
  else if (req.indexOf("/right") != -1) turnRight();
  else stopMotors();

  // Send HTML response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.println("<!DOCTYPE html><html><head><title>Rover Control</title></head><body>");
  client.println("<h1>Control Rover</h1>");
  client.println("<a href=\"/forward\"><button style='width:100px;height:50px;'>Forward</button></a><br><br>");
  client.println("<a href=\"/left\"><button style='width:100px;height:50px;'>Left</button></a>");
  client.println("<a href=\"/stop\"><button style='width:100px;height:50px;'>Stop</button></a>");
  client.println("<a href=\"/right\"><button style='width:100px;height:50px;'>Right</button></a><br><br>");
  client.println("<a href=\"/backward\"><button style='width:100px;height:50px;'>Backward</button></a>");
  client.println("</body></html>");

  client.println();
  delay(10);
  client.stop();
  //Serial.println("Client disconnected.");
}

// Movement functions
void moveForward() {
  //analogWrite(enA, 255);
  //analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  //analogWrite(enA, 255);
  //analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  //analogWrite(enA, 255);
  //analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  //analogWrite(enA, 255);
  //analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
