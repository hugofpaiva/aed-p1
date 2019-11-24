from prettytable import PrettyTable

x = PrettyTable()

x.field_names = ["Seed", "n", "n Visited",
                 "CPU Time", "Minimum Cost", "Maximum Cost"]
try:

    f = open("dados_tabela/bb_minmax_result_93195.txt", "r")
    line = f.readline()
    cnt = 1
    while line:
        values = line.strip("\t")
        x.add_row([values[0], values[1], values[2], values[3], values[4], values[5]])
        line = f.readline()
        


finally:
    f.close()
    print(x)
