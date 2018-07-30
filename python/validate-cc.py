import re
n = int(input())
cards = list()
def checkCard(number):
    isCard = True

    # compile regexs
    first       = re.compile(r"^[4-6]")
    hiphens     = re.compile(r"(\d{4}-?)*")
    splitter    = re.compile(r"-")
    consecutive = re.compile(r"(\d)\1{3,}")
    sixteen     = re.compile(r"\d{16}")

    
    # try first digit
    match = first.match(number)
    if (not(hasattr(match, "group"))):
        isCard = False
        return isCard

    # check for groups of 4 digits with hiphens
    match = hiphens.match(number)
    length = len(match.group(0))
    if (length < 16):
        isCard = False
        return isCard

    # clean string and check if sixteen numbers exist 
    if (length > 16):
        groups_list=splitter.split(number) 
        string=""
        for i in groups_list:
            string=string+i 

    else:
        string=number


    match = sixteen.match(string)
    length = len(match.group(0))
    if (length < 16):
        isCard = False

    # check for consecutive numbers on clean string
    match = consecutive.search(string)
    if (hasattr(match, "group")):
        isCard = False


    return isCard

for i in range(0, n):
    cards.append((input()))

for i in range(0, n):
    if(checkCard(cards[i])):
        print("Valid")
    else:
        print("Invalid")
