#!/bin/bash

scp src/cat/s21_cat lancelmi@192.168.100.11:~/
scp src/grep/s21_grep lancelmi@192.168.100.11:~/
ssh lancelmi@192.168.100.11 "echo "WarriorX" | sudo -S mv s21_cat s21_grep /usr/local/bin"