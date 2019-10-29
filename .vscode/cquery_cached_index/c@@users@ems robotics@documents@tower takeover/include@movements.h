#pragma once
#include "main.h"

namespace Movement{

  //void powerDrive(int leftF, int leftR, int rightF, int rightR);
  void m_move_velocity(int time, int speed);
  void m_move_degrees(int distance, int speed);
  void m_async(int distance, int speed);
  void m_turn_up(int distance, int speed);
  void m_slide_up(int distance, int speed);
  void m_move_sin(double distance, double speed, double distance_sustained_speed);
  void m_delay(int n_delay);
  void dr4b_move(double degrees, int speed);
  void dr4b_claw(double degrees);
  void claw(int speed);
  void move_cm(double distance, double speed, double distance_sustained_speed);

  //This needs to be fixed.
  //void alignUltrasonic(int rotateVelocity = 50, int threshold = 0, int delayTime = 5);
  //void alignAlternate(float rotateVelocity = 25, int threshold = 3, int delayTime = 5);
  //void alignTime(int rotateVelocity = 25, int time = 0, int delayTime = 5);

  //void slideAlign(int distance);
}
