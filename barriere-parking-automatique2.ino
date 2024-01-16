#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo sm;
LiquidCrystal_I2C lcd1(0x27,16,2);
LiquidCrystal_I2C lcd2(0x26,16,2);
int serv=9;
int BP=13;
int ledR=6;
int ledO=5;
int ledV=4;
int trig=8;
int echo=7;
long distance;
long duree;
int D=0;
void setup() {
sm.attach(serv);
sm.write(0);
pinMode(BP,INPUT);
pinMode(ledR,OUTPUT);
pinMode(ledO,OUTPUT);
pinMode(ledV,OUTPUT);
Serial.begin(9600);
digitalWrite(ledR,HIGH);
digitalWrite(ledO,LOW);
digitalWrite(ledV,LOW);

lcd1.init();
lcd1.backlight();
lcd1.setCursor(0,0);
lcd1.print("Etat barriere");
lcd1.setCursor(0,1);
lcd1.print("Fermee");
lcd2.init();
lcd2.backlight();
lcd2.setCursor(0,0);
lcd2.print("DISTANCE ou Bp");
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
}
void loop(){ 
  digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
 duree=pulseIn(echo,HIGH);
distance=duree/58;
Serial.println(distance);
if((digitalRead(BP)==HIGH||distance<=20) &&D==0)
{
  if(digitalRead(BP)==LOW)
{ 
   lcd2.setCursor(0,1);
lcd2.print("            ");
  lcd2.setCursor(0,1);
lcd2.print(distance);
}
else 
{
   lcd2.setCursor(0,1);
lcd2.print("          ");
   lcd2.setCursor(0,1);
lcd2.print("boutton appui");

 }

  digitalWrite(ledR,LOW);
  digitalWrite(ledO,HIGH);
   lcd1.setCursor(0,1);
  lcd1.print("             ");
  lcd1.setCursor(0,1);
  lcd1.print("en cours ouv");
  for(int pos=0;pos<=90;pos++)
  {
    sm.write(pos);
    delay(30);
  }

  digitalWrite(ledO,LOW);
  digitalWrite(ledV,HIGH);
    lcd1.setCursor(0,1);
  lcd1.print("                ");
  lcd1.setCursor(0,1);
  lcd1.print("ouverte");
  D=1;
    
}
if((digitalRead(BP)==HIGH||distance>=30) && D==1)
{ 
    if(digitalRead(BP)==LOW)
{ 
   lcd2.setCursor(0,1);
lcd2.print("            ");
  lcd2.setCursor(0,1);
lcd2.print("aucun objet");
}
else 
{
   lcd2.setCursor(0,1);
lcd2.print("          ");
   lcd2.setCursor(0,1);
lcd2.print("boutton appui");
 }

  digitalWrite(ledV,LOW);
  digitalWrite(ledO,HIGH);
  lcd1.setCursor(0,1);
  lcd1.print("                ");
  lcd1.setCursor(0,1);
  lcd1.print("en cours fer");
  for(int pos=90;pos>=0;pos--)
  {
    sm.write(pos);
    delay(30);
  }

  digitalWrite(ledO,LOW);
  digitalWrite(ledR,HIGH);
    lcd1.setCursor(0,1);
  lcd1.print("                ");
  lcd1.setCursor(0,1);
  lcd1.print("fermee");
  D=0;
}
delay(1000);

}
