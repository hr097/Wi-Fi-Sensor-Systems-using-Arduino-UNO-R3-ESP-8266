#include<LiquidCrystal.h>  //We need to add libary for some LCD Display function
int calibrationTime = 10; //PIR motion sensor's restart time
int piroutpin = 3; // PIR motion sensor's datapin in ardiuno datapin no 3
int BuzzPin = 2; // buzzer's datapin in ardiuno datapin no 2
const int flamepin=A5;//flam sensor's datapin in ardiuno pin Analog pin no A5
const int sensor=A4; //temprature sensor's datapin in ardiuno pin Analog pin no A5
const int threshold=200;// sets threshold value for flame sensor
int flamesensvalue=0; // initialize flamesensor reading
const int rs = 13, en = 12, d4 =11, d5 =10, d6 = 9, d7 = 8; //pin Declaration of LCD Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //pass the pin Configration in LCD
float temp;

//SETUP
void setup(){
      Serial.begin(9600);  //To Start Serial Communication

      //LCD DISPLAY
      lcd.begin(16,2); //LCD  Display Size
      lcd.setCursor(0,0); //set the cursor On 0th Column and 0th Row on LCD display
      lcd.print("Temperature"); //Print temperature in LCD displau
      delay(2000); //delay for 2 sec


      //PIN DECLERATION
      pinMode(piroutpin, INPUT);  //configure PIR motion sensor pin as a input mode
      pinMode(flamepin,INPUT);   //configure flame sensor pin as a input mode
      pinMode(BuzzPin, OUTPUT);  //configure buzzer pin as a Output mode
      digitalWrite(piroutpin, LOW); //PIR motion sensor pin is disable LOW the internal pullup on the input pin.
      Serial.print("calibrating sensor "); //to send information from your Arduino to your computer and print on serial monitor
      for(int i = 0; i < calibrationTime; i++) // loop is started by 0 and go for the 10 sec to take time start PIR motion sensor
      {
          Serial.print(".");
          delay(1000);
      }
      Serial.println(" done"); // this print that PIR motion Sensor  is done to detect motion 
      Serial.println("SENSOR ACTIVE");
      delay(50);
}
////////////////////////////
//LOOP
void loop()
{
       ///////PIR MOTION SENSOR //////////
       if(digitalRead(piroutpin) == HIGH)  //check the condition if PIR motion Sensor is Detect the motion 
       {
        int i;        
        for(i=0;i<2;i++)  //then Buzzer rigning 2 time
        {
         tone(BuzzPin,1000);  //for set the tone 1st argument is pinno and 2nd is frequncy of sound 
         delay(50); //stops program for 0.05 second
         noTone(BuzzPin);  
         delay(50);
        }
       }
       else
       {
        noTone(BuzzPin);  //if Motion is not detect then not start buzzer
       }
       
     //////FLAM SENSOR///////////
     flamesensvalue=analogRead(flamepin); // reads analog data from flame sensor
     if (flamesensvalue<=threshold)  // compares reading from flame sensor with the threshold value
     { 
         tone(BuzzPin,1000); //then tone buzzer
         
         
     }
     else
     {
        noTone(BuzzPin);  //if flam is not detected buzzer is not rigning
    }



     ///////TEMPERATURE SENSOR /////////
     temp = analogRead(sensor); //reads analog data from TEMPERATURE sensor
     temp=(temp*500)/1023;      //convert temprature value vout to celcius
     float tempc=temp;          //pass the temp value to tempc
     lcd.setCursor(0, 1);       //set the cursor on  0th Column and 1st Row on LCD Display
     lcd.setCursor(4, 1);       //set the cursor on 4th Column and 1st Row on LCD Display
     lcd.print(tempc);          //print the tempc value
     lcd.setCursor(11, 1);      //set the cursor on 11th Column and 1st Row on LCD Display
     lcd.print("C");            //print the C On LCD DISPLAY
     delay(1000);               //delay for 1sec
}
