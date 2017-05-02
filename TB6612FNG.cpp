#include <Arduino.h>
#include "Trace.h"
#include "TB6612FNG.h"

DCMotor::DCMotor(byte pinCW, byte pinCCW, byte pinPWM) :
  m_pinCW(pinCW), m_pinCCW(pinCCW), m_pinPWM(pinPWM)
{ 
  pinMode(m_pinCW, OUTPUT);
  pinMode(m_pinCCW, OUTPUT);
  pinMode(m_pinPWM, OUTPUT);
}

#ifdef DEBUG
void DCMotor::DUMP(const char *szText /*= 0*/) const
{
  if(szText != 0) {
    DEBUG_PRNT(szText);
  }
  DEBUG_PRINT(" DCMotorTB6612FNG@"); DEBUG_PRINTDEC((int)this); 
  
  DEBUG_PRINT(" m_pinCW="); DEBUG_PRINTDEC((int)m_pinCW);
  DEBUG_PRINT(" m_pinCCW="); DEBUG_PRINTDEC((int)m_pinCCW);
  DEBUG_PRINT(" m_pinPWM="); DEBUG_PRINTDEC((int)m_pinPWM);

  DEBUG_PRINT(" m_bGoing="); DEBUG_PRINTDEC((int)m_bGoing);
  DEBUG_PRINT(" m_bDirectionCW="); DEBUG_PRINTDEC((int)m_bDirectionCW);
  DEBUG_PRINT(" m_speed="); DEBUG_PRINTDEC((int)m_speed);

   
  DEBUG_PRINTLN("");
}
#endif


void DCMotor::go() 
{
  DUMP("DCMotor::go(");

  digitalWrite(m_pinCW,  m_bDirectionCW ? HIGH : LOW);
  digitalWrite(m_pinCCW, m_bDirectionCW ? LOW : HIGH);
  analogWrite(m_pinPWM, m_speed);
  m_bGoing = true;
}

void DCMotor::stop() 
{
  DUMP("DCMotor::stop()");
  digitalWrite(m_pinCW, LOW);
  digitalWrite(m_pinCCW, LOW);
  analogWrite(m_pinPWM, HIGH);
  m_bGoing = false;
}

void DCMotor::shortBreak() 
{
  DUMP("DCMotor::shortBreak()");
  digitalWrite(m_pinCW, HIGH);
  digitalWrite(m_pinCCW, HIGH);
  analogWrite(m_pinPWM, LOW);
  m_bGoing = true;
}

/*void DCMotor::setSpeedRegulation(byte speedRegulation) 
{
  m_speedRegulation = speedRegulation;
  if(m_bGoing)
    go();
}*/

void DCMotor::setSpeed(boolean bCW, byte speed) 
{
  DEBUG_PRINT("DCMotor::setSpeed bCW="); DEBUG_PRINTDEC(bCW);  DEBUG_PRINT(" speed=");  DEBUG_PRINTDEC(speed);  DEBUG_PRINTLN("");
  
  m_bDirectionCW = bCW;
  m_speed = map(speed, 0, 100, 0, 255);
  go();
}


