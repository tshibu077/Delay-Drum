//analog pins I can use: 1, 2, 3, 6, 7)
#define FSR_PIN_1 A7                //synth 1
#define FSR_PIN_2 A6                //synth 2
#define FSR_PIN_3 A3                //synth 3

#define POT_PIN_1 A1  //white       piezo short delay
#define POT_PIN_2 A2  //yellow      speed of looped piece

int blackPin = 0;   //blue wire     loop control button
int yellowPin = 2;  //white wire    choose synth sound 
int whitePin = 1;   //yellow wire   
int switchPin = 3;  //slide pot     switch between synth/piezo loop

#include <Bounce.h>

Bounce button0 = Bounce(blackPin, 15);   
Bounce button1 = Bounce(yellowPin, 15);   
Bounce button2 = Bounce(whitePin, 15);   
//Bounce switch0 = Bounce(switchPin, 15);   
int switch0 = 1;

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum1;          //xy=1170.3999977111814,844.3999938964841
AudioSynthSimpleDrum     drum2;          //xy=1170.400016784668,884.4000244140625
AudioSynthSimpleDrum     drum3;          //xy=1170.400016784668,922.4000263214111
AudioSynthWaveformSine   sine2;          //xy=1176.4000244140625,1069.0000305175781
AudioSynthWaveformSine   sine1;          //xy=1177.4000244140625,1023.0000305175781
AudioSynthWaveformSine   sine3;          //xy=1177.4000244140625,1114.0000305175781
AudioEffectEnvelope      envelope3;      //xy=1314.4000244140625,1113.0000305175781
AudioEffectEnvelope      envelope2;      //xy=1320.4000244140625,1067.0000305175781
AudioEffectEnvelope      envelope1;      //xy=1323.4000244140625,1024.0000305175781
AudioMixer4              drum_mixer;         //xy=1324.0000190734863,887.5999946594238
AudioMixer4              sine_mixer;     //xy=1488.4000244140625,1074.0000305175781
AudioInputI2S            piezo;          //xy=1506.4000244140625,416.0000305175781
AudioMixer4              piezodelay_input; //xy=1762.4000244140625,512.0000305175781
AudioMixer4              synth_mixer;    //xy=1762.4000244140625,890.0000305175781
AudioEffectDelay         piezodelay;     //xy=1769.400074005127,689.0000839233398
AudioEffectDelayExternal delayext(AUDIO_MEMORY_CY15B104);       //xy=2201.4000244140625,796.0000305175781
//AudioEffectDelayExternal delayext;       //xy=2201.4000244140625,796.0000305175781
AudioMixer4              delayext_input; //xy=2202.4000244140625,638.0000305175781
AudioSynthWaveformSine   synthloopbutton; //xy=2263.400321960449,1023.0000886917114
AudioSynthWaveformSine   piezoloopbutton; //xy=2267.4000244140625,953.0000305175781
AudioEffectEnvelope      envelopep;      //xy=2482.4000244140625,952.0000305175781
AudioEffectEnvelope      envelopes;      //xy=2484.4000244140625,1022.0000305175781
AudioMixer4              final_mixer;    //xy=2671.4000244140625,418.0000305175781
AudioMixer4              outmixer;      //xy=2749.4000244140625,792.0000305175781
AudioOutputI2S           audio_output;   //xy=2982.4000244140625,752.0000305175781
AudioConnection          patchCord1(drum1, 0, drum_mixer, 0);
AudioConnection          patchCord2(drum2, 0, drum_mixer, 1);
AudioConnection          patchCord3(drum3, 0, drum_mixer, 2);
AudioConnection          patchCord4(sine2, envelope2);
AudioConnection          patchCord5(sine1, envelope1);
AudioConnection          patchCord6(sine3, envelope3);
AudioConnection          patchCord7(envelope3, 0, sine_mixer, 2);
AudioConnection          patchCord8(envelope2, 0, sine_mixer, 1);
AudioConnection          patchCord9(envelope1, 0, sine_mixer, 0);
AudioConnection          patchCord10(drum_mixer, 0, synth_mixer, 1);
AudioConnection          patchCord11(sine_mixer, 0, synth_mixer, 0);
AudioConnection          patchCord12(piezo, 0, piezodelay_input, 0);
AudioConnection          patchCord13(piezodelay_input, piezodelay);
AudioConnection          patchCord14(piezodelay_input, 0, delayext_input, 0);
AudioConnection          patchCord15(piezodelay_input, 0, final_mixer, 0);
AudioConnection          patchCord16(synth_mixer, 0, delayext_input, 1);
AudioConnection          patchCord17(synth_mixer, 0, final_mixer, 1);
AudioConnection          patchCord18(piezodelay, 0, piezodelay_input, 1);
AudioConnection          patchCord19(piezodelay, 1, piezodelay_input, 2);
AudioConnection          patchCord20(delayext, 0, delayext_input, 3);
AudioConnection          patchCord21(delayext, 0, final_mixer, 2);
AudioConnection          patchCord22(delayext_input, delayext);
AudioConnection          patchCord23(synthloopbutton, envelopes);
AudioConnection          patchCord24(piezoloopbutton, envelopep);
AudioConnection          patchCord25(envelopep, 0, outmixer, 1);
AudioConnection          patchCord26(envelopes, 0, outmixer, 2);
AudioConnection          patchCord27(final_mixer, 0, outmixer, 0);
AudioConnection          patchCord28(outmixer, 0, audio_output, 0);
AudioConnection          patchCord29(outmixer, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2793.4000244140625,1175.0000305175781
// GUItool: end automatically generated code



const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

//Looper settings
    const int Max_LoopTime = 4000;
    int default_delay = 0;
    int loopdelaytime = 0;
    elapsedMillis looptimer = 0;
    int loopstage = 1;
      //1 = nothing
      //2 = start record
      //3 = end record and play

//Piezo sound settings
    int pshortdelay = 10;
    int plongdelay = 200;

//Synth sound settings

//Discrete/continuous button state
    bool discrete = 0;   //ie off, continuous
    bool roll = 0;       //ie roll off
  

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  AudioMemory(200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.55);
  sgtl5000_1.inputSelect(myInput);
//  sgtl5000_1.micGain(36);

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);

 
//1. Piezo setup

    piezodelay.delay(0, pshortdelay);
    piezodelay.delay(1, plongdelay);

    piezodelay_input.gain(0, 1.0);    //straight input
    piezodelay_input.gain(1, 0.85);    //short delay
    piezodelay_input.gain(2, 0.0);    //long delay
                                      //this mixer goes to the feedback delay loop
                                 
