#!/usr/bin/env bash
# Author: Seb Blair
# Version 1.6
#
# Notes: 
# - Added HELPER
# - set files to be ignored
# - changed GNU to MSVC
# - remove comparitor file at end of loop

HELPER()
{   
    echo -e "Usage:\n\t bash checkFormatting .\n\t bash checkformatting /path/to/dir\n\t Only one argument\n"
}

if [[ $# -eq 0 ]] || [[ $# -gt 1 ]] || [ $1 == '-h' ] || [ ! -d $1 ]; then
    HELPER
    exit 1
fi

# Specify the directory containing the C files
project_dir=$1
cp_of_file="copiedfile"
clang_format_file="./msvc.conf"
files_to_ignore=( "cJSON.h" "cJSON.c" "json_parser.c" "json_parser.h" "${cp_of_file}")

# Find all .c and .h files in the project directory
files=$(find "$project_dir" -name '*.c' -o -name '*.h')

# Variable to track whether any differences were found
differences_found=0

# Iterate through each file and check the format
for file in $files; do
    cat $file > $cp_of_file
        # Check if the file is in the array of files to ignore
    if [[ ! " ${files_to_ignore[@]} " =~ " ${file##*/} " ]]; then
        # Use clang-format to format the file and store the result in a temporary file
        ./clang-format.exe -style=file "$clang_format_file" -i "$cp_of_file"

        # Use diff to compare the original and formatted files, and count the differing lines
        diff_lines=$(diff -u "$file" "$cp_of_file" | grep '^[+]' | wc -l)

        # Check if any differences were found
        if [ "$diff_lines" -gt 0 ]; then
            differences_found=1
            
            # Count the total number of lines in the original file
            total_lines=$(wc -l < "$file")

            # Calculate the percentage of lines not formatted
            percentage_not_formatted=$(awk "BEGIN {printf \"%.2f\", ($diff_lines / $total_lines) * 100 }")
            
            # If have bc
            # percentage_not_formatted=$(echo "scale=2; ($diff_lines / $total_lines) * 100" | bc)
            
            echo "File $file:"
            echo -e "\t Percentage of file not formatted: $percentage_not_formatted%"
            echo "----------------------------------------"
            
        fi
    fi
done

# delete temp file, you could comment to see each file differnce...
#rm $cp_of_file

# Print summary
if [ "$differences_found" -eq 1 ]; then
    echo "Formatting differences found in some files."
else
    echo "All files are formatted correctly."
fi