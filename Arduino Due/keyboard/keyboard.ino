#define C0 53
#define CS0 51
#define D0 49
#define DS0 47
#define E0 45
#define F0 43
#define FS0 41
#define G0 39
#define GS0 37
#define A0 35
#define AS0 33  // not working
#define B0 31

#define C1 52
#define CS1 50
#define D1 48
#define DS1 46
#define E1 44
#define F1 42
#define FS1 40
#define G1 38
#define GS1 36
#define A1 34
#define AS1 32
#define B1 30

#define C2 14
#define CS2 15
#define D2 16
#define DS2 17
#define E2 18
#define F2 19
#define FS2 28
#define G2 26
#define GS2 24
#define A2 29 // not working
#define AS2 27
#define B2 25

int notes[36] = {C0, CS0, D0, DS0, E0, F0, FS0, G0, GS0, A0, AS0, B0, C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1, C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2};
int state[36], reading;

int IDP[6] = {54, 55, 56, 57, 58, 59};  // key ID pins
int INF[6] = {8, 9, 10, 11, 12, 13};    // information pins

unsigned long int debouncer[36], t0, t1;
unsigned long int debounce_time = 100;  // 100ms debouncing period

void send_ID(int pin){
  digitalWrite(IDP[0], !!(pin & 1<<0));
  digitalWrite(IDP[1], !!(pin & 1<<1));
  digitalWrite(IDP[2], !!(pin & 1<<2));
  digitalWrite(IDP[3], !!(pin & 1<<3));
  digitalWrite(IDP[4], !!(pin & 1<<4));
  digitalWrite(IDP[5], !!(pin & 1<<5));
}

void key_press(int pin){
  send_ID(pin);
  digitalWrite(INF[0], LOW);
  digitalWrite(INF[1], HIGH);
}

void key_release(int pin){
  send_ID(pin);
  digitalWrite(INF[0], HIGH);
  digitalWrite(INF[1], LOW);
}


void setup() {
  t0 = millis();
  for (int i = 0; i < 36; i++) {
    pinMode(notes[i], INPUT);
    debouncer[i] = t0;
  }

  for (int i = 0; i < 6; i++) {
    pinMode(IDP[i], OUTPUT);
    pinMode(INF[i], OUTPUT);
    digitalWrite(IDP[i], 0);
    digitalWrite(INF[i], 0);
  }
//
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 36; i++) {
    t0 = millis();
    if (t0 - debouncer[i] >= debounce_time) {
      reading = digitalRead(notes[i]);
      // key pressed
      if (reading && !state[i]) {
        state[i] = 1;
        debouncer[i] = t0;
        Serial.print("Pressed ");
        Serial.println(i);
        key_press(i);
      }
      // key released
      else if (!reading && state[i]) {
        state[i] = 0;
        debouncer[i] = t0;
        Serial.print("Released ");
        Serial.println(i);
        key_release(i);
      }
    }
  }
}
