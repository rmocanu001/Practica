#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
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

LiquidCrystal_I2C lcd(0x3F,16,2);
int switchState=0;
int switchFirstPress=0;

bool buttonPressed=0;
int jumpButton=5;
bool dinoLast=0;

int j;
int score=0;
unsigned long t; //unsigned long used for millis
unsigned long t1;
unsigned long t2;
unsigned long t3;

int objectDelay=500; //basic cactus moving speed
int objectDecrease=20; //decreases delay

bool dinoUp=0;

byte cactus[8] = { //cactus
  B00101,
  B10101,
  B10101,
  B10101,
  B10110,
  B01100,
  B00100,
  B00100,
};

byte dino[8] = { //dino
  B01110,
  B10111,
  B11110,
  B11111,
  B11000,
  B11111,
  B11010,
  B10010,
};


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  myservo.attach(7);
  irrecv.enableIRIn(); 
  myservo.write(0);
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(5,0);
  lcd.print("Salut");
  lcd.setCursor(1,1);
  lcd.print("Mocanu Razvan");

  lcd.createChar(7, cactus);
  lcd.createChar(6, dino);

   j=15;

  t=millis();
  t1=millis();
  t2=millis();
  t3=millis();

}
void start_fnc(){
    switchFirstPress = digitalRead(jumpButton);
  while(switchFirstPress == LOW) {
    lcd.setCursor(1, 1);
    lcd.print("PRESS TO START");
    lcd.setCursor(0, 0);
    lcd.print("DINO GAME ");
    lcd.setCursor(13, 0);
    lcd.write(6);
    lcd.setCursor(14, 0);
    lcd.write(7);
    delay(400);
    lcd.clear();
switchFirstPress = digitalRead(jumpButton);
Serial.println(switchFirstPress);
 if (switchFirstPress == HIGH) {
   break;
 }
  
}
}
void game_fnc(){
  switchState = digitalRead(jumpButton);
Serial.println(switchState);
if((millis()-t)>=objectDelay) { //delay on cactus move
  t=millis();
  lcd.clear();
  lcd.setCursor(j, 1);
  lcd.write(7);
  j=j-1;
    if(j == -1) {
      j=15;
    }
  lcd.setCursor(6, 0);
  lcd.print("Score:");
  lcd.print(score);
}
if((millis()-t1)>=50) {
  t1=millis();
  if (switchState == HIGH && dinoUp == false) {
    lcd.setCursor(2, 0);
    lcd.write(6);
    dinoUp = true; 
    t2=millis();
  }
  else if(dinoUp == true) {
    lcd.setCursor(2, 0);
    lcd.write(6);
  }
  else if(dinoUp == false) {
    lcd.setCursor(2, 0);
    lcd.print(" ");
    lcd.setCursor(2, 1);
    lcd.write(6);
  }
}
if((millis()-t2)>=1500 && dinoUp == true) {
  t2=millis();
  lcd.setCursor(2, 1);
  lcd.write(6);
  lcd.setCursor(2, 0);
  lcd.print(" ");
  dinoUp = false;
}
if(((millis()-t3)>=1000) && (j == 1)) {
  t3=millis();
  if (dinoUp == true) {
    score=score+1;
    if (score%5 == 0) {
    objectDelay=objectDelay-objectDecrease;
      if(objectDelay <= 200) { //makes 200 highest speed 
        objectDecrease=0; //keeps cactus/object at max speed and wont keep increasing it
      }
    }
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("TAP TO RETRY");
    score=0;
    j=15;
    objectDelay=500; //toggles back to basic speed
    switchState = digitalRead(jumpButton);
      while(switchState == LOW) {
        switchState = digitalRead(jumpButton);
      }
      delay(500);
  }
}
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
int flower_akt=0;
int timer_akt=0;
int game_akt=0;
int value = 0;
void ir_telecomanda(){
   if(irrecv.decode(&results)){     
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("Salut");
        lcd.setCursor(1,1);
        lcd.print("Mocanu Razvan");
        value = results.value;
        int var=myservo.read();
        Serial.println(value);      
       switch(value){     
         case 255: 
         {//Keypad button "1"
         myservo.write(0);
         aktivate=0;flower_akt=0;timer_akt=0;game_akt=0;
         }

         }     
       switch(value){     
         case 2295: //Keypad button "2" 
         {myservo.write(180);
         aktivate=0;flower_akt=0;timer_akt=0;game_akt=0;

         //myservo.write(0);
         }
       }
       switch(value){     
         case -30601:
         if(aktivate==0)
          {aktivate=1;flower_akt=0;timer_akt=0;game_akt=0;}
          else aktivate=0;
         
       }
       switch(value){     
         case 18615:
          if(flower_akt==0)
          {aktivate=0;flower_akt=1;timer_akt=0;game_akt=0;}
          else flower_akt=0;
       }
       switch(value){     
         case 10455:
          if(timer_akt==0)
          {aktivate=0;flower_akt=0;timer_akt=1;game_akt=0;}
          else timer_akt=0;
       }

      switch(value){     
         case -22441:
         if(game_akt==0)
          {aktivate=0;flower_akt=0;timer_akt=0;game_akt=1;switchFirstPress=LOW;}
          else game_akt=0;
      }
       irrecv.resume();      
   }
  

}
int distance=0;
int duration=0;


void if_distance(){

  delay(50);
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
      myservo.write(0);
    }
    else{
          myservo.write(180);
          delay(5000);
      }
  
}

  int tolerance=40;
  int servoGrad=90;
void flower(){

  int sensorValue=analogRead(temt6000Pin);

  if ( sensorValue < (512-tolerance) )
  {
    if (servoGrad < 180) servoGrad++;
  }

  if ( sensorValue > (512+tolerance) )
  {
    if (servoGrad > 0) servoGrad--;
  }

  myservo.write( servoGrad );
}

void timer(){
  myservo.write(0);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(1000);
  }

// the loop function runs over and over again forever
void loop() {
  for(int i=1;;i++){
  lighting();
  ir_telecomanda();
  //delay(1000);                       
  if(i%2==0)// wait for a second
  {Serial.println("Delay 10 sec cu i par");}
  else{
    Serial.println("Delay 10 sec cu i impar");
   }
  if(aktivate==1){
  if_distance();}

  if(flower_akt==1){
  flower();}

    if(timer_akt==1){
  timer();}
  if(game_akt==1){
     if(switchFirstPress==LOW){
     start_fnc();}
     game_fnc();
    }
  }// wait for a second
  }
