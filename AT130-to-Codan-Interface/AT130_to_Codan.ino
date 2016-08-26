/*
 Interface between a Codan radio and an Icom AT-130 antenna tuner

 Lawrence Billson, 2016
 */

// Pin assignments
#define ICOMSTART 5
#define ICOMKEY 3
#define CODANIND 6
#define CODANTUNE 4
#define LED 2

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(ICOMSTART, OUTPUT);
  digitalWrite(ICOMSTART,HIGH);
  
  pinMode(ICOMKEY, INPUT);
  pinMode(LED, OUTPUT);
 

  // Wait two seconds to allow the tuner to settle down
  delay(2000);
  
  // Blink the LED to show we're OK
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  Serial.println("Ready to go");
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
    Serial.println("Tuning cycle begin");
    // Start a tuning cycle
    pinMode(CODANTUNE, OUTPUT);
    pinMode(CODANIND, OUTPUT);
    digitalWrite(CODANTUNE, LOW);
    digitalWrite(CODANIND, LOW);
    delay(10);
    digitalWrite(ICOMSTART,LOW);
    delay(100);  // Needs a minimum of 50ms low to start the tune cycle
    digitalWrite(ICOMSTART,HIGH);

    // Loop until the key value is low
    icomkey = 0;
    Serial.print("icomkey value is");
    Serial.println(icomkey);

    
    while (!icomkey) {
      delay(100);
      icomkey = digitalRead(ICOMKEY);

      Serial.print("icomkey value is");
      Serial.println(icomkey);

      
      // Debounce it
      if(icomkey) {
          Serial.println("Debouncing");
          delay(500);
          icomkey = digitalRead(ICOMKEY);        
        }
    }

  sendpass();  
  Serial.println("Debounced - sending a tune pass signal");
  delay(500);
  }
} // End of main loop

void sendpass() {
    digitalWrite(CODANIND, HIGH);
    delay(50);
    digitalWrite(CODANTUNE, HIGH);
}

void sendpfail() {
    digitalWrite(CODANIND, HIGH);
    delay(50);
    digitalWrite(CODANTUNE, HIGH);
}

