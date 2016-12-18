
int b_press(const int b1) {   //Function for the Tiva Buttons
    int b1State = digitalRead(b1);
    
    if (b1State == LOW) {
     
     //Serial.println("Left");
     delay(200);
     return 1;
    }else { return 0;}
    
  }

int b_presst(const int b1) { //Function for the Orbit Booster Pack Buttons
    int b1State = digitalRead(b1);
    
    if (b1State == HIGH) {
     
     //Serial.println("Left");
     delay(200);
     return 1;
    }else { return 0;}
    
  }

