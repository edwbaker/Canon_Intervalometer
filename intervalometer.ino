// Intervalometer for Canon EOS 450D (Digital Rebel XSi)
// Ed Baker (http://ebaker.me.uk)

const int focusPin = 12;
const int photoPin = 11;
const int interval = 5000;

void setup() {
  pinMode(focusPin, OUTPUT);
  digitalWrite(focusPin, LOW);
  pinMode(photoPin, OUTPUT);
  digitalWrite(photoPin, LOW);
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
  delay(interval - take_photo());
}



