#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import arifm


def usage():
	print "\n1.txt op 2.txt out.txt -b\n"
	sys.exit(-1);
b1 = arifm.chislo();
b2 = arifm.chislo();
itog = arifm.chislo();
binary = False;
if len(sys.argv) < 5 or len(sys.argv) > 6:
	usage();
elif len(sys.argv) == 6:

	if sys.argv[5] == "-b":
		binary = True;
	else:
		usage();
	if binary == False:
		 b1.readText(sys.argv[1]);
		 b2.readText(sys.argv[3]);
	else:
		b1.ReadBin(sys.argv[1]);
		b2.ReadBin(sys.argv[3]);
	if sys.argv[2] == "+":
		itog = b1 + b2;
	elif sys.argv[2] == "-":
		itog = b1 - b2;
	elif sys.argv[2] == "x":
		itog = b1 * b2;
	elif sys.argv[2] == "/":
		itog = b1 / b2;
	elif sys.argv[2] == "%":
		itog = b1 % b2;
	elif sys.argv[2] == "^":
		itog = b1 ^ b2;
	else:
		usage();
	if binary == False:
		itog.writeText(sys.argv[4]);
	else:
		itog.WriteBin(sys.argv[4]);
