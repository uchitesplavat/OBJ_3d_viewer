#!/bin/bash

clang-format -n *.c *.h *.cpp

while true; do
    read -r -p "Fix it? (Y/N): " answer
    case $answer in
        [Yy]* ) clang-format -i *.c *.h *.cpp; echo "All done"; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer Y or N.";;
    esac
done
