/*
  GeekLover
  Dev by PépéMax (A Geek too much in love)
*/

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <DigitLedDisplay.h>

/* Arduino Pin to Display Pin
   4 to DIN,
   0 to CS,
   2 to CLK 
*/
#define DIN 4
#define CS 0
#define CLK 2

DigitLedDisplay ld = DigitLedDisplay(DIN, CS, CLK);

const int BUTTON = 21; //Declare button pin

const char *ssid = "YOUR-SSID";
const char *mdp = "YOUR_PASSWORD";

int buttonCounter = 0;
int buttonCounter_save = 0;

unsigned long the_day_all_men_must_remember = 1596844800; //Your meeting day converts to timestamp (for me 08 august 2020)

unsigned long nowInSecond;

unsigned long loveDuration;

WiFiUDP ntpUDP;

NTPClient temps(ntpUDP, "fr.pool.ntp.org", 3600, 1000); //3600 = TimeOffset for my country (France) and 1000 = frequency of update time 

void setup()
{

  Serial.begin(115200);

  temps.setUpdateInterval(500);

  WiFi.begin(ssid, mdp);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  temps.begin();

  pinMode(BUTTON, INPUT_PULLUP);

  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);

  temps.forceUpdate();
}

unsigned long convertToDays(unsigned long secondes)
{
  return secondes / 86400;
}

unsigned long convertToHours(unsigned long secondes)
{
  return secondes / 3600;
}

unsigned long convertToMinutes(unsigned long secondes)
{
  return secondes / 60;
}

void convertSecond(unsigned long secondes)
{

}

void loop()
{

  if (digitalRead(BUTTON) == 0)
  {
    delay(500);
    buttonCounter++;
    if (buttonCounter > 3)
    {
      buttonCounter = 0;
    }

    Serial.println(buttonCounter);
  }

  nowInSecond = temps.getEpochTime();

  loveDuration = nowInSecond - the_day_all_men_must_remember;

  switch (buttonCounter)
  {
  case 0:
    /* Display in seconds */

    if (buttonCounter_save != buttonCounter)
    {
      ld.clear();
      buttonCounter_save = buttonCounter;
    }

    if (loveDuration > 99999999)
    {
      //I have about 2 and a half years left to find a solution when the counter reaches 99999999 seconds. 
    }
    ld.printDigit(loveDuration);

    break;

  case 1:
    /* Display in minutes */
    if (buttonCounter_save != buttonCounter)
    {
      ld.clear();
      buttonCounter_save = buttonCounter;
    }
    ld.printDigit(convertToMinutes(loveDuration));
    break;

  case 2:
    /* Display in hours */
    if (buttonCounter_save != buttonCounter)
    {
      ld.clear();
      buttonCounter_save = buttonCounter;
    }
    ld.printDigit(convertToHours(loveDuration));
    break;

  case 3:
    /* Display in days */
    if (buttonCounter_save != buttonCounter)
    {
      ld.clear();
      buttonCounter_save = buttonCounter;
    }
    ld.printDigit(convertToDays(loveDuration));
    break;

  default:
    break;
  }
}