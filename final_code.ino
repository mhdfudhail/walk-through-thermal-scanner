//Defining header files for initialization 
#include <Adafruit_MLX90614.h>
#include <RGBmatrixPanel.h>
#include <Wire.h>
#define I2C_ADDR 0x27

//Defining LED panel pins

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

//defining ultrasonic sensor pins and buzzer

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04 
#define buzzer 8
#define relay1 5
#define relay2 6

//Operation started
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  mlx.begin();
  matrix.begin();
  Serial.begin(9600);
//  setting pinmode
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  
// fill the screen with 'White'
//  matrix.fillScreen(matrix.Color444(7, 7, 7));
//  delay(1000);
//  matrix.fillScreen(matrix.Color444(0, 0, 0));
////   draw some text!
//  matrix.setCursor(1, 0);    // start at top left, with one pixel of spacing
//  matrix.setTextSize(1);     // size 1 == 8 pixels high
//  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

//  matrix.setTextColor(matrix.Color333(7,7,7));
//  matrix.println("THERMAL");
//  matrix.println("SCANNING");
////  presenting();
//  // fill the screen with 'black'
//  matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(7, 0);
    matrix.setTextColor(matrix.Color444(7,7,0));
    matrix.print("EEE");

}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
  delay(100);
  int detect = false;
  
  
  if(distance < 30){
    Serial.println(distance);
    detect = true; 
  }
  else{
    detect = false;
    digitalWrite(relay1,HIGH);
    matrix.fillScreen(matrix.Color444(0, 0, 0));
    matrix.setCursor(7, 0);
    matrix.setTextColor(matrix.Color444(0,0,7));
    matrix.print("EEE");
    matrix.setCursor(5, 16);
    matrix.setTextColor(matrix.Color444(7,7,0));
    matrix.print("MPTC");
//    delay(1000);
  }

  if(detect == true){
//    digitalWrite(buzzer,HIGH);
//    delay(300);
//    digitalWrite(buzzer,LOW);
    temp();
  }

}

void temp(){
       
      float temperature = (mlx.readObjectTempC());
      Serial.print("Target  ");
      Serial.print(temperature);
      Serial.println(" C");
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      digitalWrite(relay1,LOW);
      
 
  if(temperature < 37.8){
    digitalWrite(buzzer,LOW);
    
    matrix.setCursor(1, 16);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color444(7,7,0));
    matrix.fillScreen(matrix.Color444(0, 0, 0));
    matrix.print(temperature);
    matrix.setCursor(7, 0);
    digitalWrite(buzzer,LOW);
    matrix.setTextColor(matrix.Color444(0,0,7));
    matrix.print("EEE");
    delay(500);
    
    
  }else{
    Serial.print("--------detected---------");
    digitalWrite(relay2,LOW);
    digitalWrite(relay1,HIGH);
    Serial.println(distance);
    matrix.setCursor(1, 16);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color444(7,0,0));
    matrix.fillScreen(matrix.Color444(0, 0, 0));
    matrix.print(temperature);
    matrix.setCursor(7, 0);
    matrix.setTextColor(matrix.Color444(0,0,7));
    matrix.print("EEE");
    delay(500);
    digitalWrite(buzzer,HIGH);
    delay(3000);
    digitalWrite(buzzer,LOW);
    digitalWrite(relay2,HIGH);
 
  }
   
}
