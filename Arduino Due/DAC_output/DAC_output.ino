# define pi 3.14159265
# define n 500

float A = 127.0;
int DAC_pins[12];
int samples[n];
int note_no;

void init_DAC(){
//  for(int i = 0; i < 12; i++){
//    DAC_pins[i] = 53-2*i;    // arduino due
//    pinMode(DAC_pins[i], OUTPUT);
//  }
  DDRD = 0b11111111;
  DDRB |= 0b00001111; 
}

void tune(int note){
//   for(int i = 0; i < 12; i++){
//    int bitState = !!(note & (1<<i));     // extract bits
//    digitalWrite(DAC_pins[i], bitState);  // set pins according to bits
//  }

  PORTD = note;
  //PORTB = (PORTB & 0b11110000)|(note>>8 & 0b00001111);
}

void setup() {
  init_DAC();
  for (int i = 0; i < n; i++){
    float degree = 2.0*pi*i/n;
    samples[i] = A *(1.0-cos(degree));
  }
}

void loop() {
  tune(samples[note_no]);
  note_no = (note_no + 1)%n;
  delayMicroseconds(500);
}
