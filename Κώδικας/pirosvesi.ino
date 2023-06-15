// Sensor pins pin D6 LED output, pin A0 analog Input

#include <DHT.h>;
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

#define DHTPIN 2            //what pin we're connected to
#define DHTTYPE DHT21       //DHT 21  (AM2301)
DHT dht(DHTPIN, DHTTYPE);   //Initialize DHT sensor for normal 16mhz Arduino

#define sensorPin A0

#define WS_POWER_PIN  5
#define WS_SIGNAL_PIN A1

const int RELAY_PIN = 3;  // the Arduino pin, which connects to the IN pin of relay

int hum;  //Stores humidity value
float temp; //Stores temperature value
int gasval;

void setup() {
  pinMode(WS_POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(WS_POWER_PIN, LOW); // turn the sensor OFF
  pinMode(RELAY_PIN, OUTPUT);

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  Serial.begin(9600);
  dht.begin();
 
  delay(5000);

}

void loop() {
  delay(1000);

  hum = dht.readHumidity();
  temp= dht.readTemperature();

  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("                ");
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("H: ");
  lcd.print(hum);
  lcd.print(" T: ");
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print("                ");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  gasval=readSensor();
  lcd.print("Gas:");
  lcd.print(gasval);
  Serial.println(gasval);
  delay(500);

  digitalWrite(WS_POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  int value = analogRead(WS_SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(WS_POWER_PIN, LOW);   // turn the sensor OFF

  lcd.setCursor(9,1);   //Set cursor to character 2 on line 1
  lcd.print("WL: ");
  lcd.print(value);
  Serial.print("wl: ");
  Serial.println(value);

  if (gasval>65 && value>390)
  {
    digitalWrite(RELAY_PIN, HIGH);
    delay(1500);
    digitalWrite(RELAY_PIN, LOW);
    delay(3500);
  }
}

//  This function returns the analog data to calling function

int readSensor() {

  unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor

  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data

  if (outputValue > 65)

    Serial.println("Alarm!!!!");

  else

    Serial.println("Normal!!!");

  return outputValue;             // Return analog moisture value

}

