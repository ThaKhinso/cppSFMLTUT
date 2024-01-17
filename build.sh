#!/usr/bin/sh

set -xe

g++ src/main.cpp -o bin/cppSFMLTUT -lsfml-graphics -lsfml-window -lsfml-system