//unused channels
piezodelay_input.gain(3, 0.0);


//2. Synth setup

    sine1.amplitude(0.3);
    sine1.frequency(164.8);

    sine2.amplitude(0.3);
    sine2.frequency(185);      //or could be major third

    sine3.amplitude(0.3);
    sine3.frequency(196);         

    sine_mixer.gain(0, 1.0);
    sine_mixer.gain(1, 1.0);
    sine_mixer.gain(2, 1.0);          //this goes to the sine delay input mixer 
    
    synth_mixer.gain(0, 1.0);         //this mixer goes to the feedback delay loop
    synth_mixer.gain(1, 0.0);         //drum sounds gain - uninitialized


////unused channels
sine_mixer.gain(3, 0.0);
synth_mixer.gain(2, 0.0);
synth_mixer.gain(3, 0.0);


//3. Loop setup 

    delayext_input.gain(0, 1.0);      //taking piezo input for loop
    delayext_input.gain(1, 0.0);      //taking synth input for loop
    delayext_input.gain(3, 0.0);      //feedback loop off 
    
    delayext.delay(0, default_delay);  //first tap delay time when not in looping mode

    final_mixer.gain(0, 1.0);         //direct piezo input, after the short delay
    final_mixer.gain(1, 1.0);         //direct synth input, after delay
    final_mixer.gain(2, 0.8);         //looping sound        

//just for testing - remove later
    outmixer.gain(0, 0.75);           //from final mixer, ie all sound inputs
    outmixer.gain(1, 0.1);            //test sound 1 for piezo loop button
    outmixer.gain(2, 0.1);            //test sound 2 for piezo loop button


 //unused channels
 delayext_input.gain(2, 0.0);
 final_mixer.gain(3, 0.0);
 outmixer.gain(3, 0.0);

    
//4. Testing sounds
    piezoloopbutton.amplitude(1.0);
    piezoloopbutton.frequency(500);
    synthloopbutton.amplitude(1.0);
    synthloopbutton.frequency(300);

//5. Envelopes
  envelopep.attack(50);
  envelopep.hold(50);
  envelopep.decay(50);
  envelopep.sustain(0);
  envelopep.release(10);
  envelopes.attack(50);
  envelopes.hold(50);
  envelopes.decay(50);
  envelopes.sustain(0);
  envelopes.release(10);

  envelope1.attack(50);
  envelope1.hold(50);
  envelope1.decay(500);
  envelope1.sustain(0);
  envelope1.release(10);
    
  envelope2.attack(50);
  envelope2.hold(50);
  envelope2.decay(500);
  envelope2.sustain(0);
  envelope2.release(10);
 
  envelope3.attack(50);
  envelope3.hold(50);
  envelope3.decay(500);
  envelope3.sustain(0);
  envelope3.release(10);

   
}

