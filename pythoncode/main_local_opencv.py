#!usr/bin/python3
import cv2
import numpy as np
import sys
import matplotlib.pyplot as plt
import time
from scipy import signal

X = 1
Y = 0

imgsize = (64,64)

def main():
    # cap = cv2.VideoCapture("/home/gregory/60fpsmovie.avi")
    cap=cv2.VideoCapture(0)
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

        korrelatie = signal.correlate2d(
                prevSmall.astype(np.float32),
                smallImg.astype(np.float32),
                mode='same', boundary='wrap')
        print("size is", korrelatie.shape)

        np.set_printoptions(threshold=np.nan)
        # print("korr  is", korrelatie)
        xdir,ydir = np.unravel_index(
                np.argmax(
                    korrelatie,
                    axis=None),
                (imgsize[0],
                imgsize[1]))
        print(xdir,ydir)
        translation = (-ydir + imgsize[0]//2 -1, -xdir + imgsize[1]//2 -1 )

        # translation, response = cv2.phaseCorrelate(prevSmall.astype(np.float32), smallImg.astype(np.float32))

        # Whats a pixel worth?
        indices[X] += int(translation[X] * y / imgsize[X] + .5)
        indices[Y] += int(translation[Y] * x / imgsize[Y] + .5)
        bloksize = (50,50)

        if (indices[X] > y - bloksize[X] -1 or indices[X] < 0):
            print("Help out of bounds")
            indices[X] = y//2
        if (indices[Y] > x  - bloksize[Y] - 1 or indices[Y] < 0):
            print("Hlp out of bounds")
            indices[Y] = x//2

        for yy in range(bloksize[Y]):
            for xx in range(bloksize[X]):
                tmp1[yy + indices[X]][xx + indices[Y]] = 0xFF

        print("meuk is " + str(round(translation[X],2)) + "\t\t" + str(round(translation[Y],2)))
        print("indices is " + str(indices[X]) + "\t\t" + str(indices[Y]))
        fps = cap.get(cv2.CAP_PROP_FPS)
        print("fps is " + str(fps))

        m = np.amax(korrelatie)

        korrelatie = korrelatie / m * 255
        cv2.imshow("labol", cv2.resize(korrelatie.astype(np.uint8), dsize=(640,640), interpolation=cv2.INTER_NEAREST))

        cv2.imshow('Prev image', cv2.resize(prevSmall, dsize=(640,640),fx=0,fy=0,interpolation=cv2.INTER_NEAREST))
        cv2.imshow('Small image', cv2.resize(smallImg, dsize=(640,640), fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        cv2.imshow('Real Image', tmp1)
        # print("Keypoints:" + str(des))
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') :
            break
        elif key == ord('p'):
            time.sleep(30)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":

    main()
