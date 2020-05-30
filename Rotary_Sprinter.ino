// motor A (left)
int enA = 10;
int in1 = 9;
int in2 = 8;

// motor B (right)
int enB = 5;
int in3 = 7;
int in4 = 6;

// sensors (from right to left)                                    **********************
int s1 = 11;    // sensor 1 (sensor one)                           * Position of sensor *
int s2 = 12;    // sensor 3 (sensor two)                           **********************
int s3 = 3;     // sensor 5 (sensor three)                  ------------------------------------
int s4 = 4;     // sensor 7 (sensor four)                   | s4 | sl | s3 | sc | s2 | sr | s1 |
int sr = A2;    // sensor 2 (sensor right)                  ------------------------------------
int sc = A3;    // sensor 4 (sensor center)                   ^^   ^^   ^^   ^^   ^^   ^^   ^^
int sl = A4;    // sensor 6 (sensor left)                      7    6    5    4    3    2    1

int velocity=140;    // set speed (85~255)
int off=2;           // kill switch

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // set all the sensor pins to inputs
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(sr,INPUT);
  pinMode(sc,INPUT);
  pinMode(sl,INPUT);
}

void loop()    //----------------------------------------------------------------------------------------------------------------------------------------------------------------// main program
{
  if (off==2)    //--------------------------------------------------------------------------------------------------------------------------------------------------------------// kill switch is off
  {
    if ((digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)||             // all sensors detect white
    (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==HIGH&&digitalRead(sl)==LOW))                 // only sensor 4 detect black | others detect white
    {
      forward();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// move forward
    }
    else if ((digitalRead(s1)==HIGH&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)||       // only sensor 1 detect black
    (digitalRead(s1)==HIGH&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==HIGH&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)||               // sensor 1,2 detect black | others detect white
    (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==HIGH&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW))                 // only sensor 2 detect black
    {
      right();    //-------------------------------------------------------------------------------------------------------------------------------------------------------------// turn right (aggressive)
      while (digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)    //-----------------------------------------------------------------------// until sensor 4,5,6,7 detect white | others not used
      {
      }
    }
    else if ((digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==HIGH&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)||       // only sensor 7 detect black | others detect white
    (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==HIGH&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==HIGH)||               // sensor 6,7 detect black | others detect white
    (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==HIGH))                 // only sensor 6 detect black | others detect white
    {
      left();    //--------------------------------------------------------------------------------------------------------------------------------------------------------------// turn left (aggressive)
      while (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW)    //-----------------------------------------------------------------------// until sensor 1,2,3,4 detect black | others not used
      {
      }
    }
    else if (digitalRead(s1)==HIGH&&digitalRead(s2)==HIGH&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==HIGH&&digitalRead(sl)==LOW)    //------------------------// sensor 1,2,3 detect black | others detect white | sensor 4 not used
    {
      forward();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// move forward
      while((digitalRead(s1)==HIGH||digitalRead(s4)==HIGH)&&(digitalRead(s2)==LOW||digitalRead(s3)==LOW))    //------------------------------------------------------------------// until sensor 6,7 detect white | others not used
      {
      }
      while (digitalRead(s4)==LOW&&digitalRead(sl)==LOW)    //-------------------------------------------------------------------------------------------------------------------// while sensor 6,7 detect white | others not used
      {
        sharpright();    //------------------------------------------------------------------------------------------------------------------------------------------------------// pivot turn (right)
      }
      left();    //--------------------------------------------------------------------------------------------------------------------------------------------------------------// turn left (aggressive)
      while (digitalRead(s2)==LOW&&digitalRead(sc)==LOW)    //-------------------------------------------------------------------------------------------------------------------// until sensor 3,4 detect black | others not used
      {
      }
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==HIGH&&digitalRead(s4)==HIGH&&digitalRead(sr)==LOW&&digitalRead(sl)==HIGH)    //------------------------// sensor 5,6,7 detect black | others detect white | sensor 4 not used
    {
      forward();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// move forward
      while((digitalRead(s1)==HIGH||digitalRead(s4)==HIGH)&&(digitalRead(s2)==LOW||digitalRead(s3)==LOW))    //------------------------------------------------------------------// until sensor 6,7 detect white | others not used
      {
      }
      while (digitalRead(s1)==LOW&&digitalRead(sr)==LOW)    //-------------------------------------------------------------------------------------------------------------------// while sensor 1,2 detect white | others not used
      {
        sharpleft();    //-------------------------------------------------------------------------------------------------------------------------------------------------------// pivot turn (left)
      }
      right();    //-------------------------------------------------------------------------------------------------------------------------------------------------------------// turn right (aggressive)
      while (digitalRead(s3)==LOW&&digitalRead(sc)==LOW)    //-------------------------------------------------------------------------------------------------------------------// until sensor 4,5 detect black | others not used
      {
      }
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==HIGH&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==HIGH&&digitalRead(sl)==LOW)         // sensor 3,4 detect black | others detect white
    {
      right_1();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// turn right (slow)
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==HIGH&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)          // only sensor 3 detect black | others detect white
    {
      right_2();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// turn right (moderate)
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==HIGH&&digitalRead(s3)==LOW&&digitalRead(s4)==LOW&&digitalRead(sr)==HIGH&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)         // sensor 2,3 detect black | others detect white
    {
      right_3();    //-----------------------------------------------------------------------------------------------------------------------------------------------------------// turn right (hard)
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==HIGH&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==HIGH&&digitalRead(sl)==LOW)         // sensor 4,5 detect black | others detect white
    {
      left_1();    //------------------------------------------------------------------------------------------------------------------------------------------------------------// turn left (slow)
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==HIGH&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==LOW)          // only sensor 5 detect black | others detect whihte
    {
      left_2();    //------------------------------------------------------------------------------------------------------------------------------------------------------------// turn left (moderate)
    }
    else if (digitalRead(s1)==LOW&&digitalRead(s2)==LOW&&digitalRead(s3)==HIGH&&digitalRead(s4)==LOW&&digitalRead(sr)==LOW&&digitalRead(sc)==LOW&&digitalRead(sl)==HIGH)         // sensor 5,6 detect black | others detect white
    {
      left_3();    //------------------------------------------------------------------------------------------------------------------------------------------------------------// turn left (hard)
    }
    else if (digitalRead(s1)==HIGH&&digitalRead(s2)==HIGH&&digitalRead(s3)==HIGH&&digitalRead(s4)==HIGH&&digitalRead(sr)==HIGH&&digitalRead(sc)==HIGH&&digitalRead(sl)==HIGH)    // all sensors detect black
    {
      for(int i=velocity; i>0; i=i-6)    //--------------------------------------------------------------------------------------------------------------------------------------// decelerate
      {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(enA, i);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enB, i);
        delay(15);
      }
      halt();    //--------------------------------------------------------------------------------------------------------------------------------------------------------------// stop moving
    }
  }
  else    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------// kill switch is on
    halt();    //----------------------------------------------------------------------------------------------------------------------------------------------------------------// stop moving
}    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------// restart program


