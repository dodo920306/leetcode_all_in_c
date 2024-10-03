#!/bin/bash

if [[ -e './"$1".out' ]]; then
    rm ./"$1".out
fi

gcc -O2 -std=c11 -Wall -o "$1".out "$1".c
./"$1".out
