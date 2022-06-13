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
int switch0 = 0;


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum1;          //xy=232.00006866455078,805.333402633667
AudioSynthSimpleDrum     drum2;          //xy=232.00006866455078,845.333402633667
AudioSynthSimpleDrum     drum3;          //xy=232.00006866455078,883.333402633667
AudioSynthWaveformSine   sine2;          //xy=258.0000991821289,1024.666696548462
AudioSynthWaveformSine   sine1;          //xy=259.0000991821289,978.6666965484619
AudioSynthWaveformSine   sine3;          //xy=259.0000991821289,1069.666696548462
AudioMixer4              drum_mixer;     //xy=386.0000686645508,848.333402633667
AudioEffectEnvelope      envelope3;      //xy=396.0000991821289,1068.666696548462
AudioEffectEnvelope      envelope2;      //xy=402.0000991821289,1022.6666965484619
AudioEffectEnvelope      envelope1;      //xy=405.0000991821289,979.6666965484619
AudioInputI2S            piezo;           //xy=457.2619400024414,497.5476722717285
AudioMixer4              sine_mixer;     //xy=570.0000991821289,1029.666696548462
AudioMixer4              shortdelay_mixer; //xy=637.0000228881836,548.0000381469727
AudioMixer4              synth_mixer;    //xy=647.000129699707,896.6668338775635
AudioEffectDelay         shortdelay; //xy=662.0000343322754,697.0000839233398
AudioMixer4              mixer2;         //xy=850.4000358581543,756.4000358581543
AudioEffectDelayExternal delaytaps(AUDIO_MEMORY_CY15B104);      //xy=1076.0001373291016,580.0000839233398
AudioMixer4              delaymixer1;        //xy=1318.4526824951172,546.5000829696655
AudioMixer4              delaymixer2;        //xy=1321.0478973388672,625.1668319702148
AudioMixer4              alldelay;         //xy=1528.3096885681152,841.9048919677734
AudioOutputI2S           audio_output;           //xy=1731.333839416504,842.5002117156982
AudioConnection          patchCord1(drum1, 0, drum_mixer, 0);
AudioConnection          patchCord2(drum2, 0, drum_mixer, 1);
AudioConnection          patchCord3(drum3, 0, drum_mixer, 2);
AudioConnection          patchCord4(sine2, envelope2);
AudioConnection          patchCord5(sine1, envelope1);
AudioConnection          patchCord6(sine3, envelope3);
AudioConnection          patchCord7(drum_mixer, 0, synth_mixer, 1);
AudioConnection          patchCord8(envelope3, 0, sine_mixer, 2);
AudioConnection          patchCord9(envelope2, 0, sine_mixer, 1);
AudioConnection          patchCord10(envelope1, 0, sine_mixer, 0);
AudioConnection          patchCord11(piezo, 0, shortdelay_mixer, 0);
AudioConnection          patchCord12(sine_mixer, 0, synth_mixer, 0);
AudioConnection          patchCord13(shortdelay_mixer, shortdelay);
AudioConnection          patchCord14(synth_mixer, 0, mixer2, 1);
AudioConnection          patchCord15(synth_mixer, 0, alldelay, 3);
AudioConnection          patchCord16(shortdelay, 0, shortdelay_mixer, 1);
AudioConnection          patchCord17(shortdelay, 0, mixer2, 0);
AudioConnection          patchCord18(shortdelay, 0, alldelay, 0);
AudioConnection          patchCord19(mixer2, delaytaps);
AudioConnection          patchCord20(delaytaps, 0, delaymixer1, 0);
AudioConnection          patchCord21(delaytaps, 1, delaymixer1, 1);
AudioConnection          patchCord22(delaytaps, 2, delaymixer1, 2);
AudioConnection          patchCord23(delaytaps, 3, delaymixer1, 3);
AudioConnection          patchCord24(delaytaps, 4, delaymixer2, 0);
AudioConnection          patchCord25(delaytaps, 5, delaymixer2, 1);
AudioConnection          patchCord26(delaytaps, 6, delaymixer2, 2);
AudioConnection          patchCord27(delaytaps, 7, delaymixer2, 3);
AudioConnection          patchCord28(delaymixer1, 0, alldelay, 1);
AudioConnection          patchCord29(delaymixer2, 0, alldelay, 2);
AudioConnection          patchCord30(alldelay, 0, audio_output, 0);
AudioConnection          patchCord31(alldelay, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2815.619373321533,1009.7380752563477
// GUItool: end automatically generated code




const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

void setup() {
  // put your setup code here, to run once:

   Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
    pinMode(switchPin, INPUT_PULLUP);


  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.55);
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.micGain(36);
  
  shortdelay_mixer.gain(0, 1.0);
  shortdelay_mixer.gain(1, 0.5);
  shortdelay_mixer.gain(2, 0.0);
  shortdelay_mixer.gain(3, 0.0);
  
  shortdelay.delay(0, 10);

  delaytaps.delay(0, 0);
  delaytaps.delay(1, 300);
  delaytaps.delay(2, 600);
  delaytaps.delay(3, 900);
  delaytaps.delay(4, 1200);
  delaytaps.delay(5, 1500);
  delaytaps.delay(6, 1800);
  delaytaps.delay(7, 2100);

  delaymixer1.gain(0, 0.7);
  delaymixer1.gain(1, 0.7);
  delaymixer1.gain(2, 0.7);
  delaymixer1.gain(3, 0.7);

  delaymixer2.gain(0, 0.7);
  delaymixer2.gain(1, 0.7);
  delaymixer2.gain(2, 0.7);
  delaymixer2.gain(3, 0.7);


  alldelay.gain(0, 1.0);
  alldelay.gain(1, 1.0);
  alldelay.gain(2, 1.0);
  alldelay.gain(3, 0.0);


  mixer2.gain(0, 0.7);
  mixer2.gain(1, 0.0);
  mixer2.gain(2, 0.0);
  

  
  delay(50);

}



