#include <Servo.h>

Servo myservo_Front_L;
Servo myservo_Front_R;
Servo myservo_Back_L;
Servo myservo_Back_R;

Servo myservo_Updown;
Servo myservo_Grab;

String message; 
const int  init_Updown_Angle = 100;// Initial position of the the up down arm
const int min_Updown_Angle = 10;// Maximum angle of the up down arm
int current_Updown_Angle = init_Updown_Angle;
int old_Updown_Angle = current_Updown_Angle;

const int init_Grab_Angle = 0;// Initial position of the up down arm
const int max_Grab_Angle = 80;// Maximum angle of the up down arm
int current_Grab_Angle = init_Grab_Angle;

bool isGrabbed = false;
bool isOn = false; 
bool steerBoth = false;
bool uTern = false;
bool standBy = false;

const int max_Steer_Angle = 105;// Maximum angle of the front wheels
const int init_Steer_Angle = 55;// Initial angle of the front wheels
const int min_Steer_Angle = 5;// Minimum angle of the front wheels

const int FL=-2;
const int FR=1;
const int BL=-2;
const int BR=1;

int current_Steer_Angle = init_Steer_Angle;
int old_Steer_Angle = init_Steer_Angle;

int pwm = 100; // Initial pwm value

int new_Low_Val = 0;
int new_High_Val = 0;

const int enable_front_left = 6;
const int front_left_moter_A = 26;
const int front_left_moter_B = 27;

const int enable_front_right = 7;
const int front_right_moter_A = 28;
const int front_right_moter_B = 29;

const int enable_back_left = 4;
const int back_left_moter_A = 22;
const int back_left_moter_B = 23;

const int enable_back_right = 5;
const int back_right_moter_A = 24;
const int back_right_moter_B = 25;

void init_Motors(){
  pinMode(front_left_moter_A,OUTPUT);
  pinMode(front_left_moter_B,OUTPUT);
  pinMode(front_right_moter_A,OUTPUT);
  pinMode(front_right_moter_B,OUTPUT);
  pinMode(back_left_moter_A,OUTPUT);
  pinMode(back_left_moter_B,OUTPUT);
  pinMode(back_right_moter_A,OUTPUT);
  pinMode(back_right_moter_B,OUTPUT);
  pinMode(enable_front_left,OUTPUT);
  pinMode(enable_front_right,OUTPUT);
  pinMode(enable_back_left,OUTPUT);
  pinMode(enable_back_right,OUTPUT);
  enable(pwm);
}

void go(char x){
  // F ---> forward
  // B ---> backward
  // L ---> left
  // R ---> right
  // S ---> standby
 switch(x){
    case 'F':
      digitalWrite(front_left_moter_A,HIGH);
      digitalWrite(front_left_moter_B,LOW);
      digitalWrite(front_right_moter_A,HIGH);
      digitalWrite(front_right_moter_B,LOW);
      digitalWrite(back_left_moter_A,HIGH);
      digitalWrite(back_left_moter_B,LOW);
      digitalWrite(back_right_moter_A,HIGH);
      digitalWrite(back_right_moter_B,LOW);
      enable(pwm);
      break;
   case 'B':
      digitalWrite(front_left_moter_A,LOW);
      digitalWrite(front_left_moter_B,HIGH);
      digitalWrite(front_right_moter_A,LOW);
      digitalWrite(front_right_moter_B,HIGH);
      digitalWrite(back_left_moter_A,LOW);
      digitalWrite(back_left_moter_B,HIGH);
      digitalWrite(back_right_moter_A,LOW);
      digitalWrite(back_right_moter_B,HIGH);
      enable(pwm);
      break;
   case 'L':
      digitalWrite(front_left_moter_A,LOW);
      digitalWrite(front_left_moter_B,HIGH);
      digitalWrite(front_right_moter_A,HIGH);
      digitalWrite(front_right_moter_B,LOW);
      digitalWrite(back_left_moter_A,LOW);
      digitalWrite(back_left_moter_B,HIGH);
      digitalWrite(back_right_moter_A,HIGH);
      digitalWrite(back_right_moter_B,LOW);
      enable(pwm);
      break;
   case 'R':
      digitalWrite(front_left_moter_A,HIGH);
      digitalWrite(front_left_moter_B,LOW);
      digitalWrite(front_right_moter_A,LOW);
      digitalWrite(front_right_moter_B,HIGH);
      digitalWrite(back_left_moter_A,HIGH);
      digitalWrite(back_left_moter_B,LOW);
      digitalWrite(back_right_moter_A,LOW);
      digitalWrite(back_right_moter_B,HIGH);
      enable(pwm);
      break;
   case 'S':
     standBy = true;
      digitalWrite(front_left_moter_A,LOW);
      digitalWrite(front_left_moter_B,LOW);
      digitalWrite(front_right_moter_A,LOW);
      digitalWrite(front_right_moter_B,LOW);
      digitalWrite(back_left_moter_A,LOW);
      digitalWrite(back_left_moter_B,LOW);
      digitalWrite(back_right_moter_A,LOW);
      digitalWrite(back_right_moter_B,LOW);
      break;
   default:break;   
 } 
}
void setMotorDirection(char x){
 switch(x){
    case 'L':
      digitalWrite(front_left_moter_A,LOW);
      digitalWrite(front_left_moter_B,HIGH);
      digitalWrite(front_right_moter_A,HIGH);
      digitalWrite(front_right_moter_B,LOW);
      digitalWrite(back_left_moter_A,LOW);
      digitalWrite(back_left_moter_B,HIGH);
      digitalWrite(back_right_moter_A,HIGH);
      digitalWrite(back_right_moter_B,LOW);
      enable(pwm);
      break; 
    case 'R':
      digitalWrite(front_left_moter_A,HIGH);
      digitalWrite(front_left_moter_B,LOW);
      digitalWrite(front_right_moter_A,LOW);
      digitalWrite(front_right_moter_B,HIGH);
      digitalWrite(back_left_moter_A,HIGH);
      digitalWrite(back_left_moter_B,LOW);
      digitalWrite(back_right_moter_A,LOW);
      digitalWrite(back_right_moter_B,HIGH);
      enable(pwm);
      break; 
 }
}
void enable(int val){
   analogWrite(enable_front_left,val);
   analogWrite(enable_front_right,val);
   analogWrite(enable_back_left,val);
   analogWrite(enable_back_right,val);
}

