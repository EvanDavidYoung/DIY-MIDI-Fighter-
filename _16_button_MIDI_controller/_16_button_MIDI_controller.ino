/* Simple Teensy DIY USB-MIDI controller.
  Created by Liam Lacey, based on the Teensy USB-MIDI Buttons example code.
   Contains 8 push buttons for sending MIDI messages,
   and a toggle switch for setting whether the buttons
   send note messages or CC messages.
   The toggle switch is connected to input pin 0,
   and the push buttons are connected to input pins 1 - 8.
   You must select MIDI from the "Tools > USB Type" menu for this code to compile.
   To change the name of the USB-MIDI device, edit the STR_PRODUCT define
   in the /Applications/Arduino.app/Contents/Java/hardware/teensy/avr/cores/usb_midi/usb_private.h
   file. You may need to clear your computers cache of MIDI devices for the name change to be applied.
   See https://www.pjrc.com/teensy/td_midi.html for the Teensy MIDI library documentation.
   
   Use the following info to connect the hardware
   
   // JUMBLED TO MATCH THE ORIGINAL CODE

	Oct------Note------Number------Button
	4------C------48------0
	4------C#------49------1
	3------G#------44------3
	3------E------40------4
	3------C#------37------8
	3------F------41------9
	3------G------43------19
	3------D#------39------20
	3------A#------46------13
	4------D#------51------15
	3------B------47------22
	3------B------47------22
	4------C------48------0
	3------F#------42------11
	3------C------36------7
	3------D------38------21
	3------A------45------23
	4------D------50------17

	5------E------64------0
	5------F------65------1
	5------C------60------3
	4------G#------56------4
	4------F------53------8
	4------A------57------9
	4------B------59------19
	4------G------55------20
	5------D------62------13
	5------G------67------15
	5------D#------63------22
	5------D#------63------22
	5------E------64------0
	4------A#------58------11
	4------E------52------7
	4------F#------54------21
	5------C#------61------23
	5------F#------66------17

	6------G#------80------0
	6------A------81------1
	6------E------76------3
	6------C------72------4
	5------A------69------8
	6------C#------73------9
	6------D#------75------19
	5------B------71------20
	6------F#------78------13
	6------B------83------15
	6------G------79------22
	6------G------79------22
	6------G#------80------0
	6------D------74------11
	5------G#------68------7
	5------A#------70------21
	6------F------77------23
	6------A#------82------17

	8------C------96------0
	8------C#------97------1
	7------G#------92------3
	7------E------88------4
	7------C#------85------8
	7------F------89------9
	7------G------91------19
	7------D#------87------20
	7------A#------94------13
	8------D#------99------15
	7------B------95------22
	7------B------95------22
	8------C------96------0
	7------F#------90------11
	7------C------84------7
	7------D------86------21
	7------A------93------23
	8------D------98------17


	// SEQUENTIAL

	Oct------Note------Number------Button
	3------C------36------7
	3------C#------37------8
	3------D------38------21
	3------D#------39------20
	3------E------40------4
	3------F------41------9
	3------F#------42------11
	3------G------43------19
	3------G#------44------3
	3------A------45------23
	3------A#------46------13
	3------B------47------22
	4------C------48------0
	4------C#------49------1
	4------D------50------17
	4------D#------51------15

	4------E------52------7
	4------F------53------8
	4------F#------54------21
	4------G------55------20
	4------G#------56------4
	4------A------57------9
	4------A#------58------11
	4------B------59------19
	5------C------60------3
	5------C#------61------23
	5------D------62------13
	5------D#------63------22
	5------E------64------0
	5------F------65------1
	5------F#------66------17
	5------G------67------15


	5------G#------68------7
	5------A------69------8
	5------A#------70------21
	5------B------71------20
	6------C------72------4
	6------C#------73------9
	6------D------74------11
	6------D#------75------19
	6------E------76------3
	6------F------77------23
	6------F#------78------13
	6------G------79------22
	6------G#------80------0
	6------A------81------1
	6------A#------82------17
	6------B------83------15


	7------C------84------7
	7------C#------85------8
	7------D------86------21
	7------D#------87------20
	7------E------88------4
	7------F------89------9
	7------F#------90------11
	7------G------91------19
	7------G#------92------3
	7------A------93------23
	7------A#------94------13
	7------B------95------22
	8------C------96------0
	8------C#------97------1
	8------D------98------17
	8------D#------99------15
	
	
	Bank selection:
	Connect the first pin of the potentiometer to 5V
	The second pin to A0 (pin 14) of the teensy LC (This code is specifically designed for Teensy LC)
	The third pin of the potentiometer to the Gnd.
   
*/

