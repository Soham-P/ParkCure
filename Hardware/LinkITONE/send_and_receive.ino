#include <LGSM.h>
String message;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   
  while(!LSMS.ready())
    delay(1000);
  Serial.println("SIM initialized!");
  //LSMS.beginSMS("5199952026");
}
 
void loop() {
  LSMS.beginSMS("5199952026");
  // put your main code here, to run repeatedly:
  char buf[20];
  int v;
  //while (Serial.available() == 0) {}  
  message = Serial.readString();        // Save user input in the message variable

  LSMS.print(message);    
  LSMS.endSMS();
  
  if(LSMS.available())
  {
    Serial.println("There is a new message.");
     
    LSMS.remoteNumber(buf, 20);
    Serial.print("Number:");
    Serial.println(buf);
     
    Serial.print("Content:");
    while(true)
    {
      v = LSMS.read();
      if(v < 0)
        break;
      Serial.print((char)v);
    }
    Serial.println();
     
    LSMS.flush();
  }
  delay(1000);
  
}