void set_Val(int val){
  new_Low_Val = val;
  new_High_Val = val;
  if(new_Low_Val < 0){
    new_Low_Val = 0;
  }
  if(new_High_Val > 255){
    new_High_Val = 255;
  }
}
void enable_Left(int val){
  set_Val(val);
  if(current_Steer_Angle > init_Steer_Angle){
     analogWrite(enable_back_left,new_Low_Val);
     analogWrite(enable_back_right,new_High_Val);
     analogWrite(enable_front_right,new_High_Val);
  }
}
void enable_Right(int val){
   set_Val(val);
  if(current_Steer_Angle < init_Steer_Angle){
     analogWrite(enable_back_right,new_Low_Val);
     analogWrite(enable_back_left,new_High_Val);
     analogWrite(enable_front_left,new_High_Val);
  }
}

void init_Servors(){
  myservo_Front_L.attach(9);
  myservo_Front_R.attach(10);
  myservo_Back_L.attach(11);
  myservo_Back_R.attach(12);
}
void moveDown(){
  old_Updown_Angle = current_Updown_Angle;
  current_Updown_Angle -= 10;
  if(current_Updown_Angle < min_Updown_Angle){
     current_Updown_Angle = min_Updown_Angle;
  }
  writeAngle(myservo_Updown, old_Updown_Angle, current_Updown_Angle);
}
void moveUp(){
  old_Updown_Angle = current_Updown_Angle;
  current_Updown_Angle += 20;
  if(current_Updown_Angle > init_Updown_Angle){
     current_Updown_Angle = init_Updown_Angle;
  }
  writeAngle(myservo_Updown, old_Updown_Angle, current_Updown_Angle);
}
void grabBox(){
  if(!isGrabbed){
    writeAngle(myservo_Grab, init_Grab_Angle, max_Grab_Angle);
    isGrabbed = true;
    delay(10); 
  }else{
    writeAngle(myservo_Grab, max_Grab_Angle, init_Grab_Angle);
    isGrabbed = false;
    delay(10);
  }
}

void setBeforeUTernSteerAngle(){
  uTern = true;
  int i = init_Steer_Angle - min_Steer_Angle;
   for(int k  = 1; k <= i; k++){
    myservo_Front_L.write(FL + init_Steer_Angle - k);
    myservo_Front_R.write(FR + init_Steer_Angle + k);
    myservo_Back_L.write(BL + init_Steer_Angle + k);
    myservo_Back_R.write(BR + init_Steer_Angle - k);
    delay(10);
   }
}
void setAfterUTernSteerAngle(){
  uTern = false;
  int i = init_Steer_Angle - min_Steer_Angle;
   for(int k  = 1; k <= i; k++){
    myservo_Front_L.write(FL + k);
    myservo_Front_R.write(FR + max_Steer_Angle - k);
    myservo_Back_L.write(BL + max_Steer_Angle - k);
    myservo_Back_R.write(BR + k);
    delay(10);
   }  
}
void setInitialAngle(){
  myservo_Front_L.write(FL + init_Steer_Angle);
  myservo_Front_R.write(FR + init_Steer_Angle);
  myservo_Back_L.write(BL + init_Steer_Angle);
  myservo_Back_R.write(BR + init_Steer_Angle);
}
void setSteerAngle(int angle){
  myservo_Front_L.write(FL + angle);
  myservo_Front_R.write(FR + angle);
  
  if(steerBoth){
    if(angle > init_Steer_Angle){
      angle = angle - 2*init_Steer_Angle;
    }else if(angle < init_Steer_Angle){
      angle = 2*init_Steer_Angle - angle;
    }
    myservo_Back_L.write(BL + angle);
    myservo_Back_R.write(BR + angle);
  }
}

