import RPi.GPIO as GPIO
import time
gpio_out = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(gpio_out, GPIO.OUT)

GPIO.output(gpio_out, GPIO.HIGH)
time.sleep(0.5)
GPIO.output(gpio_out, GPIO.LOW)
time.sleep(0.5)
GPIO.output(gpio_out, GPIO.HIGH)
time.sleep(0.5)
GPIO.output(gpio_out, GPIO.LOW)
time.sleep(0.5)

GPIO.cleanup()