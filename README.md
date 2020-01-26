## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)

By design, Blynk user can run ESP32 boards with either WiFi or BT/BLE by using different sketches, and have to upload / update firmware to change. This library enables user to  include both Blynk BT / BLE and WiFi libraries in one sketch, then select one to use at runtime after reboot.

### Installation

The suggested way to install is to:

1. Navigate to [BlynkESP32_BT_WF] (https://github.com/khoih-prog/BlynkESP32_BT_WF) page.
2. Download the latest release `BlynkESP32_BT_WF-master.zip`.
3. Extract the zip file to `BlynkESP32_BT_WF-master` directory 
4. Copy whole `BlynkESP32_BT_WF-master/src` folder to Arduino libraries' `src` directory such as `~/Arduino/libraries/Blynk/src`.

The file BlynkSimpleEsp32_BT_WF.h, and BlynkSimpleEsp32_WF.h must be placed in Blynk libraries `src` directory (normally `~/Arduino/libraries/Blynk/src`)

Another way is to use `Arduino Library Manager`. Search for `BlynkSimpleEsp32_BT_WF.h`, then select / install the latest version.

### How to use

In your code, replace
1. `BlynkSimpleEsp32_BT_WF.h` with `BlynkSimpleEsp32_BT_WF.h`
2. `BlynkSimpleEsp32_BLE.h`   with `BlynkSimpleEsp32_BLE_WF.h`
3. `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WF.h`
4. `Blynk.run();`             with `Blynk_BT.run()` for BlueTooth related function calls

or 
5. `Blynk.run();`             with `Blynk_BLE.run()` for BLE related function calls


That's it.

Also see examples: 
1. [Geiger_Counter](examples/Geiger_Counter)
2. [Geiger_Counter_OLED](examples/Geiger_Counter_OLED)

and real-life project [Hack GMC Geigercounter With Blynk](https://www.instructables.com/id/Hack-GMC-Geigercounter-With-Blynk/) of  [Crosswalkersam](https://community.blynk.cc/u/Crosswalkersam)

https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Blynk.jpg
https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Box1.jpg
https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Blynk.jpg
https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Schematics.jpg

## Prerequisite
* `ESP32 core 1.0.4 or later`
* `Blynk library 0.6.1 or later` (https://www.arduino.cc/en/guide/libraries#toc3)

## Sample code
```
#define BLYNK_PRINT Serial

#define BLYNK_USE_BT_ONLY      false  //true

#if BLYNK_USE_BT_ONLY
#include <BlynkSimpleEsp32_BT_WF.h>
#else
#include <BlynkSimpleEsp32_BT_WF.h>
#include <BlynkSimpleEsp32_WF.h>
#define BT_OR_WIFI_OPTION_PIN      14        // Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32
char ssid[] = "SSID";
char pass[] = "PASS";
#endif

char auth[] = "****";

bool USE_BT = true;

void setup() 
{
  ....
    
  #if BLYNK_USE_BT_ONLY
    Blynk_BT.setDeviceName("ESP32_BT_WF");
    Blynk_BT.begin(auth);
  #else
    if (digitalRead(BT_OR_WIFI_OPTION_PIN) == HIGH)
    {
      Serial.println(F("BT_OR_WIFI_OPTION_PIN HIGH, Use WiFi"));
      Blynk_WF.begin(auth, ssid, pass);
      USE_BT = false;
    }
    else
    {
      Serial.println(F("BT_OR_WIFI_OPTION_PIN LOW, Use BT"));
      Blynk_BT.setDeviceName("ESP32_BT_WF");
      Blynk_BT.begin(auth);
    }
  #endif
  ...
}

void loop()
{
  if (USE_BT)
    Blynk_BT.run();
  else
    Blynk_WF.run();
}
```

### Releases v1.0.0

***Why this version***

The Blynk ESP32 libraries for BlueTooth, BLE and WiFi, by design, can't coexist. So that when we'd like to use either WiFi or BlueTooth / BLE, it's not possible within the same sketch.
With this libraries modifications, we now can compile with both options, then select one (WiFi or BT/BLE) to run at run-time by pressing a switch.


## TO DO

1. Same features for other boards with WiFi / BT
2. Optimize library so that smaller code size. Currently 2 instances of Blynk coexist and don't share code.

### Contributions and thanks
1. Thanks to [Crosswalkersam](https://community.blynk.cc/u/Crosswalkersam) for the original code and request to inspire the work.

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2020- Khoi Hoang
