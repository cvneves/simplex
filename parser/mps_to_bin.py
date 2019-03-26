import sys
import mps_parser
import struct



file_name = sys.argv[1]

tableau = mps_parser.MpsParse(file_name)

for row in tableau:
    print(row)

