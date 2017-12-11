#include <CapacitiveSensor.h>
const int PIN_RED = 10;
const int PIN_GREEN = 9;
const int PIN_BLUE = 8;

bool touch;
bool state;
int val;

CapacitiveSensor   cs_3_6 = CapacitiveSensor(3,6); // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
   cs_3_6.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
   Serial.begin(300);
   pinMode(PIN_RED,OUTPUT);
   pinMode(PIN_BLUE,OUTPUT);
   pinMode(PIN_GREEN,OUTPUT);
   touch = false;
   state = false;
}

void loop()                    
{
 long sensor1 =  cs_3_6.capacitiveSensor(18);

    Serial.println(sensor1);  // print sensor output 
   if(sensor1 >= 2)  touch = true;
   else touch = false;

   if(touch == true) state = !state;

   if(state == true)  on();
   else off();
}

void on(){
    int val = ((analogRead(A7)/4));
    analogWrite(PIN_RED, analogRead(val)+25);
    analogWrite(PIN_BLUE,analogRead(val)+25-analogRead(A0));
    analogWrite(PIN_GREEN,analogRead(val)+25);
}

void off(){
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_BLUE, 0);
    analogWrite(PIN_GREEN, 0);
}
