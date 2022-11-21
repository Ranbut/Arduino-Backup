#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
void setup()
{
  disp.clear();
  disp.brightness(7);  // яркость минимум =0, стандарт=2,  максимум=7)
}
void loop()
{
  rotation_all_sign(); // вращение по часовой стрелке всех символов
  rotation_one_sign(); // вращение символов по очереди слева на право
}
void rotation_all_sign()  // вращение по часовой стрелке всех символов
{
  disp.clear();
  disp.twistByte(buff, 100);
  delay(1000);
}
void rotation_one_sign()  // вращение символов по очереди слева на право
{
  for (uint8_t i = 0; i < 4; i++)
  {
    delay(100);
  }
}