//************************************************************//
// Below are the functions to be used (called) by the program //
//************************************************************//

void forward()    // move forward
{
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void right()    // turn right (aggressive)
{
  // turn on motor A (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn on motor B (reverse)
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, velocity*0.6);
}

void right_1()    // turn right (slow)
{
  // turn on motor A (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn off motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, velocity*0);
}

void right_2()    // turn right (moderate)
{
  // turn on motor A (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn on motor B (reverse)
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, velocity*0.2);
}

void right_3()    // turn right (hard)
{
  // turn on motor A (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn on motor B (reverse)
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, velocity*0.4);
}

void sharpright()    // pivot turn (right)
{
  // turn on motor A (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, velocity);
  
  // turn on motor B (reverse)
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, velocity);
}

void left()    // turn left (aggressive)
{
  // turn on motor A (reverse)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, velocity*0.6);
  
  // turn on motor B (forward)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void left_1()    // turn left (slow)
{
  // turn off motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, velocity*0);
  
  // turn on motor B (forward)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void left_2()    // turn left (moderate)
{
  // turn on motor A (reverse)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, velocity*0.2);
  
  // turn on motor B (forward)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void left_3()    // turn left (hard)
{
  // turn on motor A (reverse)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, velocity*0.4);
  
  // turn on motor B (forward)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void sharpleft()    // pivot turn (left)
{
  // turn on motor A (reverse)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, velocity);
  
  // turn on motor B (forward)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, velocity);
}

void halt()    // stop moving
{
  // turn off motor A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  
  // turn off motor B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
  off=3;       // turn on kill switch
}
