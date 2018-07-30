#!/usr/bin/python

import sdl2.ext

class ClickableObject(sdl2.ext.Entity):
    def __init__(self, world, sprite, clickFunction, hoverFunction, posx=0, posy=0):
        self.sprite = sprite
        self.sprite.position = posx, posy
        self.mouseevent = MouseEvent()
        self.mouseevent.onClick = clickFunction
        self.mouseevent.onHover = hoverFunction

class MouseEvent(object):
    def __init__(self):
        self.hovered = False
        self.clicked = False
        self.onClick = None
        self.onHover = None

class Mouse(object):
    def __init__(self):
        self.x = 0
        self.y = 0
        self.click=False
    def update(self, x, y):
        self.x=x
        self.y=y

def detectClick(mouse, clickableObject):
    if clickableObject.mouseevent.onClick == None:
        return None
    if (mouse.click):
        x = mouse.x
        y = mouse.y
        sprite = clickableObject.sprite
        if (x > sprite.position[0] and x < sprite.position[0] + sprite.size[0]):
            if (y > sprite.position[1] and y < sprite.position[1] + sprite.size[1]):
                clickableObject.mouseevent.clicked = True
    else:
        clickableObject.mouseevent.clicked = False
    return clickableObject

def detectHover(mouse, clickableObject):
    x = mouse.x
    y = mouse.y
    sprite = clickableObject.sprite
    if (x > sprite.position[0] and x < sprite.position[0] + sprite.size[0]):
        if (y > sprite.position[1] and y < sprite.position[1] + sprite.size[1]):
            clickableObject.mouseevent.hovered = True
    else:
        clickableObject.mouseevent.hovered = False
    return clickableObject

def updateClickables(mouse, clickableObjects):
    hovered = []
    for each in clickableObjects:
        result = detectHover(mouse, each)
        if (result):
            hovered.append(result)
    for obj in hovered:
        detectClick(mouse, obj)

def executeClickables(world, clickableObjects):
    for each in clickableObjects:
        if (each.mouseevent.hovered):
            if (each.mouseevent.onHover):
                each.mouseevent.onHover(world, each)
        if (each.mouseevent.clicked):
            if (each.mouseevent.onClick):
                each.mouseevent.onClick(world, each)
        
