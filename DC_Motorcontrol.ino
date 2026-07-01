const int enablePin = 5;  
const int in1Pin = 4;     
const int in2Pin = 3;     

int currentSpeed = 150; 
char currentDir = 'X';  

void setup() {
  pinMode(enablePin, OUTPUT); 
  pinMode(in1Pin, OUTPUT); 
  pinMode(in2Pin, OUTPUT);
  digitalWrite(enablePin, LOW);
  Serial.begin(9600); // Talk to Stanley
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'w')      { currentDir = 'W'; }
    else if (command == 's') { currentDir = 'S'; }
    else if (command == 'x') { currentDir = 'X'; }
    else if (command == 'd') { currentSpeed = min(currentSpeed + 25, 255); }
    else if (command == 'a') { currentSpeed = max(currentSpeed - 25, 0); }
    
    if (currentDir == 'W') {
      digitalWrite(in1Pin, HIGH); digitalWrite(in2Pin, LOW);
      analogWrite(enablePin, currentSpeed);
    } else if (currentDir == 'S') {
      digitalWrite(in1Pin, LOW);  digitalWrite(in2Pin, HIGH);
      analogWrite(enablePin, currentSpeed);
    } else {
      digitalWrite(enablePin, LOW);
    }
    
    Serial.print("STATUS -> Dir: "); Serial.print(currentDir);
    Serial.print(" | Speed: ");      Serial.println(currentSpeed);
  }
}
