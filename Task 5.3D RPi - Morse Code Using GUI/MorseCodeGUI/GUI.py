from tkinter import *
from tkinter.ttk import *
import RPi.GPIO as GPIO
import time
import importlib

morseLetters = importlib.import_module("MorseLetters")

LED_PIN = 37

DOT_TIME = 0.5
DASH_TIME = DOT_TIME * 3

PART_TRANSITION_TIME = DOT_TIME
LETTER_TRANSITION_TIME = DOT_TIME * 3
WORD_TRANSITION_TIME = DOT_TIME * 7

def initSystem():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(LED_PIN, GPIO.OUT)
    GPIO.output(LED_PIN, GPIO.LOW)

def toggle_led():
    if digitalRead(LED_PIN) == GPIO.HIGH:
        GPIO.output(LED_PIN, GPIO.LOW)
    else:
        GPIO.output(LED_PIN, GPIO.HIGH)

def toggle_led(state):
    if state:
        GPIO.output(LED_PIN, GPIO.HIGH)
    else:
        GPIO.output(LED_PIN, GPIO.LOW)

def dot_sequence():
    toggle_led(True)
    time.sleep(DOT_TIME)

def dash_sequence():
    toggle_led(True)
    time.sleep(DASH_TIME)

def part_transition_sequence():
    toggle_led(False)
    time.sleep(PART_TRANSITION_TIME)

def letter_transition_sequence():
    toggle_led(False)
    time.sleep(LETTER_TRANSITION_TIME)

def word_transition_sequence():
    toggle_led(False)
    time.sleep(WORD_TRANSITION_TIME)

def letter_sequence(morseSequence, isFinalLetter):
    for i in range(len(morseSequence)):
        if morseSequence[i] == '*':
            dot_sequence()
        elif morseSequence[i] == '-':
            dash_sequence()
        
        if i != len(morseSequence) - 1:
            part_transition_sequence()

    if isFinalLetter:
        word_transition_sequence()
    else:
        letter_transition_sequence()

def blink_sentence(sentence):
    if sentence[-1] == ' ':
        sentence = sentence.rstrip(sentence[-1])

    for i in range(len(sentence)):
        if sentence[i] != ' ':

            print("Blinking ", sentence[i])
            
            if i <= len(sentence) - 1:
                letter_sequence(morseLetters.get_morse_sequence(sentence[i]), False)
            elif sentence[i + 1] == ' ':
                letter_sequence(morseLetters.get_morse_sequence(sentence[i]), True)
            else:
                letter_sequence(morseLetters.get_morse_sequence(sentence[i]), False)

    print("Done")

def do_blink_sentence():
    blink_sentence(sentenceInputBox.get("1.0", "end-1c"))
    

root = Tk()
label = Label(root, text="Morse Code Blinker")
label.pack()
sentenceInputBox = Text(root)
sentenceInputBox.pack()
morseCodeButton = Button(root, text = "Blink Messsage", command=do_blink_sentence)
morseCodeButton.pack()

initSystem()
root.mainloop()