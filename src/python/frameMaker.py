#!/usr/bin/env python3
# -- coding:utf-8 --
"""
| File             frameMaker.py
| Directory        python
| Created Date     Wednesday, November 17th 2021, 3:57:47 pm
| Author           Nouhou KANE
| Email            nouhou.kane@ensea.fr
| 
| Copyright (c) 2021  ENSEA(FR)
| __________________________________________________________________________
"""

import cv2
import numpy as np

im1 = cv2.imread('/home/mkas/ENSEA/karadagkanelouis/res/demon/demon/demon_attack_nw/01.png', mode='RGB')


def concat_tile2(im2d):
    return np.concatenate([np.concatenate(im, axis = 1) for im in im2d], axis = 0)

def concat_tile(im_list_2d):
    return cv2.vconcat([cv2.hconcat(im_list_h) for im_list_h in im_list_2d])

#im1 =    (im1, (0, 0), 0.5, 0.5)
im_tile = concat_tile2([[im1, im1, im1, im1],[im1, im1, im1, im1],[im1, im1, im1, im1]])


cv2.imshow("Resized image", im_tile)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite('/home/mkas/ENSEA/karadagkanelouis/res/python_Out/frame.png', im_tile)