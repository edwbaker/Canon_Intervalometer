// Intervalometer for Canon EOS 450D (Digital Rebel XSi)
// Ed Baker (http://ebaker.me.uk)

const int focusPin = 12;
const int photoPin = 11;
const int laserPin = 0;
const int interval = 5000;
int mode = 1; 
//mode 0 = intervalometer
//mode 1 = laser trap

int laserVal = 0;

void setup() {
  pinMode(focusPin, OUTPUT);
  digitalWrite(focusPin, LOW);
  pinMode(photoPin, OUTPUT);
  digitalWrite(photoPin, LOW);
  pinMode(laserPin, INPUT);
  Serial.begin(9600);
}

int take_photo() {
  int elapsed =0;
  digitalWrite(focusPin, HIGH);
  elapsed += timed_delay(250);
  digitalWrite(focusPin, LOW);
  digitalWrite(photoPin, HIGH);
  elapsed += timed_delay(500);
  digitalWrite(photoPin, LOW);
  return elapsed;
}

int timed_delay(int delay_time) {
  delay(delay_time);
  return delay_time;
}

void loop() {
switch (mode) {
  case 0:
    delay(interval - take_photo());
    break;
  case 1:
    laserVal = analogRead(laserPin);
    Serial.println(laserVal);
    if (laserVal < 1023) {
      take_photo(); 
    }
  break;
}
}



