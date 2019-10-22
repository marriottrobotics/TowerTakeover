#include "Movements.h"
#include <iostream>
#include <math.h>

ADIAnalogIn auto_select(2);
pros::ADIAnalogIn sensor (1);
Controller master(CONTROLLER_MASTER);
Motor left_front(1, mtr_s_n);
Motor right_front(10, mtr_s_p);
Motor left_back(11, mtr_s_p);
Motor right_back(20, mtr_s_n);
Motor dr4b_left(15, torque_p);
Motor dr4b_right(12, torque_n);
Motor claw_pivot(17,torque_p);
Motor claw(14, torque_p);

extern bool s_side; //true = red
extern bool s_pos; //true = mat side
bool s_side;
bool s_pos;
extern bool m_clawrot = NULL;

//bool Movement::red = false;
//bool Movement::top = false;

void Movement::m_move_velocity(int time, int speed){
  left_front.move_velocity(speed);
  right_front.move_velocity(speed);
  left_back.move_velocity(speed);
  right_back.move_velocity(speed);
  delay(time);
}

void Movement::m_move_degrees(int distance, int speed){
  left_front.move_relative(distance, speed);
  right_front.move_relative(distance, speed);
  left_back.move_relative(distance, speed);
  right_back.move_relative(distance, speed);
  while(abs(right_front.get_position()-right_front.get_target_position()) >= 10 || abs(right_front.get_position()-right_front.get_target_position()) >= 10
    || abs(left_front.get_position()-left_front.get_target_position()) >= 10 || abs(left_back.get_position()-left_back.get_target_position()) >= 10){
    //Do nothing
    delay(1);
  }
}

void Movement::m_async(int distance, int speed){
  left_front.move_relative(distance, speed);
  left_back.move_relative(distance, speed);
  right_front.move_relative(distance, speed);
  right_back.move_relative(distance, speed);
}

void Movement::m_turn_up(int distance, int speed){
    if(s_side){
      left_front.move_relative(-distance, speed);
      left_back.move_relative(-distance, speed);
      right_front.move_relative(distance, speed);
      right_back.move_relative(distance, speed);
    }else{
      left_front.move_relative(distance, speed);
      left_back.move_relative(distance, speed);
      right_front.move_relative(-distance, speed);
      right_back.move_relative(-distance, speed);
    }
    while(abs(right_back.get_position()-right_back.get_target_position()) >= 10){
      update_shit();
      //Do nothing
      delay(20);
    }
}

void Movement::m_slide_up(int distance, int speed){
    if(s_side){
      left_front.move_relative(distance, speed);
      left_back.move_relative(-distance, speed);
      right_front.move_relative(-distance, speed);
      right_back.move_relative(distance, speed);
    }else{
      left_front.move_relative(-distance, speed);
      left_back.move_relative(distance, speed);
      right_front.move_relative(distance, speed);
      right_back.move_relative(-distance, speed);
    }
    while(abs(right_back.get_position()-right_back.get_target_position()) >= 10){
      //Do nothing
      update_shit();
      delay(20);
    }

}
    void Movement::m_move_sin(double distance, double speed, double distance_sustained_speed) {
      //Tune System
      int tolerance = 10;
      int accuracy = 5;

      double accel_rtio = speed / ((abs(distance) - distance_sustained_speed) / 2);
      float accel_duration = (abs(distance) - distance_sustained_speed) / 2;
      float left_front_spos;
      double sin_speed;
      bool direction;
      //get direction of movement
      if(distance > 0){
        direction = true;
      } else {
        direction = false;
      }

      //starting pos
      left_front_spos = left_front.get_position();

      left_front.set_brake_mode(MOTOR_BRAKE_HOLD);
      right_front.set_brake_mode(MOTOR_BRAKE_HOLD);
      left_back.set_brake_mode(MOTOR_BRAKE_HOLD);
      right_back.set_brake_mode(MOTOR_BRAKE_HOLD);

      if(direction == true){
      while((left_front.get_position() + accuracy) < distance + left_front_spos){
//forwards
        int current_pos = left_front.get_position() - left_front_spos;
        if(current_pos < accel_duration){
          sin_speed = accel_rtio * current_pos;
        } else if(((current_pos - distance) * -1) < accel_duration){
          sin_speed = accel_rtio * ((current_pos - distance) * -1);
        } else {
          sin_speed = speed;
        }

        sin_speed = sin_speed * (0.5 * sin(3.14159 * (sin_speed/speed) - 1.5708) + 0.5);

        if(sin_speed < tolerance){
          sin_speed = tolerance;
        } else {
          //do nothing
        }
        left_front.move_velocity(sin_speed);
        right_front.move_velocity(sin_speed);
        left_back.move_velocity(sin_speed);
        right_back.move_velocity(sin_speed);
        delay(20);
        update_shit();
      }
    } else {
//backwards
      while((left_front.get_position() - accuracy) > distance + left_front_spos){

        int current_pos = left_front.get_position() - left_front_spos;
        if(abs(current_pos) < accel_duration){
          sin_speed = accel_rtio * abs(current_pos);
        } else if((current_pos - distance) < accel_duration){
          sin_speed = accel_rtio * (current_pos - distance);
        } else {
          sin_speed = speed;
        }

        sin_speed = sin_speed * (0.5 * sin(3.14159 * (sin_speed/speed) - 1.5708) + 0.5);

        if(sin_speed < tolerance){
          sin_speed = tolerance;
        } else {
          //do nothing
        }

        left_front.move_velocity(-sin_speed);
        right_front.move_velocity(-sin_speed);
        left_back.move_velocity(-sin_speed);
        right_back.move_velocity(-sin_speed);
        delay(20);
        update_shit();
      }
    }
    left_front.move_velocity(0);
    right_front.move_velocity(0);
    left_back.move_velocity(0);
    right_back.move_velocity(0);

}

void Movement::m_delay(int n_delay){
  for(int i = 0; i < n_delay / 20; i++)
  {
    //code here
    Movement::update_shit();
    delay(20);
  }
}

void Movement::update_shit(){
  float lerp = 26;
  if(m_clawrot){
    cout << "TRUE " << "\n";
  } else {
    cout << "False " << "\n";
  }
  cout << "mtr: " << claw_pivot.get_target_velocity() << "\n";
  if(m_clawrot == true){
  if(abs(sensor.get_value() - 1900) > 10){
  if(sensor.get_value() > 1900)
  {
    claw_pivot.move_velocity(abs(sensor.get_value() - 1900)/lerp);
  }else
  {
    claw_pivot.move_velocity(-abs(sensor.get_value() - 1900)/lerp);
  }
} else {claw_pivot.move_velocity(0);}
}else
{
  if(abs(sensor.get_value() - 300) > 10){
  if(sensor.get_value() < 300)
  {
    claw_pivot.move_velocity(-abs(sensor.get_value() - 300)/lerp);
  }else
  {
    claw_pivot.move_velocity(abs(sensor.get_value() - 300)/lerp);
  }
 } else {claw_pivot.move_velocity(0);}
}
}

void Movement::claw_rot(int c_rot){
  if(c_rot == 1){
    m_clawrot = true;
  } else {
    m_clawrot = false;
  }
}
