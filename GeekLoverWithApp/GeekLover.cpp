/*
  GeekLover
  Dev by PépéMax (A Geek too much in love)
*/

#include <Arduino.h>
#include <WiFi.h>

#include <WiFiManager.h>
#include <ESPAsyncWebServer.h>
#include <NTPClient.h>

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

AsyncWebServer server(80);

int count = 0;
int count_save = 0;

unsigned long the_day_all_men_must_remember = 1596844800; //Your meeting day converts to timestamp (for me 08 august 2020)

unsigned long nowInSecond;

unsigned long loveDuration;

WiFiUDP ntpUDP;

NTPClient temps(ntpUDP, "fr.pool.ntp.org", 3600, 1000); //3600 = TimeOffset for my country (France) and 1000 = frequency of update time

//callback notifying us of the need to save config
void saveConfigCallback()
{
    
  ESP.restart();

}

void setup()
{

  ld.printDigit(00000000);

  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  Serial.begin(115200);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result
  wm.setSaveConfigCallback(saveConfigCallback);

  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  wm.autoConnect("GeekLover", "!GeekLover!"); // password protected ap

  if (WiFi.status() == WL_CONNECTED)
  {
    temps.setUpdateInterval(500);

    Serial.println(WiFi.localIP());

    temps.begin();

    //Set display in secondes
    server.on("/seconds", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                count = 0;
                Serial.println(loveDuration);
                request->send(200, "text/plain", String(1));
                Serial.println("Requête nb");
              });

    //Set display in minutes
    server.on("/minutes", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                count = 1;
                Serial.println(loveDuration);
                request->send(200, "text/plain", String(1));
                Serial.println("Requête nb");
              });

    //Set display in hours
    server.on("/hours", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                count = 2;
                Serial.println(loveDuration);
                request->send(200, "text/plain", String(1));
                Serial.println("Requête nb");
              });

    //Set display in days
    server.on("/days", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                count = 3;
                Serial.println(loveDuration);
                request->send(200, "text/plain", String(1));
                Serial.println("Requête state");
              });

    //Set display in weeks
    server.on("/weeks", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                count = 4;
                Serial.println(loveDuration);
                request->send(200, "text/plain", String(1));
                Serial.println("Requête nb");
              });

    // //Set display in months
    // server.on("/months", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //             count = 5;
    //             Serial.println(loveDuration);
    //             request->send(200, "text/plain", String(1));
    //             Serial.println("Requête nb");
    //           });

    // //Set display in years
    // server.on("/years", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //             count = 6;
    //             Serial.println(loveDuration);
    //             request->send(200, "text/plain", String(1));
    //             Serial.println("Requête state");
    //           });

    /* Set the brightness min:1, max:15 */
    ld.setBright(10);

    /* Set the digit count */
    ld.setDigitLimit(8);

    temps.forceUpdate();
    server.begin();
  }
}

// unsigned long convertToYears(unsigned long secondes)
// {
//   return secondes / 1540000000;
// }

// unsigned long convertToMonths(unsigned long secondes)
// {
//   return secondes / 628000000;
// }

unsigned long convertToWeeks(unsigned long secondes)
{
  return secondes / 604800;
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

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    nowInSecond = temps.getEpochTime();

    loveDuration = nowInSecond - the_day_all_men_must_remember;

    switch (count)
    {
    case 0:
      /* Display in seconds */

      if (count_save != count)
      {
        ld.clear();
        count_save = count;
      }

      if (loveDuration > 99999999)
      {
        //I have about 2 and a half years left to find a solution when the counter reaches 99999999 seconds.
      }
      ld.printDigit(loveDuration);

      break;

    case 1:
      /* Display in minutes */
      if (count_save != count)
      {
        ld.clear();
        count_save = count;
      }
      ld.printDigit(convertToMinutes(loveDuration));
      break;

    case 2:
      /* Display in hours */
      if (count_save != count)
      {
        ld.clear();
        count_save = count;
      }
      ld.printDigit(convertToHours(loveDuration));
      break;

    case 3:
      /* Display in days */
      if (count_save != count)
      {
        ld.clear();
        count_save = count;
      }
      ld.printDigit(convertToDays(loveDuration));
      break;
    case 4:
      /* Display in weeks */
      if (count_save != count)
      {
        ld.clear();
        count_save = count;
      }
      ld.printDigit(convertToWeeks(loveDuration));
      break;
      // case 5:
      //   /* Display in months */
      //   if (count_save != count)
      //   {
      //     ld.clear();
      //     count_save = count;
      //   }
      //   ld.printDigit(convertToMonths(loveDuration));
      //   break;
      // case 6:
      //   /* Display in years */
      //   if (count_save != count)
      //   {
      //     ld.clear();
      //     count_save = count;
      //   }
      //   ld.printDigit(convertToYears(loveDuration));
      //   break;

    default:
      break;
    }
  }
}