#include <Bounce.h>

//The number of push buttons
const int NUM_OF_BUTTONS = 18;

// the MIDI channel number to send messages
const int MIDI_CHAN = 1;

// Create Bounce objects for each button and switch. The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 5 = 5 ms debounce time which is appropriate for good quality mechanical push buttons.
// If a button is too "sensitive" to rapid touch, you can increase this time.

//button debounce time
const int DEBOUNCE_TIME = 15;


// the analog pin to be used for the bank control potentiometer
const int bank_pot = 2;    // change it to match the analog pin to which you're connecting the pot

  Bounce button0 = Bounce (0, DEBOUNCE_TIME);
  Bounce button1 = Bounce (1, DEBOUNCE_TIME);
  Bounce button3 = Bounce (3, DEBOUNCE_TIME);
  Bounce button4 = Bounce (4, DEBOUNCE_TIME);
  Bounce button5 = Bounce (5, DEBOUNCE_TIME);
  Bounce button6 = Bounce (6, DEBOUNCE_TIME);
  Bounce button7 = Bounce (7, DEBOUNCE_TIME);
  Bounce button8 = Bounce (8, DEBOUNCE_TIME);
  Bounce button9 = Bounce (9, DEBOUNCE_TIME);
  Bounce button11 = Bounce (11, DEBOUNCE_TIME);
  Bounce button13 = Bounce (13, DEBOUNCE_TIME);
  Bounce button15 = Bounce (15, DEBOUNCE_TIME);
  Bounce button16 = Bounce (16, DEBOUNCE_TIME);
  Bounce button17 = Bounce (17, DEBOUNCE_TIME);
  Bounce button18 = Bounce (18, DEBOUNCE_TIME);
  Bounce button19 = Bounce (19, DEBOUNCE_TIME);
  Bounce button20 = Bounce (20, DEBOUNCE_TIME);
  Bounce button21 = Bounce (21, DEBOUNCE_TIME);
  Bounce button22 = Bounce (22, DEBOUNCE_TIME);
  Bounce button23 = Bounce (23, DEBOUNCE_TIME);


const int MIDI_MODE_NOTES = 0;
const int MIDI_MODE_CCS = 1;

//Variable that stores the current MIDI mode of the device (what type of messages the push buttons send).
int midiMode = MIDI_MODE_NOTES;

//Arrays the store the exact note and CC messages each push button will send
                                         // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15   16    17
