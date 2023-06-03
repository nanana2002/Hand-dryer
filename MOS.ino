#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//LCD屏幕初始化
int LED=7;
int BEE=6;
int GET=9;//电平接收脚
int data=1,disp=0,i,j,re;//data为9脚接收到的电平，disp为发送的字符在mosdecode中的序号，ij为for循环中计数用，re为发送数据对应的mosdecode
int decodeElement[5]={0,0,0,0,0};//用来接收摩斯电码
int digit[5];//用来放发送的数据对应的mosdecode的每一位
char readchar;//串口发送的数据
bool receive,flag=1,f;//标志位
unsigned long code;//接收的摩斯电码
const char mos[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};//明码
unsigned long mosdecode[]={12333,21113,21213,21133,13333,11213,
                          22133,1113,11333,12223,21233,12113,
                          22333,21333,22233,12213,22123,12133,
                          11133,23333,11233,11123,1223,21123,21223,22113,
                          22222,12222,11222,11122,11112,11111,
                          21111,22111,22211,22221,33333};//密码

void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(LED,OUTPUT);
pinMode(BEE,OUTPUT);
pinMode(GET,INPUT_PULLUP);
}

void loop() {
  readchar=Serial.read(); //从串口发送数据
  //readchar='C';//仿真中没有串口，模拟串口
  disp=readchar>57?readchar-65:readchar-22;//计算需要发送的数据的序号
  delay(500);

  while(disp>=0&disp<37){//当序号是有效的时候，进入发送环节
    lcd.print("send");
    delay(1000);
    lcd.clear();
    lcd.print("readchar=");
    lcd.print(readchar);//打印明码
    delay(1000);
    lcd.clear();
  
    lcd.print("disp=");//打印序号
    lcd.print(disp);
    delay(1000);
    lcd.clear();
  
    re=mosdecode[disp];//打印对应密码
    lcd.print("re=");
    lcd.print(re);
    delay(1000);
    lcd.clear();
  
    for(i=4;i>=0;i--){
      lcd.print("i=");
      lcd.print(i);
      digit[i]=re%10;//一位位取出密码
      re=re/10;     
      // lcd.print(digit[i]);
      // delay(1000);
      lcd.clear();
    }

    lcd.print("begin");

    for(j=0;j<5;j++) {
      switch(digit[j]){
        case 1:lcd.print(digit[j]);digitalWrite(LED,HIGH);tone(BEE,20,1000);delay(1000);digitalWrite(LED,LOW);noTone(BEE);delay(500);break;//蜂鸣器响1s，小灯亮1s
        case 2:lcd.print(digit[j]);digitalWrite(LED,HIGH);tone(BEE,20,2000);delay(2000);digitalWrite(LED,LOW);noTone(BEE);delay(500);break;//蜂鸣器响2s，小灯亮2s
        case 3:lcd.print(digit[j]);delay(500);digitalWrite(LED,LOW);disp=10086;lcd.clear();break;//3是为了补齐所有mosdecode加入的无意义数
        default:lcd.print(digit[j]);delay(500);digitalWrite(LED,LOW);disp=10086;lcd.clear();break;
      }
    }
    tone(6,200,100);//短促蜂鸣器响，以示结束
    delay(100);
    noTone(6);
  }
  while(disp<0||disp>36){//输入字符非法时，默认回到第36位33333
    digitalWrite(LED,LOW);
    disp=36;
  }

data=digitalRead(GET);//循环扫描输入口
receive=((data==0)||(decodeElement[0]!=0));//如果开始输入，或者已经接收到值，receive=1
// lcd.print(disp);//调试用
// lcd.print(data);
// lcd.print(decodeElement[0]);
// lcd.print(receive);
delay(1000);

while(receive){
  lcd.print("receive");
  delay(1000);
  lcd.clear();
  for(j=0;j<5;j++){
    //  lcd.print("come in");
    while(1){//目的是让没有输入数据时，j不自增，停在循环中等下一个电平信号输入
      i=0;
      data=digitalRead(GET);
      flag=(i==0)&(data==0);
    //  lcd.print(i);
    //  lcd.print(data);
    // lcd.print(flag);
    //  lcd.print("come in");
      delay(1000);
      if(flag==1)break;
      lcd.clear();
    }
    //  lcd.clear();
    //  lcd.print("out");
    while(flag==1){//每接收到一个低电平，i加一，蜂鸣器响一下，
      tone(BEE,20,1000);
      i++;
      lcd.print(i);
      delay(500);
      lcd.print(data);
      delay(1000);
      noTone(BEE);
      data=digitalRead(GET);
      data==0?flag=1:flag=0;
      lcd.print(flag);
    }
    
    flag=0;
    //将输入的低电平数存入decodeElement
    switch(i){
      case 1:decodeElement[j]=1;lcd.print("FA");lcd.print("j=");lcd.print(j);lcd.print(decodeElement[j]);delay(1000);lcd.clear();break;
      case 2:decodeElement[j]=2;lcd.print("FA");lcd.print("j=");lcd.print(j);lcd.print(decodeElement[j]);delay(1000);lcd.clear();break;
      case 3:decodeElement[j]=3;lcd.print("FA");lcd.print("j=");lcd.print(j);lcd.print(decodeElement[j]);delay(1000);lcd.clear();break;
    }

  }
  break;
}

  while(decodeElement[4]!=0){
    //lcd.print("MA");
    code=0;
    for(j=0;j<5;j++){
    //lcd.print(decodeElement[j]);
    code=code*10+decodeElement[j];//计算输入的密码
    //Serial.print(decodeElement[j]);
    decodeElement[j]=0;      
  }

  lcd.print("code=");
  lcd.print(code);
  delay(2000);
  lcd.clear();
  f=0;
  while(code!=0){
    for(i=0;i<37;i++){
      while(mosdecode[i]==code){ //遍历寻找对应的明码并输出
      f=1;
      lcd.print(mos[i]);
      break;
      }
   }
  code=0;
  f==1?lcd.print("yes"):lcd.print("no");//如果输入的密码并不能找到对应明文，则显示no
  }
  delay(2000);
  lcd.clear();
}
}
