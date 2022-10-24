
int ontime,offtime,duty;
float freq,period;
int duty_cycle = 0;
int hall_value = 0;
int rpm = 0;
int current = 0;

const byte pulse_ip = D2;        // the number of the pwm pin
const byte buttonPin = D10;     // the number of the pushbutton pin
//const byte analogPin = A0;     // the number of the analog pin
const byte interruptPin1 = D3;

int buttonState = 0;            // variable for reading the pushbutton status
long rotation_time = 0;
volatile unsigned long rotations = 0;
volatile long RPMN1count=0;
volatile long RPMN1=0;
volatile boolean flag=0;
long RPMN1period;
const int columns = 11000;

int array0[columns];
long array1[ columns ];
int array2[ columns ];
int array3[ columns ];



void setup() {
  Serial.begin(9600);
  
  //Setting Pin for PWM measurement
  pinMode(pulse_ip,INPUT);   // initialize pwm pin as an input:
  analogReadResolution(12);  // setting the adc resolution to 12 bits
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input:
  pinMode(interruptPin1, INPUT); // initialize the rpm interrupt pin as an input:
  attachInterrupt(D4, N1, FALLING);
 // attachInterrupt(digitalPinToInterrupt(interruptPin1), rising, RISING); // attach interrupt to the rpm interrupt pin and the function rising:
 
}

int measure_pwm(){
  
   ontime = pulseIn(pulse_ip,HIGH);
   offtime = pulseIn(pulse_ip,LOW);
   period = ontime+offtime;
   freq = 1000000.0/period;
   duty = (ontime/period)*100;
   return duty;
  }


long measure_rotation_speed()
{
  if(flag)
  {
    noInterrupts();
    RPMN1=(30000000UL/RPMN1period);   //Two signals per rotation.
    interrupts();
    flag=0;
    return RPMN1;
  }
  
   return RPMN1;
  }


void loop() { 


// read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
    {
     int index = 0;
     
     while(buttonState == HIGH){
      
       array0[index] = measure_pwm();
       array1[index] = measure_rotation_speed();
       array2[index] = analogRead(A0); //Read Hall sensor
       array3[index] = analogRead(A2); // Read Current
       
       buttonState = digitalRead(buttonPin);
       index = index+1;
       
     }


  for(int i = 0; i < index; i++)
{
  Serial.print(array0[i]);
  Serial.print(",");
  //Serial.print('\t');
  Serial.print(array1[i]);
  Serial.print(",");
  //Serial.print('\t');
  Serial.print(array2[i]);
  Serial.print(",");
  //Serial.print('\t');
  Serial.println(array3[i]);

    }
  }
     
  else 
    {
      delay(100);        // delay in between reads for stability
    }
 
}


void N1()
{
  RPMN1period=micros()-RPMN1count;
  RPMN1count=micros();
  flag=1;
}
