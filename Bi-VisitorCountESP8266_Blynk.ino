/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN"

char ssid[] = "ssid";  // Your WiFi credentials.
char pass[] = "pass";

#define Max_Visitors 10


// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// #define SCREEN_WIDTH 128    // OLED display width, in pixels
// #define SCREEN_HEIGHT 64    // OLED display height, in pixels
// #define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




#define inSensor 14   //D5
#define outSensor 12  //D6

#define redLed D0   //D0
#define blueLed D2  //D0

int inStatus;
int outStatus;

int countin = 0;
int countout = 0;

int in;
int out;
int now;

#define relay 0  //D3
WidgetLED light(V0);

/////////////////////////Servo
#include <Servo.h>
// declaring and defining myservo
Servo in_Servo;
Servo out_Servo;
#define in_servo_Pin D1
// #define out_servo_Pin D2
/////////////////////////Servo

void setup() {
  // delay(1000);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  delay(1000);  // wait a second
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(2000);
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  // digitalWrite(redLed, HIGH);
  Serial.println("Visitor Counter Demo");
  //display.clearDisplay();
  //display.setTextSize(2);
  //display.setTextColor(WHITE);
  //display.setCursor(20, 20);
  //display.print("Visitor");
  //display.setCursor(20, 40);
  //display.print("Counter");
  //display.display();
  servoSetup();
  Blynk.logEvent("notify", String("Temperature above threshold: "));
  delay(3000);
}

void loop() {
  Blynk.run();  // Initiates Blynk
  inStatus = digitalRead(inSensor);
  outStatus = digitalRead(outSensor);
  if (inStatus == 0) {
    Serial.println("Visitors! In");
    in = countin++;


    Blynk.virtualWrite(V1, in);   // Visitors In
    Blynk.virtualWrite(V2, out);  // Visitors Out
    Blynk.virtualWrite(V3, now);  // Current Visitors

    moveServo(in_Servo, 10, 0, 90);
    digitalWrite(blueLed, HIGH);
    delay(2000);
    digitalWrite(blueLed, LOW);
    moveServo(out_Servo, 10, 90, 0);
  }

  if (outStatus == 0) {
    Serial.println("Visitors! Out");
    out = countout++;
    if (out > in) out = in;
    // moveServo(out_Servo, 20, 0, 90);
  }

  now = in - out;
  if (now >= Max_Visitors) {
    digitalWrite(redLed, HIGH);
    light.on();
  } else {
    light.off();
    digitalWrite(redLed, LOW);
  }
  if (now <= 0) {
    digitalWrite(relay, HIGH);
    // light.off();
    // digitalWrite(D0, HIGH);
    Serial.println("No Visitors! Light Off");
    // Blynk.logEvent("notify", String("Temperature above threshold: "));

    delay(500);
  } else {
    digitalWrite(relay, LOW);
    // light.on();
    // digitalWrite(D0, LOW);
    Serial.print("Current Visitor: ");
    Serial.println(now);
    Serial.print("IN: ");
    Serial.println(in);
    Serial.print("OUT: ");
    Serial.println(out);
    delay(500);
  }



  Blynk.virtualWrite(V1, in);   // Visitors In
  Blynk.virtualWrite(V2, out);  // Visitors Out
  Blynk.virtualWrite(V3, now);  // Current Visitors



  delay(1000);
}