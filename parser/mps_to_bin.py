import sys
import mps_parser
import struct



file_name = sys.argv[1]

tableau, basic_variables = mps_parser.MpsParse(file_name)


print(len(tableau))
print(len(tableau[0]))
for row in tableau:
    for column in row:
        print(column)
print(len(basic_variables))
for b_var in basic_variables:
    print(b_var)
