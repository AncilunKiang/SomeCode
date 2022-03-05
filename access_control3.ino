#include <SPI.h>
#include <RFID.h>
#include <Servo.h>

Servo myservo;//创建舵机
RFID rfid(10,9);//创建RC522模块 D10-SDA D13-SCK D11-MOSI D12-MISO D9-RST
int ESP = 7;//esp8266-01s信号接收口(GPIO 0)

void setup()
{
  Serial.begin(9600);//设置波特率为9600
  SPI.begin();//SPI总线初始化
  rfid.init();//RC522模块初始化
  myservo.attach(8);//设置舵机接口为D8
  myservo.write(0);//舵机初始化0度
  pinMode(ESP, INPUT);//设置ESP为输入模式
  delay(5000);
}

void ESP_control()
{//esp8266模块控制
  if(digitalRead(ESP)==1)
  {
    delay(100);
    if(digitalRead(ESP)==1)
    {
      myservo.write(180);
      delay(5000);
      myservo.write(0);
    }
  }
}

void RC_control()
{//IC识别模块控制
  //找卡
  if(rfid.isCard()){
    Serial.println("Find the card!");
    //读取卡序列号
    if (rfid.readCardSerial())
    {
      Serial.print("your card id is   : ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(" , ");
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(" , ");
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(" , ");
      Serial.print(rfid.serNum[3],HEX);
      Serial.println(" ");
      if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0**B&&rfid.serNum[3]==0x***)//判断函数
      {
        Serial.println("Welcome ***！");
        myservo.write(180);
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else if(rfid.serNum[0]==0x**&&rfid.serNum[1]==0x**&&rfid.serNum[2]==0x**&&rfid.serNum[3]==0x**)
      {
        Serial.println("Welcome ***！");
        myservo.write(180); 
        delay(5000);
      }
      else
      {
        Serial.println("非法卡"); 
      }
      myservo.write(0); 
      Serial.println("closed");
      }
  }
}

void loop()
{
  RC_control();//RC522模块
  ESP_control();//ESP8266模块
}
