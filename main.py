import cv2
import serial
import time
import pygame
import RPi.GPIO as GPIO
                            #To do: Google "Crack alternative"
if __name__ == '__main__':
    # set pin as output
    pin_number = 18
    pygame.mixer.init()
    speaker_volume = -1
    pygame.mixer.music.set_volume(speaker_volume)
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    while True:
        if ser.in_waiting > 0:
            GPIO.setmode(GPIO.BCM)
            GPIO.setup(pin_number, GPIO.OUT)
            line = ser.readline().decode('utf-8').rstrip()
            print('Somebody Stinky!!!')
            if float(line) >= 0:
                time.sleep(0.5)
                
                # turn on the pin
                GPIO.output(pin_number, GPIO.HIGH)
                
                pygame.mixer.music.load('/var/www/html/stinks.mp3')
                pygame.mixer.music.play()
                time.sleep(0.5)
                cam_port = -1
                cam = cv2.VideoCapture(cam_port)
                result, image = cam.read()
                f = open("id.txt", 'r+')
                id = int(f.readlines()[0])
                cv2.imwrite(f"img/Shame{id}.png", image)
                wid = str(id+1)
                f.close()
                w = open("id.txt", 'w')
                w.write(str(wid))
                
                # wait for 4 seconds
                time.sleep(4)
                # turn off the pin
                GPIO.output(pin_number, GPIO.LOW)
                # clean up
                GPIO.cleanup()
                
                f.close()
                w.close()
            else:
                print("Smth went wring....to ge honest, idfk what...")