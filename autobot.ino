typedef void (*functiontype)();

int leftMotor = D1;
int leftMotorDir = D5;
int rightMotor = D0;
int rightMotorDir = D4;

int frontBumper = D2;
int frontRightBumper = D6;
int frontLeftBumper = D3;

int statusLED = D7;

int speed = 100;
int spiralRate = speed / 2;

int FORWARD = 1;
int BACK = 0;
int RIGHT = 0;
int LEFT = 1;

void setup() {
  Serial.begin(9600);

  pinMode(leftMotor, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);

  pinMode(frontBumper, INPUT_PULLUP);
  pinMode(frontRightBumper, INPUT_PULLUP);
  pinMode(frontLeftBumper, INPUT_PULLUP);

  pinMode(statusLED, OUTPUT);

  spiralStart();
}

void checkBumper(int bumper, std::function<void ()> response) {
  int hit = digitalRead(bumper);

  if (hit == 0) {
    response();
  }
}

void stop() {
  analogWrite(rightMotor, 0);
  analogWrite(leftMotor, 0);
}

void spiralStart() {
  stop();

  digitalWrite(rightMotorDir, FORWARD);
  digitalWrite(leftMotorDir, FORWARD);

  analogWrite(leftMotor, speed * 1.25);
}

void go(int dir) {
  spiralRate = 0;
  digitalWrite(statusLED, LOW);
  stop();

  digitalWrite(rightMotorDir, dir);
  digitalWrite(leftMotorDir, dir);

  analogWrite(rightMotor, speed);
  analogWrite(leftMotor, speed);
}

void turn(int dir) {
  stop();

  Serial.println(dir);
  Serial.println(abs(dir - 1));

  digitalWrite(rightMotorDir, dir);
  digitalWrite(leftMotorDir, abs(dir - 1));

  analogWrite(rightMotor, speed);
  analogWrite(leftMotor, speed);
}

void bumpFront() {
  int newDir = random(0, 1);

  go(BACK);
  delay(500);
  turn(newDir);
  delay(350);
  go(FORWARD);
}

void bumpFrontRight() {
  go(BACK);
  delay(250);
  turn(LEFT);
  delay(250);
  go(FORWARD);
}

void bumpFrontLeft() {
  go(BACK);
  delay(250);
  turn(RIGHT);
  delay(250);
  go(FORWARD);
}

void loop() {
  if (spiralRate > 0) {
    digitalWrite(statusLED, HIGH);
    delay(400);
    if (spiralRate < (speed * .90)) {
      spiralRate = spiralRate + 1;

      analogWrite(rightMotor, spiralRate);
    }
    Serial.println(spiralRate);
  }

  checkBumper(frontBumper, bumpFront);
  checkBumper(frontRightBumper, bumpFrontRight);
  checkBumper(frontLeftBumper, bumpFrontLeft);

  delay(300);
}
