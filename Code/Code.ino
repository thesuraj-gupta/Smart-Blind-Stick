// Smart Blind Stick using Arduino Nano
// HC-SR04 + Active Buzzer

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8

long duration;
float distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Smart Blind Stick Started");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = duration * 0.0343 / 2;

  // Print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // -------- Buzzer Alert Logic --------

  if (distance > 0 && distance < 20) {
    // Very close - continuous beep
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (distance >= 20 && distance < 50) {
    // Medium distance - fast beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
  else if (distance >= 50 && distance < 100) {
    // Far distance - slow beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }
  else {
    // No obstacle nearby
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}
