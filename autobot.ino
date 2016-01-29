typedef void (*functiontype)();

int leftMotor = D1;
int leftMotorDir = D5;
int rightMotor = D0;
int rightMotorDir = D4;

int frontBumper = D2;
int frontRightBumper = D6;
int frontLeftBumper = D3;

int speed = 150;
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

void go(int dir) {
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
  checkBumper(frontBumper, bumpFront);
  checkBumper(frontRightBumper, bumpFrontRight);
  checkBumper(frontLeftBumper, bumpFrontLeft);

  delay(300);
}
