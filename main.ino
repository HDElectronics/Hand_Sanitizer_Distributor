#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BP 3
#define BM 4
#define PUMP 5
#define IRSENSOR 8 
#define PEDAL 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(6, 7); //RX, TX

unsigned long pumpOnDuration = 1000;

void setup(){
	pinMode(PUMP, OUTPUT);
    digitalWrite(PUMP, LOW),
	pinMode(BP, INPUT);
	pinMode(BM, INPUT);
	pinMode(IRSENSOR, INPUT);
	pinMode(PEDAL, INPUT);

    lcd.begin();
    lcd.noCursor();
    //print some Hi it's Celec

    mySerial.begin(9600); //begin communication with the bluetooth module
    //Starting a 10 seconds while loop down here
    unsigned long currentT = millis();
    while (millis() - currentT < 10000)
    {
        if (mySerial.available() > 0){ //if data comes from bluetooth then it's
            pumpOnDuration = mySerial.parseInt();   // gonna be the duration
        }                                           //of the pump
    }
    mySerial.~SoftwareSerial();
}

void loop(){
	if(digitalRead(IRSENSOR)){
        //Hand Detected
        delay(300);
        digitalWrite(PUMP, HIGH);
        delay(pumpOnDuration);
        digitalWrite(PUMP, LOW);
        while (digitalRead(PUMP)){
            delay(1);
        }
    }
    else if(digitalRead(PEDAL)){
        //Pedal pressed
        delay(300);
        digitalWrite(PUMP, HIGH);
        delay(pumpOnDuration);
        digitalWrite(PUMP, LOW);
        while (digitalRead(PUMP)){
            delay(1);
        }
    }
    else if(digitalRead(BP)){
        //Button+ Pressed
        delay(50);
        pumpOnDuration += 50;
        delay(400);
    }
    else if(digitalRead(BM)){
        //Button- Pressed
        delay(50);
        pumpOnDuration -= 50;
        delay(400);
    }
    lcd.home();
    lcd.print(pumpOnDuration);
}
