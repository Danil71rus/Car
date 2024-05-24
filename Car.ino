/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL44wZlpqkR"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "sj9fmdZxCzxtyosW6-dHTdQtZ3zfqX47"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Stepin71";
char pass[] = "354627DON71RUS";

BlynkTimer timer;
Servo sr;

unsigned long timing; // Переменная для хранения точки отсчета



// Движение Вперед
BLYNK_WRITE(V0)
{  
  int value = param.asInt();
  digitalWrite(D5, value);
  Serial.println(sr.read());
  
  // Update state
  // Blynk.virtualWrite(V1, value);
}

// Движение Назад
BLYNK_WRITE(V1)
{  
  int value = param.asInt();
  digitalWrite(D7, value);
}


// Повороты
BLYNK_WRITE(V4)
{  
  if (millis() - timing > 100) { // 100мс
    timing = millis(); 

    int value = param.asInt();
    value = map(value, 0, 100, 0, 170);
    Serial.println(value);
    Blynk.virtualWrite(V2, value); // передаем в V2
    sr.write(value);  
  }
}


BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  // Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{  
  // Debug console
  Serial.begin(115200);

  // 
  pinMode(D5, OUTPUT); // D5
  pinMode(D7, OUTPUT);
  sr.attach(D6);  
  sr.write(0);  


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  // timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
