/**
 *  A library to controll the TB6612FNG Toshiba H-bridge
 * The pins must be connected accordingly (see the datasheet of the H-bridge).
    -the PWM pins must support PWM on the Arduino
    -the enable pin on the H-bridge should be connected either to 5V
     or to a pin on the Arduino, which is set to HIGH, for the H-bridge to function
 * Original code by shrajtofle@gmail.com.
 * Modified by Alex Sokolsky asokolsky@yahoo.com 4/2015
 */
#ifndef TB6612FNG_h
#define TB6612FNG_h
 
class DCMotor 
{

public:
  /** IN1, IN2, PWM */
  DCMotor(byte pinCW, byte pinCCW, byte pinPWM);

  /** start rotation at the rate of m_speed in m_bDirectionCW */
  void go();
  /** stops rotation */
  void stop();
  /** executes short break */
  void shortBreak();
   
  /** set the speed is in 0%...100% and start rotation */
  void setSpeed(boolean bCW, byte speed);
  /** are we spinning? */ 
  boolean isGoing() 
  {
    return m_bGoing;
  }

#ifdef DEBUG
  void DUMP(const char *szText = 0) const;
#else
  void DUMP(const char *szText = 0) {}
#endif
  
   
private:
  byte m_pinCW;  // a.k.a. IN1
  byte m_pinCCW; // a.k.a. IN2
  byte m_pinPWM;
   
  boolean m_bGoing = false;
  boolean m_bDirectionCW = true;
  byte m_speed = 255;
};

#endif

