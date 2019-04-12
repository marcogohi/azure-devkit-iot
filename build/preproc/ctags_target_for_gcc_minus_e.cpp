# 1 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
# 1 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
// To get started please visit https://microsoft.github.io/azure-iot-developer-kit/docs/projects/connect-iot-hub?utm_source=ArduinoExtension&utm_medium=ReleaseNote&utm_campaign=VSCode
# 5 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2
# 6 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2
# 7 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2

# 9 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2
# 10 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2
# 11 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 2

static bool hasWifi = false;
int messageCount = 1;
static bool messageSending = true;
static uint64_t send_interval_ms;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
static void InitWifi()
{
  Screen.print(2, "Connecting...");

  if (WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Screen.print(1, ip.get_address());
    hasWifi = true;
    Screen.print(2, "Running... \r\n");
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi\r\n ");
  }
}

static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result)
{
  if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
  {
    blinkSendConfirmation();
  }
}

static void MessageCallback(const char* payLoad, int size)
{
  blinkLED();
  Screen.print(1, payLoad, true);
}

static void DeviceTwinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char *payLoad, int size)
{
  char *temp = (char *)malloc(size + 1);
  if (temp == 
# 54 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
             __null
# 54 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
                 )
  {
    return;
  }
  memcpy(temp, payLoad, size);
  temp[size] = '\0';
  parseTwinMessage(updateState, temp);
  free(temp);
}

static int DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size)
{
  do{{ if (0) { (void)printf("Try to invoke method %s", methodName); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 66 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
 __null
# 66 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 66, 0x01, "Try to invoke method %s", methodName); } }; }while((void)0,0);
  const char *responseMessage = "\"Successfully invoke device method\"";
  int result = 200;

  if (strcmp(methodName, "start") == 0)
  {
    do{{ if (0) { (void)printf("Start sending temperature and humidity data"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 72 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
   __null
# 72 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 72, 0x01, "Start sending temperature and humidity data"); } }; }while((void)0,0);
    messageSending = true;
  }
  else if (strcmp(methodName, "stop") == 0)
  {
    do{{ if (0) { (void)printf("Stop sending temperature and humidity data"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 77 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
   __null
# 77 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 77, 0x01, "Stop sending temperature and humidity data"); } }; }while((void)0,0);
    messageSending = false;
  }
  else
  {
    do{{ if (0) { (void)printf("No method %s found", methodName); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 82 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
   __null
# 82 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 82, 0x01, "No method %s found", methodName); } }; }while((void)0,0);
    responseMessage = "\"No method found\"";
    result = 404;
  }

  *response_size = strlen(responseMessage) + 1;
  *response = (unsigned char *)strdup(responseMessage);

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup()
{
  Screen.init();
  Screen.print(0, "IoT DevKit");
  Screen.print(2, "Initializing...");

  Screen.print(3, " > Serial");
  Serial.begin(115200);

  // Initialize the WiFi module
  Screen.print(3, " > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    return;
  }

  EEPROMInterface eeprom;
  uint8_t temp[100];
  if (eeprom.read(temp, 100, 0, 5) == -1)
  {
    do{{ if (0) { (void)printf("Error reading"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 117 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
   __null
# 117 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 117, 0x01, "Error reading"); } }; }while((void)0,0);
  }
  else
  {
    do{{ if (0) { (void)printf((char *)temp); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 121 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
   __null
# 121 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 121, 0x01, (char *)temp); } }; }while((void)0,0);
  }



  Screen.print(3, " > Sensors");
  SensorInit();

  Screen.print(3, " > IoT Hub");
  DevKitMQTTClient_SetOption("MiniSolution", "DevKit-GetStarted");
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
  DevKitMQTTClient_SetMessageCallback(MessageCallback);
  DevKitMQTTClient_SetDeviceTwinCallback(DeviceTwinCallback);
  DevKitMQTTClient_SetDeviceMethodCallback(DeviceMethodCallback);

  send_interval_ms = SystemTickCounterRead();
}

void loop()
{
  if (hasWifi)
  {
    if (messageSending &&
        (int)(SystemTickCounterRead() - send_interval_ms) >= getInterval())
    {
      // Send teperature data
      char messagePayload[256];

      bool temperatureAlert = readMessage(messageCount++, messagePayload);
      EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(messagePayload, MESSAGE);
      DevKitMQTTClient_Event_AddProp(message, "temperatureAlert", temperatureAlert ? "true" : "false");
      DevKitMQTTClient_SendEventInstance(message);

      send_interval_ms = SystemTickCounterRead();
      do{{ if (0) { (void)printf(" > Message sent"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 157 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino" 3 4
     __null
# 157 "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino"
     ) l(AZ_LOG_INFO, "c:\\Users\\marco.gonzalez\\Documents\\IoTWorkbenchProjects\\examples\\devkit_getstarted\\Device\\GetStarted.ino", __func__, 157, 0x01, " > Message sent"); } }; }while((void)0,0);
    }
    else
    {
      DevKitMQTTClient_Check();
    }
  }
  delay(1000);
}
