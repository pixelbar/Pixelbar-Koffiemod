// Koffiezettermod Version 2.0.1 Beta ( Pre Stable Release )
//
// The whole source code has been rechecked and allmost completely rewritten and re-assambled just to make it quicker, and to make it compatible with an Arduino Mega 2560
// Since this Arduino had so much I/O busses that the whole multiplexing became unnessecarry
//

#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
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
#define stopbutton        4

#define timeout           10000

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

// SET INTEGERS

int loopcount = 0;
int liter = 0;
int select = 0;
int nummer;
char tosend[68];
int canmake = 0;

// INITIALIZATION

// Initialize LCD

LiquidCrystal lcd(33, 30, 35, 32, 37 ,34);

// Initialize Ethernet

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x30, 0x5A };
byte ip[] = { 172,24,1,253 };
byte server[] = { 172,24,1,2 };
byte subnet[] = { 255,255,255,0 };

EthernetClient client;

void setup()
{

  Ethernet.begin(mac, ip, subnet);
  delay(1000);

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
  
  attachInterrupt(stopbutton, StopProduce, LOW);
  interrupts();

  // DISABLE KEYPAD DEFAULT

  digitalWrite(relais_lock, HIGH);

  //  Define Coffecup
  lcd.createChar(3, cup);
  
  // Start LCD
  lcd.begin(16, 2);

  // START BOOTLOADER
  bootloader();

  //  Set LCD to Defaults
  lcddefaults();

}


void loop()
{
  selection();

  delay(10);
  loopcount++;

  if (loopcount == 6000) {
    quote();
  }
  if (loopcount == 6500) {
    lcddefaults();
  }
  if (loopcount == 12000) {
    loopcount = 0;
    lcddefaults();
  }
}


