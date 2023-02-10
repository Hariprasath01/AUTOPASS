#include "arduino_secrets.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>
#include <Keyboard.h>
Adafruit_SSD1306 display(4);
char enterKey = KEY_RETURN;
char ctrlKey = KEY_LEFT_CTRL;
unsigned long period = 120000,period1=20000;
unsigned long time_now = 0,time_now1=0;
String readString;  

//SoftwareSerial MyBlue(0, 1);
SoftwareSerial mySerial(8, 9);
char flag = 0;
char Gpass[]=SECRET_GOOGLE;
char Ipass[]=SECRET_INSTA;
char Fpass[]=SECRET_FACEBOOK;
char LAPpass[]=SECRET_LAPTOP;
char DOCpass[]=SECRET_DOCUMENT;
       
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup()  
{ 
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  Keyboard.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(false);

  Serial.println("\n\nAdafruit finger detect test");
  //MyBlue.begin(9600);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();

    if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  } 
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  display.clearDisplay();
    //display.setTextSize(2);
    display.setCursor(0,10);
    display.print("   WELCOME  ");
    display.display();  
    //delay(2000);
}

void loop()                     
{
    
    display.clearDisplay();

    //display.setTextSize(2);
    display.setCursor(0,0);
    display.print("  VERIFY  ");
    display.setCursor(0,19);
    display.print("FINGERPRINT");
    display.display();  

  getFingerprintIDez();
  
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    
    Serial.println("Found a print match!");
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("   ACCESS  ");
    display.setTextSize(2);
    display.setCursor(0,19);
    display.print("   GRANTED ");
    display.display();
    delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("   ACCESS  ");
    display.setTextSize(2);
    display.setCursor(0,19);
    display.print("   DENIED ");
    display.display();
    delay(2000);  

    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   

  BLE();
  return finger.fingerID; 
}
int BLE()
{
unsigned long myTime;
time_now = millis();
while(millis() < time_now + period)
{
  while(Serial1.available()) //Send data only when you receive data  
    {  //Serial1.println("hi");
        delay(4); //delay time  
        char c = Serial1.read();  
        readString += c;  
    }  
    if (readString.length() > 0)  
    {  
        
        Serial1.println(readString);
  /*if (Serial1.available())
 {
   flag = Serial1.read();
   Serial1.println(flag);
   
 }*/
 
 
 if(readString=="0type")
 { 
 Serial1.println("Start typing...");
 time_now1 = millis();
 while(millis() < time_now1 + period1)
{readString="";
 while(Serial1.available())
 {   
  //readString="";
  //Serial1.println("Start typing...");
  
  delay(2); //delay time  
  char ch = Serial1.read();  
  readString += ch;
  
  
  }
  //Serial1.println("hello");
  if(readString!="0type"&&readString!="")
  {
  Serial1.println(readString);//0type
  Keyboard.print(readString);
  Keyboard.write(enterKey);  
  Keyboard.releaseAll();
  break;
  }
 }
 //readString="";
 }
if (readString == "google")
 {
  Keyboard.print(Gpass);
  Keyboard.press(enterKey);
  Keyboard.releaseAll();
  readString="9";
  //break;
  
 }
  if (readString == "instagram")
 {
     Keyboard.print(Ipass);
     Keyboard.write(enterKey);
     Keyboard.releaseAll();
     readString="9";
 }
if (readString == "facebook")
 {
  Keyboard.print(Fpass);
  Keyboard.write(enterKey);
  Keyboard.releaseAll();
  readString="9";
  

 }

 if (readString == "laptop")
 {
  Keyboard.print(LAPpass);
  Keyboard.write(enterKey);  
  Keyboard.releaseAll();
  readString="9";
 } 
  readString="";
 
}
  
 if (digitalRead(A0) == 0)
 {
  //Serial.println("0");

 Keyboard.print(Gpass);
 Keyboard.press(enterKey);
 Keyboard.releaseAll();
 delay(2000);

  //flag="9";
  //break;
  
  
 }
  if (digitalRead(A1) == 0)
 {
    //Serial.println("1");
     Keyboard.print(Ipass);
     Keyboard.write(enterKey);
     Keyboard.releaseAll();
     delay(2000);

     //flag="9";
 }
if (digitalRead(A2) == 0)
 {
  //Serial.println("2");

  Keyboard.print(Fpass);
  Keyboard.write(enterKey);
  Keyboard.releaseAll();
  delay(2000);

  //flag="9";
  
 }

 if (digitalRead(A3) == 0)
 {
  //Serial.println("3");

  Keyboard.print(LAPpass);
  Keyboard.write(enterKey);  
  Keyboard.releaseAll();
  delay(2000);

  //flag="9";
 }
   
} 
return 0;

}
