void UPDATECONTROLS_CZ() {


  switch (ARC + 1) {

    case 8:
//Serial.print(CRUSHBITS);
//Serial.print("     ");
//Serial.println(CRUSH_Remain);
      break;

    case 10:

      
      //outputs the frequency on USB serial. tune lock, FM and X must be off


      break;

    case 3:

      detuneAmountCont = analogControls[2];
      

      break;

    case 4:

      TUNELOCK_TOGGLE();

      waveTableMidLink = CZWTselMid[analogControls[5] >> 9];

      break;

    case 5:

      waveTable2Link = CZWTselLo[analogControls[8] >> 9];


      break;

    case 6: //select hi wave

      waveTableLink = CZWTselHi[analogControls[4] >> 9];

      break;

    case 1:
      mixPos = (analogControls[6] >> 5) << 4;

      OSC_MODE_TOGGLES();
     

      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0];
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);
      FMTable = CZWTselFM[analogControls[3] >> 9];

      break;


  }
}
//--------------------------------------------------------------------CZ-ALT--------------------------------------------------
void UPDATECONTROLS_CZALT() {

  switch (ARC + 1) {

    case 8:

      break;

    case 10:


      break;

    case 3:
      TUNELOCK_TOGGLE();
      detuneAmountCont = analogControls[2];
     
      break;

    case 4:

      waveTableMidLink = CZAltWTselMid[analogControls[5] >> 9];

      break;

    case 5:

      waveTable2Link = CZAltWTselLo[analogControls[8] >> 9];

      break;

    case 6: //no hi wave in alt(x) mode

      FMX_HiOffsetContCub = (analogControls[4] >> 3) - 512;
      FMX_HiOffsetCont = (int32_t)(FMX_HiOffsetContCub * FMX_HiOffsetContCub * FMX_HiOffsetContCub) >> 20;
    

    case 1:
      mixPos = (analogControls[6] >> 5) << 4;

      OSC_MODE_TOGGLES();
    


      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0];
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      FMTable = CZAltWTselFM[analogControls[3] >> 9];
      FMTableAMX = CZAltWTselFMAMX[analogControls[3] >> 9]; //am mod on hi position


      break;


  }
}


//----------------------------------------------------------------FM--------------------------------------------------------
void UPDATECONTROLS_FM() {

  switch (ARC + 1) {
    case 8: //8 and 10 are skipped when tune lock is on, do not use.
      break;
    case 10:
      break;

    case 3:
      TUNELOCK_TOGGLE();
      detuneAmountCont = analogControls[2];
          
      break;

    case 4: //mid wave
      waveTableMidLink = FMWTselMid[analogControls[5] >> 9];
      break;

    case 5:  //lo wave
      waveTable2Link = FMWTselLo[analogControls[8] >> 9];
      break;

    case 6: //select hi wave
      waveTableLink = FMWTselHi[analogControls[4] >> 9];

      break;

    case 1:
      mixPos = (analogControls[6] >> 1);

      OSC_MODE_TOGGLES();

      break;

    case 7:

      FX_TOGGLES();

      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);     

      FMTable = FMWTselFM[analogControls[3] >> 9];
      if ((analogControls[3] >> 9) == 15) WTShiftFM = 31;
      else WTShiftFM = 23;


      break;


  }
}
//--------------------------------------------------------------------------FMALT--------------------------------------------------------------

void UPDATECONTROLS_FMALT() {

  switch (ARC + 1) {

    case 8: //7 and 9 are skipped when tune lock is on, do not use.
      break;
      case 10:
      break;

    case 3:
      TUNELOCK_TOGGLE();
      detuneAmountCont = analogControls[2];
     
      break;

    case 4:
      waveTableMidLink = FMAltWTselMid[analogControls[5] >> 9];
      break;

    case 5:
      waveTable2Link = FMAltWTselLo[analogControls[8] >> 9];
      break;

    case 6: //select hi pitch offset
      FMX_HiOffsetContCub = ((analogControls[4]) - 2048) / 164.0 ;
      FMX_HiOffsetCont = FMX_HiOffsetContCub * FMX_HiOffsetContCub * FMX_HiOffsetContCub  ;

      break;

    case 1:
      mixPos = (analogControls[6] >> 1);

      OSC_MODE_TOGGLES();
     

      break;

    case 7:

      FX_TOGGLES();

      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);     

      FMTable = FMAltWTselFM[analogControls[3] >> 9];
      if ((analogControls[3] >> 9) == 15) WTShiftFM = 31;
      else WTShiftFM = 23;

      break;


  }
}

void UPDATECONTROLS_DRUM() {


  switch (ARC + 1) {

    case 8:

      break;

    case 10:




      break;

    case 3:

      detuneAmountCont = analogControls[2];

      break;

    case 4:

      TUNELOCK_TOGGLE();
     
      
      //((((drum_d * drum_d)>>16)+1)*drum_d)>>2;drum_d
      //drum decay

      break;

    case 5:

      drum_a = analogControls[5] << 10; //drum hold time

      break;

    case 6: //select hi wave

      

      break;

    case 1:
      mixPos = (analogControls[6] >> 5) << 4; //this is env > pitch control in drum mode

      OSC_MODE_TOGGLES();
     

      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:
      

      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      waveTableMidLink = drumWT[analogControls[3] >> 9]; //drum uses mid wave from fm

      break;


  }
}