void selection() {
  canmake=0;
  select=0;
  if (digitalRead(sw_Koffie) == LOW){
    digitalWrite(led_Koffie,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003   Koffie     \003");
    lcd.setCursor(0, 1);
    lcd.print("Selecteer Liters");
    select=1;
  }
  else if (digitalRead(sw_Thee) == LOW){
    digitalWrite(led_Thee,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003    Thee      \003");
    lcd.setCursor(0, 1);
    lcd.print("Selecteer Liters");
    select=2;
  }
  else if (digitalRead(sw_WarmWater) == LOW){
    digitalWrite(led_WarmWater,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003 Warm Water   \003");
    lcd.setCursor(0, 1);
    lcd.print("Selecteer Liters");
    select=3;
  }
  else if (digitalRead(sw_Afwas) == LOW){
    digitalWrite(led_Afwas,HIGH);
    digitalWrite(relais_lock,LOW);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\003 Afwas Water  \003");
    lcd.setCursor(0, 1);
    lcd.print("Selecteer Liters");
    select=4;
  }

  if (select > 0){
    liter = 0;
    long _start=millis();
    while (millis()-_start < timeout){
      if (digitalRead(sw_25L) == LOW){
        lcd.setCursor(0, 1);
        lcd.print("   2.5 Liter    ");
        liter = 1;
        _start = 0;
      }
      else if (digitalRead(sw_50L) == LOW){
        lcd.setCursor(0, 1);
        lcd.print("    5 Liter     ");
        liter = 2;
        _start = 0;
      }
      else if (digitalRead(sw_75L) == LOW){
        lcd.setCursor(0, 1);
        lcd.print("   7.5 Liter    ");
        liter = 3;
        _start = 0;
      }
      else if (digitalRead(sw_10L) == LOW){
        lcd.setCursor(0, 1);
        lcd.print("    10 Liter    ");
        liter = 4;
        _start = 0;
      }
    }
    
    if (liter > 0){
      switch(liter){
      case 1:
        digitalWrite(relais_lock,HIGH);
        eth_update();
        lcdprogressbar(150000);
        prodcompleted();
        break;
      case 2:
        digitalWrite(relais_lock,HIGH);
        eth_update();
        lcdprogressbar(300000);
        prodcompleted();
        break;
      case 3:
        digitalWrite(relais_lock,HIGH);
        eth_update();
        lcdprogressbar(450000);
        prodcompleted();
        break;
      case 4:
        digitalWrite(relais_lock,HIGH);
        eth_update();
        lcdprogressbar(600000);
        prodcompleted();
        break;
      }
    }
    digitalWrite(led_Koffie,LOW);
    digitalWrite(led_Thee,LOW);
    digitalWrite(led_WarmWater,LOW);
    digitalWrite(led_Afwas,LOW);
    digitalWrite(relais_lock,HIGH);

    lcddefaults();
  }
}

void eth_update() {
    Serial.println(client.status(),DEC);
    if (client.connect(server, 80)) {
        sprintf(tosend, "GET /CoffeeCounter/index.php?Quantity=%d&Product=%d&Token=34789650234", select, liter);
        client.println(tosend);
        client.println();
        client.stop();
    }
    delay(500); 
} 

void bootloader() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Illuzion    ");
  lcd.setCursor(0, 1);
  lcd.print("  Koffiezetter  ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Made by :   ");
  lcd.setCursor(0, 1);
  lcd.print("   PiXeLBar  &  ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("    Bitlair     ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Please Enjoy  ");
  lcd.setCursor(0, 1);
  lcd.print("  Teh Coffeez!  ");
  delay(800);
  lcd.clear();
  delay(500);
}  

void lcddefaults() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\003   PiXeLBar   \003");
  lcd.setCursor(0, 1);
  lcd.print(" Maak een keuze ");
}

void lcdprogressbar(long ms){
 
  lcd.setCursor(0, 1);
  lcd.print("[              ]");
  lcd.setCursor(1, 1);
  for(int i = 1; i < 15; i++){
    if(canmake == 0 ){
    delay(ms/14);
    lcd.print("\003");
  }
  }
}

void prodcompleted() {
  for(int i = 1; i < 5; i++) {
    lcd.setCursor(0, 1);
    lcd.print("/003   Bereiding  /003");
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("/003   Voltooid   /003");
    delay(200);
  }
}

void quote() {
    nummer = random(9);
    switch(nummer) {
        case 0:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Is het nog geen ");
            lcd.setCursor(0, 1);
            lcd.print(" tijd voor bier ");
        break;
        case 1:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lekker bakkie ? ");
            lcd.setCursor(0, 1);
            lcd.print("Of wil je thee ?");
        break;
        case 2:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" Hiekie Faalt ! ");
            lcd.setCursor(0, 1);
            lcd.print(" FAAL FAAL FAAL ");
        break;
        case 3:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Live nyan feed :");
            lcd.setCursor(0, 1);
            lcd.print(" NYAN NYAN NYAN ");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("N NYAN NYAN NYAN");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("AN NYAN NYAN NYA");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("YAN NYAN NYAN NY");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("NYAN NYAN NYAN N");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print(" NYAN NYAN NYAN ");
        break;
        case 4:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Als je dit leest");
            lcd.setCursor(0, 1);
            lcd.print(" Ik wil koffie! ");
        break;
        case 5:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" Windows is kut ");
            lcd.setCursor(0, 1);
            lcd.print(" Ik wil LINUX!  ");
        break;
        case 6:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nu je hier toch ");
            lcd.setCursor(0, 1);
            lcd.print("bent,zet koffie!");
        break;
        case 7:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   Voor stats : ");
            lcd.setCursor(0, 1);
            lcd.print("koffie.illuzion.");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("offie.illuzion.l");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("ffie.illuzion.la");
            delay(400);
            lcd.setCursor(0, 1);
            lcd.print("fie.illuzion.lan");
        break;
        case 8:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" Trolololololol ");
            lcd.setCursor(0, 1);
            lcd.print(" U iz Trolled!! ");
        break;
        case 9:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Like this mod ? ");
            lcd.setCursor(0, 1);
            lcd.print("wiki.pixelbar.nl");
        break;

        default:
        break;
    }
}

void StopProduce() {
  if(canmake == 0) {
      select = 5;
      liter = 5;
      eth_update();
  }
  canmake=1;
  lcd.clear();
  digitalWrite(relais_lock,HIGH);
  lcd.setCursor(0, 0);
  lcd.print(" What The FUCK! ");
  lcd.setCursor(0, 1);
  lcd.print("  Fatal FAAL!!  ");
  delay(75000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Productie    ");
  lcd.setCursor(0, 1);
  lcd.print("  Geannuleerd   ");
  delay(30000);
  //  Set LCD to Defaults
  lcddefaults();
  }
