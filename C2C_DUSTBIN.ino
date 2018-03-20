#include <SPI.h>
#include <EEPROM.h>
int EEaddress=0;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define TRIGGER 14
#define ECHO    12
int A;
int pushButton = 2;
int x2;
int meassure;
int b;
int value;

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);





void setup()   {                
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pushButton , INPUT);
  EEPROM.begin(32);  
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC , 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();   
}


 void loop() {

  
  int EEaddress = 0;
  //EEPROM.write(EEaddress,meassure); // Writes the value 123 to EEPROM
  // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 // Contents of EEPROM
  // 7B 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 // Contents of RAM copy of EEPROM
  EEPROM.commit();
  // 7B 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 // Contents of EEPROM
  Serial.print("EEPROM contents at Address=0 is  : ");
  Serial.println(EEPROM.read(EEaddress));
  value = EEPROM.read(EEaddress);
  Serial.print("value at 0 is : ");
  Serial.println(value);

  //begin
  x2=digitalRead(pushButton); 
  Serial.println(x2);
  if( x2 ==0){
    
   long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  meassure = distance;
  Serial.println(meassure);
  EEPROM.write(EEaddress,meassure); // Writes the value 123 to EEPROM
 
  }
  
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  A=(map (distance,value,0,0,24));
  Serial.println(A);
  b=(map (A ,0,24,0,100));
  Serial.print(b);
  Serial.println("persentage");
  delay(1000);
  display.clearDisplay();

    // draw rectangles
  testdrawrect();
 


  // draw multiple rectangles
  testfillrect();
 


  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(35,0);
  display.println("DUST BIN");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(b);
  display.println("%");
  
 
  display.setCursor(0,15);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("CHIP2CLOUD"); 
  display.display();
  //delay(1000);
  

  
}


void testdrawrect(void) {
 
    display.drawRect(100,0,22,7, WHITE);
   
  }


  void testfillrect(void) {
  
    display.fillRect(100,0,A,7,WHITE);
   
  
}

