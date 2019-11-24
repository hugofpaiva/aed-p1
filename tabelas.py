from prettytable import PrettyTable
import os

try:
    for filename in os.listdir('dados_tabela'):
        f = open("dados_tabela/"+filename, "r")
        line = f.readline()
        x = PrettyTable()
        title_table = filename[0:len(filename)-4]
        x.title = title_table
        x.field_names = ["Seed", "n", "n Visited",
                         "CPU Time", "Minimum Cost", "Maximum Cost"]
        while line:
            values = line.strip("\n").split("\t")
            while("" in values):
                values.remove("")

            x.add_row([values[0], values[1], values[2],
                       values[3], values[4], values[5]])
            line = f.readline()
        print(x)
        print("\n")

finally:
    f.close()
