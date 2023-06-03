#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//LicuidCrystsal_PCF8574 lcd(0x27);
int LED=7,DATAIN=9;
int OUT=10;
int BEE=6;
int i;
int j;
bool judgeOverheat=0;
bool flag=0;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //lcd.setBacklight(50);

  // Print a message to the LCD.
  lcd.print("LET'S GO");
  pinMode(LED, OUTPUT);
  pinMode(OUT,OUTPUT);
  pinMode(BEE,OUTPUT);
  pinMode(DATAIN, INPUT_PULLUP);
  
}

void loop() {

  digitalWrite(LED, LOW);
  digitalWrite(OUT, HIGH);

  while(digitalRead(9)){  
  lcd.clear();
  lcd.print("LET'S GO");
  lcd.display();
  delay(500);
  }
  //问候显示


  digitalWrite(LED, HIGH);
  lcd.clear();

  Serial.print(digitalRead(9));

  for(i=10;i>0&(~digitalRead(9));i--){
    digitalWrite(LED, HIGH);
    digitalWrite(OUT, LOW);
    lcd.print(i);
    lcd.display();
    tone(6, 262, 10000);
    delay(1000);
    if(i==1)
    {
      flag=1;
    }
  }        
  //吹风以及倒数显示结束
  while(flag&(~digitalRead(9)))
  {
    digitalWrite(OUT, HIGH);
    digitalWrite(LED, LOW);
    tone(0, 0, 0);
    lcd.clear();
    lcd.print("OVERHEAT");
    delay(1000);

  }
  //过热保护


  for(i=5;i>0&(digitalRead(9));i--){
    lcd.clear();
    lcd.print("THANK YOU");
    lcd.display();
    delay(200);
  }
  //再见显示结束
}
    

