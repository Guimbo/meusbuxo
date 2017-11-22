#include <OneWire.h>

// DS1821 on digital pin 8
OneWire ds(10); 
    
void setup(void){
  Serial.begin(9600); 

  //start 1821 conversion 
  ds.reset();
  ds.write(0xEE);
  }

  void loop(void){
    Serial.print("C");
    
    // internal
    byte temperatura_;
    byte r;
    byte t;
    int i;
    byte present;

    delay(500);
    
    // Read value internal
    present = ds.reset();
    ds.reset();
    ds.write(0xAA); 
    temperatura_ = ds.read();
    //start 1821 conversion
    ds.reset();
    ds.write(0xEE);

    // negative temperature
    if (temperatura_ >> 7 == 1){ 
        r = temperatura_ ^ 0xFF; // bit inversion external
        t = r + 1;        // external

        Serial.print(t);
        Serial.print("C"); 
        Serial.println("\n");
    }
    
    // positive temperature
    else  
    {
        t = temperatura_;

        Serial.print("+");
        Serial.print(t);
        Serial.print("C");
        Serial.println("\n");
        
    }
    delay(500);
    }
