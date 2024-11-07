const int UP   = 2;
const int DN   = 3;
const int NC   = 4;
const int NO   = 5;
const int LS   = 6; 
const int IR   = 7;
const int DIR  = A3;
const int STEP = A4;
const int R    = A5;
const int G    = A6;
const int B    = A7;

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
  pinMode(LS,    INPUT);
  pinMode(IR,    INPUT);
  pinMode(NO,    INPUT);
  pinMode(NC,    INPUT);
  pinMode(UP,   OUTPUT);
  pinMode(DN,   OUTPUT);
  pinMode(R,    OUTPUT);
  pinMode(G,    OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR,  OUTPUT);
  
  
  Serial.begin(115200);
  prox  = digitalRead(IR); 
  if(prox == 1){
    lift_up();
  }
  digitalWrite(R,1);
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
 
