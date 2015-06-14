/*macro definition of water sensor and the buzzer*/
#define WATER_SENSOR 2
#define SPEAKER 3
int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7
void setup()
{
	pins_init();
}
void loop()
{
	if(isExposedToWater())
	sound(3);
        delay(1000);
}
void pins_init()
{
	pinMode(WATER_SENSOR, INPUT);
	pinMode(SPEAKER, OUTPUT);
        digitalWrite(SPEAKER,LOW);
}
/************************************************************************/
/*Function: When the sensor is exposed to the water, the buzzer sounds	*/
/*			for 2 seconds.												*/
void sound(uint8_t note_index)
{
	for(int i=0;i<100;i++)   
 	{
		digitalWrite(SPEAKER,HIGH);
		delayMicroseconds(BassTab[note_index]);
		digitalWrite(SPEAKER,LOW);
		delayMicroseconds(BassTab[note_index]);
	}
}
/************************************************************************/
/*Function: Determine whether the sensor is exposed to the water		*/
/*Parameter:-void           											*/
/*Return:	-boolean,if it is exposed to the water,it will return true. */
boolean isExposedToWater()
{
	if(digitalRead(WATER_SENSOR) == LOW)
		return true;
	else return false;
}
