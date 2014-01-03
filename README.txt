Deus Ex:  Human Revolution has a 100 save limit.
You can't even just go into your save directory and move the files out.
This is because the game keeps track of all the saves in a file called "saveindex"

This program goews through and clears that file out for you.

Just move gamer[1-next to last] out to whatever folder you like, and run this.

New versions may do this for you, or actually regenerate the index based on what's in the folder.

To Compile:
g++ -o indexer indexer.cpp

To Run:
indexer.exe saveindex