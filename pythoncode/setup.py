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
hdmi_out.configure(hdmi_in.mode)

# hdmi_in.cacheable_frames = True
# hdmi_out.cacheable_frames = True

hdmi_in.start()
hdmi_out.start()

hdmi_in.tie(hdmi_out)
# Now we have video

grayscale = np.ndarray(shape=(hdmi_in.mode.height, hdmi_in.mode.width),
                       dtype=np.uint8)
