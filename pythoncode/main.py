
# coding: utf-8

# In[ ]:


# %load setup
#!/usr/bin/env python3
#ofzo


from pynq.overlays.base import BaseOverlay
from pynq.lib.video import *
import cv2
import numpy as np
import time

base = BaseOverlay("base.bit")
hdmi_in = base.video.hdmi_in
hdmi_out = base.video.hdmi_out

hdmi_in.configure()
# hdmi_out.configure(hdmi_in.mode)
hdmi_out.configure(VideoMode(800,600,24))
#hdmi_out.configure(640,360,24)

# hdmi_in.cacheable_frames = True
# hdmi_out.cacheable_frames = True

hdmi_in.start()
hdmi_out.start()

# hdmi_in.tie(hdmi_out)
# Now we have video

grayscale = np.ndarray(shape=(hdmi_in.mode.height, hdmi_in.mode.width),
                       dtype=np.uint8)


# In[47]:


hdmi_in.mode


# In[44]:





# In[52]:


result = np.ndarray(shape=(hdmi_in.mode.height, hdmi_in.mode.width),
                       dtype=np.uint8)

result2 = np.ndarray(shape=(hdmi_in.mode.height, hdmi_in.mode.width),
                       dtype=np.uint8)
while (True):
    time.sleep(0.01)
    start = time.time()

    inframe = hdmi_in.readframe()
    outframe = hdmi_out.newframe()
    cv2.cvtColor(inframe,cv2.COLOR_BGR2GRAY,dst=result)
    inframe.freebuffer()


    cv2.cvtColor(result, cv2.COLOR_GRAY2BGR,dst=result2)
    cv2.pyrDown(result2, dstsize=(800,600), dst=outframe)

    hdmi_out.writeframe(outframe)
#     print("Duration (ms): " + str(1000*(time.time()-start)))



# In[53]:


hdmi_out.close()
hdmi_in.close()
