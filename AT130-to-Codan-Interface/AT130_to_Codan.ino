/*
 Interface between a Codan radio and an Icom AT-130 antenna tuner

 Lawrence Billson, 2016
 */

// Pin assignments
#define ICOMSTART 3
#define ICOMKEY 4
#define CODANIND 2
#define CODANTUNE 1
#define LED 0

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ICOMSTART, OUTPUT);
  digitalWrite(ICOMSTART,HIGH);
  pinMode(ICOMKEY, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
 

  // Wait two seconds to allow the tuner to settle down
  delay(2000);
  
  // Blink the LED to show we're OK
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);

}

// the loop function runs over and over again forever
void loop() {
  int tunereq;
  int icomkey; 

  // Restore Sanity
  pinMode(CODANTUNE, INPUT);
  pinMode(CODANIND, INPUT);
  digitalWrite(LED,LOW);
  digitalWrite(ICOMSTART,HIGH);


  // Wait until we get a tune signal from the radio
  tunereq = digitalRead(CODANTUNE);
  if (!tunereq) {
    // Start a tuning cycle
    pinMode(CODANTUNE, OUTPUT);
    pinMode(CODANIND, OUTPUT);
    digitalWrite(CODANTUNE, LOW);
    digitalWrite(CODANIND, LOW);
    delay(10);
    digitalWrite(ICOMSTART,LOW);
    delay(50);  // Needs a minimum of 50ms low to start the tune cycle
    digitalWrite(ICOMSTART,HIGH);
    delay(300);
    // Loop until the key value is low
    icomkey = 0;

    
    while (!icomkey) {
      delay(100);
      icomkey = digitalRead(ICOMKEY);
      
      // Debounce it
      if(icomkey) {
          delay(1000);
          icomkey = digitalRead(ICOMKEY);        
        }
    }

  delay(500);
  sendpass();  
  delay(500);
  }
  
} // End of main loop

void sendpass() {
    digitalWrite(LED, HIGH);
    digitalWrite(CODANIND, HIGH);
    delay(50);
    digitalWrite(CODANTUNE, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    
}

void sendpfail() {
    digitalWrite(CODANIND, HIGH);
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(CODANTUNE, HIGH);
    delay(5000);
    digitalWrite(LED, LOW);
}

