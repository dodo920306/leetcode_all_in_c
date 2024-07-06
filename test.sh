#!/bin/bash

gcc -O2 -std=c11 -Wall -o "$1".out "$1".c
./"$1".out
