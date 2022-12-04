int throttleIn = A5;
int turnIn = A4;
int In4 = 2,In3 = 4,In1 = 8,In2 = 7;
int enLeft = 6, enRight = 5; //PWM pins
int a = 0,b = 0;

int dir = 0;

void setLeft(bool a,int val, int turnFactor)
{
  if(a == false)
  {
    digitalWrite(In1,LOW); digitalWrite(In2,LOW);
  }
  else
  {
    if(val > 0)
    {
      digitalWrite(In1,HIGH); digitalWrite(In2,LOW);
      if(val > 255)
        val = 255;
       int result = val;
      if(turnFactor > 0)
      {
        result = val - turnFactor/3;
      }
      if(result > 255)
        result = 255;
      analogWrite(enLeft,result);
      //analogWrite(enRight,val);
    }
    else
    {
      digitalWrite(In1,LOW); digitalWrite(In2,HIGH);
      if(val < -255)
        val = -255;
      int result = val;
      if(turnFactor > 0)
      {
        result = val + turnFactor/3;
      }
      if(result < -255)
        result = -255;
      analogWrite(enLeft,-(result));
      //analogWrite(enRight,-val);
    }
  }
}
void setRight(bool a,int val,int turnFactor)
{
  if(a == false)
  {
    digitalWrite(In3,LOW); digitalWrite(In4,LOW);
  }
  else
  {
    if(val > 0)
    {
      digitalWrite(In4,HIGH); digitalWrite(In3,LOW);
      if(val > 255)
        val = 255;
      int result = val;
      if(turnFactor < 0)
      {
        result = val + turnFactor/3;
      }
      if(result > 255)
        result = 255;
      analogWrite(enRight,result);
      //analogWrite(enRight,val);
    }
    else
    {
      digitalWrite(In4,LOW); digitalWrite(In3,HIGH);
      if(val < -255)
        val = -255;
      int result = val;
      if(turnFactor < 0)
      {
        result = val - turnFactor/3;
      }
      if(result < -255)
        result = -255;
      analogWrite(enRight,-(result));
      //analogWrite(enRight,-val);
    }
  }
}

void setup() 
{
  // put your setup code here, to run once:
  //set it up
  pinMode(throttleIn, INPUT);
  pinMode(In1,OUTPUT); pinMode(In2,OUTPUT); pinMode(In3,OUTPUT); pinMode(In4,OUTPUT);
  pinMode(enLeft,OUTPUT); pinMode(enRight,OUTPUT);
  Serial.begin(9600);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = map(pulseIn(throttleIn,HIGH),1100,1830,-250,250); //1830 TO 1100
  b = pulseIn(turnIn,HIGH)-1505;//,1110,1830,-250,250);
  Serial.println(b);
  if(a <= 150 && a >= -150)
  {
    //then it should be in off state
    setLeft(false,0,0);
    setRight(false,0,0);
  }
  else
  {
    setLeft(true,a,b);
    setRight(true,a,b);
  }

  //delay(40);
//    digitalWrite(In1,HIGH);
//    digitalWrite(In2,LOW);
//    digitalWrite(In3,HIGH);
//    digitalWrite(In4,LOW);
//    analogWrite(enRight,200);
//    analogWrite(enLeft,200);
  
  //Serial.println(a);
}
