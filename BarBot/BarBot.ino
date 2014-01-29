#include <AccelStepper.h>
#include <Servo.h>

AccelStepper stepper(AccelStepper::DRIVER, 10, 11);


Servo servo;

  int enableStepper = 12;
   int steps = 0;
   int length = 0;
   int maxSpeed = 1200;
   
   int servoUp = 2000;
   int servoDown= 500;
   
   char chr;
   int minEnd =2;
   int maxEnd =3;
   
void setup()
{
    Serial.begin(115200);
  
  
    stepper.setMaxSpeed(maxSpeed);
    stepper.setAcceleration(1000.0); 
    //stepper.setMinPulseWidth(200);
    //stepper.setEnablePin(12);  // not sure how to set this yet
    
    //servo.attach(14); 
    
    
    digitalWrite(enableStepper, HIGH);
    servo.write(servoDown);

}


void loop()
{


if(Serial.available() > 0) {

    chr = Serial.read();
    
    if (chr == 'G') {
        delay(5);
      steps =  Serial.parseInt();
      length =  Serial.parseInt();
      servo.write(servoDown);
      
      
      Serial.print("Running to position :");
      Serial.println(steps);
      
      digitalWrite(enableStepper, LOW);
      stepper.moveTo(steps);
      while(stepper.distanceToGo() != 0) {
        stepper.run();
//        Serial.println("running Stepper");
      } 
      
      
      delay(50);//pause for a sec to let the glass settle
      servo.attach(14); 
      Serial.print("Pouring for miliseconds:");
      Serial.println(length);
      servo.write(servoUp);
      delay(length); //pauses to pour liquid
      servo.write(servoDown);
      
      delay(1000); //pauses to let the last liquid drain, not sure if neccesary
        //also wait for the servo to go down
      servo.detach(); 

      Serial.println("K");
      digitalWrite(enableStepper, HIGH);
    } else if (chr == 'H') {
      Serial.println("Homing");
      stepper.setMaxSpeed(500.0);
      digitalWrite(enableStepper, LOW);
      
      
        stepper.move(-20000);
        Serial.println(stepper.distanceToGo());
        while(stepper.distanceToGo() != 0) {
          if(digitalRead(minEnd)!=0){
            stepper.run();
            //Serial.println("Homing");
          } else{
            stepper.setCurrentPosition(0);
            stepper.move(0);
          }
          
        }
        
      
      
      digitalWrite(enableStepper, HIGH);
      
      stepper.setMaxSpeed(maxSpeed);

    } else{
      Serial.println("UnknownCommand");
    }
    
    
  }

  
}

