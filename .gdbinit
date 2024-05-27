# Connect to the remote target
target extended-remote :3333
# Load the application
load
# Set a breakpoint on our entry to main
break main
