#!/usr/bin/env python3

import cgi, cgitb
import sys
cgitb.enable()

# print int stderror
sys.stderr.write("This is a test of stderr\n")

input_data = cgi.FieldStorage()


print("Content-Type: text/html") # HTML is following
print("")                        # Leave a blank line
print("<h1>Addition Results</h1>")
# print("input_data: ", input_data)
try:
    num1 = int(input_data.getvalue('num1'))
    num2 = int(input_data.getvalue('num2'))
except:
    print("<output>Sorry, the script cannot turn your inputs into numbers (integers).</output>")
    raise SystemExit(1)
print("<output>{0} + {1} = {2}</output>".format(num1, num2, num1 + num2))