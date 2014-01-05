Deus Ex:  Human Revolution has a 100 save limit.
You can't even just go into your save directory and move the files out.
This is because the game keeps track of all the saves in a file called "saveindex"

This program goews through and clears that file out for you.

Just move gamer[1-next to last] out to whatever folder you like, and run this.

New versions may do this for you, or actually regenerate the index based on what's in the folder.

To Compile:
g++ -std=c++11 -o indexer indexer.cpp

To Run:
indexer.exe saveindex


Analysis (without attempting to start an actual game):
Note:  CTD bits were left alone.
Start time/date: 2/20/2013 19:30:42

It might be storing the time as GMT, so subtracting to EST might trigger a bug.

Bits[0-5]:	(*    -> 0x00) No Change
Bit[6]:		(0xEB -> 0x00) Time went back 1 second
Bit[7]:		(0xE8 -> 0x00) Time went back 6 minutes 30 seconds
Bit[8]:		(0xC6 -> 0x00) Time went back just under 1 day
Bit[9]:		(0x0F -> 0x00) Time went back to 1/31/2013 17:12:04

Bit[10]:	(0xCE -> 0xC0) Time went back to 8/06/2000 19:42:36
Bit[10]:	(0xCE -> 0xA0) Time went back to 1/21/1972 18:43:51
Bit[10]:	(0xCE -> 0x9F) Time went back to 3/01/1971 23:58:53
Bit[10]:	(0xCE -> 0x9E) Time went back to 4/10/1970 06:13:55
Note: That date translates to this in Unix Time:  8576035
Note: That date translates to this in Unix Time for GMT:  8594035
Bit[10]:	(0xCE -> 0x9D) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x9C) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x9A) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x98) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x90) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x81) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x80) Crash to Desktop on trying to open the load menu
Bit[10]:	(0xCE -> 0x00) Crash to Desktop on trying to open the load menu

Bit[11]:	(0x01 -> 0x00) Crash to Desktop on trying to open the load menu
Bit[11]:	(0x01 -> 0xFF) Crash to Desktop on trying to open the load menu

Bit[12]:	(0x23 -> 0x00) Location changed to Detroit: Jensen's Apartment Building
Bit[13]:	(0xD1 -> 0x00) No Change
Bit[14]:	(0x25 -> 0x00) No Change
Bit[15]:	(0x00 -> 0xFF) No Change
Bit[16]:	(0x32 -> 0x00) Dificulty Changed to Unkown
Bit[17]:	(0x6C -> 0x00) No Change
Bit[18]:	(0x87 -> 0x00) No Change
Bit[19]:	(0x01 -> 0x00) No Change






