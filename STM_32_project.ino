//
////int PB13;
////int PB14;
//int PB6;
//sint PB7;
//int PB8;
//int PB9;
//int PB12;
//int PB10;
//int PB11;

int robot1=PB13;
int robot2=PB14;
int robot3=PB6;
int robot4=PB7;

int grass1=PB8;
int grass2=PB9;

int relay=PB12;

#define echoPin PB11
#define pingPin PB10

long duration, cm;

void setup() {

   Serial.begin(9600);
   
   pinMode(robot1,OUTPUT);
   pinMode(robot2,OUTPUT);
   pinMode(robot3,OUTPUT);
   pinMode(robot4,OUTPUT);
   
   pinMode(relay,OUTPUT);

   pinMode(grass1,OUTPUT);
   pinMode(grass2,OUTPUT); 
   
   digitalWrite(robot1,LOW);
   digitalWrite(robot2,LOW);
   digitalWrite(robot3,LOW);
   digitalWrite(robot4,LOW);
   
   digitalWrite(grass1,LOW);
   digitalWrite(grass2,LOW);  

   digitalWrite(relay,LOW);
  
}

void loop() 
{
  while(1)
  {
      forward_movement();
      Serialevent();
       ultra_check();
       
   }
}
void Serialevent()
{

   if(Serial.available()>0)
       {
        char ch=Serial.read();
        Serial.print("character:");
        Serial.println(ch);
          if(ch=='W')
           {
            stop_robot();
            delay(1000);
              digitalWrite(grass1,HIGH);
              digitalWrite(grass2,LOW);
              delay(8000);
              digitalWrite(grass1,LOW);
              digitalWrite(grass2,LOW);
              delay(1000);
           }
          else if(ch=='P')
           {
            stop_robot();
            delay(1000);
             digitalWrite(relay,HIGH);
             delay(6000);
             digitalWrite(relay,LOW);
             delay(1000);
           }
       }
  
}
void forward_movement()
{
   Serial.println("FORWARD");
   digitalWrite(robot1,HIGH);
   digitalWrite(robot2,LOW);
   digitalWrite(robot3,HIGH);
   digitalWrite(robot4,LOW);
   Serialevent();
  //  ir_check();
}
void reverse_movement()
{
   Serial.println("REVERSE");
   digitalWrite(robot1,LOW);
   digitalWrite(robot2,HIGH);
   digitalWrite(robot3,LOW);
   digitalWrite(robot4,HIGH);
Serialevent();
}

void right_movement()
{
   Serial.println("RIGGHT");
   digitalWrite(robot1,HIGH);
   digitalWrite(robot2,LOW);
   digitalWrite(robot3,LOW);
   digitalWrite(robot4,HIGH);
   Serialevent();
  
}
void left_movement()
{
   Serial.println("LEFT");
   digitalWrite(robot1,LOW);
   digitalWrite(robot2,HIGH);
   digitalWrite(robot3,HIGH);
   digitalWrite(robot4,LOW);
 Serialevent();
}
void stop_robot()
{
   Serial.println("STOP");
   digitalWrite(robot1,LOW);
   digitalWrite(robot2,LOW);
   digitalWrite(robot3,LOW);
   digitalWrite(robot4,LOW);
   digitalWrite(grass1,LOW);
   digitalWrite(grass2,LOW);
   digitalWrite(relay,LOW);
}

void ultra_check()
{  
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm =  duration*0.034/2;
   Serial.print("Front:");
   Serial.print(cm);
   Serial.println("cm");
   Serial.println();
   delay(500);
  if(cm<20)
  {
     
    Serial.println("FRONT OBJECT DETECTED");
    stop_robot();
    delay(2000);
    left_movement();
    delay(2000);
    forward_movement();
  }
  Serialevent();
}
