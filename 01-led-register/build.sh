#!/bin/bash
xmake c
xmake f -c
xmake
cp build/*.hex $Desktop
