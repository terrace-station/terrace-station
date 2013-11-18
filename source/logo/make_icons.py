#!/usr/bin/python

import os, subprocess
from PIL import Image, ImageDraw

APPNAME = "dis"
TEMPDIR = "temp"
WIDTH = HEIGHT = 256
FINAL_WIDTH = FINAL_HEIGHT = 50
CENTER_X = WIDTH / 2
CENTER_Y = HEIGHT / 2

im = Image.new("L", (WIDTH, HEIGHT), color=255)

radius = [120, 100, 80, 60, 40]
segments = [4, 2, 1, 4, 2]
rotation = [1, -1, 1, -1, 1]
start_angle = [13, 47, 70, 23, 55]

thickness = 12

if not os.path.isdir(TEMPDIR):
    os.mkdir(TEMPDIR)
for angle in range(0, 180, 2):
    draw = ImageDraw.Draw(im)
    draw.pieslice( (-CENTER_X,
                    -CENTER_Y,
                    3 * CENTER_X,
                    3 * CENTER_Y),
                    0, 360, 255)
    for i in range(len(radius)):
        if segments[i] == 1:
            draw.pieslice( (CENTER_X - radius[i],
                            CENTER_Y - radius[i],
                            CENTER_X + radius[i],
                            CENTER_Y + radius[i]),
                            0, 360, 50 )
            draw.pieslice( (CENTER_X - radius[i] + thickness,
                            CENTER_Y - radius[i] + thickness,
                            CENTER_X + radius[i] - thickness,
                            CENTER_Y + radius[i] - thickness),
                            0, 360, 255 )
        else:
            for j in range(segments[i]):
                draw.pieslice( (CENTER_X - radius[i],
                                CENTER_Y - radius[i],
                                CENTER_X + radius[i],
                                CENTER_Y + radius[i]),
                                start_angle[i] + j * 360 / segments[i] + rotation[i] * angle,
                                start_angle[i] + j * 360 / segments[i] + 360 / (segments[i] + 1) + rotation[i] * angle,
                                50 )
                draw.pieslice( (CENTER_X - radius[i] + thickness,
                                CENTER_Y - radius[i] + thickness,
                                CENTER_X + radius[i] - thickness,
                                CENTER_Y + radius[i] - thickness),
                                0, 360, 255)
    del draw
    im2 = im.resize((FINAL_WIDTH, FINAL_HEIGHT), Image.ANTIALIAS)
    im2.save(os.path.join(TEMPDIR, "frame{0:03}.png".format(angle)))
im2.save(APPNAME + ".png")
subprocess.call(['convert', os.path.join(TEMPDIR, '*.png'), APPNAME + '.gif'])
for f in os.listdir(TEMPDIR):
    os.remove(os.path.join(TEMPDIR, f))
os.rmdir(TEMPDIR)
