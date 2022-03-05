#define BLINKER_WIFI
#define BLINKER_PRINT Serial
#define BLINKER_ALIGENIE_OUTLET
#include <Blinker.h>

char auth[] = "**********";
char ssid[] = "**********";
char pswd[] = "**********";

bool oState = false;

// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc");

int counter = 0;

//天猫精灵回调函数
void aligeniePowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(0, HIGH);
        Blinker.delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        Blinker.delay(200);
        digitalWrite(LED_BUILTIN, HIGH);
        Blinker.delay(200);
        digitalWrite(0, LOW);
        BlinkerAliGenie.powerState("on");
        BlinkerAliGenie.print();

        oState = true;
    }
}

// 天猫精灵支持函数
void aligenieQuery(int32_t queryCode)
{
    BLINKER_LOG("AliGenie Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("AliGenie Query All");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("AliGenie Query Power State");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        default :
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
    }
}

// 按键回调函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(0, HIGH);
    Blinker.delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    Blinker.delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    Blinker.delay(200);
    digitalWrite(0, LOW);
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    Blinker.vibrate();
    counter++;
    Number1.print(counter);
    uint32_t BlinkerTime = millis();
    Blinker.print(BlinkerTime);
    Blinker.print("millis", BlinkerTime);
}

void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);

    // 天猫精灵初始化选项
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    BlinkerAliGenie.attachPowerState(aligeniePowerState);
    BlinkerAliGenie.attachQuery(aligenieQuery);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  Blinker.run();
}
