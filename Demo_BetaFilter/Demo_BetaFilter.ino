#define CHANNEL 12
byte PWM[CHANNEL] = {0}; //Output Register
byte PWM_Min = 0, PWM_Max = 0; //0 to 255
byte Level[CHANNEL] = {0}; //Let say 1 to 8
//------
float SensorNormalize[CHANNEL] = {0}; //Our counter
unsigned int Sensor[CHANNEL] = {0}; //Register for Raw input
float Beta = 0.999;
//--------
unsigned int Threshold;
bool Enable[CHANNEL] = {0}; //0 or 1
byte Alpha = 0; //Number of channel available
//--------

void setup() {

}

void loop() {

}

void Beta_filter() {
  Alpha = 0;
  //Gather Information
  for (int i = 0; i < CHANNEL; i++) {

  }
  //Normalize value
  for (int i = 0; i < CHANNEL; i++) {
    SensorNormalize[i] = SensorNormalize[i] * Beta + (1 - Beta) * Sensor[i];
  }
  //Calculate Alpha
  for (int i = 0; i < CHANNEL; i++) {
    if (SensorNormalize[i] > Threshold) Alpha += 1;
    else Enable[i] = false;
  }
  //Writeback to PWM register, with level and Alpha

  //Update PWM
  for (int i = 0; i < CHANNEL; i++) {
    if (Enable[i] == false) continue;
    else if (Enable[i] == true) {

    }
  }
}

