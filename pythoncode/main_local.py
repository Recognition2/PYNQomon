#!usr/bin/python3
import cv2
import numpy as np
import sys

def diff(prevFrame, curFrame):
    diffFrame = np.ndarray(shape=prevFrame.shape, dtype=np.int8)
    np.subtract(curFrame,prevFrame, out=diffFrame)
    return diffFrame

class History:
    size = 5
    imgsize = (45,50)
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
        return d

    def diffdiff(self):
        pd = self.getPrevDiff()
        d = self.getDiff()

        dd = diff(pd,d)
        cv2.imshow(self.framename + ' difdif', cv2.resize(dd, dsize=(640,480),
                                        fx=0, fy=0, interpolation=cv2.INTER_NEAREST))


def main():
    h = History()
    cap = cv2.VideoCapture(0)
    fps = int(cap.get(cv2.CAP_PROP_FPS))
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH ) )
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT ))
    print("Working with size (w x h)" + str(width) + " x " + str(height))

    tmp1 = np.ndarray(shape=(height,width),dtype=np.uint8)
    tmp2 = np.ndarray(shape=(height,width),dtype=np.uint8)

    while (True):
        ret,frame = cap.read()

        cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY, dst=tmp1)

        smallImg = cv2.resize(tmp1, dsize=(h.imgsize[1], h.imgsize[0]), fx=0, fy=0,
                                interpolation=cv2.INTER_LINEAR)
        # hist[hIdx % HSIZE] = smallImg.copy()
        h.append(smallImg)
        tmp2 = cv2.resize(smallImg, dsize=(640,480), fx=0, fy=0,
                                interpolation=cv2.INTER_NEAREST)

        cv2.imshow('Image', cv2.resize(h.getCurrentFrame(), dsize=(640,480), fx=0, fy=0, interpolation=cv2.INTER_NEAREST))
        cv2.imshow('Fapperoni', tmp1)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') :
            break
        elif key == ord('p'):
            h.show()
        # elif key == ord('d'):
        h.diffdiff()

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