const int MIDI_NOTE_NUM_0[NUM_OF_BUTTONS] =   {48, 49, 44, 40, 37, 41, 43, 39, 46, 51, 47, 47, 48, 42, 36, 38, 45, 50};
const int MIDI_NOTE_NUM_1[NUM_OF_BUTTONS] =   {64, 65, 60, 56, 53, 57, 59, 55, 62, 67, 63, 63, 64, 58, 52, 54, 61, 66};
const int MIDI_NOTE_NUM_2[NUM_OF_BUTTONS] =   {80, 81, 76, 72, 69, 73, 75, 71, 78, 83, 79, 79, 80, 74, 68, 70, 77, 82};
const int MIDI_NOTE_NUM_3[NUM_OF_BUTTONS] =   {96, 97, 92, 88, 85, 89, 91, 87, 94, 99, 95, 95, 96, 90, 84, 86, 93, 98};
const int MIDI_NOTE_VELS[NUM_OF_BUTTONS] =  {110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
const int MIDI_CC_NUMS[NUM_OF_BUTTONS] =    {51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68};
const int MIDI_CC_VALS[NUM_OF_BUTTONS] =    {65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65};


// create an empty array that will be populated in the runtime depending on the bank selected
int MIDI_NOTE_NUM[NUM_OF_BUTTONS];


//==============================================================================
//==============================================================================
//==============================================================================
//The setup function. Called once when the Teensy is turned on or restarted

void setup()
{
  // Configure the pins for input mode with pullup resistors.
  // The buttons/switch connect from each pin to ground.  When
  // the button is pressed/on, the pin reads LOW because the button
  // shorts it to ground.  When released/off, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!

  for (int i = 0; i < 24 + 1; i++)
  {
    pinMode (i, INPUT_PULLUP);
  }

}

//==============================================================================
//==============================================================================
//==============================================================================
//The loop function. Called over-and-over once the setup function has been called.

void loop()
{
  //==============================================================================
  // Update all the buttons/switch. There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
 
  button0.update();
  button1.update();
  button3.update();
  button4.update();
  button5.update():
  button6.update();
  button7.update();
  button8.update();
  button9.update();
  button19.update();
  button20.update();
  button17.update();
  button13.update();
  button15.update();
  button16.update();
  button22.update();
  button11.update();
  button21.update();
  button18.update();
  button23.update();                        // button 23.update
  //==============================================================================
  // Check the status of each push button

  for (int i = 0; i < NUM_OF_BUTTONS; i++)
  {
  
  int analogPotVal = analogRead(bank_pot);
  
  int bankVal = map(analogPotVal, 0, 1023, 0, 1000);
  
  if (bankVal <= 250){
  for (int a = 0; a < NUM_OF_BUTTONS; a++){
    MIDI_NOTE_NUM[a] = MIDI_NOTE_NUM_0[a];
  }
  } else if (bankVal > 250 && bankVal <= 500){
  for (int a = 0; a < NUM_OF_BUTTONS; a++){
    MIDI_NOTE_NUM[a] = MIDI_NOTE_NUM_1[a];
  }
  } else if (bankVal > 500 && bankVal <= 750){
  for (int a = 0; a < NUM_OF_BUTTONS; a++){
    MIDI_NOTE_NUM[a] = MIDI_NOTE_NUM_2[a];
  }
  } else if (bankVal > 750 && bankVal <= 1000){
  for (int a = 0; a < NUM_OF_BUTTONS; a++){
    MIDI_NOTE_NUM[a] = MIDI_NOTE_NUM_3[a];
  }
  }


// If the below line does not work comment out the below line and uncomment the next line
    midiMode = (digitalRead(2) == HIGH) ? MIDI_MODE_CCS : MIDI_MODE_NOTES;
    // midiMode = button2.fallingEdge() ? MIDI_MODE_CCS : MIDI_MODE_NOTES;

    //========================================
    // Check each button for "falling" edge.
    // Falling = high (not pressed - voltage from pullup resistor) to low (pressed - button connects pin to ground)

    /* if (buttons[i + 1].fallingEdge())
    {
      
      //If in note mode send a MIDI note-on message.
      //Else send a CC message.
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn (MIDI_NOTE_NUMS[i], MIDI_NOTE_VELS[i], MIDI_CHAN);
      else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[i], MIDI_CC_VALS[i], MIDI_CHAN);
    }
    */
 
    if (button0.fallingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[0], MIDI_NOTE_VELS[13],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[0], MIDI_CC_VALS[0], MIDI_CHAN);
    }
    if (button1.fallingEdge())
   {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[1], MIDI_NOTE_VELS[14],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[1], MIDI_CC_VALS[0], MIDI_CHAN);
    }
  if (button3.fallingEdge())
  {
     if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[2], MIDI_NOTE_VELS[12],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[2], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button4.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[3], MIDI_NOTE_VELS[11],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[3], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button6.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[3], MIDI_NOTE_VELS[11],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[3], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button8.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[4], MIDI_NOTE_VELS[10],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[4], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button9.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[5], MIDI_NOTE_VELS[0],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[5], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button19.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[6], MIDI_NOTE_VELS[1],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[6], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button20.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[7], MIDI_NOTE_VELS[2],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[7], MIDI_CC_VALS[0], MIDI_CHAN);
  }

  }
  if (button21.fallingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[15], MIDI_NOTE_VELS[13],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[15], MIDI_CC_VALS[0], MIDI_CHAN);
    }

    if (button13.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[8], MIDI_NOTE_VELS[3],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[8], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button18.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[8], MIDI_NOTE_VELS[3],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[8], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button15.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[9], MIDI_NOTE_VELS[4],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[9], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button16.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[10], MIDI_NOTE_VELS[5],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[10], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button22.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[11], MIDI_NOTE_VELS[6],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[11], MIDI_CC_VALS[0], MIDI_CHAN);
  }
  if (button11.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[13], MIDI_NOTE_VELS[8],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[13], MIDI_CC_VALS[0], MIDI_CHAN);
  }
   if (button7.fallingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[14], MIDI_NOTE_VELS[9],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[14], MIDI_CC_VALS[0], MIDI_CHAN);
  }
     if (button23.fallingEdge()) // sends note 14 on button 23
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[16], MIDI_NOTE_VELS[9],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[16], MIDI_CC_VALS[0], MIDI_CHAN);
  }
     /*if (button17.fallingEdge()) // sends note 17 on button 17
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[17], MIDI_NOTE_VELS[9],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[17], MIDI_CC_VALS[0], MIDI_CHAN);
  }*/
  if (button5.fallingEdge()) // sends note 17 on button 17
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOn(MIDI_NOTE_NUM[17], MIDI_NOTE_VELS[9],MIDI_CHAN);
    else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[17], MIDI_CC_VALS[0], MIDI_CHAN);
  }
