def init():
    battle_matrix = open("data/battle_matrix.txt", "w")
    for i in range(15):
        for j in range(25):
            battle_matrix.write(str(0))
            battle_matrix.write(" ")
        battle_matrix.write("\n")


def save_turn(matrix, turn):
    string = "data/battle_matrix_turn_" + str(turn)
    battle_matrix = open(string, "w")
    for i in range(15):
        for j in range(25):
            battle_matrix.write(str(matrix[i][j]))
            battle_matrix.write(" ")
        battle_matrix.write("\n")
    
init()

#unit ID, pos

#functions yet to be coded:
#create UNIT: generate ID, search for the "unit type" for stats info and set a POS
#if player unit, uses the main_characters.txt
#else use the default_units_base

#each unit should also contain the basic functions that are unique to that class
#code the basic_actions.py, available to all types of unit
#
