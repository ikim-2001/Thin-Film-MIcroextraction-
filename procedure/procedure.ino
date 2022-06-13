// z axis stepper pins


const int z_dir = 4;
const int z_step = 3;
const int z_enable = 2;
String incomingValue = "waiting";


int i;
int j;


// agitation stepper pins


const int agt_dir = 10;
const int agt_step = 11;
const int agt_enable = 12;
                                                                     


// z-axis stepper functions


void z_motorStep(){
  digitalWrite(z_step, HIGH);
  delayMicroseconds(150);
  digitalWrite(z_step, LOW);
}
// delaymicroseconds(low values faster,speedofrod)

void zStepAscend(){
  digitalWrite(z_dir, HIGH);
}


void zStepDescend(){
  digitalWrite(z_dir, LOW);
}


// agitation functions


void agtMotorStep(){
  digitalWrite(agt_step, HIGH);
  delayMicroseconds(208);    // agitation speed (higher numbers = slower rpm)
  digitalWrite(agt_step, LOW);
}
// delaymicroseconds(low values faster,agitationspeed)

void agtClockwise(){
  digitalWrite(agt_dir, HIGH);
}


void agtCounterclockwise(){
  digitalWrite(agt_dir, LOW);
}


void setup() {
 


  Serial.begin(9600);
  // z axis pinModes:
  pinMode(z_dir, OUTPUT);
  pinMode(z_step, OUTPUT);
  pinMode(z_enable, OUTPUT);


  // agitation pinModes:
  pinMode(agt_dir, OUTPUT);
  pinMode(agt_step, OUTPUT);
  pinMode(agt_enable, OUTPUT);
}


void loop() {
  if(Serial.available() > 0){
    incomingValue = Serial.read();
    Serial.print(incomingValue);
    Serial.print("\n");          
      // put your main code here, to run repeatedly:
      zStepDescend();
      for (i = 0; i < 17000; i++){        //fully descend gantry using z steppers, wait time between deployment and agitation (delay). Change i < X for length.
        z_motorStep();
        delayMicroseconds(2000);
      }
      delay(1000);
      agtCounterclockwise();      
      for (j = 0; j < 2160000; j++){       //agitate the samples while submerged in "water". delaymicroseconds same value as agitation speed previously. Change j < X for agitation time.
        agtMotorStep();
        delayMicroseconds(208);     // changes spinning rate
      }
      delay(1000);
   


      zStepAscend();
      for (i = 0; i < 17000; i++){      // speed of gantry ascending
        z_motorStep();
        delayMicroseconds(2000);
      }
   
      delay(5000);
  }
}
