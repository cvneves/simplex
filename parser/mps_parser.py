f = open("p1.mps", "r")


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

    if section == 'COLUMNS':
        var_name = l[0]
        del l[0]
        if var_name not in variables:
            variables[var_name] = {}
        for c in range(0, len(l)):
            if c % 2 == 0:
                variables[var_name][l[c]] = float(l[c+1])

    if section == 'RHS':
        rhs_name = l[0]
        del l[0]
        if rhs_name not in rhs:
            rhs[rhs_name] = {}
        for c in range(0, len(l)):
            if c % 2 == 0:
                rhs[rhs_name][l[c]] = float(l[c+1])

    if section == 'BOUNDS':
        if l[0] == 'UP':
            bound_type = 'L'
        elif l[0] == 'LO':
            bound_type = 'G'
        row_name = l[2] + "_" + l[0]
        restrictions[row_name] = bound_type

        variables[l[2]][row_name] = float(l[3])


# print(variables)
# print(restrictions)
# print(rhs)

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


for row in tableau:
    print(row)

print(n_artificial_vars)
print(n_slack_vars)
f.close()
