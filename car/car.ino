#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

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

AsyncWebServer server(80);
int count = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  // Motor control endpoints
  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request){
    moveForward();
    Serial.println("forward: " + String(count));
    request->send(200, "text/plain", String(count));
    delay(200);
    stopMotors();
  });

  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request){
    moveBackward();
    Serial.println("backward: " + String(count));
    request->send(200, "text/plain", String(count));
    delay(200);
    stopMotors();
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
    turnLeft();
    Serial.println("left: " + String(count));
    request->send(200, "text/plain", String(count));
    delay(50);
    stopMotors();
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    turnRight();
    Serial.println("right: " + String(count));
    request->send(200, "text/plain", String(count));
    delay(50);
    stopMotors();
  });

  // HTML interface
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>ESP32 Car Controller</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          body {
            text-align: center;
            font-family: sans-serif;
            background-color: #f2f2f2;
          }

          .controller {
            display: inline-block;
            margin: 40px auto;
            text-align: center;
          }

          .controller .row {
            display: flex;
            justify-content: center;
            margin: 5px 0;
          }

          .controller button {
            width: 70px;
            height: 70px;
            font-size: 20px;
            margin: 2px;
            border-radius: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            box-shadow: 0 4px #2d6a35;
            transition: 0.2s;
          }

          .controller button:active {
            box-shadow: 0 2px #2d6a35;
            transform: translateY(2px);
            background-color: #3e8e41;
          }

          .center-dot {
            width: 70px;
            height: 70px;
            margin: 2px;
          }

          pre#count {
            font-size: 24px;
            margin-top: 20px;
          }
        </style>
      </head>
      <body>
        <h1>ESP32 Car Controller</h1>
        <div class="controller">
          <div class="row">
            <button id="forward">FOWARD</button>
          </div>
          <div class="row">
            <button id="left">LEFT</button>
            <div class="center-dot"></div>
            <button id="right">RIGHT</button>
          </div>
          <div class="row">
            <button id="backward">BACKWARDS</button>
          </div>
        </div>

        <pre id="count" data-count="0">0</pre>

        <script>
          const buttons = {
            forward: document.getElementById('forward'),
            backward: document.getElementById('backward'),
            left: document.getElementById('left'),
            right: document.getElementById('right')
          };

          const count = document.getElementById('count');

          function startSendingRequest(url) {
            fetch(url).then(r => r.text()).then(v => updateCountValue(v));
            return setInterval(() => {
              fetch(url).then(r => r.text()).then(v => updateCountValue(v));
            }, 50);
          }

          function stopSendingRequest(id) {
            if (id) clearInterval(id);
          }

          function setupButtonEvents(btnId, endpoint) {
            let intervalId = null;

            const start = () => intervalId = startSendingRequest(endpoint);
            const stop = () => {
              stopSendingRequest(intervalId);
              intervalId = null;
            };

            const btn = buttons[btnId];
            btn.addEventListener('mousedown', start);
            btn.addEventListener('touchstart', start);
            btn.addEventListener('mouseup', stop);
            btn.addEventListener('mouseleave', stop);
            btn.addEventListener('touchend', stop);
            btn.addEventListener('touchcancel', stop);
          }

          function updateCountValue(v) {
            count.dataset.count = v;
            count.innerText = v;
          }

          setupButtonEvents('forward', '/forward');
          setupButtonEvents('backward', '/backward');
          setupButtonEvents('left', '/left');
          setupButtonEvents('right', '/right');
        </script>
      </body>
      </html>
    )rawliteral";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  // AsyncWebServer handles everything
}

// Movement functions
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
