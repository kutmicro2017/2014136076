#include <CapacitiveSensor.h>
const int PIN_RED = 11;
const int PIN_BLUE = 10;
const int PIN_GREEN = 9;

CapacitiveSensor   cs_28_30 = CapacitiveSensor(28,30); // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
   cs_28_30.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   pinMode(PIN_RED,OUTPUT);
   pinMode(PIN_BLUE,OUTPUT);
   pinMode(PIN_GREEN,OUTPUT);
}

void loop()                    
{
 long sensor1 =  cs_28_30.capacitiveSensor(30);

    Serial.println(sensor1);  // print sensor output 
   if(sensor1 >= 1000)
   {
    on();
   }
   else{
    off();
   }  
}

void on(){
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_BLUE, 255);
    analogWrite(PIN_GREEN, 255);
}

void off(){
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_BLUE, 0);
    analogWrite(PIN_GREEN, 0);
}

