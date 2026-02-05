//UART-Driven Finite State Diagnostic Controller
enum mode{
INIT,IDLE,ACTIVE,DIAG,STATUS
};
//interval time......
unsigned long lasttime = 0;;
mode state = INIT;
mode sysstate = INIT;
void setup(){
Serial.begin(115200);
Serial.println("There are 4 states you can operate over");
Serial.println("'i' for idle");
Serial.println("'a' for active");
Serial.println("'d' for diagnostics");
Serial.println("'s' for status");
Serial.println("built in led blinking fast for active ");
Serial.println("slow for diagnostics,simply on for lock");
Serial.println("led off for idle");
pinMode(LED_BUILTIN, OUTPUT);
state = IDLE;
}
//boolean variable for led blinking......
bool ledstate = false;

void loop(){
  //using millis for timing......
  unsigned long time = millis();

  if(Serial.available()){
    char a = Serial.read();
    // IDLE......
    if(a == 'i'){
    state = IDLE;
    Serial.println("The machine in IDLE state now");
    }
    // ACTIVE......
    else if(a == 'a'){
      state = ACTIVE;
    Serial.println("The machine in ACTIVE state now");
    }
    // DIAG......
    else if(a == 'd'){
      state = DIAG;
    Serial.println("The machine in DIAGNOSTICS state now");
    }
    // STATUS......
    else if(a == 's'){
      sysstate = STATUS;
    Serial.println("The machine in STATUS state now");
    }
  }

  //switching cases......
  switch(state){

    //case ACTIVE......
    case ACTIVE :
    if(time - lasttime >=500){
    lasttime = time;
    //toggle......
    ledstate = !ledstate;
    digitalWrite(LED_BUILTIN,ledstate);
    }
    break;

    //case IDLE......
    case IDLE : 
    digitalWrite(LED_BUILTIN, LOW);
    break;

    //case DIAGNOSTICS......
    case DIAG :
    if(time - lasttime >=1500){
    lasttime = time;
    //toggle......
    ledstate = !ledstate;
    digitalWrite(LED_BUILTIN,ledstate);
    }
    break;
  }  
  switch(sysstate){
    //case STATUS......
    case STATUS :
    if(state == IDLE){
    Serial.println("IDLE");
    }
    if(state == ACTIVE){
    Serial.println("ACTIVE");
    }
    if(state == DIAG){
    Serial.println("DIAGNOSTICS");
    }
    sysstate = INIT;
    break;
}
}
