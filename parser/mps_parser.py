f = open("p1.mps", "r")

M = 1000000
restrictions = {}
variables = {}
rhs = {}
bounds = {}

for line in f:

    l = line.split()
    # print(l)

    if l[0] == 'NAME' or l[0] == 'ROWS' or l[0] == 'COLUMNS' or l[0] == 'RHS' or l[0] == 'BOUNDS' or l[0] == 'ENDATA':
        section = l[0]
        continue

    if section == 'ROWS':
        restrictions[l[1]] = l[0]
        if l[0] == 'N':
            obj_func_name = l[1]

    if section == 'COLUMNS':
        var_name = l[0]
        del l[0]
        if var_name not in variables:
            variables[var_name] = ({}, {})
        for c in range(0, len(l)):
            if c % 2 == 0:
                variables[var_name][0][l[c]] = float(l[c+1])

    if section == 'RHS':
        rhs_name = l[0]
        del l[0]
        if rhs_name not in rhs:
            rhs[rhs_name] = {}
        for c in range(0, len(l)):
            if c % 2 == 0:
                rhs[rhs_name][l[c]] = float(l[c+1])

    if section == 'BOUNDS':
        variables[l[2]][1][l[0]] = float(l[3])


# standard form pass

std_variables = variables
std_restrictions = restrictions
std_rhs = rhs


for var in std_variables.items():
    if var[1][1] == {}:
        continue

    elif 'FR' in var[1][1] or 'UP' in var[1][1] or 'LO' in var[1][1]:
        std_variables[var[0]+"+"] = (std_variables[var[0]][0].copy(), std_variables[var[0]][1].copy()) 
        std_variables[var[0]+"+"][1].clear()
        std_variables[var[0]+"-"] = (std_variables[var[0]][0].copy(), std_variables[var[0]][1].copy()) 
        std_variables[var[0]+"-"][1].clear()
        
        for i in std_variables[var[0]+"-"][0].items():
            std_variables[var[0]+"-"][0][i[0]] = -i[1]         
            del i

        if 'UP' in var[1][1]:
            std_restrictions[var[0]+"_UP_BOUND"] = 'L'
            std_variables[var[0]+"+"][0][var[0]+"_UP_BOUND"] = 1
        if 'LO' in var[1][1]:
            std_restrictions[var[0]+"_LO_BOUND"] = 'G'
            std_variables[var[0]+"-"][0][var[0]+"_LO_BOUND"] = -1

        del std_variables[var[0]]
    
    if 'FX' in var[1][1]:
        if var[1][1]['FX'] >= 0:
            std_restrictions[var[0]+"_FX_BOUND"] = 'E'
            var[1][0][var[0]+"_FX_BOUND"] = 1

        elif var[1][1]['FX'] < 0:
            std_restrictions[var[0]+"_FX_BOUND"] = 'E'
            var[1][0][var[0]+"_FX_BOUND"] = -1
        

for row in std_restrictions.items():
    if row[1] == 'N':
        continue
    elif row[1] == 'L':
        std_variables["SLACK_" + row[0]] = ({row[0]: 1.0}, {})
    elif row[1] == 'G':
        std_variables["SURPLUS_" + row[0]] = ({row[0]: -1.0}, {})
        std_variables["ARTIF_" + row[0]] = ({row[0]: 1, obj_func_name: M}, {})
    elif row[1] == 'E':
        std_variables["ARTIF_" + row[0]] = ({row[0]: 1, obj_func_name: M}, {})    
    
    
'''
UP LO FX FR
1  0  0  0
0  0  1  0
0  1  0  0
1  1  0  0

'''

#print(rhs)

# tableau creation



n_variables = len(std_variables.items())
n_restrictions = len(std_restrictions.items())

tableau = [[0 for x in range(n_variables)] for y in range(n_restrictions)]

i = 0
j = 0

for v in std_variables.items():
    pass
    print(v)


for row in std_restrictions.items():
    j = 0
    for column in std_variables.items():
        if row[0] in column[1][0]:
            tableau[i][j] = column[1][0][row[0]]
        j += 1
    i += 1
            

for row in tableau:
    print(row)

# for row in tableau:
#    print(row)

f.close()
