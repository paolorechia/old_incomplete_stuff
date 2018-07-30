#!/usr/bin/python

import sys
import sdl2
import sdl2.ext
from random import randint
from clickables import *

RESOURCES = sdl2.ext.Resources(__file__, "resources")
WHITE = sdl2.ext.Color(255, 255, 255)


class SoftwareRenderer(sdl2.ext.SoftwareSpriteRenderSystem):
    def __init__(self, window):
        super(SoftwareRenderer, self).__init__(window)

    def render(self, components):
        sdl2.ext.fill(self.surface, sdl2.ext.Color(0, 0, 0))
        super(SoftwareRenderer, self).render(components)

class Stats(object):
    def __init__(self):
        self.HP=0
        self.Attack=0
        self.Defense=0

class DrawableObject(sdl2.ext.Entity):
    def __init__(self, world, sprite, posx=0, posy=0):
        self.sprite = sprite
        self.sprite.position = posx, posy

def printHello(world, entity):
    print "Hello"

def changeColor(world, entity):
    factory = sdl2.ext.SpriteFactory(sdl2.ext.SOFTWARE)
    sp_paddle1 = factory.from_color((127, 127, 127), size=(20, 100))
    """
    aux = entity.sprite.color[0]
    entity.sprite.color[0]=1
    entity.sprite.color[1]=aux
    """

def run():
    sdl2.ext.init()

    ## Window setup
    window = sdl2.ext.Window("Hello World!", size=(800, 600))
    window.show()

    windowsurface = window.get_surface()


    ## World
    world = sdl2.ext.World()

    # Add systems
    spriterenderer = SoftwareRenderer(window)
    world.add_system(spriterenderer)

    # Init mouse global instance
    mouse = Mouse()

    factory = sdl2.ext.SpriteFactory(sdl2.ext.SOFTWARE)
    sp_paddle1 = factory.from_color(WHITE, size=(20, 100))
    sp_paddle2 = factory.from_color(WHITE, size=(20, 100))
    sp_paddle3 = factory.from_color(WHITE, size=(50, 50))

    player1 = DrawableObject(world, sp_paddle1, 0, 250)
    player2 = ClickableObject(world, sp_paddle2, printHello, None, 780, 250)
    player3 = ClickableObject(world, sp_paddle3, changeColor, None, 400, 100)

    sideMenuPaddle = factory.from_color(WHITE, size=(100, 50))
    sideMenu = DrawableObject(world, sideMenuPaddle, 600, 600)

    clickableEntities = [ player1, player2, player3 ]
    world.delete(clickableEntities[0])
    clickableEntities.pop(0)

    components = world.get_components(sdl2.ext.Sprite)
    print world.get_entities(components[0])

    running = True
    while running:
        mouse.click=False
        events = sdl2.ext.get_events()
        for event in events:
            if event.type == sdl2.SDL_MOUSEMOTION:
                mouse.update(event.motion.x, event.motion.y)
#                print (mouse.x, mouse.y)
            if event.type == sdl2.SDL_MOUSEBUTTONUP:
                mouse.click=True
                print "Click"
            if event.type == sdl2.SDL_QUIT:
                print("Exiting")
                running = False
                break
        updateClickables(mouse, clickableEntities)
        executeClickables(world, clickableEntities)
        world.process()

    sdl2.ext.quit()

if __name__ == "__main__":
    sys.exit(run())
