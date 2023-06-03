int LED=7;
int BEE=6;
int GET=9;

//int mos[]=[A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,1,2,3,4,5,6,7,8,9,0];
//int mosdecode[]=[01222,10002,10102,10022,02222,00102,11022,00002,00222,01112,10122,01002,11222,
                //10222,11122,01102,11012,01022,00022,12222,00122,00012,01122,10012,10112,11002,
                //01111,00111,00011,00001,00000,10000,11000,11100,11110,11111];

void setup() {
  // put your setup code here, to run once:

serial.begin(9600);
pinMode(LED,OUTPUT);
pinMode(BEE,OUTPUT);
PINMODE(GET,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);

}
