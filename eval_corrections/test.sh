#!/bin/bash

FILENUMS=15
VAL_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

build() {
    clear
    echo -e "${NC}===========================${NC}"
    echo -e "${GREEN}     Building...${NC}"
    echo -e "${NC}===========================${NC}"
    make re
    make clean
    DIR="${1}s/$1"
    echo -e "${NC}===========================${NC}"
    echo -e "${GREEN}     Done: building...${NC}"
    echo -e "${NC}===========================${NC}"
}

cleanup() {
    echo -e "${NC}===========================${NC}"
    echo -e "${GREEN}     Done: cleaning...${NC}"
    echo -e "${NC}===========================${NC}"
    make fclean
    echo -e "${NC}===========================${NC}"
    echo -e "${GREEN}     Done: cleaned...${NC}"
    echo -e "${NC}===========================${NC}"
}

print_error() {
    echo -e "${RED}================${NC}"
    echo -e "${RED}     Error${NC}"
    echo -e "${RED}================${NC}"
    echo -e "${GREEN}Usage: ./test.sh [scene | error] [leak] ${NC}"
    echo -e "${BLUE}scene:${NC} scenes test for scenes"
    echo -e "${BLUE}error:${NC} scenes test for errors"
    exit 1
}

print_test_title() {
    echo -e "${BLUE}===========================${NC}"
    echo -e "${BLUE}     $2 $1 Test $I${NC}"
    echo -e "${BLUE}===========================${NC}"
}

if [ "$1" == "scene" ] || [ "$1" == "error" ]; then
    build $1
    for I in $(seq 1 $FILENUMS)
    do
        EXEC="./minirt $DIR$I.rt"
        print_test_title $1 $2
        if [ "$2" == "leak" ]; then
            if [ "$(uname)" == "Darwin" ]; then
                $EXEC
                leaks -atExit -- $EXEC | grep "total leaked bytes" | awk '{print "'${GREEN}'" $0 "'${NC}'"}'
            else
                valgrind $VAL_FLAGS $EXEC 2>&1 | grep "ERROR SUMMARY:" | awk '{print "'${GREEN}'" $0 "'${NC}'"}'
            fi
        else
            $EXEC
        fi
    done
    cleanup
else
    print_error
fi