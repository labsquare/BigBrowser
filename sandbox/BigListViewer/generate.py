#!/usr/bin/python 
import sys 
import string 
import random 
import shutil
import os

alpha = [l for l in string.ascii_lowercase]


if os.path.exists("motif.txt"):
	os.remove("motif.txt")

if os.path.exists("data.txt"):
	os.remove("data.txt")

with open("motif.txt", "w") as motif_file:
	for i in range(100000):
		word = "".join(random.sample(alpha, 8))
		motif_file.write(word+"\n")


with open("data.txt", 'a') as file:
	for i in range(2000):
		shutil.copyfileobj(open("motif.txt", "r"), file)



