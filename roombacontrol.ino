// Programmed for Roomba 560
// Based upon Will's work here: https://community.particle.io/t/sparkbot-spark-core-roomba/625
// This code was created using the https://build.particle.io/ web interface.


void wakeup();
void stop ();
void dock();
void clean();

int roombaControl(String command);

// Variables
int ddPin = D0;  // Pin to wakeup Roomba and set Baud Rate
int ledPin = D7;  // LED on Particle

// Setup runs everytime on Particle startup
void setup() {

  Spark.function("roombaControl", roombaControl);  // Publish the roombaControl to Particle API

// Set Pins and turn on Serial 1 (Rx,Tx)
  pinMode(ddPin,  OUTPUT);
  pinMode(ledPin, OUTPUT);
// The Roomba is not in 19200 Baud Rate normally, read the Open Interface documentation.
// You have to manually hold the power button for 10 seconds and wait for a descending tone to 
// get this baud rate.  Else you can do it by toggling the ddPin in a sequence.  You could 
// also probably use the default baud rate - I didn't test that yet. 
  Serial1.begin(19200);
  wakeup(); 
}

void wakeup() {

  digitalWrite(ledPin, HIGH);                       // Turn on LED

// Wake up Roomba
  digitalWrite(ddPin, HIGH);                        // Start High
  delay(100);
  digitalWrite(ddPin, LOW);                         // 500ms LOW signal wakes up Roomba
  delay(500);
  digitalWrite(ddPin, HIGH);                        // Set it back to HIGH once Roomba is awake
  

// Set Roomba's Control Mode
// "Upon sending the Start command or any one of the cleaning mode commands (e.g., Spot, Clean, Seek
// Dock), the OI enters into Passive mode. When the OI is in Passive mode, you can request and receive
// sensor data using any of the sensor commands"
  Serial1.write(128);                               // Passive mode
  //delay(50);
  //Serial1.write(130);                               // Safe mode
  //delay(50);
  //Serial1.write(132);                               // Full Control mode
  //delay(50);
  
  digitalWrite(ledPin, LOW);                        // Turn off LED
}


void loop() {
}

void dock() {
  Serial1.write(143); 
}

void stop() {
  Serial1.write(133);  // Actually is the power off command
}

void clean () {
  Serial1.write(135);
}

int roombaControl(String command) {

  wakeup();  //Wakeup the Roomba when a command is received
  
  
  if(command == "DOCK") {
    dock();
    return 1;
  }
    
  if(command == "STOP") {
    stop();
    return 1;
  }

  if(command == "CLEAN") {
    clean();
  }

  return -1;
  
}
