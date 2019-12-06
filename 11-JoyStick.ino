 /*
 * JoyStick
 * 双轴按键摇杆
 */
#define pinX  A0
#define pinY  A1
#define pinK  2

int value = 0;

void setup()
{
  pinMode(pinK, INPUT);
  Serial.begin(9600);
}

void loop()
{
  value = analogRead(pinX);
  Serial.print("X: ");
  Serial.print(value);

  value = analogRead(pinY);
  Serial.print(" Y: ");
  Serial.print(value);

  value = digitalRead(pinK);
  Serial.print(" Z: ");
  Serial.println(value);
  
  delay(1000);
}
