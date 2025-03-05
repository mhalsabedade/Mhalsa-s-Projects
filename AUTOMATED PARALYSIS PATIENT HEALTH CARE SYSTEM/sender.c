#include <LiquidCrystal.h> 
#include <RF24.h> 
LiquidCrystal lcd(8,7,6,5,4,3);//LCD’s pin. 
Unsigned long lastReceiveTime = 0; 
Unsigned long currentTime = 0; 
Const int Buzzer = 17; 
Const int VT_LED = 18; 
// Max size of this struct is 32 bytes – NRF24L01 buffer limit 
Struct Data_Package  
{ 
  Char msg; 
 }; 
Void setup()  
{ 
  pinMode(Buzzer,OUTPUT); 
  pinMode(VT_LED,OUTPUT); 
  digitalWrite(Buzzer,LOW); 
  digitalWrite(VT_LED,LOW); 
  Serial.begin(9600); 
  Radio.begin(); 
  Lcd.begin(16,2); 
  Lcd.setCursor(0, 0);  
  Lcd.print(“*  Welcome To  *”); 
  Lcd.setCursor(0, 1);   
   Lcd.print(“* Year 2022-23 *”); 
   Delay(1000); 
   Lcd.clear(); 
   Lcd.setCursor(0, 0);   
   Lcd.print(“Initalising GSM”); 
   Lcd.setCursor(0, 1);   
   Lcd.print(“Connecting…”); 
   Lcd.clear(); 
   digitalWrite(Buzzer,HIGH); 
   delay(511); 
   digitalWrite(Buzzer,LOW); 
 } 
 Void loop() 
 { 
   // Check whether there is data to be received 
   If (radio.available()) { 
    Radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the ‘data’ 
 structure 
     digitalWrite(VT_LED,HIGH); 
   } 
   If ( currentTime – lastReceiveTime > 1000 ) { // If current time is more then 1 second since we 
 have recived the last data, that means we have lost connection 
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
} 
Lcd.setCursor(0, 0);   
 Lcd.print(“Waiting For…  “); 
Lcd.setCursor(0, 1);   
 Lcd.print(“Massage…      “); 
If(data.msg ==1) 
{ 
 Lcd.clear(); 
 Lcd.setCursor(0, 0);   
 Lcd.print(“Petient Need,”); 
 Lcd.setCursor(0, 1);   
 Lcd.print(“Food-Food…”); 
 digitalWrite(Buzzer,HIGH); 
 delay(151); 
 digitalWrite(Buzzer,LOW); 
 delay(151); 
} 
If(data.msg ==2) 
{ 
 Lcd.clear(); 
 Lcd.setCursor(0, 0);   
 Lcd.print(“Petient Need,”); 
 Lcd.setCursor(0, 1);   
 Lcd.print(“Water-Water…”); 
 digitalWrite(Buzzer,HIGH);
 delay(151); 
 digitalWrite(Buzzer,LOW); 
delay(151); 
} 
If(data.msg ==3) 
{ 
 Lcd.clear(); 
 Lcd.setCursor(0, 0);   
 Lcd.print(“Petient Need,”); 
  Lcd.setCursor(0, 1);   
  Lcd.print(“To Attend…”); 
 digitalWrite(Buzzer,HIGH); 
 delay(151); 
 digitalWrite(Buzzer,LOW); 
 delay(151); 
} 
If(data.msg ==4) 
{ 
 Lcd.clear(); 
 Lcd.setCursor(0, 0);   
 Lcd.print(“Emergence Call,”); 
 Lcd.setCursor(0, 1);   
 Lcd.print(“From Patient…”); 
 digitalWrite(Buzzer,HIGH); 
  delay(151);
  digitalWrite(Buzzer,LOW); 
  delay(151); 
  SMS_Call(); 
 } 
}//LOOP 
Void resetData()  
{ 
  // Reset the values when there is no radio connection – Set initial default values. 
  Data.Right = 0; 
  Data.Far   = 0; 
  Data.Back  = 0; 
  Data.Fall  = 0; 
  digitalWrite(VT_LED,LOW); 
  digitalWrite(Buzzer,LOW); 
  } 
  Void SMS_Call() 
{ 
  digitalWrite(Buzzer,HIGH); 
  lcd.clear(); 
  lcd.setCursor(0, 0);   
  lcd.print(“Sending SMS…”); 
 //-----------------------------------------------SMS Sending Routing 
    Serial.write(“AT+CMGF=1\r\n”);   //Set SMS format to ASCII 
    Serial.write(“AT+CMGS=\”08668909740\”\r\n”); //Send new SMS command and message number
    Serial.print(“Attention!! Patient Is Serious, Please Do Needfull Action….”);  //Send SMS content 
    Lcd.setCursor(0, 0);   
    Lcd.print(“Sending SMS   “); 
    Lcd.setCursor(0, 1);   
    Lcd.print(“Is Finished   “); 
    Lcd.setCursor(0, 0);   
    Lcd.print(“Calling To Dr..”); 
    Lcd.setCursor(0, 1);   
    Lcd.print(“               “); 
     Serial.println(“ATD+918668909740;”); 
     Delay(5100); 
   Lcd.setCursor(0, 1);   
    Lcd.print(“Is Finished   “); 
    Serial.println(“ATH0”); 
    Delay(500); 
    Lcd.clear(); 
    digitalWrite(Buzzer,LOW); 
}