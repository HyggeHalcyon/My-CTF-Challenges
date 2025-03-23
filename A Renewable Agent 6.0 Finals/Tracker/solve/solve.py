import win32api
import cv2
import numpy as np
from time import sleep

canvas_size = (600, 800, 3) 
canvas = np.ones(canvas_size, dtype=np.uint8) * 255

def MoveCursor(x, y, prev_x=None, prev_y=None):
    if prev_x is not None and prev_y is not None:
        cv2.line(canvas, (prev_x, prev_y), (x, y), (0, 0, 255), 2)  # Red line
        
    print(f"moving cursor to {x}, {y}")
    win32api.SetCursorPos((x, y))
    sleep(2)

def MousePatternA():
    points = [
        # just one of the coordinates that will resembles 'A', continue
        # to reverse and discover all of the coordinates 
        (185, 447),
        (354, 156),
        (428, 310),
        (264, 315),
        (430, 310),
        (466, 412),
    ]

    prev_x, prev_y = points[0]
    for x, y in points[1:]:
        MoveCursor(x, y, prev_x, prev_y)
        prev_x, prev_y = x, y

    cv2.imshow("Mouse Movement Path", canvas)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

MousePatternA()