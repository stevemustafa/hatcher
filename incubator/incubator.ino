#include <dht.h>

dht DHT;
int in1 = 9;


#define DHT11_PIN 7
#define PrimeTarget 37.5

double tempUpperBound  = (PrimeTarget + 1.5);
double tempLowerBound  = (PrimeTarget - 1.5);

unsigned long seconds = 1000L; // !!! SEE THE CAPITAL "L" USED!!!
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60;

bool switchOn = false;


void SetTemperatureBond() {
  tempUpperBound = PrimeTarget + 1.5;
  tempLowerBound = PrimeTarget - 1.5;
}

void setup() {
  
  //set temperatre bounds
  
  SetTemperatureBond();
  
  pinMode(in1, OUTPUT);
  digitalWrite(in1, LOW);
  
  Serial.begin(9600);
  //Serial.flush();
  
}

void LcdNotification()
{
  Serial.println(DHT.temperature, DEC);
  Serial.println(switchOn);
  Serial.println();
  delay(5 * seconds);
}

void temperatureCheck()
{
  double temp = DHT.temperature;

  if (temp <= tempLowerBound) {
    switchOn = true;
  }
  else if (temp >= tempUpperBound) {
    switchOn = false;
  }
}
  
void WarmingLoop()
{
  while (switchOn) {
    digitalWrite(in1, HIGH);  
    temperatureCheck();
  }
}

void loop() {

  LcdNotification();
  temperatureCheck();

  if (switchOn == true)
  {
    digitalWrite(in1, LOW);  
  }
  else if (switchOn == false) // if temp is greater than or equal to the upper bound, switch off
  {
    digitalWrite(in1, HIGH);
  }
  
 

  //check the temperature
  int chk = DHT.read11(DHT11_PIN);
  double temp = DHT.temperature;


/*
  digitalWrite(in1, LOW);
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);

  

  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);

  delay(2500);

  digitalWrite(in1, HIGH);    
  delay(1000);
  digitalWrite(in1, LOW   );    
  */
  //check if temperature is in between the bounds

 /*
  //if the temperture is less than the lower bound, turn on the lamp
  if (temp <= tempLowerBound)
  {
    digitalWrite(in1, HIGH);  
  }
  else if (temp >= tempUpperBound) // if temp is greater than or equal to the upper bound, switch off
  {
    digitalWrite(in1, LOW);
  }

  delay(2 * minutes);*/

}
