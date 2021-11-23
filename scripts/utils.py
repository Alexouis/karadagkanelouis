import json
#import numpy as np
from pathlib import Path
from PIL import Image
from pprint import pprint
import json

def get_characters_dir(base_folder):
    out = []
    for subdir in base_folder.iterdir():
        if subdir.is_dir():
            #print('\t', subdir.stem)

            for subsubdir in subdir.iterdir():
                if subsubdir.is_dir():
                    #print('\t'*2, subsubdir.stem)  

                    if subdir.stem.lower() == subsubdir.stem.lower():
                        out.append(subsubdir)
    return out

def parse(dirs:list):
    out = {}
    for d in dirs:
        out[d] =  {}
        for sd in d.iterdir():
            if sd.is_dir():
                out[d][sd.stem] = list(sd.iterdir())
    return out

def h_concat(images_path):
    images = [Image.open(x) for x in images_path]
    widths, heights = zip(*(i.size for i in images))

    # assert that tile have the same size
    assert min(widths) == max(widths) and min(heights) == max(heights)
    n, w, h = len(images), min(widths), max(heights)

    total_width, max_height = sum(widths), max(heights)
    new_im = Image.new('RGBA', (total_width, max_height))

    x_offset = 0
    for im in images:
        new_im.paste(im, (x_offset, 0))
        x_offset += im.size[0]

    return new_im, {'n':n,'w':w,'h':h}


def merge(parsed:dict):
    j = {}
    lines_im = [] # List[Image]

    w_max, h_current = 0, 0
    for d, anim in parsed.items():
        j[d.stem] = {}
        for anim_name, frames_path in anim.items():
            n_frames = len(frames_path)
            print(anim_name, end=' ')

            # merge to a line tileset
            line_im, line_info = h_concat(frames_path)
            line_info['y_offset'] = h_current
            print(line_info)
            
            # keep track
            w, h = line_im.size
            h_current += h
            w_max = max(w_max, w)

            j[d.stem][anim_name] = line_info
            lines_im.append(line_im)

    
    tileset = Image.new('RGBA', (w_max, h_current), (255,0,0,0))
    y_offset = 0
    for line_im in lines_im:
        tileset.paste(line_im, (0, y_offset))
        y_offset += line_im.size[1]
    tileset.save('test.png')

    print('-'*60)
    pprint(j)
    with open("tileset.json", "w") as f_json:
        json.dump(j, f_json, indent=4)
            




if __name__ == '__main__':
    
    base = Path(__file__).resolve().parents[1] / 'res'
    #print(base)
                
    characters_dir = get_characters_dir(base)
    #print(characters_dir)

    out = parse(characters_dir)
    #pprint(out)

    merge(out)



