#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <math.h>
/*
This sketch receives strings from sending unit via nrf24 
and prints them out via serial.  The sketch waits until
it receives a specific value (2 in this case), then it 
prints the complete message and clears the message buffer.
*/
/* 40 lewo
 * 41 prawo
 * pwm 11 lewo
 * pwm 12 prawo
 * obrotnica lewo 28
 * obrotnica prawo 29
 * pierwszy gora 30
 * pierwszy dol 31
 * drugi gora 32
 * drugi dol 33
 * trzeci gora 34
 * trzeci dol 35
 * otworz 36
 * zamknij 37
 * pwm obrotnica 3
 * pwm pierwszy 4
 * pwm drugi 5
 * pwm trzeci 6
 * pwm lapka 7
 * 
 * oswietlenie 42
 * 
 * guziki
 * default    00001100000
 * lewy dol   10001100000
 * lewy gora  01001100000
 * prawy dol  00101100000
 * prawy gora 00011100000
 * lewy joy   00001000000
 * prawy joy  00000100000
 * guzik 1    00001110000
 * guzik 2    00001101000
 * guzik 3    00001100100
 * guzik 4    00001100010
 * guzik 5    00001100001
 * 
 * 
 * 
 * /
 */
int fail=0; //2 sekundy liczy do 20
int msgcounter=0;
int calcounter=3;
int msg[1];
int LNOISE=15;
int RNOISE=10;
int buttonval=0;
bool calib=false;
bool debug=false;
int RX=0;
int RY=0;
int LX=0;
int LY=0;
int S1=0;
int S2=0;
int S3=0;
int S4=0;

int ABSLX=0;
int ABSLY=0;
int ABSRX=0;
int ABSRY=0;
int RXcal=0;
int RYcal=0;
int LXcal=0;
int LYcal=0;

double PRIpower=0; //primary power
double angle;// joy angle
int LEFTpower=0;
int RIGHTpower=0;
bool LEFTback=false;
bool RIGHTback=false;
const float pi = 3.14;