void loop() {

  
button0.update();
button1.update();
button2.update();
switch0 = digitalRead(switchPin);

  // put your main code here, to run repeatedly:

  int shortdelaytime = map(analogRead(A1), 0, 1023, 4, 20);
  shortdelay.delay(0, 1000/(10*shortdelaytime));

   float shortdelaygain = float(map(analogRead(A2), 27, 1002, 700, 970))/1000.0;

 //  float shortdelaygain = analogRead(A2)/1010.0;
   shortdelay_mixer.gain(1, shortdelaygain);

    
if (switch0 == HIGH) {
if (button0.fallingEdge()) {

  delaytaps.delay(0, 300); //start here
  delaytaps.delay(1, 600);
  delaytaps.delay(2, 900);
  delaytaps.delay(3, 1200);
  delaytaps.delay(4, 1500);
  delaytaps.delay(5, 1800);
  delaytaps.delay(6, 2100);
  delaytaps.delay(7, 2400);

} 

if (button1.fallingEdge()) {

//  delaytaps.delay(0, 300); //start here
//  delaytaps.delay(1, 600);
//  delaytaps.delay(2, 900);
//  delaytaps.delay(3, 1050);
//  delaytaps.delay(4, 1200);
//  delaytaps.delay(5, 1500);
//  delaytaps.delay(6, 1650);
//  delaytaps.delay(7, 1800);

      delaytaps.delay(0, 300);
    delaytaps.delay(1, 400);
    delaytaps.delay(2, 600);
    delaytaps.delay(3, 800);
    delaytaps.delay(4, 1000);
    delaytaps.delay(5, 1200);
    delaytaps.delay(6, 1300);
    delaytaps.delay(7, 1400);
  
} 

if (button2.fallingEdge()) {

    delaytaps.delay(1, 300);
    delaytaps.delay(2, 600);
    delaytaps.delay(3, 900);
    delaytaps.delay(4, 1050);
    delaytaps.delay(5, 1200);
    delaytaps.delay(6, 1500);
    delaytaps.delay(7, 1650);
}
} else if (switch0 == LOW) {

  int delayadj2 = map(analogRead(A6), 100, 1000, 3, 1);
  int tempo = delayadj2;

  int delayadj1 = map(analogRead(A7), 100, 1000, 50, 0);
  
  int delayadj3 = map(analogRead(A3), 100, 1000, 50, 0);
  
  delaytaps.delay(0, (tempo*300)+delayadj1); //start here
  delaytaps.delay(1, tempo*600);
  delaytaps.delay(2, (tempo*900)+delayadj1+delayadj3);
  delaytaps.delay(3, (tempo*1200)+delayadj1);
  delaytaps.delay(4, tempo*1500);
  delaytaps.delay(5, (tempo*1800)+delayadj1+delayadj3);
  delaytaps.delay(6, tempo*2100);
  delaytaps.delay(7, (tempo*2400)+delayadj1);

   
}
  

//
  



    
}





  
 
