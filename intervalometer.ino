// Intervalometer for Canon EOS 450D (Digital Rebel XSi)
// Ed Baker (http://ebaker.me.uk)

const int focusPin = 12;
const int photoPin = 11;
const int laserPin = 0;
int interval =0;
const int buttonPin = 7;
const int irLED = 8;
const int irGRD = 9;
int mode = 1; 

//Variables for  
long int dark = 0;
long int light = 0;
int trigger = 0;


//mode 0 = intervalometer
//mode 1 = laser trap

int laserVal = 0;

void setup() {
  pinMode(irGRD, INPUT);
  pinMode(irLED, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(focusPin, OUTPUT);
  digitalWrite(focusPin, LOW);
  pinMode(photoPin, OUTPUT);
  digitalWrite(photoPin, LOW);
  pinMode(laserPin, INPUT);
  Serial.begin(9600);
  delay(2000);
  
  //For light trap mode get dark and light values
  if (mode == 1) {
    for (int i=0; i<100; i++) {
      dark += analogRead(laserPin);
      
    }
    dark /= 100;
    Serial.print("Dark Value : ");
    Serial.println(dark);
    indicate();
    delay(2000);
    
    for (int i =0; i<100; i++) {
      light += analogRead(laserPin); 
    }
    light /= 100;
    Serial.print("Light Value : ");
    Serial.println(light);
    indicate();
    /*
    //Get delay duration
    Serial.println("Press button to record delay.");
    do {} while (digitalRead(buttonPin == HIGH));
    long int start = millis();
    Serial.println(start);
    do {} while ( digitalRead(buttonPin == LOW));
    Serial.println(millis());
    interval = millis() - start;
    if (interval < 1000) {
      interval = 0;
    }
    Serial.print("Interval ");
    Serial.println(interval);
    */
  }
  
  trigger = (dark + light) / 2;
  Serial.print("Trigger     : ");
    Serial.println(trigger);
}

int take_photo() {
  //add ir function call
  delay(interval);
  sendInfraredSignal();
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
    //Serial.println(laserVal);
    if (laserVal < trigger) {
      take_photo(); 
    }
  break;
}
}

void indicate() { //Used to indicate to user
 take_photo(); 
}


/*
Function taken from:
Arduino sketch for simulating a Canon RC-1 IR remote control to do timelapse photography with a compatible Canon DSLR
2010, Martin Koch
http://controlyourcamera.blogspot.com/
Huge thanks go to http://www.doc-diy.net/photo/rc-1_hacked/index.php for figuring out the IR code.
*/
void sendInfraredSignal() {
  for(int i=0; i<16; i++) { 
    digitalWrite(irLED, HIGH);
    delayMicroseconds(11);
    digitalWrite(irLED, LOW);
    delayMicroseconds(11);
   } 
   delayMicroseconds(7330); 
   for(int i=0; i<16; i++) { 
     digitalWrite(irLED, HIGH);
     delayMicroseconds(11);
     digitalWrite(irLED, LOW);
     delayMicroseconds(11);
   } 
}
