
/*
 Simple arduino RC car using the L298 two motors and a rc receiver
 */
 
 int rightMotor[] = { 9, A2, A3 };
 int leftMotor[] = { 10, A4, A5 };
 const int CH1 = 2;
 const int CH2 = 3;
 const int THROTTLEMIN = 1140;
 const int THROTTLECENTRE = 1470;
 const int THROTTLEMAX = 1820;
 const int STEERINGCENTRE = 1470;
 const int STEERINGLEFT = 1040;
 const int STEERINGRIGHT = 1820;
 const int RESOLUTION = 25;
 int speedLeft;
 int speedRight; 
 int ch1;
 int ch2;

void setup() {
  //Serial.begin(115200);
  initMotor(rightMotor);
  initMotor(leftMotor);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}

void initMotor(int motor[]){
  for(int i = 0; i <= sizeof(motor); i++){
    pinMode(motor[i], OUTPUT);
  }
}

void enableMotor(int motor[]){
  digitalWrite(motor[0], HIGH);
}

void stopMotor(int motor[]){
  digitalWrite(motor[0], LOW);
}

void forwardMotor(int motor[]){
  digitalWrite(motor[1], HIGH);

  digitalWrite(motor[2], LOW);
}

void brakeMotor(int motor[]){
  digitalWrite(motor[1], HIGH);
  digitalWrite(motor[2], HIGH);
}

void coastMotor(int motor[]){
  digitalWrite(motor[1], LOW);
  digitalWrite(motor[2], LOW);
}

void reverseMotor(int motor[]){
  digitalWrite(motor[1], LOW);
  digitalWrite(motor[2], HIGH);
}

void forward(){
  enableMotor(leftMotor);
  enableMotor(rightMotor);
  forwardMotor(leftMotor);
  forwardMotor(rightMotor);
}

void reverse(){
  enableMotor(leftMotor);
  enableMotor(rightMotor);
  reverseMotor(leftMotor);
  reverseMotor(rightMotor);
}

void stop(){
  stopMotor(leftMotor);
  stopMotor(rightMotor);
}
void coast(){
  coastMotor(leftMotor);
  coastMotor(rightMotor);
}

void brake(){
  brakeMotor(leftMotor);
  brakeMotor(rightMotor);
}
int setSpeed(int input, int range){
  double multiplier = (double)RESOLUTION/(double)range;
  int returnValue = (int)(multiplier * (double)input);   
  if(returnValue > RESOLUTION) returnValue = RESOLUTION;
  return returnValue; 
}
void drive(){
  if(ch1 < THROTTLECENTRE + 40 && ch1 > THROTTLECENTRE - 40){
    stop();
  }
  if(ch1 > THROTTLECENTRE + 40){
    speedLeft = setSpeed(ch1 - THROTTLECENTRE, THROTTLEMAX-THROTTLECENTRE);
    speedRight = setSpeed(ch1 - THROTTLECENTRE, THROTTLEMAX-THROTTLECENTRE);
    forward();
  }
  if(ch1 < THROTTLECENTRE - 40){
    speedLeft = setSpeed(THROTTLECENTRE - ch1, THROTTLECENTRE - THROTTLEMIN);
    speedRight = setSpeed(THROTTLECENTRE - ch1, THROTTLECENTRE - THROTTLEMIN);
    reverse();
  }
}

void turn(){
 if(ch2 > STEERINGCENTRE +40 ){
   enableMotor(leftMotor);
   coastMotor(rightMotor);
   //reverseMotor(rightMotor);
   forwardMotor(leftMotor);
 } 
 if(ch2 < STEERINGCENTRE - 40){
   coastMotor(leftMotor);
   enableMotor(rightMotor);
   //reverseMotor(leftMotor);
   forwardMotor(rightMotor);
 }
}

void loop() {
  ch1 = pulseIn(CH1,HIGH);
  ch2 = pulseIn(CH2,HIGH);
  if(RESOLUTION-speedRight > 2){
    delay(10);
    coast();
    delay(RESOLUTION-speedRight);
  }
  drive();
  turn();
}
