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

for row in std_restrictions.items():
    if row[1] == 'N':
        continue
    elif row[1] == 'L':
        variables["SLACK_" + row[0]] = ({row[0]: 1.0}, {})
    elif row[1] == 'G':
        variables["SURPLUS_" + row[0]] = ({row[0]: -1.0}, {})
        variables["ARTIF_" + row[0]] = ({row[0]: 1, obj_func_name: M}, {})
    elif row[1] == 'E':
        variables["ARTIF_" + row[0]] = ({row[0]: 1, obj_func_name: M}, {})

for var in std_variables.items():
    if var[1][1] == {}:
        continue
    elif 'FR' in var[1][1]:
        std_variables[var[0]+"+"] = (std_variables[var[0]][0].copy(), std_variables[var[0]][1].copy()) 
        std_variables[var[0]+"+"][1].clear()
        std_variables[var[0]+"-"] = (std_variables[var[0]][0].copy(), std_variables[var[0]][1].copy()) 
        std_variables[var[0]+"-"][1].clear()
        
        for i in std_variables[var[0]+"-"][0].items():
            std_variables[var[0]+"-"][0][i[0]] = -i[1]         
            del i

        del std_variables[var[0]]
    
'''
UP LO FX FR
1  0  0  0
0  0  1  0
0  1  0  0
1  1  0  0

'''



for v in std_variables.items():
    print(v)
#print(rhs)

# tableau creation

tableau = []
i = 0
j = 0
n_artificial_vars = 0
n_slack_vars = 0
N = 0
for row in restrictions.items():
    tableau.append([])

    for column in variables.items():
        if row[0] in column[1]:
            if row[1] == 'G':
                k = -1
            elif row[1] == 'N':
                N = i
                k = -1
            elif row[1] == 'L':
                k = 1
            elif row[1] == 'E':
                k = 1
            tableau[i].append(k * column[1][row[0]])
        else:
            tableau[i].append(0)

    tableau[N], tableau[0] = tableau[0], tableau[N]

    i += 1

tableau[0].insert(0, 1)
for row in tableau[1:]:
    row.insert(0, 0)

for row in restrictions.items():
    pass


# for row in tableau:
#    print(row)

f.close()
