#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

const int ledCount=2;
const int Sound=0;
const int ledPins[] = {13,10,8,7,3};
int val;

void setup() {
  Bridge.begin();
  Console.begin();
  
  // For debugging, wait until the Console Console is connected
  delay(4000);
  while(!Console);

  pinMode(ledPins[0],OUTPUT);
  pinMode(ledPins[1],OUTPUT);
  pinMode(ledPins[2],OUTPUT);
  pinMode(ledPins[3],OUTPUT);
  pinMode(ledPins[4],OUTPUT);
/*
  Console.println("LABEL,A,B"); 
  */
}

void loop() {
  /*Console.print("DATA");
  Console.print(",");
  Console.print(10);
  Console.print(",");
  Console.print(20);*/
  
  if (calls <= maxCalls) {

      //getVoice
      val = analogRead(Sound);
      Console.println(val);
      Console.println();
      if(val>0){
        digitalWrite(ledPins[0],HIGH);
      }
      if(val>50){
        digitalWrite(ledPins[1],HIGH);
      }
      if(val>100){
        digitalWrite(ledPins[2],HIGH);
      }
      if(val>150){
        digitalWrite(ledPins[3],HIGH);
      }
      if(val>200){
        digitalWrite(ledPins[4],HIGH);
      }
      delay(33);
  
      digitalWrite(ledPins[0],LOW);
      digitalWrite(ledPins[1],LOW);
      digitalWrite(ledPins[2],LOW);
      digitalWrite(ledPins[3],LOW);
      digitalWrite(ledPins[4],LOW);

   }
}

void temboo(){
    Console.println("Running AppendRow - Run #" + String(calls++));
    
    TembooChoreo AppendRowChoreo;

    // Invoke the Temboo client
    AppendRowChoreo.begin();

    // Set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    AppendRowChoreo.addInput("SpreadsheetTitle", "FinalProject");
    AppendRowChoreo.addInput("RowData", String(val));
    AppendRowChoreo.addInput("RefreshToken", "1/iyhTO39v-3xQnEEBb-ujpaBuxKbS561huDtsMae8Peo");
    AppendRowChoreo.addInput("ClientSecret", "asYNUUtPMfii7x88SyA0vTnZ");
    AppendRowChoreo.addInput("ClientID", "1078155533361-ol59tc0eqrn1bkftqhqh0rs088a5fpu0.apps.googleusercontent.com");
    
    // Identify the Choreo to run
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");
    
    // Run the Choreo; when results are available, print them to Console
    AppendRowChoreo.run();
    
    while(AppendRowChoreo.available()) {
      char c = AppendRowChoreo.read();
      Console.print(c);
    }
    AppendRowChoreo.close();
}



