// Define the input pin connected to the PIR senosr
const int inputPin = 3;

// Define the output pin connected to the LED
const int ledPin = 11;

//Define the trigger and echo pins connected to the ultrasonic sensor
const int triggerPin = 1;
const int echoPin = 2;

// Variables to store the distance and duration calculated by the ultrasonic sensor
volatile float distance;
volatile long duration;

// Variable to check whether an ultrasonic wave has been sent or not
volatile bool ultrasonicPulseSent = false;

// Variable to store the state of the PIR sensor 
volatile int pirState = LOW;

void setup() {

  // Set the inputPin as INPUT
  pinMode(inputPin, INPUT);

  // Set the ledPin as OUTPUT
  pinMode(ledPin, OUTPUT);

  // Set the triggerPin as output and echopin as input
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach interrupts for PIR senor and ultrasonic senosr echo pulse
  attachInterrupt(digitalPinToInterrupt(inputPin), motionDetectedInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(echoPin),  echoPulseEndInterrupt, FALLING);

   // Intialize the serial communication at 9600 baud rate
  Serial.begin(9600);

}

// Interrupt service routine for PIR motion detected
void motionDetectedInterrupt()
{ 
    // Reads the state of the PIR senor
    pirState = digitalRead(inputPin);

    
    if(pirState == HIGH) // Motion is detected by the PIR sensor
    {
         Serial.println("Motion detected");

         // Sends an ultrasonic pulse by triggering the trigger pin
         digitalWrite(triggerPin,HIGH);
         delayMicroseconds(10);
         digitalWrite(triggerPin,LOW);

         // Updating the value of the variable 
         ultrasonicPulseSent = true;
    }
    else // Motion is not detected by the PIR sensor
    {
         Serial.println("Motion not detected");
         
         // Turn LED off in case it is on
         digitalWrite(ledPin, LOW); 
         
         ultrasonicPulseSent = false;
    }
  
    
}

// Interrupt service routine for the ultrasonic sensor echo pulse
void echoPulseEndInterrupt() 
{
  
  if (ultrasonicPulseSent)
  {
      // pulseIn function measure the duration of the echo pulse and its value is stored in duration variable
      duration = pulseIn(echoPin, HIGH); 

      // Calculates the distance in cm based on th eduration of the echo pulse
      distance = duration / 58.0;
      
      ultrasonicPulseSent = false;

     // Check if the object is within 100cm
     if (distance <= 100)
     {
        Serial.print(" Distance from the object is: ");
        Serial.println(distance);
        Serial.println(" Motion detected is within 100cm, turning LED on");

        // Turns on the led
        digitalWrite(ledPin, HIGH);
     } 
     else
    {
       Serial.print("Distance of the object is: ");
       Serial.println(distance);
       Serial.println(" Motion detected is out of range, turning LED off");

       // Turns LED off
       digitalWrite(ledPin, LOW);
    }
  }
}

  
  
void loop() {
  
// We can do anything else here
 }
