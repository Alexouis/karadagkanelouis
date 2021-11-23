#!/usr/bin/env python3
# -- coding:utf-8 --
"""
| File             frame.py
| Directory        python
| Created Date     Wednesday, November 17th 2021, 4:48:20 pm
| Author           Nouhou KANE
| Email            nouhou.kane@ensea.fr
| 
| Copyright (c) 2021  ENSEA(FR)
| __________________________________________________________________________
"""
from PIL import Image
import os
import json

im1 = Image.open('/home/mkas/ENSEA/karadagkanelouis/res/demon/demon/demon_attack_nw/01.png')
#dst = Image.new('RGBA', (im.width * column, im.height), (0, 0, 0, 0))
def get_concat_h_repeat(im, column):
    dst = Image.new('RGBA', (im.width * column, im.height), (0, 0, 0, 0))
    for x in range(column):
        dst.paste(im, (x * im.width, 0))
    return dst

def get_concat(frames, width, height):
    dst = Image.new('RGBA', (im.width * column, im.height), (0, 0, 0, 0))
    for x in range(column):
        dst.paste(im, (x * im.width, 0))
    return dst


def get_concat_v_repeat(im, row):
    dst = Image.new('RGBA', (im.width, im.height * row), (0, 0, 0, 0))
    for y in range(row):
        dst.paste(im, (0, y * im.height))
    return dst

def get_concat_tile_repeat(im, row, column):
    dst_h = get_concat_h_repeat(im, column)
    return get_concat_v_repeat(dst_h, row)


#"/home/mkas/ENSEA/karadagkanelouis/res/demon/demon"
def load_paths(direcotry):
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


def load_images(dict_paths):
    frames_info = {}
    images = []
    imWidth = 0
    imHeight = 0
    info = (0,0,0)
    for imges_dir, img_path_list in dict_paths.items():
        images += []
        for im_path in img_path_list:
            images.append([Image.open(im_path)])
            info = (images[-1][0].width, images[-1][0].height, len(img_path_list))
            frames_info[imges_dir] = info
        maxw = info[0]*info[2]
        maxh = info[1]*info[2]
        imWidth = maxw if (imWidth < maxw) else imWidth
        imHeight = maxh if (imHeight < maxh) else imHeight
    return (images,frames_info, (imWidth,imHeight))

print(load_images(load_paths("/home/mkas/ENSEA/karadagkanelouis/res/demon/demon")))


im_s = im1.resize((im1.width, im1.height))
get_concat_tile_repeat(im_s, 3, 4).save('/home/mkas/ENSEA/karadagkanelouis/res/python_Out/frame.png')


print([1,2,3]+[0])