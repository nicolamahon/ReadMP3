# ReadMP3
Program to read and display the metadata from any MP3, run from command line

For this project I created a utility called read_mp3.c that is called by command line specifying the name of the MP3 file to be analyzed. For example: C:> read_mp3 mysong.mp3

The utility is designed to get some metadata information from the mp3 file by reading the MP3 audio tag stored in the file, and displaying the following information on the screen. 

- Title of the song
- Author of the song (artist)
- Album
- Year
- Genre

Some of the information may not be available. In that case an “Unknown” value is be displayed.
We use only MP3 files that contain a valid MP3 audio tag ID3 version 1.

The program reads the audio tag at the end of the file, saves it into a structure in memory and analyses the data. 
In order to check if the mp3 file contains a correct audio tag, the first 3 bytes are checked to see if they contain 
the letters ‘T’ , ‘A’ , ‘G’ . 
If not, an error message is displayed e.g. “The file does not contain a valid audio tag” and the program terminates. 
If the audio tag is valid, the Title, Artist, Album, Year and Genre are all displayed. 
