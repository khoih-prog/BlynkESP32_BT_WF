/****************************************************************************************************************************
  Credentials.h
  For ESP32 using WiFi along with BlueTooth BLE
  
  BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. 
  Then select either one or both at runtime.
  
  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/BlynkESP32_BT_WF
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef Credentials_h
#define Credentials_h

#if USE_BLYNK_WM

  /// Start Default Config Data //////////////////
  
  /*
    // Defined in <BlynkSimpleESP32_WFM.h>
  
    #define SSID_MAX_LEN      32
    #define PASS_MAX_LEN      64
    
    typedef struct
    {
    char wifi_ssid[SSID_MAX_LEN];
    char wifi_pw  [PASS_MAX_LEN];
    }  WiFi_Credentials;
  
    #define BLYNK_SERVER_MAX_LEN      32
    #define BLYNK_TOKEN_MAX_LEN       36
  
    typedef struct
    {
    char blynk_server[BLYNK_SERVER_MAX_LEN];
    char blynk_token [BLYNK_TOKEN_MAX_LEN];
    }  Blynk_Credentials;
  
    #define NUM_WIFI_CREDENTIALS      2
    #define NUM_BLYNK_CREDENTIALS     2
  
    typedef struct Configuration
    {
    char header         [16];
    WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
    Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    int  blynk_port;
    char board_name     [24];
    int  checkSum;
    } Blynk_WM_Configuration;
  
  */
  
  //bool LOAD_DEFAULT_CONFIG_DATA = true;
  bool LOAD_DEFAULT_CONFIG_DATA = false;
  
  Blynk_WM_Configuration defaultConfig =
  {
    //char header[16], dummy, not used
  #if USE_SSL  
    "SSL",
  #else
    "NonSSL",
  #endif
    //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
    //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
    "SSID1", "password1",
    "SSID2", "password2",
    // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
    "account.ddns.net",     "token",
    "account.duckdns.org",  "token1", 
    //int  blynk_port;
  #if USE_SSL
    9443,
  #else
    8080,
  #endif
    //char board_name     [24];
    "ESP32-BLE-WF",
    //int  checkSum, dummy, not used
    0
  };
  
  /////////// End Default Config Data /////////////

#endif    // #if USE_BLYNK_WM

#endif    //Credentials_h
