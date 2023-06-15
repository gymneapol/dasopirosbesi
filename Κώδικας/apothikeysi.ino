#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

#define WS_POWER_PIN  3
#define WS_SIGNAL_PIN A0

double flow=0; //Liters of passing water volume
unsigned long pulse_freq;

const int RELAY_PIN = 13;  // the Arduino pin, which connects to the IN pin of relay

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
    
  pinMode(2, INPUT);
  attachInterrupt(0, pulse, RISING); // Setup Interrupt

  pinMode(WS_POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(WS_POWER_PIN, LOW); // turn the sensor OFF
  pinMode(RELAY_PIN, OUTPUT);   // configure D7 pin as an OUTPUT

  
}

void loop() 
{
  
  flow = .0225 * pulse_freq;
  pulse_freq = 0; 
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("                ");
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Water Flow: ");
  lcd.print(flow);
  delay(500);

  digitalWrite(WS_POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  int value = analogRead(WS_SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(WS_POWER_PIN, LOW);   // turn the sensor OFF

  lcd.setCursor(2,1);   //Set cursor to character 2 on line 1  lcd.print("                ")
  lcd.print("                ");
  lcd.setCursor(2,1);   //Set cursor to character 2 on line 1
  lcd.print("Water Level: ");
  lcd.print(value);
  if (value> 150)
  {
    digitalWrite(RELAY_PIN, HIGH);
    delay(2500);
    digitalWrite(RELAY_PIN, LOW);
    delay(2500);
  }
}

void pulse () // Interrupt function

{
  pulse_freq++;
}