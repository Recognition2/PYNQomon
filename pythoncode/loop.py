import cv2
start = time.time()

inframe = hdmi_in.readframe()
cv2.cvtColor(inframe,cv2.COLOR_BGR2GRAY,dst=grayscale)
inframe.freebuffer()

cv2.pyrDown(grayscale)

hdmi_out.writeframe(grayscale)
print("Duration (ms): " + str(time.time()-start))