//RISING EDGE

      if (button0.risingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[0], MIDI_NOTE_VELS[13],MIDI_CHAN);
    }
  
     if (button1.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[1], MIDI_NOTE_VELS[14],MIDI_CHAN);
  }
  if (button3.risingEdge())
  {
     if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[2], MIDI_NOTE_VELS[12],MIDI_CHAN);
  }
  if (button4.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[3], MIDI_NOTE_VELS[11],MIDI_CHAN);
  }
  if (button8.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[4], MIDI_NOTE_VELS[10],MIDI_CHAN);
  }
  if (button9.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[5], MIDI_NOTE_VELS[0],MIDI_CHAN);  
  }
  if (button19.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[6], MIDI_NOTE_VELS[1],MIDI_CHAN);   
  }
  if (button20.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[7], MIDI_NOTE_VELS[2],MIDI_CHAN); 
  }
    if (button13.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[8], MIDI_NOTE_VELS[3],MIDI_CHAN);
  }
  if (button18.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[8], MIDI_NOTE_VELS[3],MIDI_CHAN);
  }
  if (button15.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[9], MIDI_NOTE_VELS[4],MIDI_CHAN);
  }
  if (button16.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[10], MIDI_NOTE_VELS[5],MIDI_CHAN);
  }
  if (button22.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[11], MIDI_NOTE_VELS[6],MIDI_CHAN);
  }
  if (button23.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[16], MIDI_NOTE_VELS[7],MIDI_CHAN);
  }
  if (button11.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[13], MIDI_NOTE_VELS[8],MIDI_CHAN);
  }
   if (button7.risingEdge())
  {
    if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[14], MIDI_NOTE_VELS[9],MIDI_CHAN);  
  }    
  
  if (button21.risingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[15], MIDI_NOTE_VELS[13],MIDI_CHAN);
    }  
  /*if (button17.risingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[17], MIDI_NOTE_VELS[13],MIDI_CHAN);
    }*/
    if (button5.risingEdge())
    {
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff(MIDI_NOTE_NUM[17], MIDI_NOTE_VELS[13],MIDI_CHAN);
    } 

   
    

    //========================================
    // Check each button for "rising" edge
    // Rising = low (pressed - button connects pin to ground) to high (not pressed - voltage from pullup resistor)
/*
    else if (buttons[i + 1].risingEdge())
    {
      //If in note mode send a MIDI note-off message.
      //Else send a CC message with a value of 0.
      if (midiMode == MIDI_MODE_NOTES)
        usbMIDI.sendNoteOff (MIDI_NOTE_NUMS[i], 0, MIDI_CHAN);
      else
        usbMIDI.sendControlChange (MIDI_CC_NUMS[i], 0, MIDI_CHAN);
    }
   */

   //for (int i = 0; i < 24; i++)

  //==============================================================================
  // Check the status of the toggle switch, and set the MIDI mode based on this.


  //==============================================================================
  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read())
  {
    // ignoring incoming messages, so don't do anything here.
  }
  
}
