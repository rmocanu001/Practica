#include <Servo.h>
#include <IRremote.h>  //including infrared remote header file     
int RECV_PIN = 8; // the pin where you connect the output pin of IR sensor     
IRrecv irrecv(RECV_PIN);     
decode_results results;
Servo myservo;
int MOTOR_PORT=7;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  myservo.attach(7);
  irrecv.enableIRIn(); 
}

// the loop function runs over and over again forever
void loop() {
  for(int i=1;;i++){
  digitalWrite(LED_BUILTIN, HIGH); 
  //myservo.write(0);// turn the LED on (HIGH is the voltage level)
  delay(1000);                       
  if(i%2==0)// wait for a second
  {Serial.println("Delay 10 sec cu i par");}
  else{
    Serial.println("Delay 10 sec cu i impar");
   }
  digitalWrite(LED_BUILTIN, LOW); 
  //myservo.write(120);// turn the LED off by making the voltage LOW
  delay(1000);
  if (irrecv.decode(&results)){     
        int value = results.value;
        int var=myservo.read();
        Serial.println(value);      
       switch(value){     
         case 2295: //Keypad button "1"
         myservo.write(0);            
         }     
       switch(value){     
         case -30601: //Keypad button "2"     
         myservo.write(180); 
         }     
       switch(value){     
         case 18615: //Keypad button "3"
         if(var<=160){     
         var+=20;
         myservo.write(var);
         }     
         else        {  myservo.write(180);}
         }
       switch(value){     
         case 10455: //Keypad button "4" 
                  if(var>=20){     
         var-=20;
         myservo.write(var);
         }     
         else        {  myservo.write(0);}    
         }     
       irrecv.resume();      
   }
  }// wait for a second
}
