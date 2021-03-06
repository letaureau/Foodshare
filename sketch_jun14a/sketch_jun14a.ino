unsigned int egg_sensor1;
unsigned int egg_sensor2;
unsigned int freshness_ind;
void setup(void) 
{
  Serial.begin(115200);
  foodshare_setup();
}

void loop(void) 
{
//  ChillHub.loop();
  foodshare_loop();
  delay(300);
}
 
void foodshare_setup() 
{
  
  // load FSR limits here
//  for (int j = 0; j < 3; j++) {
//    int iStart = j*4;
//    LO_MEAS[j] = (EEPROM.read(iStart+0) << 8) | EEPROM.read(iStart+1);
//    HI_MEAS[j] = (EEPROM.read(iStart+2) << 8) | EEPROM.read(iStart+3);
//  }
  
  // subscribe to door messages to trigger 
  //  ChillHub.subscribe(doorStatusMsgType, (chillhubCallbackFunction)readEggPresence);
  
  // setup factory calibration listener
  //  ChillHub.addCloudListener(0x94, (chillhubCallbackFunction)factoryCalibrate);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(A0,INPUT);
  foodshare_announce();
}

void foodshare_announce(void) {

  // Each device has a "type name" and a UUID.
  // A type name could be something like "toaster" or "light bulb"
//  ChillHub.setup("foodshare", FOODSHARE_UUID);

  // add a listener for device ID request type
  // Device ID is a request from the chill hub for the Arduino to register itself.
//  ChillHub.subscribe(deviceIdRequestType, (chillhubCallbackFunction) foodshare_announce);

  // add a listener for keepalive from chillhub
  // The chillhub sends this periodcally.
//  ChillHub.subscribe(keepAliveType, (chillhubCallbackFunction)keepaliveCallback);

  // add a listener for setting the UUID of the device
  // The UUID is set via the USB port and the set-device-uuid.js script as part of
  // chillhub-firmware.
  // No cloud listener is required for this.
  //v - Commenting out for now
  // ChillHub.subscribe(setDeviceUUIDType, (chillhubCallbackFunction)setDeviceUUID);

/*  ChillHub.createCloudResourceU16("egg_present1", EGG_SENSOR_ID1, 0, egg_sensor1);
  ChillHub.createCloudResourceU16("egg_present2", EGG_SENSOR_ID2, 0, egg_sensor2);
  ChillHub.createCloudResourceU16("freshness_ind", FRESHNESS_ID, 0, freshness_ind);
*/
}


 // This handles the keep alive message from the chillhub.
// This chillhub will send this message periodically.
void keepaliveCallback(uint8_t dummy) {
  (void)dummy;
}

/*void setDeviceUUID(char *pUUID) {
  uint8_t len = (uint8_t)pUUID[0];
  char *pStr = &pUUID[1];
  
  if (len <= MAX_UUID_LENGTH) {
    // add null terminator
    pStr[len] = 0;
    memcpy(FOODSHARE_UUID, pStr, len+1);
    saveEeprom();
  } 
}

*/



void foodshare_loop()
//unsigned char doorStatus) 
{
    //boolean doorNowOpen = (doorStatus & 0x01);
    
    unsigned int sensorReading;
    int backup1=egg_sensor1;
    int backup2=egg_sensor2;
    int backup3=freshness_ind;
    int avg[10];
    int total =0;
    //if (doorWasOpen && !doorNowOpen) {
    if(digitalRead(6)==HIGH)  
    {
      egg_sensor1 =1;
    }
    else  
    {
      egg_sensor1=0;
    }    
    if(digitalRead(7)==HIGH)  
    {
      egg_sensor2=1;
    }
    else  
    {
      egg_sensor2=0;
    }
    //freshness_ind = map(analogRead(A0), 30, 300, 100, 0); 
    Serial.print(egg_sensor1);
    Serial.print("\t");
    Serial.print(egg_sensor2);
    Serial.print("\t new value ");
    //Serial.print(freshness_ind);
    for(int i=0;i<10;i++)
    {
      avg[i]=map(analogRead(A0), 30, 300, 100, 0);
      total+=avg[i];
      delay(50);
    }
    freshness_ind = total/10;
    total=0;
    Serial.print(freshness_ind);
    //applyFsrCurve(sensorWeights, sensorReadings);
    
    //unsigned int weight = sensorWeights[0] + 
    //  sensorWeights[1] + 
    //  sensorWeights[2];
  
    /*if (weight >= (FULL_WEIGHT - DIFF_THRESHOLD)) {
    //  for (int j = 0; j < 3; j++)
    //    HI_MEAS[j] = sensorReadings[j];
    //  storeLimits();
    //}
    //else if (weight < (EMPTY_WEIGHT + DIFF_THRESHOLD)) {
      for (int j = 0; j < 3; j++)
        LO_MEAS[j] = sensorReadings[j];
      storeLimits();
    }*/
    
    /*ChillHub.sendU16Msg(EGG_SENSOR_ID1, egg_sensor1);
    ChillHub.sendU16Msg(EGG_SENSOR_ID2, egg_sensor2);
    ChillHub.sendU16Msg(FRESHNESS_ID, freshness_ind); */
    if(backup1!=egg_sensor1)
    {
      Serial.print("\t sensor 1 changed \t");
    //  ChillHub.updateCloudResourceU16(EGG_SENSOR_ID1, egg_sensor1);
    }
    if(backup2!=egg_sensor2)
    {
      Serial.print("\t sensor 2 changed \t");
   //   ChillHub.updateCloudResourceU16(EGG_SENSOR_ID2, egg_sensor2);
    }
    int diff=backup3-freshness_ind;
    Serial.print("\t prev value ");
    Serial.print(backup3);
    //Serial.print("\t");
    //Serial.print(freshness_ind);
    Serial.print("\t diff ");
    Serial.print(diff);
    if(abs(diff) >5)
    {
    /*  Serial.print("\t");
      Serial.print(backup3);
      Serial.print("\t");
      Serial.print(freshness_ind);
      Serial.print("\t");
      Serial.print(diff);*/
      Serial.print("\t sensor 3 changed \t");
    //  ChillHub.updateCloudResourceU16(FRESHNESS_ID, freshness_ind);
    }
  Serial.println();
}

