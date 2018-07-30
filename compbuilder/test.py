from Tkinter import *

# Data dictionaries
class Item:
    def __init__(self, name, value):
        self._name = name
        self._value = value
    def getName(self):
        return self._name
    def getValue(self):
        return self._value

computerParts=[
        "CPU",
        "Motherboard",
        "Power Supply Unit",
        "RAM",
        "Persistant Storage",
        "GPU",
        "Case"
]

partsDict = {}
for part in computerParts:
    partsDict[part]=[]

# Data entries
partsDict["CPU"].append(Item('Intel i3 8100', 650.0))
partsDict["CPU"].append(Item('Intel i3 8350', 900.0))
partsDict["CPU"].append(Item('Intel i5 8400', 1000.0))
partsDict["Motherboard"].append(Item('Asus PRIME H310M', 500.0))
partsDict["Motherboard"].append(Item('Gigabyte DS3 H310M', 450.0))
partsDict["Power Supply Unit"].append(Item('CORSAIR RMi 1000', 600.0))
partsDict["Power Supply Unit"].append(Item('EVGA RMi 1000', 600.0))
partsDict["RAM"].append(Item('CORSAIR 4gb', 200.0))
partsDict["RAM"].append(Item('HyperFlex 4gb', 250.0))
partsDict["Persistant Storage"].append(Item('Western Digital 1TBb', 250.0))
partsDict["Persistant Storage"].append(Item('Toshiba Digital 1TBb', 230.0))
partsDict["GPU"].append(Item('Geforce GTX 1050 Ti 4GB', 900.0))
partsDict["GPU"].append(Item('Geforce GTX 1060 Ti 6GB', 1300.0))
partsDict["Case"].append(Item('Midtower', 115.0))
partsDict["Case"].append(Item('High tower', 310.0))

priceDict={}
for itemType, items in partsDict.iteritems():
    for item in items:
        priceDict[item.getName()]=item.getValue()


class App:

    def __init__(self, master):

        frame = Frame(master)
        frame.grid()

        self.button = Button(
            frame, text="QUIT", fg="red", command=frame.quit
            )
        self.button.grid()

        self.listv = []
        self.listv2 = []
        self.col1Buttons = []
        self.col2Menu= []
        self.col3Labels= []
        row_number = 3
        for part in computerParts:
            self.col1Buttons.append(
                    Button(
                        frame, text=part,
                        width=50
                        )
                    )
            self.col1Buttons[-1].grid(row=row_number, column=0)
            self.listv.append(StringVar())
            tmp_names_list = []
            for each in partsDict[part]:
                tmp_names_list.append(each.getName())
            self.col2Menu.append(
                    OptionMenu(
                            frame, self.listv[-1],
                            *tmp_names_list,
                            command = self.menuHandler
                            )
                    )
            self.col2Menu[-1].config(width=50)
            self.col2Menu[-1].grid(row=row_number, column=1)
            self.listv2.append(StringVar())
            self.col3Labels.append(
                    Label(
                        frame,
                        textvariable = self.listv2[-1],
                        width=30
                        )
                    )
            self.col3Labels[-1].grid(row=row_number, column=2)
            row_number = row_number + 1

        self.totalv = DoubleVar()
        self.totalv.set(0)
        self.totalLabel = Label(
                    frame,
                    textvariable = self.totalv,
                    width=30
                    )
        self.totalLabel.grid(row=row_number, column=2)



    def say_hi(self):
        print "hi there, everyone!"

    def __testHandler(self, event):
        print "I'm a handler"
        self.v2.set(self.dict[self.v.get()])

    def menuHandler(self, event):
        for i in range(len(self.listv)):
            if (event == self.listv[i].get()):
                print "Price is: " + str(priceDict[event])
                self.listv2[i].set(priceDict[event])
        total = 0
        for each in self.listv2:
            try:
                total += float(each.get())
            except:
                pass
        self.totalv.set(total)

root = Tk()

app = App(root)

root.mainloop()
root.destroy() # optional; see description below
