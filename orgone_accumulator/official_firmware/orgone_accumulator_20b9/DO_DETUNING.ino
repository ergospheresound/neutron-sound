void DODETUNING() {


  pcounter = millis() - pcounterOld;//used for LED flash
  pcounterOld = millis();

//Serial.println(detune[0]);
  switch (FX) {
    case 0: //symetrical detune - primes (bipolar)
      bipolarFX = (constrain((((4095 - aInDetuneReading )<< 1) + (analogControls[2] - 4095)), -4095, 4095));
      aInModDetuneCubing = bipolarFX / 64.0;
      detuneScaler = (aInModDetuneCubing * aInModDetuneCubing * aInModDetuneCubing) / 8.0;
      if (bipolarFX > 0) {
        detune[1] = (int32_t)((detuneScaler / 32768.0) * (inputConverter));
        detune[2] = - detune[1];
        detune[3] = (int32_t)((detuneScaler / 16384.0) * (inputConverter)) ;
        detune[0] = - detune[3];
      }
      else {
        detuneScaler = detuneScaler * mixDetune;
        detune[0] = (int32_t)((detuneScaler * primes[0]) / 100000.0) ;
        detune[1] = -(int32_t)((detuneScaler * primes[1]) / 100000.0) ;
        detune[2] = (int32_t)((detuneScaler * primes[2]) / 100000.0) ;
        detune[3] = -(int32_t)((detuneScaler * primes[3]) / 100000.0) ;
      }
      break;

    case 1: //twin
      GRADUALWAVE();

      o1.phaseOffset = (uint32_t)( constrain(((4095 - aInDetuneReading) + (analogControls[2])), 0, 8190))<<20;//difference between the waves.
      //o1.phaseOffset = (map(o1.phaseOffset,0,8190,7000,100))<<20;
      o1.amp = 0;//turn off folding, using same ISR
      detune[0] = 0; //while in wavetwin dont want detuning
      break;

    case 2: //crush/fold distortions 1 (bipolar)
      bipolarFX = (constrain((((4095 - aInDetuneReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      if (bipolarFX > 0) {
        o1.amp = bipolarFX;
        FXMixer[0] = mixDetune;
        FXMixer[1] = 0;
        FXMixer[2] = 0;
        FXMixer[3] = 0;
      }
      else {
        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
        o1.amp = 0;
        FXMixer[0] = 0;
        FXMixer[1] = mixDetune;
        FXMixer[2] = 0;
        FXMixer[3] = 0;
        CRUSHBITS = (monopoleFX >> 10) + 8; //
        CRUSH_Remain = (monopoleFX << 22) >> 22;
      } //remainder used for mixing crush levels
      GRADUALWAVE();

      break;

    case 3: //Distortions2 (bipolar)
      bipolarFX = (constrain((((4095 - aInDetuneReading )<< 1) + (analogControls[2] - 4095)), -4095, 4095));
      if (bipolarFX > 0) {
        o1.amp = bipolarFX;
        FXMixer[0] = 0;
        FXMixer[1] = 0;
        FXMixer[2] = mixDetune;
        FXMixer[3] = 0;
      }
      else {
        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
        o1.amp = monopoleFX;
        FXMixer[0] = 0;
        FXMixer[1] = 0;
        FXMixer[2] = 0;
        FXMixer[3] = mixDetune;
      } 
      GRADUALWAVE();

    case 4: //chord allready bipolar
      chordArrayOffset = ((constrain(((4095 - aInDetuneReading) + (analogControls[2])), 0, 8190)) >> 10) * 3;
      for (int i = 0; i <= 2; i++) {
        chord[i] = (equalTemprementTable[chordTable[i + chordArrayOffset]]);
      }
      break;

    case 5: //spectrum bipolar
      bipolarFX = (constrain((((4095 - aInDetuneReading )<< 1) + (analogControls[2] - 4095)), -4095, 4095));
      aInModDetuneCubing = bipolarFX / 64.0;
      detuneScaler = (aInModDetuneCubing * aInModDetuneCubing * aInModDetuneCubing) / 200.0;
      if (bipolarFX > 0) {
        FXMixer[0] = 0;
       detuneScaler = (detuneScaler * mixDetune) / 4095.0;
         
        detune[0] = (int32_t)((detuneScaler * primes[0])) ;
        detune[1] = (int32_t)((detuneScaler * primes[1])) ;
        detune[2] = (int32_t)((detuneScaler * primes[2])) ;
        detune[3] = (int32_t)((detuneScaler * primes[3]));
      }
      else {
        if (pulsarOn){ FXMixer[1] = abs(bipolarFX) * mixDetune >> 9; FXMixer[0]=0;}
        else {FXMixer[0] = abs(bipolarFX) * mixDetune >> 9;FXMixer[1]=0;}
        detuneScaler = 0;
        detune[0]=detune[1]=detune[2]=detune[3]=0;
      }
      
      Lbuh = (analogControls[8] >> 9) * 9;
      Mbuh =  (analogControls[5] >> 9) * 9;
      Hbuh =  (analogControls[4] >> 9) * 9;
      break;

    case 6: //delay (bipolar)
      GRADUALWAVE();
      o3.phaseOffset = (uint32_t)(analogControls[8]) << 20;
      delayTime = constrain(((averageaInRAv - 4065) + averageratio), 8, 8190); //For Feedback altFX ratio knob
      delayFeedback = (int32_t)((analogControls[2]>>1)-2048)+(int32_t)((4095 - aInDetuneReading)>>1); //detune become feedback
      delayFeedback = constrain(delayFeedback,-2046,2046);
      break;

    case 7: //drum voice

      o8.phase_increment =  ((int32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time
    
      floats[0] = (float)((constrain(((4095-aInModIndex ) + (analogControls[1])), 0.0, 8191.0))/8192.0); //make a log pot of index.
      floats[0] =  (floats[0]*floats[0]*floats[0])*524288.0;
      o6.phase_increment = ((int32_t)floats[0])>>6; //the amount of xmod

      o1.amp = (constrain(((AInRawFilter-4095) + analogControls[0]), 0, 8191))>>3;//amount of pbend on fm freq pot

      drum_d = map(( analogControls[8]), 1, 8191, 24000, 24); //decaY 1
      if (detuneLoOn) drum_d = drum_d + (o1.phase_increment>>12);
      drum_d = signed_multiply_32x16t((drum_d * drum_d), drum_d << 13) + (32 << 10);
      
      drum_d2 = (map( analogControls[4], 1, 8191, 32000, 24)); //decay 2
      drum_d2 = signed_multiply_32x16t((drum_d2 * drum_d2), drum_d2 << 12) + (32 << 10);
      
      bipolarFX = (constrain((((4095 - aInDetuneReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));//detune amounts
      aInModDetuneCubing = (float)((abs(bipolarFX) / 9000.0));      
      detuneScaler = (aInModDetuneCubing * aInModDetuneCubing * aInModDetuneCubing);      
      //detuneScaler = 0;       
      
      if (bipolarFX > 0) {
        detune[0] = (int32_t)((detuneScaler * primes[0])+1 );
        detune[1] = (int32_t)((detuneScaler * primes[1])+1 );
        detune[2] = (int32_t)((detuneScaler * primes[2])+1);
        detune[3] = (int32_t)((detuneScaler * primes[3])+1);
      }
      else {
        detune[0] = (int32_t)((detuneScaler * fibi[0] * 55.0) +1);
        detune[1] = (int32_t)((detuneScaler * fibi[1]* 55.0)+1 );
        detune[2] = (int32_t)((detuneScaler * fibi[2]* 55.0)+1);
        detune[3] = (int32_t)((detuneScaler * fibi[3]* 55.0)+1);
      }
      break;
  }
}







