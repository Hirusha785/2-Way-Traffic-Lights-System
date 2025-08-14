// ---------------- Traffic light pins ----------------
const int upperRed    = 13;
const int upperYellow = 12;
const int upperGreen  = 11;
const int lowerRed    = 10;
const int lowerYellow = 9;
const int lowerGreen  = 8;

// ---------------- 7-seg wiring ---------------------
// Shared segment lines A..G on D0..D6  (bit0=A ... bit6=G)
const int segmentPins[7] = {0, 1, 2, 3, 4, 5, 6};
// Digit enables (common-cathode): LOW = ON, HIGH = OFF
// 0 = TOP display, 1 = BOTTOM display
const int digitPins[2]   = {A1, A2};

// Build patterns safely: bit0..bit6 correspond to A..G
#define SEG(a,b,c,d,e,f,g) ((a<<0)|(b<<1)|(c<<2)|(d<<3)|(e<<4)|(f<<5)|(g<<6))

// Common-cathode patterns 0..9 (1 = segment ON)
const byte DIGIT_CC[10] = {
  SEG(1,1,1,1,1,1,0), // 0
  SEG(0,1,1,0,0,0,0), // 1
  SEG(1,1,0,1,1,0,1), // 2
  SEG(1,1,1,1,0,0,1), // 3
  SEG(0,1,1,0,0,1,1), // 4
  SEG(1,0,1,1,0,1,1), // 5
  SEG(1,0,1,1,1,1,1), // 6
  SEG(1,1,1,0,0,0,0), // 7
  SEG(1,1,1,1,1,1,1), // 8
  SEG(1,1,1,1,0,1,1)  // 9
};

// -------- timings --------
const int GREEN_SEC  = 7;      // show 1..7
const int YELLOW_SEC = 7;      // show 1..7
const int dwell_us   = 1200;   // ~1.2 ms per digit scan

// ---------------- helpers ----------------
inline void disableBoth() {
  digitalWrite(digitPins[0], HIGH);
  digitalWrite(digitPins[1], HIGH);
}
inline void setPattern(byte p) {
  for (int s=0; s<7; s++) digitalWrite(segmentPins[s], (p>>s)&1 ? HIGH : LOW);
}
inline void scanTop(byte p) {
  disableBoth(); setPattern(p);
  digitalWrite(digitPins[0], LOW);  // TOP on
  delayMicroseconds(dwell_us);
  disableBoth();
}
inline void scanBottom(byte p) {
  disableBoth(); setPattern(p);
  digitalWrite(digitPins[1], LOW);  // BOTTOM on
  delayMicroseconds(dwell_us);
  disableBoth();
}
void showBoth(byte pTop, byte pBot, unsigned long ms){
  unsigned long t0 = millis();
  while (millis()-t0 < ms) { scanTop(pTop); scanBottom(pBot); }
}
void showTop(byte p, unsigned long ms){
  unsigned long t0 = millis();
  while (millis()-t0 < ms) scanTop(p);
}
void showBottom(byte p, unsigned long ms){
  unsigned long t0 = millis();
  while (millis()-t0 < ms) scanBottom(p);
}

// Traffic lights
void setLights(int uR,int uY,int uG,int lR,int lY,int lG){
  digitalWrite(upperRed, uR);   digitalWrite(upperYellow, uY);   digitalWrite(upperGreen, uG);
  digitalWrite(lowerRed, lR);   digitalWrite(lowerYellow, lY);   digitalWrite(lowerGreen, lG);
}

// Sequences (1..7)
void countBottom_1to7(){ for(int d=1; d<=7; d++) showBottom(DIGIT_CC[d], 1000); }
void countTop_1to7()   { for(int d=1; d<=7; d++) showTop   (DIGIT_CC[d], 1000); }
void countBoth_1to7()  { for(int d=1; d<=7; d++) showBoth  (DIGIT_CC[d], DIGIT_CC[d], 1000); }

void setup(){
  // DO NOT start Serial (D0/D1 used as segments)
  pinMode(upperRed,OUTPUT); pinMode(upperYellow,OUTPUT); pinMode(upperGreen,OUTPUT);
  pinMode(lowerRed,OUTPUT); pinMode(lowerYellow,OUTPUT); pinMode(lowerGreen,OUTPUT);
  for(int i=0;i<7;i++) pinMode(segmentPins[i], OUTPUT);
  pinMode(digitPins[0], OUTPUT); pinMode(digitPins[1], OUTPUT);

  disableBoth();
  setLights(LOW,LOW,LOW, LOW,LOW,LOW);
}

void loop(){
  // Top RED, Bottom GREEN -> bottom counts 1..7
  setLights(HIGH,LOW,LOW,  LOW,LOW,HIGH);
  countBottom_1to7();

  // Both YELLOW -> both count 1..7
  setLights(LOW,HIGH,LOW,  LOW,HIGH,LOW);
  countBoth_1to7();

  // Top GREEN, Bottom RED -> top counts 1..7
  setLights(LOW,LOW,HIGH,  HIGH,LOW,LOW);
  countTop_1to7();

  // Both YELLOW -> both count 1..7
  setLights(LOW,HIGH,LOW,  LOW,HIGH,LOW);
  countBoth_1to7();
}
