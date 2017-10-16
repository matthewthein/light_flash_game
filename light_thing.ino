#define MAX 7
#define GREEN 12
#define YELLOW 11
#define RED 10
#define BLUE 9
#define GREEN_BUTTON 8
#define YELLOW_BUTTON 7
#define RED_BUTTON 6
#define BLUE_BUTTON 5
#define WRONG_BLINKS 3
#define SEQUENCE_DELAY 500
#define WRONG_DELAY 100

byte myPins[] = {12, 11, 10, 9}; //Enter the number of the pins being used
byte RNum = 0;
byte *sequence;
byte *selected;
byte count = 0;
byte previous = 0;
bool released = true;
bool pressed = false;
static const char green[] = {'G', 'r', 'e', 'e', 'n', '\0'};
static const char yellow[] = {'Y', 'e', 'l', 'l', 'o', 'w', '\0'};
static const char red[] = {'R', 'e', 'd', '\0'};
static const char blue[] = {'B', 'l', 'u', 'e', '\0'};


void setup() {
  sequence = calloc(8, sizeof(byte));
  selected = calloc(8, sizeof(byte));
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN_BUTTON, INPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(BLUE_BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  make_sequence();
  count = 0;
  while (count < 8) {
    while (released) {
      while (digitalRead(GREEN_BUTTON) == HIGH) {
        digitalWrite(GREEN, HIGH);
        released = false;
      }
      //Serial.println("Pressed color is GREEN ");
      selected[count] = 12;
      digitalWrite(GREEN, LOW);

      while (digitalRead(YELLOW_BUTTON) == HIGH) {
        digitalWrite(YELLOW, HIGH);
        released = false;
      }
      //Serial.println("Pressed color is YELLOW ");
      selected[count] = 11;
      digitalWrite(YELLOW, LOW);

      while (digitalRead(RED_BUTTON) == HIGH) {
        digitalWrite(RED, HIGH);
        released = false;
      }
      //Serial.println("Pressed color is RED ");
      selected[count] = 10;
      digitalWrite(RED, LOW);

      while (digitalRead(BLUE_BUTTON) == HIGH) {
        digitalWrite(BLUE, HIGH);
        released = false;
      }
      //Serial.println("Pressed color is BLUE ");
      selected[count] = 9;
      digitalWrite(BLUE, LOW);
      //Serial.println(count);
    }
    released = true;
    count++;
    Serial.print("Counter is at : ");
    Serial.println(count);
  }
  check_sequence();
}
void wrong() {
  for (count = 0; count < WRONG_BLINKS; count++) {
    Serial.println("WRONG!");
    digitalWrite(RED, HIGH);
    delay(WRONG_DELAY);
    digitalWrite(RED, LOW);
    delay(WRONG_DELAY);
  }
}
void make_sequence() {
  for (count; count <= MAX; count++) {
    sequence[count] = random(9, 13); // MAX being the number of LEDs connected minus one
    Serial.print("Random color is : ");
    //Serial.println(sequence[count]);     // the raw analog reading
    switch (sequence[count]) {
      case 12: Serial.println(green);
      break;
      case 11: Serial.println(yellow);
      break;
      case 10: Serial.println(red);
      break;
      case 9: Serial.println(blue);
    }
  }
  digitalWrite(sequence[count], HIGH);
  //the above generates a random number
  delay(SEQUENCE_DELAY);
  digitalWrite(sequence[count], LOW);
  delay(SEQUENCE_DELAY);
}
void check_sequence() {
  for (count = 0; count < MAX; count++) {
    Serial.print("Random value was : ");
    Serial.println(sequence[count]);
    Serial.print("Selected value was :");
    Serial.println(selected[count]);
    if (sequence[count] != selected[count]) {
      wrong();
      count = 0;
      break;
    }
  }
}

