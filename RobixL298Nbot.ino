#include "BluetoothSerial.h" 
BluetoothSerial ESP_BT;

// Connect Your Pins Like This
#define RPWM1 18   // for motor 1
#define LPWM1 19   // for motor 1
#define RPWM2 23   // for motor 2
#define LPWM2 22   // for motor 2
#define pwmPin1 21  // for pwm
#define pwmPin2 4  // for pwm

int incoming;
int speedValue = 255; // Default maximum speed between 0-255 you can adjust but adjustable later on via pwm

void setup() {
  Serial.begin(115200);
  ESP_BT.begin("Robix L298N Bot");

  Serial.println("The Robix Bot is Ready to Pair");
  ESP_BT.println("Robix L298N is ready to pair");

  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);

  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
}

void loop() {

  if (ESP_BT.available()) {
    incoming = ESP_BT.read();
    Serial.print("Received: ");
    Serial.println(incoming);

    // STOP
    if (incoming == 83) { 
      digitalWrite(RPWM1, LOW);
      digitalWrite(LPWM1, LOW);
      digitalWrite(RPWM2, LOW);
      digitalWrite(LPWM2, LOW);
      analogWrite(pwmPin1, 0);
      analogWrite(pwmPin2, 0);
      ESP_BT.println("The Bot Has Stopped"); // serial monitor prints for debugging
    }

    else if (incoming == 70) { 
      digitalWrite(RPWM1, HIGH);
      digitalWrite(LPWM1, LOW);
      digitalWrite(RPWM2, LOW);
      digitalWrite(LPWM2, HIGH);
      analogWrite(pwmPin1, speedValue);
      analogWrite(pwmPin2, speedValue);
      ESP_BT.println("Turning left");
    }

    else if (incoming == 66) { 
      digitalWrite(RPWM1, LOW);
      digitalWrite(LPWM1, HIGH);
      digitalWrite(RPWM2, HIGH);
      digitalWrite(LPWM2, LOW);
      analogWrite(pwmPin1, speedValue);
      analogWrite(pwmPin2, speedValue);
      ESP_BT.println("Turning right");
    }

    else if (incoming == 76) { 
      digitalWrite(RPWM1, LOW);
      digitalWrite(LPWM1, HIGH);
      digitalWrite(RPWM2, LOW);
      digitalWrite(LPWM2, HIGH);
      analogWrite(pwmPin1, speedValue);
      analogWrite(pwmPin2, speedValue);
      ESP_BT.println("Moving forward");
    }

    else if (incoming == 82) { 
      digitalWrite(RPWM1, HIGH);
      digitalWrite(LPWM1, LOW);
      digitalWrite(RPWM2, HIGH);
      digitalWrite(LPWM2, LOW);
      analogWrite(pwmPin1, speedValue);
      analogWrite(pwmPin2, speedValue);
      ESP_BT.println("Moving backward");
    }

    // SPEED CONTROL 0–9 where pwm comes to play
    else if (incoming >= 48 && incoming <= 57) { 
      speedValue = map(incoming, 48, 57, 0, 255);
      analogWrite(pwmPin1, speedValue);
      analogWrite(pwmPin2, speedValue);

      Serial.print("Speed set to: ");
      Serial.println(speedValue);
      ESP_BT.print("Speed set to: ");
      ESP_BT.println(speedValue);
    }
  }

  delay(20);
}

// MADE BY ROBIX BUT FREE TO USE FOR ALL


