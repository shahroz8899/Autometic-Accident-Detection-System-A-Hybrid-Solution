#include <Wire.h>
#include <TimerOne.h>
//#include  "Arduino.c"
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);



//************************MPU 6050 Start*********************
const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
//****************Init**************
void MPU_6050_Init() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
//****************Read**************
void MPU_6050_read() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  //AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  //GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  //	GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  //GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //***************to digri converter**************
  AcX = map(AcX, -16000, 16000, -90, 90);
  AcY = map(AcY, -16000, 16000, -90, 90);


}
//********************************END MPU6050**********************


int flag = 0, count = 0;
float Temp;
//**********************define**************
void setup()
{
  pinMode(8, INPUT);
  MPU_6050_Init();
  Serial.begin(9600);
  //***********************lcd init**********************
  lcd.begin(16, 2);// set up the LCD's number of columns and rows:
  lcd.print("Init....");
  delay(500);

  lcd.clear();
}
//********************main loop star**************
void loop()
{

  /*
    Temperatture
  */





  MPU_6050_read();
  lcd.clear();
  //*************
 lcd.setCursor(0, 0);  lcd.print("X=");
  lcd.print(AcX);
  //*************
 lcd.setCursor(0, 1); lcd.print("Y=");
  lcd.print(AcY);
lcd.print(" ");
  Temp = analogRead(A0);
  Temp = Temp * 0.48828125;
   lcd.print("Temp=");
  lcd.print(Temp);



                                 //*********************
                                 if (AcX > 50) {
                                 Serial.println("got an Accident at: ");

                                 delay(500);
                                 Serial.print("; ");
                                 while (1);
                               }
                                 //*********************
                                 if (AcX < -50) {
                                 Serial.println("got an Accident at: ");
                                 delay(500);
                                 Serial.print("; ");
                                 while (1);
                               }
                                 //*********************
                                 if (AcY > 50) {
                                 Serial.println("got an Accident at: ");
                                 delay(500);
                                 Serial.print("; ");
                                 while (1);
                               }
                                 //*********************
                                 if (AcY < -50) {
                                 Serial.println("got an Accident at: ");
                                 delay(500);
                                 Serial.print("; ");
                                 while (1);
                               }

                                      if (Temp > 25) {
                                 Serial.println("got an Accident at: ");
                                 delay(500);
                                 Serial.print("; ");
                                 while (1);
                               }

                                 if (digitalRead(8) == LOW) {
                                 Serial.println("got an Accident at: ");
                                 delay(500);
                                 Serial.print("; ");
                                 while (2);
                                 
                               }

                                 delay(200);

                               }