int vals[14];
bool buttons[11];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int lastmsg = 1;
String theMessage = "";
void setup(void){
  Serial.begin(57600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  //podwozie
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  //lapka
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);  
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);  
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);  
  pinMode(42,OUTPUT);
  
  //lapka enable
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT);  


}
void loop(void){
  if (radio.available()){
    bool done = false;  
      done = radio.read(msg, 1); 
      char theChar = msg[0];
      if (msg[0] != 2){
        theMessage.concat(theChar);
        msgcounter++;
        }
      else 
      {Serial.print(" counter ");
        Serial.print(msgcounter);
            if(msgcounter==3*14){ fail=0;
             
             for (int i = 0; i < 14; i++) {
              vals[i]=theMessage.substring(3*i,3*i+3).toInt();
              // Serial.print(vals[i]);
             //  Serial.print(" ");
             
             }
             
             buttonval=vals[12]*10+vals[13]/100-1000;
             for (int licz=0;licz<11;licz++) buttons[licz]=((buttonval&(1<<licz))>0);
             /* guziki
 * default    00001100000
 * lewy dol   10001100000
 * lewy gora  01001100000
 * prawy dol  00101100000
 * prawy gora 00011100000
 * lewy joy   00001000000
 * prawy joy  00000100000
 * guzik 1    00001110000
 * guzik 2    00001101000
 * guzik 3    00001100100
 * guzik 4    00001100010
 * guzik 5    00001100001
 * */
              digitalWrite(32,LOW);digitalWrite(33,LOW);
              digitalWrite(34,LOW);digitalWrite(35,LOW);
              digitalWrite(36,LOW);digitalWrite(37,LOW);
              digitalWrite(38,LOW);digitalWrite(39,LOW);
             if (buttons[0]==1){digitalWrite(32,HIGH);}; //
             if (buttons[1]==1){digitalWrite(33,HIGH);}; //
             if (buttons[2]==1){digitalWrite(34,HIGH);}; //
             if (buttons[3]==1){digitalWrite(35,HIGH);}; //
             if (buttons[4]==0); //
             if (buttons[5]==0); //
             if (buttons[6]==1){digitalWrite(36,HIGH);}; //
             if (buttons[7]==1){digitalWrite(37,HIGH);}; //
             if (buttons[8]==1)digitalWrite(42,HIGH);; //
             if (buttons[9]==1)digitalWrite(42,LOW);; //
             if (buttons[10]==1) calib=false; //
             
             //Serial.println();
             theMessage= ""; 
             LX=(vals[5]-100)/2;
             LY=(612-vals[4])/2;
             RX=612-vals[7];
             RY=612-vals[6];
             S1=vals[0]-100;
             S2=vals[1]-100;
             S3=vals[2]-100;
             S4=vals[3]-100;
             
             if (calib==false)
             {
              if(calcounter==0){
             calib=true;
             LXcal=LX;
             LYcal=LY;
             RXcal=RX;
             RYcal=RY;
              }
              else
              calcounter--;
             }
             LX=LX-LXcal;
             LY=LY-LYcal;
             RX=RX-RXcal;
             RY=RY-RYcal;
             ABSLX=abs(LX);
             ABSLY=abs(LY);
             PRIpower=sqrt(LX*LX+LY*LY);
             angle=atan2(LX,LY);
             RIGHTpower=abs(PRIpower*cos(angle+pi/4))*(2*S3+512)/768;
             LEFTpower=abs(PRIpower*sin(angle+pi/4))*(2*S3+512)/768;


            if (LY>=ABSLX) {LEFTback=false; RIGHTback=false;} 
            if (LX>=ABSLY) {LEFTback=false; RIGHTback=true;} 
            if (0-LY>=ABSLX) {LEFTback=true; RIGHTback=true;} 
            if (0-LX>=ABSLY) {LEFTback=true; RIGHTback=false;}
            if (ABSLX<LNOISE) if (ABSLY<LNOISE) {LEFTback=false; RIGHTback=false; LEFTpower=0; RIGHTpower=0;}
      
             analogWrite(11, map(min(120,LEFTpower+1), 0, 120, 0 ,255)); //LEWO
             analogWrite(12, map(min(120,RIGHTpower+1), 0, 120, 0 ,255)); //PRAWO
             if(LEFTback==true) digitalWrite(40,HIGH); else digitalWrite(40,LOW);
             if(RIGHTback==true) digitalWrite(41,HIGH); else digitalWrite(41,LOW);

             analogWrite(3, map(min(170,abs(RX)+1), 0, 170, 0 ,100)); //LEFT_RIGHT
             digitalWrite(28,LOW);digitalWrite(29,LOW);
             if(RX>RNOISE)digitalWrite(28,HIGH); 
             if(RX<-RNOISE)digitalWrite(29,HIGH);
             
             analogWrite(4, map(min(170,abs(RY)+1), 0, 170, 0 ,250)); //UP-DOWN1
             digitalWrite(30,LOW);digitalWrite(31,LOW);
             if(RY>RNOISE)digitalWrite(30,HIGH); 
             if(RY<-RNOISE)digitalWrite(31,HIGH);

             analogWrite(5, map(min(511,abs(S4)+1), 0, 512, 0 ,100)); //UP-DOWN2
             analogWrite(6, map(min(511,abs(S1)+1), 0, 512, 0 ,140)); //UP-DOWN3
             analogWrite(7, map(min(511,abs(S2)+1), 0, 512, 0 ,120)); //open/close
             if (debug)
             {
              
              Serial.print(" LX ");
              Serial.print(LX);
              Serial.print(" LY ");
              Serial.print(LY);
              Serial.print(" RX ");
              Serial.print(RX);
              Serial.print(" RY ");
              Serial.print(RY);
              Serial.print(" Lp ");
              Serial.print(LEFTpower);
              Serial.print(" Rp ");
              Serial.print(RIGHTpower);
              Serial.print(" Lb ");
              Serial.print(LEFTback);
              Serial.print(" Rb ");
              Serial.print(RIGHTback);
              Serial.print(" ANGLE ");
              Serial.print(angle);
              Serial.print(" POWER ");
              Serial.print(PRIpower);
              Serial.print(" buttons ");
              

              for (int licz=0;licz<11;licz++)Serial.print(buttons[licz]);
              
             
              
              
              }
             Serial.println( " OK " );
            }
     msgcounter=0;
   }
  } else{
  //Serial.println("brak radia");
  delay(1);
  
  if( fail==200) {digitalWrite(32,LOW);digitalWrite(33,LOW);
              digitalWrite(34,LOW);digitalWrite(35,LOW);
              digitalWrite(36,LOW);digitalWrite(37,LOW);
              digitalWrite(38,LOW);digitalWrite(39,LOW);
              digitalWrite(30,LOW);digitalWrite(31,LOW);
              digitalWrite(28,LOW);digitalWrite(29,LOW);
              analogWrite(3, 0); //UP-DOWN
              analogWrite(4, 0); //UP-DOWN
              analogWrite(5, 0); //UP-DOWN
              analogWrite(6, 0); //UP-DOWN
              analogWrite(7, 0); //UP-DOWN
                  
              analogWrite(11,0); //LEWO
              analogWrite(12, 0); //PRAWO
              calcounter=3;
              } else fail=fail+1;}
  
}
