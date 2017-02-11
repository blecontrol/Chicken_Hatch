
/*
 * Arduino MEGA-2560
 */
 /*
  * DHT_11
  * ความแม่นยำ +- 2 องศาเซลเซียส
  * ลำดับขาใช้งาน
  * 1 VCC 5 VDC
  * 2 DATA  pin 2
  * 3 NC -- NULL
  * 4 GND  
  */
  /*
   * DS3231 for Arduino Mega2560  SPI
   * GND   
   * VCC   +5V
   * SCL  to Pin 21
   * SDA  to Pin 20
   */
  /*
   * LCD 16*2  for Arduino Mega2560 
   *  LCD RS pin to digital pin 12
   * LCD Enable pin to digital pin 11
   * LCD D4 pin to digital pin 6
   * LCD D5 pin to digital pin 5
   * LCD D6 pin to digital pin 4
   * LCD D7 pin to digital pin 3
   * LCD R/W pin to ground
   * 10K resistor:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin )
   */
#include "DHT.h"
#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

DHT dht; //สร้างออปเจค DHT22 สำหรับติดต่อเซนเซอร์
RTC_DS1307 RTC; //สร้างออปเจค 
LiquidCrystal lcd(12, 11, 6, 5, 4, 3); // RS, E, D4, D5, D6, D7

//#define Lamp1 //
#define Fan 1 // กำหนดขาให้ delay พัดลมทำงาน

void setup() {
  
  Serial.begin(9600);
   Wire.begin();
   RTC.begin();

   pinMode(Fan, OUTPUT); //กำหนดให้เป็น Output
  
  dht.setup(2); // กำหนดขาที่ต่อกับ data ของ DHT22 เป็น ขา arduino pin 2
//-------Time RTC-------
// DateTime now = RTC.now();
  // if (! RTC.isrunning()) {
  //  Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   // RTC.adjust(DateTime(__DATE__, __TIME__)); //ตั้งเวลาใหม่ทุกครั้งที่รันโปรแกรม
 // }
 //   DateTime now = RTC.now();
  /* ตั้งเวลา ในตัวอย่างนี้ เซตค่าเป็นเวลา 23:09 ถ้าถึงเวลานี้จะให้ทำงานที่ฟังก์ชัน 
    RTC.setAlarm1Simple(23, 9);
   if (RTC.checkIfAlarm(1)) {
   Serial.println("Alarm Triggered");
   }*/
 // RTC.setAlarm1Simple(23, 9);

//  RTC.turnOnAlarm(1);

 // if (RTC.checkAlarmEnabled(1)) {
 //   Serial.println("Alarm Enabled");
 // }
  //-----------LCD -------------
  lcd.begin(16, 2); // จอกว้าง 16 ตัวอักษร 2 บรรทัด
   lcd.setCursor(1, 0);
    lcd.print("Loading...");
    delay(3000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Hatch Chicken"); // แสดงผลคำว่า Hello, world! ออกหน้าจอ
  //lcd.setCursor(0, 1); // เลื่อนเคเซอร์ไปบรรทัดที่ 2 ลำดับที่ 0 (ก่อนหน้าตัวอักษรแรก)
 // lcd.print("www.ioxhop.com"); // แสดงผลคำว่า www.ioxhop.com
 // delay(3000); // หน่วงเวลา 3 วินาที
   delay(3000);
   lcd.clear(); // ล้างหน้าจอ
  //-----------------
}

void loop() {

//---DHT 11
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity() + 5;  //ดึงค่าความชื้นจาก DHT11 ที่ต้องการ 55 - 65%
  float temperature = dht.getTemperature() + 2; //ดึงค่าอุณหภูมิจาก DHT11  ที่ต้องการ  37.5 - 38.0 องศา
  int fahrenheit = dht.toFahrenheit(temperature) ;  //แปลงองศาเซลเซียสเป็นฟาเรนไฮน์
//-----DS1307--------------------------- 
RTC.adjust(DateTime(__DATE__, __TIME__));
 //print Temperature
  //Serial.print(dht.getStatusString()); //เช็คสถานะการเชื่อมต่อ DHT11
 // Serial.print("\t");

//--pirnt time
  //Serial.print("Time : ");
 //Serial.print(now.day(), DEC);
   Serial.print("\t");
   DateTime now = RTC.now();
   Serial.print("Time : ");

//-------Prin LCD-------------------
 lcd.clear();
 //lcd.setCursor(0, 0);
// lcd.home();
// lcd.print("D ");
 //lcd.print(now.day(), DEC);
 ////lcd.print('/');
 //lcd.print(now.month(), DEC);
 //lcd.print(' ');
// lcd.print(now.year());
// lcd.print("T");
// lcd.print(' ');
/// lcd.print(now.hour(), DEC);
// lcd.print(':');
// lcd.print(now.minute(), DEC);
// lcd.print(':');
// lcd.print(now.second(), DEC);
 
 lcd.setCursor(0, 0);
 lcd.print("Temperature = ");
 lcd.print(temperature, 2);
 lcd.print(' ');
 lcd.setCursor(0, 1);
 lcd.print("Humidity = ");
 lcd.print(humidity, 2);
 //lcd.print(' ');
// lcd.print("F=");
// lcd.print(fahrenheit);
 delay(500); //หน่วงเวลา 0.5 วินาที

//ถ้า อุณหภูมิ อยู่ระหว่าง 39 - 40 ให้พัดลมทำงาน
if(temperature > 39 && temperature <= 40){
     delay(1023);
      if(temperature > 39 && temperature <= 40)
     {
      digitalWrite(Fan, HIGH);
       delay(3000);
     }

}
}
