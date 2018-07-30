import hlt
from hlt import NORTH, EAST, SOUTH, WEST, STILL, Move, Square
import random
import pprint


myID, game_map = hlt.get_init()
hlt.send_init("MyPythonBot")

# Square class
# x, y
# owner
# strength
# production


directions = (NORTH, EAST, SOUTH, WEST)
maxStrength = 255

while True:
    game_map.get_frame()
    mySquares = [square for square in game_map if square.owner == myID]
    moves = []
    for square in mySquares:
        moved=False
        for direction in directions:
            neighbor = game_map.get_target(square, direction)
            if (square.strength > neighbor.strength and square.owner != neighbor.owner):
               moves.append(Move(square, direction))
               moved=True
               break
        if not moved:
            moves.append(Move(square, STILL))

    hlt.send_frame(moves)
#    with open("test.log", "a") as mylog:
#        mylog.write(str(mySquares))
#        mylog.write(str(game_map.contents))
#        for each in moves:
#            mylog.write(str(each) + "\n")


