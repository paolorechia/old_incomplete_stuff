# global functions that are used across all scripts
# named gf.py for easy typing

import pygame, settings


def create_button(x, y, string, buttons_text, buttons_coor, buttons_wh, button_font):
    buttons_text.append(string)
    string_length = button_font.size(string)
    buttons_coor.append((x, y))
    buttons_wh.append((string_length[0], string_length[1]))


def render_buttons(buttons_text, rendered_buttons, button_font):
    for i in range(1, len(buttons_text), 1):
        rendered_buttons.append(button_font.render(buttons_text[i], True, settings.black, settings.white))

def render_hovered_buttons(buttons_text, rendered_hovered_buttons, button_font):
    for i in range(1, len(buttons_text), 1):
        rendered_hovered_buttons.append(button_font.render(buttons_text[i], True, settings.white, settings.black))


def check_buttons_hover(mouse_x, mouse_y, buttons_coor, buttons_wh):

    print("mouse_x = " + str(mouse_x))
    print("mouse_y = " + str(mouse_y))
    for i in range(1, len(buttons_coor)):
#        print ("building boundaries.... (left, right, up, bottom)")
        lb = buttons_coor[i][0]
        rb = lb + buttons_wh[i][0]
        ub = buttons_coor[i][1]
        bb = ub + buttons_wh[i][1]
        print(lb)
        print(rb)
        print(ub)
        print(bb)
        if mouse_x > lb and mouse_x < rb and mouse_y > ub and mouse_y < bb:
            return i
    return 0


def increase_screen(size_list, max_size):
    if size_list[0] < max_size:
        size_list[0] += 1
    return size_list[0]


def decrease_screen(size_list, min_size):
    if size_list[0] > min_size:
        print("decreasing")
        size_list[0] -= 1
    return size_list[0]

    

        

