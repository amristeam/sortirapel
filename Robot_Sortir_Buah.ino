/*     Robot Arduino - Sortir Buah
 */
#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo aServo; //servo pertama atas
Servo bServo; //servo kedua bawah

// mengatur frequensi awal dari sensor warna
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// mengatur inisiasi warna RGB
int redColor = 0; //merah
int greenColor = 0; //hijau
int blueColor = 0; //biru

void setup() {
  // Setting utk output
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frekuensi skala 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  //mengatur pin servo
  aServo.attach(7);
  bServo.attach(8);

  // serial komunikasi
  Serial.begin(9600);
}

void loop() {

  //inisiasi sevo atas untuk waktu membaca sensor warna
 aServo.write(115);
  delay(5000);
  
  for(int i = 115; i > 25; i--) {
    aServo.write(i);
    delay(2);
  }
  delay(500);
  
  // setting warna merah agar terbaca
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // membaca output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Map function untuk warna merah dari frekuensi 0 to 255
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, 39, 103, 255,0);
  
  // Memberi info warna merah
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
  // setting warna hijau agar terbaca
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // membaca output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Map function untuk warna hijau dari frekuensi 0 to 255
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, 61, 109, 255, 0);
  
  // Memberi info warna hijau
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // setting warna biru agar terbaca
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // membaca output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Map function untuk warna biru dari frekuensi 0 to 255
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, 38, 125, 255, 0);
  
  // Memberi info warna biru
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  // mendeteksi dan mengatur gerakan servo bawah
  // informasi pada serial monitor dan gerakan servo bawah
  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - Buah matang");
      bServo.write(115);
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - Buah belum matang");
    bServo.write(45);
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println(" - Buah belum matang");
     bServo.write(45);
  }
}
