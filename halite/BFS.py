import hlt
from hlt import NORTH, EAST, SOUTH, WEST, STILL, Move, Square
import random
import pprint


myID, game_map = hlt.get_init()
hlt.send_init("BFS")

# Square class
# x, y
# owner
# strength
# production


directions = (NORTH, EAST, SOUTH, WEST)
maxStrength = 255
offSet = 150

def closestFrontier(square, frontiers):
    closestF = 0
    shortestDistance = 100000 
    for i in range(0, 4):
        if (i < 2):
            distance = abs(square.x - frontiers[i])
        else:
            distance = abs(square.y - frontiers[i])
        if distance < shortestDistance:
            shortestDistance = distance
            closestF = i
    return closestF

def findFrontiers(squares):
    Frontier = [10000, 0, 0, 10000]
    for square in squares:
        if square.x < Frontier[0]:
            Frontier[0] = square.x
        if square.x > Frontier[1]:
            Frontier[1] = square.x
        if square.y > Frontier[2]:
            Frontier[2] = square.y
        if square.y < Frontier[3]:
            Frontier[3] = square.y
    return Frontier

while True:
    game_map.get_frame()
    mySquares = [square for square in game_map if square.owner == myID]
    moves = []
    frontiers=findFrontiers(mySquares)

    for square in mySquares:
        moved=False
        for direction in directions:
            neighbor = game_map.get_target(square, direction)
            if (square.strength > neighbor.strength and square.owner != neighbor.owner):
               moves.append(Move(square, direction))
               moved=True
               break
        if not moved:
            if (square.strength >= maxStrength - offSet):
                closest = closestFrontier(square, frontiers)
                moves.append(Move(square, directions[closest]))
            else:
                moves.append(Move(square, STILL))
    hlt.send_frame(moves)
    with open("test.log", "a") as mylog:
        mylog.write(str(frontiers))
#        mylog.write(str(game_map.contents))
#        for each in moves:
#            mylog.write(str(each) + "\n")


