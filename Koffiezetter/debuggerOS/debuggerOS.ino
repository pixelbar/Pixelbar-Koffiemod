// Koffiezettermod Version 2.0.1 Beta ( Pre Stable Release )
//
// The whole source code has been rechecked and allmost completely rewritten and re-assambled just to make it quicker, and to make it compatible with an Arduino Mega 2560
// Since this Arduino had so much I/O busses that the whole multiplexing became unnessecarry
//

#include <SPI.h>
#include <util.h>
#include <LiquidCrystal.h>

// Koffiezettermod as made on an Arduino Mega

// Pins :
// Pin : 22-25 Switches Koffie, Thee, Warm water, Afwas water 
// Pin : 26-29 Leds in kast
// Pin : 31 Relais Koffiezetter
// Pin : 30,32-35,37 LCD
// Pin : 36,38-39,41 Externe switches
// Pin : INTERRUPT 4 stopbutton = 19

//Defines

#define led_Koffie        27
#define led_Thee          26
#define led_WarmWater     28
#define led_Afwas         29

#define relais_lock       31

#define sw_Koffie         23
#define sw_Thee           22
#define sw_WarmWater      25
#define sw_Afwas          24
#define sw_25L            38
#define sw_50L            41
#define sw_75L            36
#define sw_10L            39
#define stopbutton        19  //interrupt 4

// DEFINE CUSTOM COFFEE CHAR

byte cup[8] = { 
  B00100,
  B01000,
  B00100,
  B10010,
  B10011,
  B10010,
  B01100,
  B00000 };

// INITIALIZATION

// Initialize LCD

LiquidCrystal lcd(33, 30, 35, 32, 37 ,34);

void setup()
{
  // Define Pins
  
  pinMode(led_Koffie, OUTPUT);
  pinMode(led_Thee, OUTPUT);
  pinMode(led_WarmWater, OUTPUT);
  pinMode(led_Afwas, OUTPUT);
  pinMode(relais_lock, OUTPUT);
  
  pinMode(sw_Koffie, INPUT);
  pinMode(sw_Thee, INPUT);
  pinMode(sw_WarmWater, INPUT);
  pinMode(sw_Afwas, INPUT);
  pinMode(sw_25L, INPUT);
  pinMode(sw_50L, INPUT);
  pinMode(sw_75L, INPUT);
  pinMode(sw_10L, INPUT);
  pinMode(stopbutton, INPUT);


  //  Define Coffecup
  lcd.createChar(3, cup);
  
  // Start LCD
  lcd.begin(16, 2);

  // START BOOTLOADER
  bootloader();

  //  Set LCD to Defaults
  coffeeterror();
  lcddefaults();
  testleds();
  testrelais();
  
    
  // DISABLE KEYPAD DEFAULT

  digitalWrite(relais_lock, LOW);
}


void loop()
{
  selection();
}


void selection() {
  if (digitalRead(sw_Koffie) == LOW){
    digitalWrite(led_Koffie,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003   sw_Koffie  \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_Thee) == LOW){
    digitalWrite(led_Thee,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003    sw_Thee   \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_WarmWater) == LOW){
    digitalWrite(led_WarmWater,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003 sw_WarmWater \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_Afwas) == LOW){
    digitalWrite(led_Afwas,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003 sw_AfwasWater\003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_25L) == LOW){
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003  2.5 Liter   \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_50L) == LOW){
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003   5 Liter    \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
   else if (digitalRead(sw_75L) == LOW){
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003   7.5 Liter  \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(sw_10L) == LOW){
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003  10 Liter    \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
  }
  else if (digitalRead(stopbutton) == LOW){
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003 Stop button  \003");
    lcd.setCursor(0, 1);
    lcd.print("  Debugger OS   ");
    delay(2000);
    digitalWrite(led_Koffie,LOW);
    digitalWrite(led_Thee,LOW);
    digitalWrite(led_Afwas,LOW);
    digitalWrite(led_WarmWater,LOW);
    digitalWrite(relais_lock,LOW);
    lcddefaults();
  }
}

void bootloader() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("\003\003\003 PiXeLBar \003\003\003");
  lcd.setCursor(0, 1);
  lcd.print("  Koffiezetter  ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Debugger OS   ");
  lcd.setCursor(0, 1);
  lcd.print("  Made by Miep  ");
  delay(500);
}  

void testleds() {
  digitalWrite(led_Koffie,HIGH);
  digitalWrite(led_Thee,HIGH);
  digitalWrite(led_Afwas,HIGH);
  digitalWrite(led_WarmWater,HIGH);
  delay(500);
  digitalWrite(led_Koffie,LOW);
  digitalWrite(led_Thee,LOW);
  digitalWrite(led_Afwas,LOW);
  digitalWrite(led_WarmWater,LOW);
  delay(300); 
  digitalWrite(led_Koffie,HIGH);
  digitalWrite(led_Thee,HIGH);
  digitalWrite(led_Afwas,HIGH);
  digitalWrite(led_WarmWater,HIGH);
  delay(500);
  digitalWrite(led_Koffie,LOW);
  digitalWrite(led_Thee,LOW);
  digitalWrite(led_Afwas,LOW);
  digitalWrite(led_WarmWater,LOW);
}

void testrelais(){
  digitalWrite(relais_lock,LOW);
  delay(500);
  digitalWrite(relais_lock,HIGH);
  delay(500);
  digitalWrite(relais_lock,LOW);
  delay(500);
  digitalWrite(relais_lock,HIGH);
}

void coffeeterror(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("\003               ");
  lcd.setCursor(0, 1);
  lcd.print("               \003");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print(" \003              ");
  lcd.setCursor(0, 1);
  lcd.print("              \003 ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("  \003             ");
  lcd.setCursor(0, 1);
  lcd.print("             \003  ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("   \003            ");
  lcd.setCursor(0, 1);
  lcd.print("            \003   ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("    \003           ");
  lcd.setCursor(0, 1);
  lcd.print("           \003    ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("     \003          ");
  lcd.setCursor(0, 1);
  lcd.print("          \003     ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("      \003         ");
  lcd.setCursor(0, 1);
  lcd.print("         \003      ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("       \003        ");
  lcd.setCursor(0, 1);
  lcd.print("        \003       ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("        \003       ");
  lcd.setCursor(0, 1);
  lcd.print("       \003        ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("         \003      ");
  lcd.setCursor(0, 1);
  lcd.print("      \003         ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("          \003     ");
  lcd.setCursor(0, 1);
  lcd.print("     \003          ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("           \003    ");
  lcd.setCursor(0, 1);
  lcd.print("    \003           ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("            \003   ");
  lcd.setCursor(0, 1);
  lcd.print("   \003            ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("             \003  ");
  lcd.setCursor(0, 1);
  lcd.print("  \003             ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("              \003 ");
  lcd.setCursor(0, 1);
  lcd.print(" \003              ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("               \003");
  lcd.setCursor(0, 1);
  lcd.print("\003               ");
  delay(100);
}

void lcddefaults() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\003   PiXeLBar   \003");
  lcd.setCursor(0, 1);
  lcd.print("  Debugger OS  ");
}
