#! /usr/bin/env python
# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------
# Copyright (c) 2014, Nicolas P. Rougier. All rights reserved.
# Distributed under the terms of the new BSD License.
# -----------------------------------------------------------------------------
import sys
import numpy as np
import OpenGL.GL as gl
import OpenGL.GLUT as glut
from vispy.gloo import Program, VertexBuffer, IndexBuffer, set_viewport, clear
from vispy import app
from vispy import gloo


c = app.Canvas(title='Topological Field Theory', keys='interactive')
vertex = """
    uniform float scale;
    attribute vec4 color;
    attribute vec2 position;
    varying vec4 v_color;
    void main()
    {
        gl_Position = vec4(scale*position, 0.0, 1.0);
        v_color = color;
    } """

fragment = """
    varying vec4 v_color;
    void main()
    {
        gl_FragColor = v_color;
    } """





# Build program & data
# ----------------------------------------
program = Program(vertex, fragment, count=4)
program['color']    = [ (1,0,0,1), (0,1,0,1), (0,0,1,1), (1,1,0,1) ]
program['position'] = [ (-1,-1),   (-1,+1),   (+1,-1),   (+1,+1)   ]
program['scale'] = 1.0

@c.connect
def on_draw(event):
    clear((1,1,1,1))
    program.draw('triangle_strip')

@c.connect
def on_resize(event):
    set_viewport(0,0, *event.size)
    
tick = 0;
def on_time(event):
	tick += 1/60.0
	program['scale'] = (np.sin(2*pi*0.25*tick) + 1.01)/2.0
	c.update()

# Timer
# ------------------
my_timer = app.Timer(connect=on_time, start=True)

# Enter mainloop
# --------------------------------------
c.show()
app.run()
