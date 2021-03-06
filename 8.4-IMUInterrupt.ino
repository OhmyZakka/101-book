/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.
   See the bottom of this file for full license terms.
*/

/*
   This sketch example demonstrates how the BMI160 accelerometer on the
   Intel(R) Curie(TM) module can be used to detect zero motion events
*/

#include "CurieIMU.h"

boolean ledState = false;          // state of the LED
void setup() {
  Serial.begin(9600); // initialize Serial communication
  while(!Serial) ;    // wait for serial port to connect.

  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Zero Motion Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_ZERO_MOTION, 50);  // 50mg
  CurieIMU.setDetectionDuration(CURIE_IMU_ZERO_MOTION, 2);    // 2s
  CurieIMU.interrupts(CURIE_IMU_ZERO_MOTION);

  /* Enable Motion Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 20);      // 20mg
  CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 10);       // trigger times of consecutive slope data points
  CurieIMU.interrupts(CURIE_IMU_MOTION);

  Serial.println("IMU initialisation complete, waiting for events...");
}

void loop() {
  // if zero motion is detected, LED will be turned up. 
  digitalWrite(13, ledState);
}

static void eventCallback(void){
  if (CurieIMU.getInterruptStatus(CURIE_IMU_ZERO_MOTION)) {
    ledState = true; 
    Serial.println("zero motion detected...");
  }  
  if (CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)) {
    ledState = false;
    if (CurieIMU.motionDetected(X_AXIS, POSITIVE))
      Serial.println("Negative motion detected on X-axis");
    if (CurieIMU.motionDetected(X_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on X-axis");
    if (CurieIMU.motionDetected(Y_AXIS, POSITIVE))
      Serial.println("Negative motion detected on Y-axis");
    if (CurieIMU.motionDetected(Y_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on Y-axis");
    if (CurieIMU.motionDetected(Z_AXIS, POSITIVE))
      Serial.println("Negative motion detected on Z-axis");
    if (CurieIMU.motionDetected(Z_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on Z-axis");
  }  
}
