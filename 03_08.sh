#!/bin/bash
#
#Team Number 3
# Date- 30/10/2023
#
# Siddharth Banerjee- 002111001097
# Tanmay Roy- 002111001017
# Anupam Ghosh- 002111001102
# Vikash Sangai- 002111001100
# 
# Details:
# This shell script contains bash scripts corresponding to the questions in assignment 8.
#
# Input and Output of each question are as specified per question. 
#
# Q1.> Create a directory ‘All My Cprogs Files’ in your home directory.
# mkdir 'All My Cprogs Files'
# execution: chmod +x 03_08.sh 
# ./03_08.sh
# output of ls command:
# 03_03.c    03_1A.txt   03_2A.c   03_3.c   03_5.c   03_7.c                 deadlock   interrupt   pagef      sock
# 03_08.sh   03_1B.c     03_2B.c   03_4.c   03_6.c  'All My Cprogs Files'   fifo       ipc         procinfo


# Q2.> Move all the C files to the new creating directory.
# mv *.c 'All My Cprogs Files'
# execution:
# ./03_08.sh


# Q3.> Show the list of files in your current directory.
# ls 
# execution:
# ./03_08.sh
# output:
# 03_08.sh
# 03_1A.txt
# All My Cprogs Files
# deadlock
# fifo
# interrupt
# ipc
# pagef
# procinfo
# sock

#
# Q4.> Show current working directory.
# pwd
# execution: 
# ./03_08.sh
# output:
# /home/siddharth/Programs/Assignments/OS



# Q5.> Display date in the dd:mm:yy format
# formatted_date=$(date +'%d:%m:%y')
# echo "Formatted Date: $formatted_date"
#
# execution:
# ./03_08.sh
# output:
# Formatted Date: 30:10:23 


# Q6.> Count the number of files in your home directory.
#
# ls -l | wc -l
# execution:
# ./03_08.sh
# output:
# 11

# Q7.> Create a file that lists all of the .C files in your directory.
# ls -l *.c > list_of_cprogs.txt
#
# execution:
# ./03_08.sh
# output: 
# zsh: no matches found: *.c 


# Q8.> Write a script for addition of two numbers for real numbers also.
# result=$(echo "$1 + $2" | bc)
# echo "The sum of $1 and $2 is $result"
# execution:
# ./03_08.sh {1st number} {2nd number}
#
# output:
# ./03_08.sh 2 4
# The sum of 2 and 4 is 6


# Q9.>  Write a script to convert string lower to upper and upper to lower from a file.
# input_file=$1
# output_file=$2
# # Check if the input file exists
# if [ -f "$input_file" ]; then
#     # Perform conversion and save to output file
#     tr 'a-zA-Z' 'A-Za-z' < "$input_file" > "$output_file"
#     echo "Conversion completed. Output saved to $output_file."
# else
#     echo "Error: Input file not found."
# fi
# execution: 
# ./03_08.sh <input_filename> <output_filename>
# output:
# ./03_08.sh smol.txt big.txt
# Conversion completed. Output saved to big.txt.
# content of smol.txt:
# hello world
# content of big.txt
# HELLO WORLD 


# Q10.> Read ‘n’ and generate a pattern given below.
# 1
# 1 2
# 1 2 3
# 1 2 3 4
#
# n=$1
# for ((i = 1; i <= n; i++)); do
#  for ((j = 1; j <= i; j++)); do
#    echo -n "$j "
#  done
#  echo
# done

# execution: 
# ./03_08.sh {number of lines}
#
# output:
# ./03_08.sh 5
# 1 
# 1 2 
# 1 2 3 
# 1 2 3 4 
# 1 2 3 4 5
