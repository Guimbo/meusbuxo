    #include <OneWire.h>

    // DS1821 on digital pin 2 external
    OneWire ds(2); 

    // DS1821 on digital pin 8 internal
    OneWire ds1(8); 

    void setup(void)
    {

    Serial.begin(9600); 

    //start 1821 conversion external
    ds.reset();
    ds.write(0xEE);

    //start 1821 conversion internal
    ds1.reset();
    ds1.write(0xEE);
    }

    void loop(void){
    // external
    byte temperatura_externa;
    byte read_value;
    byte temperatura_final;
    byte existe_sensor_externa;
    float valor_final;

    // internal
    byte temperatura_interna;
    byte read_value2;
    byte temperatura_final2;
    byte existe_sensor_interna;
    float valor_final2;

    delay(500);

    // Read value external
    existe_sensor_externa = ds.reset();
    ds.reset();
    ds.write(0xAA); 
    temperatura_externa = ds.read();

    // Read value internal
    existe_sensor_interna = ds1.reset();
    ds1.reset();
    ds1.write(0xAA); 
    temperatura_interna = ds1.read();

    //start 1821 conversion external
    ds.reset();
    ds.write(0xEE);

    //start 1821 conversion internal
    ds1.reset();
    ds1.write(0xEE);

    // negative temp external
    if (temperatura_externa >> 7 == 1){ 
        read_value = temperatura_externa ^ 0xFF; // bit inversion external
        temperatura_final = read_value + 1;        // external
        valor_final = (float) temperatura_final;

        Serial.print("Externo:");
        Serial.print("T");
        Serial.print("-");
        Serial.print(valor_final);
        Serial.println("C"); 
    }
    
    // positive temp external
    else{
        temperatura_final = temperatura_externa; // external
        valor_final = (float) temperatura_final;

        Serial.print("Externo");
        Serial.print("T");
        Serial.print("+");
        Serial.print(valor_final);
        Serial.println("C");

    }

        // negative temp internal
    if (temperatura_interna >> 7 == 1){ 
        read_value2 = temperatura_interna ^ 0xFF; // bit inversion external
        temperatura_final2 = read_value2 + 1;        // external
        valor_final2 = (float) temperatura_final2;

        Serial.print("Interno");
        Serial.print("T");
        Serial.print("-");
        Serial.print(valor_final2);
        Serial.println("C");
    }
    // positive temp internal
    else{
        temperatura_final2 = temperatura_interna; // internal
        valor_final2 = (float) temperatura_final2;

        Serial.print("Interno");
        Serial.print("T");
        Serial.print("+");
        Serial.print(valor_final2);
        Serial.println("C");

    }
    delay(500);
    }