void UTernLeft(){
  if(!uTern){
    setBeforeUTernSteerAngle();
  }
  setMotorDirection('L');
}
void UTernRight(){
  if(!uTern){
    setBeforeUTernSteerAngle();
  }
  setMotorDirection('R');
}
void writeSteerAngle(int old, int angle){// For Steer Servos
  int i = angle - old;
  if(i > 0){
     for(int k  = 1; k <= i; k++){
      setSteerAngle(old + k);
      delay(10);
     } 
  }else if(i < 0){
     for(int k  = 1; k <=(-i); k++){
      setSteerAngle(old - k);
      delay(10);
     } 
  }
}
void writeAngle( Servo servo, int old, int angle){// Fore Other Servos
  int i = angle - old;
  
  if(i > 0){
     for(int k  = 1; k <= i; k++){
      servo.write(old + k);
      delay(10);
     } 
  }else if(i < 0){
     for(int k  = 1; k < (-i); k++){
      servo.write(old - k);
      delay(10);
     } 
  }
}
void setup()
{
  myservo_Updown.write(init_Updown_Angle);
  myservo_Grab.write(init_Grab_Angle);

  init_Motors();
  init_Servors();
  
  setInitialAngle();
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available()>0)
  {
    message+=char(Serial.read());
//==================== Go Forward ==========================   
    if(message == "1"){ 
      if(!standBy){
        if(uTern){
          setAfterUTernSteerAngle();
        }else{
          writeSteerAngle(current_Steer_Angle,init_Steer_Angle);
        }
        current_Steer_Angle = init_Steer_Angle;
      }else{
        standBy = false;
      }
      go('F');
      enable(pwm);
      delay(1);  
//==================== Go Backward ==========================    
    }else if(message == "2"){
      if(!standBy){
        if(uTern){
          setAfterUTernSteerAngle();
        }else{
          writeSteerAngle(current_Steer_Angle,init_Steer_Angle);
        }
        current_Steer_Angle = init_Steer_Angle;
      }else{
        standBy = false;
      }
      go('B');
      enable(pwm);
      delay(1);
//==================== Turn Right ==========================
    }else if(message == "3"){
      enable(pwm);
      old_Steer_Angle = current_Steer_Angle;
      current_Steer_Angle += 10;
      if(current_Steer_Angle > max_Steer_Angle){
        current_Steer_Angle = max_Steer_Angle;
      }
      writeSteerAngle(old_Steer_Angle, current_Steer_Angle);
      enable_Left(pwm);
//==================== Turn Left ==========================    
    }else if(message == "4"){
      enable(pwm);
      old_Steer_Angle = current_Steer_Angle;
      current_Steer_Angle -= 10;
      if(current_Steer_Angle < min_Steer_Angle){
        current_Steer_Angle = min_Steer_Angle;
      }
      writeSteerAngle(old_Steer_Angle, current_Steer_Angle);
      enable_Right(pwm);
//==================== Speed UP ==========================
    }else if(message == "5"){
      pwm += 20;
      if(pwm > 255){
        pwm = 255;
      }
      enable(pwm);
      delay(1);
//==================== Speed Down ==========================
    }else if(message == "6"){
      pwm -= 20;
      if(pwm < 100){
        pwm = 100;
      }
      enable(pwm);
      delay(1);
//==================== StandBy ==========================
    }else if(message == "7"){
     go('S'); 
//==================== Arm Move Up ==========================
    }else if(message == "8"){
      moveUp();
//==================== Arm Move Down ==========================
    }else if(message == "9"){
      moveDown();
//==================== Grab Box ==========================
    }else if(message == "0"){
      grabBox();
//==================== U Tern Left ==========================
    }else if(message == "l"){
      UTernLeft();
//==================== U Tern Right ==========================
    }else if(message == "r"){
      UTernRight();
    }
    message="";
    delay(100);
  }
} 
