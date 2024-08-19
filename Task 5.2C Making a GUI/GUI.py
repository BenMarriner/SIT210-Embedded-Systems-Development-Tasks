from tkinter import *
from tkinter.ttk import *
import RPi.GPIO as GPIO

LED_PINS = [33, 35, 37]
states = [False, False, False]

def initSystem(led_pins):
    GPIO.setmode(GPIO.BOARD)

    i = 0
    while i < len(led_pins):
        GPIO.setup(led_pins[i], GPIO.OUT)
        i += 1

def toggle_led(pinIdx):
    i = 0
    while i < len(LED_PINS):
        if i != pinIdx:
            GPIO.output(LED_PINS[i], GPIO.LOW)
        else:
            GPIO.output(LED_PINS[i], GPIO.HIGH)

        i += 1

def toggle_red_led():
    toggle_led(0)

def toggle_green_led():
    toggle_led(1)

def toggle_blue_led():
    toggle_led(2)

root = Tk()
label = Label(root, text="Toggle LEDs")
label.pack()
redButton = Radiobutton(root, text="Red", command=toggle_red_led)
redButton.pack()
greenButton = Radiobutton(root, text="Green", command=toggle_green_led)
greenButton.pack()
blueButton = Radiobutton(root, text="Blue", command=toggle_blue_led)
blueButton.pack()

initSystem(LED_PINS)
root.mainloop()