#include <Joystick.h>
#include <RotaryEncoder.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  11, 0,
  false, true, false,
  false, false, false,
  false, false,
  false, false, false);

RotaryEncoder encoder(8, 7);

int newPos = 0;
static int Pos = 0;

void setup()
{
  Joystick.begin();
  Joystick.setYAxisRange(-15, 15);
}

void loop() 
{
  encoder.tick();
  newPos = encoder.getPosition();
  Joystick.setYAxis(Pos);
  }
