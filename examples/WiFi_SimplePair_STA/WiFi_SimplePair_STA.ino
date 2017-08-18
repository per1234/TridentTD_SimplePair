/********************************************************
 * 
 * ตัวอย่างนี้ เป็นตัวอย่างสำหรับ รับ WiFi Password ผ่านทาง Simple-Pair 
 * โดยลูกข่าย WiFi ไม่จำเป็นต้อง มีชื่อ AP และ Password แต่อย่างใด
 * 
 *******************************************************/

#include <ESP8266WiFi.h>
#include <TridentTD_SimplePair.h>

// ค่า SIMPLE_PAIR_KEY ใช้สำหรับเข้ารหัส Simple-Pair ให้ตรงกัน
// Simple-Pair ที่จะจับคู่กัน ต้องตั้งค่านี้ให้ตรงกัน โดยมีความยาวไม่เกิน 16 ตัวอักษร
#define SIMPLE_PAIR_KEY   "HELLO_SIMPLEPAIR"

String AP_SSID;
String AP_PASSWORD;

/* เมื่อ STA ได้รับข้อมูล ทาง Simple-Pair เรียบร้อยแล้ว */
void On_SimplePair_ReceivedData(){
  // รับค่า AP_SSID และ AP_PASSSWORD ผ่านทาง Simple-Pair
  AP_SSID        = SimplePair.getSSID();
  AP_PASSWORD    = SimplePair.getSimplePairData(); 

  Serial.println("Recv. SSID     : " + AP_SSID);  
  Serial.println("Recv. PASSWORD : " + AP_PASSWORD);
}

/* เมื่อ STA ไม่สามารถพบ Simple-Pair ใดๆ */
void On_SimplePair_ScanNotFound(){
  Serial.println("Simple-Pair not found!");

  /* กำหนด AP_SSID และ AP_PASSSWORD ที่รู้จักเอง */
  AP_SSID     = "---- KNOWN SSID -------";
  AP_PASSWORD = "-----KNOWN PASSWORD----";
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.println("Simple-Pair STA Mode");
  
  SimplePair.mode(SP_STA);
  SimplePair.setSimplePairKey(SIMPLE_PAIR_KEY);
  SimplePair.onReceivedData(&On_SimplePair_ReceivedData);
  SimplePair.onScanNotFound(&On_SimplePair_ScanNotFound);
  
  SimplePair.scanSP();  // STA ทำการแสกนหา Simple-Pair

  if( AP_SSID != "") {
    //เชื่อมต่อ WiFi
    WiFi.begin(AP_SSID.c_str(), AP_PASSWORD.c_str());
    while (WiFi.waitForConnectResult() != WL_CONNECTED);
    Serial.println("WiFi connected to ssid "+AP_SSID)
    Serial.print("IP Address is "); Serial.println(WiFi.localIP());
  }
}

void loop() {

}