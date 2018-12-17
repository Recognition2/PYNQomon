#!usr/bin/python3
import cv2
import numpy as np
import sys
import matplotlib.pyplot as plt
import time
from scipy import signal

X = 1
Y = 0

imgsize = (128,128)

def main():
    cap = cv2.VideoCapture(0)
    x = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH ) )
    y = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT ))
    print("Working with size (w x h)" + str(y) + " x " + str(x))

    tmp1 = np.ndarray(shape=(y,x),dtype=np.uint8)
    ret,frame = cap.read()

    smallImg = np.ndarray(shape=imgsize, dtype=np.uint8)
    prevSmall = np.ndarray(shape=imgsize, dtype=np.uint8)

    smallImg = cv2.resize(tmp1, dsize=imgsize, fx=0, fy=0,
                            interpolation=cv2.INTER_LINEAR)
    indices = [y//2, x//2]
    while (True):
        prevFrame = frame.copy()
        ret,frame = cap.read()

        cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY, dst=tmp1)

        prevSmall = smallImg.copy()
        smallImg = cv2.resize(tmp1, dsize=imgsize, fx=0, fy=0,
                                interpolation=cv2.INTER_LINEAR)

        translation, response = cv2.phaseCorrelate(prevSmall.astype(np.float32), smallImg.astype(np.float32))

        # Whats a pixel worth?
        indices[X] += int(translation[X] * y // imgsize[X])
        indices[Y] += int(translation[Y] * x // imgsize[Y])
        bloksize = (10, 50)

        if (indices[X] > y - bloksize[Y] -1 or indices[X] < 0):
            print("Help out of bounds")
            indices[X] = y//2
        if (indices[Y] > x  - bloksize[X] - 1 or indices[Y] < 0):
            print("Hlp out of bounds")
            indices[Y] = x//2

        for yy in range(bloksize[Y]):
            for xx in range(bloksize[X]):
                tmp1[yy + indices[X]][xx + indices[Y]] = 0x00

        # print("meuk is " + str(round(translation[X],2)) + "\t\t" + str(round(translation[Y],2)))
        print("indices is " + str(indices[X]) + "\t\t" + str(indices[Y]))

        cv2.imshow('Image', cv2.resize(smallImg, dsize=(640,640), fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        cv2.imshow('Real Image', tmp1)
        # print("Keypoints:" + str(des))
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') :
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":

    main()
