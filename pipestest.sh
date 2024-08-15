#!/bin/bash

# Construct the command
command="ls"
for ((i=1; i<=500; i++)); do
    command+=" | ls"
done

# Print the command
echo "$command"

# Save the command into a variable
export COMMAND="$command"

# Inform user about how to run the command in the terminal
# echo "To execute the command, run: \$COMMAND"
