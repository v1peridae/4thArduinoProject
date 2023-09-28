int level;
int sequence[100];
int pressed[100];
int mode = 0;
int counter;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  Serial.begin(9600);
  
  level = 1;
}

void allOn()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
}

void allOff()
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}

void showSequence()
{
  //level...
  Serial.print("Level: ");
  Serial.println(level);
  //Generate sequence
  for (int i = 0;i<level;i++) {
    sequence[i] = random(1,4);
  }
  //LEDS on/off to start
  allOn();
  delay(1000);
  allOff();
  delay(1000);
  
  //Play sequence
  for (int i=0;i<level;i++) {
    //Serial.println(sequence[i]);
    if (sequence[i] == 1) {
      digitalWrite(2,HIGH);
    }
    if (sequence[i] == 2) {
      digitalWrite(3,HIGH);
    }
    if (sequence[i] == 3) {
      digitalWrite(4,HIGH);
    }
    delay(500);
    allOff();
    delay(500);
  }

  //LEDS on/off to end display
  allOn();
  delay(1000);
  allOff();
  delay(1000);
}

void loop()
{
  if (mode == 0) { //Show sequence
    showSequence();
    mode = 1; //Change to get input
    counter = 0;
  } else {
    if (digitalRead(A1) == HIGH) {
      Serial.println("1");
      pressed[counter] = 1;
	  counter++;
      digitalWrite(2,HIGH);
      delay(200);
      allOff();
    } else {
      if (digitalRead(A2) == HIGH) {
      	Serial.println("2");
      	pressed[counter] = 2;
  	  	counter++;
      	digitalWrite(3,HIGH);
      	delay(200);
     	allOff();
      } else {
       	if (digitalRead(A3) == HIGH) {
      	  Serial.println("3");
      	  pressed[counter] = 3;
	  	  counter++;
      	  digitalWrite(4,HIGH);
      	  delay(200);
      	  allOff();
        }
      }
    }
    if (counter == level) {
      Serial.println("Checking...");
      int OK = 1;
      for (int i=0;i<level;i++) {
        if (sequence[i] != pressed[i]) {
          OK = 0;
        }
      }
      if (OK == 1) {
        Serial.println("Correct. Next level!");
        level = level + 1;
      } else {
        Serial.println("Nope! Back to the start!");
        level = 1;
      }
      mode = 0;
      delay(1000);
    }
  }
}

