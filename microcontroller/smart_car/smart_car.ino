#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Ganti dengan WiFi dan Firebase milikmu
#define WIFI_SSID "Galaxy A05"
#define WIFI_PASSWORD "12345678"
#define FIREBASE_HOST "smartcar-f2205-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_API_KEY "AIzaSyBzwFjTAbBI4cLrYXiw03A2VG48_YEbVwE"

// Motor A
const int IN1 = D1;
const int IN2 = D2;
const int ENA = D3;

// Motor B
const int IN3 = D5;
const int IN4 = D6;
const int ENB = D4;

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("WiFi Terhubung");

  config.host = FIREBASE_HOST;
  config.api_key = FIREBASE_API_KEY;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Sign-up berhasil (Anonymous)");
  } else {
    Serial.printf("Sign-up gagal: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void controlMotor(String direction) {
  if (direction == "forward") {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (direction == "left") {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (direction == "right") {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  } else { // stop
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    return;
  }

  // Default speed pelan
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void loop() {
  if (Firebase.getJSON(firebaseData, "/robot_control")) {
    FirebaseJson &json = firebaseData.jsonObject();
    FirebaseJsonData result;

    String direction = "stop";

    if (json.get(result, "direction") && result.success) {
      direction = result.stringValue;
    }

    Serial.println("Arah: " + direction);
    controlMotor(direction);
  } else {
    Serial.println("Gagal membaca Firebase: " + firebaseData.errorReason());
  }

  delay(300);
}
