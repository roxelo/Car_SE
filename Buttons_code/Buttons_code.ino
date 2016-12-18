int i;
const int b1 = PUSH1; //Bottom-Left button
const int b2 = PUSH2; //Bottom-Right button


void setup() {
  //To include in setup
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  Serial.begin(9600);
}

//Bottom Left

int b_left(const int b1) {
    int b1State = digitalRead(b1);
    
    if (b1State == LOW) {
     
     Serial.println("Left");
     delay(150);
     return 1;
    }else { return 0;}
    
  }

int b_right(const int b2) {
   int b2State = digitalRead(b2);
   if (b2State == LOW) {
    
     Serial.println("Right");
     delay(150);
     return 1;
   }else { return 0; }
  
}

void loop() {
  i++; //insures that if button is press one time, it is considered only once in the program.
  b_right(b2, i);
  b_left(b1, i);
  
}
