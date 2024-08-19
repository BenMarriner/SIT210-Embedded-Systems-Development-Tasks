// -----------------------------------
// Spelling my name in morse code
// Morse code reference: https://i.etsystatic.com/10374207/r/il/c1f220/1227657168/il_1140xN.1227657168_j17x.jpg
// -----------------------------------

// On state timings
const int DOT_TIME = 500;
const int DASH_TIME = DOT_TIME * 3; // DOT_TIME * 3

// Off state timings
const int PART_TRANSITION_TIME = DOT_TIME; // Time between parts of a letter
const int LETTER_TRANSITION_TIME = DOT_TIME * 3; // DOT_TIME * 3
const int WORD_TRANSITION_TIME = DOT_TIME * 7; // DOT_TIME * 7

int led = D7;

int ledToggle(String command);

int ledToggle(String command) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        digitalWrite(led,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        return 0;
    }
    else {
        return -1;
    }
}

// Turn LED on for the length of a dot
void dotSequence()
{
    ledToggle("on");
    delay(DOT_TIME);
}

// Turn LED on for the length of a dash
void dashSequence()
{
    ledToggle("on");
    delay(DASH_TIME);
}

// Turn LED off for the length of being in between two parts
void partTransitionSequence()
{
    ledToggle("off");
    delay(PART_TRANSITION_TIME);
}

// Turn LED off for the length of the transition between one letter to the next
void letterTransitionSequence()
{
    ledToggle("off");
    delay(LETTER_TRANSITION_TIME);
}

// Turn LED off for the length of the transition between one word to the next
void wordTransitionSequence()
{
    ledToggle("off");
    delay(WORD_TRANSITION_TIME);
}

void letterSequence(String morseSequence, bool isFinalLetter)
{
    for (int i = 0; i < morseSequence.length(); i++)
    {
        if (morseSequence[i] == '*')
        {
            dotSequence();
        }
        else if (morseSequence[i] =='-')
        {
            dashSequence();
        }
        
        if (i != morseSequence.length() - 1)
            partTransitionSequence();
    }
    
    if (isFinalLetter)
    {
        wordTransitionSequence();
    }
    else
    {
        letterTransitionSequence();
    }
}

void spellFirstName()
{
    letterSequence("-***", false); // B
    letterSequence("*", false); // E
    letterSequence("-*", true); // N
}

void spellLastName()
{
    letterSequence("--", false); // M
    letterSequence("*-", false); // A
    letterSequence("*-*", false); // R
    letterSequence("*-*", false); // R
    letterSequence("**", false); // I
    letterSequence("-*", false); // N
    letterSequence("*", false); // E
    letterSequence("*-*", true); // R
}

void setup()
{

   // Here's the pin configuration, same as last time
   pinMode(led, OUTPUT);

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(led, LOW);
   
   // Spell my first name
   spellFirstName();
   
   // Spell my last name
   spellLastName();

}

void loop()
{
   // Nothing to do here
}
