
// Define the input pin connected to the PIR senosr
const int inputPin = 3;

// Define the output pin connected to the LED
const int ledPin = 11;

// Variable to store the state of the PIR sensor 
volatile int pirState = LOW;

void setup() {

  // Set the inputPin as INPUT
  pinMode(inputPin, INPUT);

  // Set the ledPin as OUTPUT
  pinMode(ledPin, OUTPUT);
  
  //Attach an interrupt to the inputPin which will trigger the MotionDetector_ISR when its state changes.
  attachInterrupt(digitalPinToInterrupt(inputPin),MotionDetector_ISR, CHANGE); 

  // Intialize the serial communication at 9600 baud rate
  Serial.begin(9600);

}

void loop() {
 }

  // Interrupt service routine
void MotionDetector_ISR()
{
  // Reads the state of the PIR senor
  pirState = digitalRead(inputPin);

   if(pirState == HIGH)
  {
    Serial.println("Motion detected");
  }
  else
  {
    Serial.println("Motion not detected");
  }

  // Set the ledPin to the same state as the PIR sensor
  digitalWrite(ledPin, pirState);
}
