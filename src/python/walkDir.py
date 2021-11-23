#!/usr/bin/env python3
# -- coding:utf-8 --
"""
| File             walkDir.py
| Directory        python
| Created Date     Wednesday, November 17th 2021, 5:24:10 pm
| Author           Nouhou KANE
| Email            nouhou.kane@ensea.fr
| 
| Copyright (c) 2021  ENSEA(FR)
| __________________________________________________________________________
"""


#!/usr/bin/python

import os

#"/home/mkas/ENSEA/karadagkanelouis/res/demon/demon"
def load_images(direcotry):
    # traverse root directory, and list directories as dirs and files as files
    img = {}
    for root, dirs, files in os.walk(direcotry):
        path = root.split(os.sep)
        print(path)
        img[os.path.basename(root)] = []
        print((len(path) - 1) * '', os.path.basename(root))
        for file in files:
            img[os.path.basename(root)] += [os.path.join(root, file)]
            #print(img)
            print((len(path)) * ' ', file)
        img[os.path.basename(root)].sort()
    return img


var = load_images("/home/mkas/ENSEA/karadagkanelouis/res/demon/demon")
print(var)