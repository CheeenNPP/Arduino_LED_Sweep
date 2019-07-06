int M_SDA = 4;
int M_RCK = 5;
int M_SCL = 6;
int M_CLR = 7;

#define HC595_RCK_H()   digitalWrite(M_RCK, HIGH);
#define HC595_RCK_L()   digitalWrite(M_RCK, LOW);

#define HC595_CLR_H()   digitalWrite(M_CLR, HIGH);
#define HC595_CLR_L()   digitalWrite(M_CLR, LOW);  

#define HC595_SCL_H()   digitalWrite(M_SCL, HIGH);
#define HC595_SCL_L()   digitalWrite(M_SCL, LOW); 

#define HC595_SDA_H()   digitalWrite(M_SDA, HIGH);
#define HC595_SDA_L()   digitalWrite(M_SDA, LOW); 

int LED_1 = 9;
int LED_2 = 10;
int LED_3 = 11;
int LED_4 = 12;

#define LED_1_ON()   digitalWrite(LED_1, HIGH); 
#define LED_1_OFF()  digitalWrite(LED_1, LOW);

#define LED_2_ON()   digitalWrite(LED_2, HIGH); 
#define LED_2_OFF()  digitalWrite(LED_2, LOW);

#define LED_3_ON()   digitalWrite(LED_3, HIGH); 
#define LED_3_OFF()  digitalWrite(LED_3, LOW);

#define LED_4_ON()   digitalWrite(LED_4, HIGH); 
#define LED_4_OFF()  digitalWrite(LED_4, LOW);

#define LED_Sweep_Time 4

int LED_Code_Positive[] =
{
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e    
} ;

void setup()
{
    LED_Init();
    HC595_Init();

    Serial.begin(9600);
}

void loop()
{
/*
  String inputbuf = "";
  int serialFlag = 0;
  int i = 0;
  int cnt = 0;
  
  while (Serial.available() > 0) 
  {
    serialFlag = 1;
    inputbuf += char(Serial.read());
    cnt++;
    delay(1);
  }  

  for (i = 0; i < cnt; i++)
  {
        LED_Display(inputbuf[i], 1);
        delay(LED_Sweep_Time);
        LED_Display(inputbuf[i], 2);
        delay(LED_Sweep_Time);
        LED_Display(inputbuf[i], 3);
        delay(LED_Sweep_Time);
        LED_Display(inputbuf[i], 4);
        delay(LED_Sweep_Time);
        delay(200);  
  }
*/
        LED_Display('8', 1);
        LED_Display('0', 2);
        LED_Display('1', 3);
        LED_Display('0', 4);
}

void LED_Init()
{
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);

}

void LED_Clear()
{
  LED_1_OFF(); 
  LED_2_OFF();
  LED_3_OFF();
  LED_4_OFF();
}

void LED_Display(char data, int n)
{
    delay(LED_Sweep_Time);
    
    switch  (n)
    {
      case 1:    LED_Clear();
                 LED_1_ON();
        break; 
      case 2:    LED_Clear();
                 LED_2_ON();
        break; 
      case 3:    LED_Clear();
                 LED_3_ON();
        break; 
      case 4:    LED_Clear();
                 LED_4_ON();
        break; 
      default:
        break;
        
    }
    switch  (data)
    {
      case '0':  HC595_WriteByte(LED_Code_Positive[0]);
        break;
      case '1':  HC595_WriteByte(LED_Code_Positive[1]);
        break;
      case '2':  HC595_WriteByte(LED_Code_Positive[2]);
        break;
      case '3':  HC595_WriteByte(LED_Code_Positive[3]);
        break;
      case '4':  HC595_WriteByte(LED_Code_Positive[4]);
        break;
      case '5':  HC595_WriteByte(LED_Code_Positive[5]);
        break;
      case '6':  HC595_WriteByte(LED_Code_Positive[6]);
        break;
      case '7':  HC595_WriteByte(LED_Code_Positive[7]);
        break;
      case '8':  HC595_WriteByte(LED_Code_Positive[8]);
        break;
      case '9':  HC595_WriteByte(LED_Code_Positive[9]);
        break;
      case 'A':  HC595_WriteByte(LED_Code_Positive[10]);
        break;
      case 'B':  HC595_WriteByte(LED_Code_Positive[11]);
        break;
      case 'C':  HC595_WriteByte(LED_Code_Positive[12]);
        break;
      case 'D':  HC595_WriteByte(LED_Code_Positive[13]);
        break;
      case 'E':  HC595_WriteByte(LED_Code_Positive[14]);
        break;
      case 'F':  HC595_WriteByte(LED_Code_Positive[15]);
        break;
      default:  
        break;
    }


}

void HC595_Delay(uint32_t t)
{
  while(t--)  for(uint8_t i = 0; i < 10; i++);
}

void HC595_Init()
{
    pinMode(M_SDA, OUTPUT);
    pinMode(M_RCK, OUTPUT);
    pinMode(M_SCL, OUTPUT);
    pinMode(M_CLR, OUTPUT);


  HC595_CLR_L();  //CLR(Pin_10)低电平时将移位寄存器数据清零
  delay(10);
  HC595_CLR_H();
  
  HC595_SCL_H();
  HC595_SDA_L();
  
  HC595_RCK_H();  //RCK(Pin_12)上升沿移位寄存器数据进入存储寄存器

}

void HC595_WriteByte(int data)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    if((data << i) & 0x80)
    {
      HC595_SDA_H();
    }
    else
    {
      HC595_SDA_L();
    }
    
    HC595_SCL_L();
    HC595_Delay(1);
    HC595_SCL_H();
    HC595_Delay(1);
    
  }
  
  HC595_RCK_L();
  HC595_Delay(1);
  HC595_RCK_H();

}
