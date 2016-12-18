#include "accel.h";

int tilt() {
   check++;
  if (check%250 == 0) {
    if (x<=1.5 && x >=-1.5) {
      Serial.println("Center");
      return 1;
     // Serial.println(gyro_correct);
    }
    if (x >1.5) {
      Serial.println("Left");
      return 2;
      //Serial.println(gyro_correct);
    }
    if (x <-1.5) {
      Serial.println("Right");
      return 3;
      //Serial.println(gyro_correct);
    }
  }
  return 0;
}

int shake_f () {
  //Serial.println("work");
   if (i == when) {
    digitalWrite(LED, HIGH);
    time_shake = 0;
    shake = 0;
    count_s = 0;
    return 1;
  }

   if (time_shake >= 0 && time_shake < 200) {
     
     time_shake++;
     if (sqrt(x*x + y*y + z*z) >= 16) {
      count_s++;
     }
     
     Serial.print("c: ");Serial.println(count_s);
     if (count_s == shake_difficulty) {
     
     //Makes it harder to pass the shake, greater number means more shaking
     //For greater difficulty either lower max time-shake or ask for more count_s
      
      time_shake = 200;
      shake = 1;
     }
    if (shake == 0 && time_shake == 200) { //Speed Up, shake difficulty remain the same
      Serial.println("Failed");
      digitalWrite(LED, LOW);
      gameSpeed-=5000;
      when += random(5000,10000); 
      return 0;
    }
    if (shake == 1) { //No speed up, shake difficulty increases
      Serial.println("Good Job");
      digitalWrite(LED, LOW);
      when += random(5000,10000); 
      shake_difficulty +=5;
      return 0; 
    }
    return 1;
  }
  return 0;
}

