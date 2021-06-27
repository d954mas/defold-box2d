#!/usr/bin/env python

# This script generates static hash values of strings to be used with the hash_string()
# function and switch statements.
# Allowing to easily switch on const char* expressions.

import re
import os

strings = set()

def process(content):
	for string in re.findall(r'case HASH_(.*):', content):
		strings.add(string)

def string_hash(string):
	h = 0
	for character in string:
		h = 65599 * h + ord(character)
		h = h & 0xffffffff
	return str(h ^ (h >> 16))

def generateEnum():
	enum = ['enum HASH_STRINGS : unsigned int {']
	for string in strings:
		enum.append('\tHASH_' + string + ' = ' + string_hash(string) + 'u,')
	last_line = enum[len(enum) - 1]
	enum[len(enum) - 1] = last_line[:-1]
	enum.append('};')
	with open('../include/static_hash_enum.h', 'w') as f:
		f.write('\n'.join(enum))

for file in os.listdir('.'):
	if file.endswith('.cpp') or file.endswith('.c'):
		with open(file, 'r') as f:
			process(f.read())
	generateEnum()