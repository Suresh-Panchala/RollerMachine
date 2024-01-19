const int NC   = 12;
const int NO   = 11;
const int LS   = 10; 
const int IR   = 13;
const int DIR  = 15;
const int STEP = 14;
const int UP   = 18;
const int DN   = 19;
const int R    = 20;
const int G    = 21;





const int stepsPerRevolution = 800;
int limit,temp = 0;
int rev = 0, f_run = 0,prox = 0;
void motor(){
    digitalWrite(DIR, HIGH);
    digitalWrite(STEP, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP, LOW);
    delayMicroseconds(200);
}
void motor_off(){
  digitalWrite(STEP,LOW);
}
void c_motor(){
    digitalWrite(DIR, LOW);
    digitalWrite(STEP, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP, LOW);
    delayMicroseconds(200);
}
void lift_up(){
   Serial.println("UP");
  digitalWrite(UP,1);
  delay(2500);
  digitalWrite(UP,0);
 
}
void lift_down(){
   Serial.println("DOWN");
  digitalWrite(DN,1);
  delay(3800);
  digitalWrite(DN,0);
}
void ind_on(){
  digitalWrite(R,1);
  digitalWrite(G,0);
}
void ind_off(){
  digitalWrite(R,0);
  digitalWrite(G,1);
}
void setup()
{
  // Declare pins as Outputs
  pinMode(10,  INPUT);
  pinMode(11,  INPUT);
  pinMode(12,  INPUT);
  pinMode(13,  INPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  
  
  Serial.begin(115200);
  prox  = digitalRead(IR); 
  if(prox == 1){
    lift_up();
  }
  digitalWrite(3,1);
}
void loop()
{
  prox  = digitalRead(IR); 
  limit = digitalRead(LS);
  rev   = digitalRead(NC);
  int _on = digitalRead(NO);
  Serial.println(_on);
 if(digitalRead(NO) == 0 && temp == 0  && prox == 0){
  ind_on();
   while(limit == 0){
    motor();
    limit = digitalRead(LS);
  }
  delay(30);
  while(limit == 1){
    motor();
    limit = digitalRead(LS);
    f_run = 1;
  }
  
  lift_down();
  delay(2000);
  lift_up();
  temp = 1;
  f_run = 0;
  motor_off();
 }
 ind_off();
 if(digitalRead(NO) == 0 && temp == 1 && prox == 0){
  ind_on();
  while(limit == 1){
    motor();
    limit = digitalRead(LS);
    f_run = 1;
  }
  temp = 0;
  f_run = 0;
  motor_off();
 }
 ind_off();

 
 if(rev == 1 && f_run == 0  && prox == 0 ){
  ind_on();
  c_motor();
 }
}
 
