#!usr/bin/python3
import cv2
import numpy as np
import sys
import matplotlib.pyplot as plt
import time
from scipy import signal


def diff(prevFrame, curFrame):
    diffFrame = np.ndarray(shape=prevFrame.shape, dtype=np.int8)
    np.subtract(curFrame,prevFrame, out=diffFrame)
    return diffFrame

class History:
    size = 1
    imgsize = (32,16)
    framename = "Aardbei"
    def __init__(self):
        self.idx = self.size
        self.data = np.ndarray(shape=(self.size, self.imgsize[0], self.imgsize[1]), dtype=np.uint8)

    def getPrevFrame(self, i=1):
        return self.data[(self.idx - i) % self.size]

    def getCurrentFrame(self):
        return self.data[self.idx % self.size]

    def append(self, f):
        self.idx += 1
        self.data[self.idx % self.size] = f.copy()

    def getAllData(self):
        return self.data[(self.idx+1) % self.size:] + self.data[:self.idx%self.size]

    def getPlacement(self, i):
        return ((i%3) * 640, 510 if i > 2 else 0)

    def show(self):
        for i in range(self.size):
            cv2.imshow(self.framename + str(i), cv2.resize(self.data[(self.idx + i + 1) % self.size],
                        dsize=(640,480), fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
            cv2.moveWindow(self.framename + str(i), self.getPlacement(i)[0], self.getPlacement(i)[1])

    def getPrevDiff(self):
        d = diff(self.getPrevFrame(2), self.getPrevFrame(1))
        cv2.imshow(self.framename + ' prev diff', cv2.resize(d, dsize=(640,480),
                                        fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        return d

    def getDiff(self):
        d = diff(self.getPrevFrame(), self.getCurrentFrame())
        cv2.imshow(self.framename + ' diff', cv2.resize(d, dsize=(640,480),
                                        fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        return dprevSmall

    def diffdiff(self):
        pd = self.getPrevDiff()
        d = self.getDiff()

        dd = diff(pd,d)
        cv2.imshow(self.framename + ' difdif', cv2.resize(dd, dsize=(640,480),
                                        fx=0, fy=0, interpolation=cv2.INTER_NEAREST))

def toGrey(px):
    return px[0]*0.3 + px[1] * 0.587 + px[2]*0.114

def main():
    h = History()
    cap = cv2.VideoCapture(0)
    fps = int(cap.get(cv2.CAP_PROP_FPS))
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH ) )
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT ))
    print("Working with size (w x h)" + str(width) + " x " + str(height))

    tmp1 = np.ndarray(shape=(height,width),dtype=np.uint8)
    tmp2 = np.ndarray(shape=(height,width),dtype=np.uint8)

    # Initiate ORB detector
    # orb = cv2.ORB_create(10)

    # History buffers
    # xbuff = np.ndarray(shape=(width), dtype=np.uint8)
    # ybuff = np.ndarray(shape=(640), dtype=np.uint8)
    #
    # xhist = np.ndarray(shape=(width), dtype=np.uint8)
    # yhist = np.ndarray(shape=(640), dtype=np.uint8)
    ret,frame = cap.read()
    # xbuff = list(map(toGrey, frame[1:width][height//2]))
    # ybuff = list(map(toGrey, frame[width//2][1:height]))
    # plt.style.use('seaborn-darkgrid')
    # my_dpi = 96
    # plt.figure(figsize=(480/my_dpi, 480/my_dpi), dpi=my_dpi)
    # plt.ion()

    smallImg = np.ndarray(shape=h.imgsize, dtype=np.uint8)
    prevSmall = np.ndarray(shape=h.imgsize, dtype=np.uint8)
    cv2.resize(tmp1, dsize=(h.imgsize[1], h.imgsize[0]), fx=0, fy=0,
                            interpolation=cv2.INTER_LINEAR, dst=smallImg)
    while (True):
        time.sleep(0.1)
        prevFrame = frame.copy()
        ret,frame = cap.read()

        # xhist = xbuff.copy();
        # yhist = ybuff.copy();
        # print("meuk is ", len(frame[0][:]))
        # print("meuk is ", len(frame[:][0]))

        # for idx, v in enumerate(frame[height//2][:]):
        #     # print(idx, v)
        #     xbuff[idx] = toGrey(v)
        # for idx, v in enumerate(frame[:][width//2]):
        #     # print(idx, v)
        #     ybuff[idx] = toGrey(v)
        # xbuff = list(map(toGrey, frame[:][height//2]))
        # ybuff = list(map(toGrey, frame[width//2][:]))



        # print("xbuff is")
        # print(xbuff)
        # xconv = np.correlate(xhist,xbuff, mode='full')
        # yconv = np.correlate(yhist,ybuff, mode='full')
        # xmax = np.argmax(xconv) - width
        # ymax = np.argmax(yconv) - height
        # print("Frame res: width = " + str(width) + " and height " + str(height) +  " and movement detection: x = " + str(xmax) + "\ty = " + str(ymax))
        # plt.plot(conv)
        # plt.show()
        # plt.draw()

        # find the keypoints with ORB
        cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY, dst=tmp1)

        prevSmall = smallImg.copy()
        smallImg = cv2.resize(tmp1, dsize=(h.imgsize[1], h.imgsize[0]), fx=0, fy=0,
                                interpolation=cv2.INTER_LINEAR)

        trials = 4
        results = {}
        # results = np.ndarray(shape=(trials*2-1, trials*2-1), dtype=np.uint32)
        # for i in range(-trials, trials):
        #     for j in range(-trials,trials):
                # a = smallImg.astype(np.int16)
                # # b = np.roll(prevSmall, (i,j)).astype(np.int16)
                # b = np.roll(smallImg, (i,j)).astype(np.int16)
                # if i is 0 and j is 0:
                #     results[(i,j)] = np.sum(abs(a[:][:] - b[:][:]), dtype=np.uint64)
                # elif i is 0:
                #     results[(i,j)] = np.sum(abs(a[abs(j):-abs(j)][:] - b[abs(j):-abs(j)][:]), dtype=np.uint64)
                # elif j is 0:
                #     results[(i,j)] = np.sum(abs(a[:][abs(i):-abs(i)] - b[:][abs(i):-abs(i)]), dtype=np.uint64)
                # else:
                #     results[(i,j)] = np.sum(abs(a[abs(j):-abs(j)][abs(i):-abs(i)] - b[abs(j):-abs(j)][abs(i):-abs(i)]), dtype=np.uint64)

        results = signal.correlate2d(prevSmall, smallImg)
        print(results)
        print("Minimum sum is ", np.unravel_index(np.argmax(results), results.shape))
        # convolved = signal.convolve2d(prevSmall, smallImg, mode='full')
        # (x,y) = np.unravel_index(np.argmax(convolved, axis=None), convolved.shape)
        # print("Largest indices are " + str(x) + " and " + str(y))


        # kp = orb.detect(smallImg, None)
        # # compute the descriptors with ORB
        # kp, des = orb.compute(smallImg, kp)
        # keypoints = cv2.drawKeypoints(smallImg, kp, smallImg, color=(0,255,0), flags=0)

        # hist[hIdx % HSIZE] = smallImg.copy()
        h.append(smallImg)
        # tmp2 = cv2.resize(smallImg, dsize=(640,480), fx=0, fy=0,
        #                         interpolation=cv2.INTER_NEAREST)

        cv2.imshow('Image', cv2.resize(h.getCurrentFrame(), dsize=(640,640), fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        cv2.imshow('Fapperoni', tmp1)
        # print("Keypoints:" + str(des))
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') :
            break
        elif key == ord('p'):
            h.show()
        # elif key == ord('d'):
        # h.diffdiff()
        # elif key == ord('o'):
            # draw only keypoints location,not size and orientation
        # cv2.imshow('keypoints',cv2.resize(keypoints, dsize=(640,480), fx=0,fy=0,interpolation=cv2.INTER_NEAREST))

        # break;

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":

    main()
