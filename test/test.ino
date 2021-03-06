#include <Servo.h>
#include <IRremote.h>  //including infrared remote header file
     
int RECV_PIN = 8; // the pin where you connect the output pin of IR sensor     
IRrecv irrecv(RECV_PIN);     
decode_results results;
Servo myservo;
int MOTOR_PORT=7;
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3
int temt6000Pin = A0;
float light;
int light_value;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  myservo.attach(7);
  irrecv.enableIRIn(); 
  myservo.write(0);
}

void lighting(){
  int light_value = analogRead(temt6000Pin);
  light = light_value * 0.0976;// percentage calculation 
  Serial.println(light);
  delay(100);
  if (light < 50) {
      digitalWrite(LED_BUILTIN, HIGH); 
  }
  else {  digitalWrite(LED_BUILTIN, LOW); }
  }
int aktivate=0;
void ir_telecomanda(){
  int value = 0;
      if(irrecv.decode(&results)){     
        value = results.value;
        int var=myservo.read();
        Serial.println(value);      
       switch(value){     
         case 255: 
         {//Keypad button "1"
         myservo.write(0);
         aktivate=0;
         }

         }     
       switch(value){     
         case 2295: //Keypad button "2" 
         {myservo.write(180);
         delay(10000);
         aktivate=1;
         //myservo.write(0);
         }
       }
       irrecv.resume();      
   }
  
}

int distance=0;
int duration=0;


void if_distance(){

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.println(distance);


    //delay(1000);
    if (distance>50)
    {
      myservo.write(160);
      myservo.write(120);
      myservo.write(100);
      myservo.write(80);
      myservo.write(60);
      myservo.write(30);
      myservo.write(0);
    }
    else{
          myservo.write(180);
      }
  
}


// the loop function runs over and over again forever
void loop() {
  for(int i=1;;i++){
  lighting();
  //delay(1000);                       
  if(i%2==0)// wait for a second
  {Serial.println("Delay 10 sec cu i par");}
  else{
    Serial.println("Delay 10 sec cu i impar");
   }
  if(aktivate==1){
  if_distance();}
  ir_telecomanda();
  }// wait for a second
}
