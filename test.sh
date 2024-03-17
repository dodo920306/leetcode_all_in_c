#!/bin/bash

gcc -O3 -std=c11 -Wall -o "$1".out "$1".c
./"$1".out
