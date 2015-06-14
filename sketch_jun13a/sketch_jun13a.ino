void setup()  
{
  Serial.begin(9600);
  pinMode(A1,INPUT);
}
void loop()  {
  while(1)  {
    delay(500);
    int val = analogRead(A1)==LOW;
//      Serial.println("Somebody is here.");
      Serial.println(val);
//    }
//    else  {
//      Serial.println("Nobody.");
//    }
  }
}
