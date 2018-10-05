#!/bin/bash

directory=/comp/15/files/proj2tests/smallGutenberg/

./the_gerp $directory < commands.txt > ref_output.txt

./gerp $directory < commands.txt > my_output.txt

sort ref_output.txt > ref_output_sorted.txt
sort my_output.txt  > my_output_sorted.txt

diff ref_output_sorted.txt my_output_sorted.txt