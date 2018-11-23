#!/usr/bin/python3
import cv2
import numpy as np
import sys


cap = cv2.VideoCapture(0)

width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH ) )
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT ))
print("Working with size (w x h)" + str(width) + " x " + str(height))

fps = int(cap.get(cv2.CAP_PROP_FPS))

tmp1 = np.ndarray(shape=(height,width),dtype=np.uint8)
tmp2 = np.ndarray(shape=(height,width),dtype=np.uint8)

while (True):
    ret,frame = cap.read()

    cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY, dst=tmp1)

    tmp2 = cv2.resize(tmp1, dsize=(50,45), fx=0, fy=0,interpolation=cv2.INTER_LINEAR)
    tmp2 = cv2.resize(tmp2, dsize=(640,480), fx=0, fy=0,interpolation=cv2.INTER_NEAREST)

    cv2.imshow('Image', tmp2)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
