import re 
import string

#prints item name and quantity
def printGroceryList():
    groceryList = readGroceryListFile()
    for itemName in groceryList:
        print(itemName + ":" + str(groceryList[itemName]))

#prints selected item and its quantity
def countGroceryItem(itemName):
    groceryList = readGroceryListFile()
    if itemName in groceryList:
        return groceryList[itemName]
    return 0

#creates frequency file and writes dict to it
def writeGroceryListToFile():
    groceryList = readGroceryListFile()
    f = open("frequency.dat", "w")
    for itemName in groceryList:
        f.write(itemName + " " + str(groceryList[itemName]))
    f.close()

#function reads the items in grocery list and counts frequency
def readGroceryListFile():
    groceryList = open("Project3InputFile.txt", "r")
    d = dict()
    for item in groceryList:
        item = item.strip()
        if item in d:
            d[item] = d[item] + 1
        else:
            d[item] = 1 
    groceryList.close()
    return d