void loop() {

//Looping code 

button0.update();       //looper
button1.update();       //discretizing/making continuous piezo and synth frequencies
button2.update();       //switching between synth chords
switch0 = digitalRead(switchPin);


  if (discrete == 0) {

    pshortdelay = map(analogRead(A1), 34, 1008, 196, 41);
    piezodelay.delay(0, 1000.0/pshortdelay);

   
  } else if (discrete == 1) {

    int discshortdelay = map(analogRead(A1), 34, 1008, 8, 1);
    float pshortdelay = float(discshortdelay)*41.2;
    piezodelay.delay(0, (1000.0/pshortdelay));
    
  }

  if (button1.fallingEdge()) {
    
      discrete = !discrete;
      
  }

  

if (switch0 == HIGH) {

  //piezo loop
  if (button0.fallingEdge()) {      
      envelopep.noteOn();
       
      if ( loopstage == 1 ) {
       
        looptimer = 0;

        delayext.delay(0, Max_LoopTime);
        delayext_input.gain(0, 1.0);
        delayext_input.gain(1, 0.0);
        delayext_input.gain(3, 0.0);
        final_mixer.gain(2, 0.0);

        loopstage = 2;
             
      } else if (loopstage == 2) {
        
        delayext.delay(0, looptimer);
        delayext_input.gain(0, 0.0);    //piezo input
        delayext_input.gain(1, 0.0);    //synth input
        delayext_input.gain(3, 1.0);    //feedback loop
        final_mixer.gain(2, 1.0); 

        loopstage = 3;
     
      } else if (loopstage == 3) {

        delayext.delay(0, default_delay);
        delayext_input.gain(0, 1.0);    //piezo input
        delayext_input.gain(1, 0.0);
        delayext_input.gain(3, 0.0);    //feedback loop
        final_mixer.gain(2, 1.0); 

        loopstage = 1;

      }

      }
    } else if (switch0 == LOW) {

      //loop synths
      if (button0.fallingEdge()) {      
          envelopes.noteOn();
           
          if ( loopstage == 1 ) {
           
            looptimer = 0;
    
            delayext.delay(0, Max_LoopTime);
            delayext_input.gain(1, 1.0);
            delayext_input.gain(0, 0.0);
            delayext_input.gain(3, 0.0);
            final_mixer.gain(2, 0.0);
    
            loopstage = 2;
                 
          } else if (loopstage == 2) {
            
            delayext.delay(0, looptimer);
            delayext_input.gain(1, 0.0);    //piezo input
            delayext_input.gain(0, 0.0);
            delayext_input.gain(3, 1.0);    //feedback loop
            final_mixer.gain(2, 1.0); 
    
            loopstage = 3;
         
          } else if (loopstage == 3) {
    
            delayext.delay(0, default_delay);
            delayext_input.gain(1, 1.0);    //piezo input
            delayext_input.gain(0, 0.0);
            delayext_input.gain(3, 0.0);    //feedback loop
            final_mixer.gain(2, 1.0); 
    
            loopstage = 1;
    
          }

      }

      
    }

    //synth sounds
    //frequency control of synths

    int fundamental = map(analogRead(A2), 1009, 33, 165, 330);   //E3 to E4

    int majorsecond = float(fundamental)*(9.0/8.0);
    int fifth = float(fundamental)*(3.0/2.0);
    int majorthird = float(fundamental)*(5.0/4.0);
    int minorthird = float(fundamental)*(6.0/5.0);
    int octave = fundamental*2;

    sine1.frequency(fundamental);
    sine2.frequency(minorthird);
    sine3.frequency(fifth);

    int fsr1 = analogRead(A7);
    
           if (fsr1 < 400) {
             envelope1.noteOn();
             delay(80);
           }
           else if (fsr1 < 600) {
             envelope1.noteOn();
             delay(95);
           }
           else if (fsr1 < 900) {
             envelope1.noteOn();
             delay(110);
           }
           else if (fsr1 < 900) {
             envelope1.noteOn();
             delay(130);
           }
    
    int fsr2 = analogRead(A6);
    
           if (fsr2 < 400) {
             envelope2.noteOn();
             delay(80);
           }
           else if (fsr2 < 600) {
             envelope2.noteOn();
             delay(95);
           }
           else if (fsr2 < 900) {
             envelope2.noteOn();
             delay(110);
           }
           else if (fsr2 < 900) {
             envelope2.noteOn();
             delay(130);
           }

   int fsr3 = analogRead(A3);
    
           if (fsr3 < 400) {
             envelope3.noteOn();
             delay(80);
           }
           else if (fsr3 < 600) {
             envelope3.noteOn();
             delay(95);
           }
           else if (fsr3 < 900) {
             envelope3.noteOn();
             delay(110);
           }
           else if (fsr3 < 900) {
             envelope3.noteOn();
             delay(130);
           }
 

    delay(5);
}
