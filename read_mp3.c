/* Program to read and display the metadata from an MP3 file. 

Name: Nicola Mahon C15755031
Date: 2016-05-01

Compiler: Borland
OS: Windows 10

*/

// header files
#include <stdio.h>
#include <stdlib.h>

// symbollic names
#define SIZE 30
#define TAG 3
#define GENRES 126

// structure templates
struct metadata
{
    char tag[TAG];
    char title[SIZE];
    char artist[SIZE];
    char album[SIZE];
    char year[4];
    char comment[SIZE];
    char genre[1];
};

int main(int argc, char* argv[])
{
    if (argc !=2)
    {
        printf("\nERROR: Function requires 2 inputs.\n");
        printf("Please try again.\n");
        printf("Enter the name of 1) the program file and 2) the song.mp3 to be read.\n");
        exit(0);
    }
    else
    {
        // file pointers for reading and writing to files
        FILE *fp_read;
        
        // array of genres, listed in order of their corresponding numeric value i.e. 0 = Blues, 1  = Classic Rock, etc
        char *genres[GENRES] = {"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz", "Metal", 
            "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno", "Industrial", 
            "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", 
            "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental", "Acid", "House", "Game", 
            "Sound Clip", "Gospel", "Noise", "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative", 
            "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave", "Techno-Industrial", 
            "Electronic", "Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult", "Gangsta", 
            "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave", 
            "Psychadelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", 
            "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk-Rock", "National Folk", 
            "Swing", "Fast Fusion", "Bebob", "Latin", "Revival", "Celtic", "Bluegrass", "Avantgarde", 
            "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band", 
            "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera", "Chamber Music", 
            "Sonata", "Symphony", "Booty Brass", "Primus", "Porn Groove", "Satire", "Slow Jam", "Club", "Tango", 
            "Samba", "Folklore", "Ballad", "Poweer Ballad", "Rhytmic Soul", "Freestyle", "Duet", "Punk Rock", 
            "Drum Solo", "A Capela", "Euro-House", "Dance Hall"};
            
        // variable to hold data about a song 
        struct metadata song;
            
        // variables to check if song has a valid TAG identifier
        char check_tag[TAG] = "TAG";
        int check = 0;
        
        // try to open the file (entered through command line)
        fp_read = fopen(argv[1], "r");
        
        // error check for opening the file
        if (fp_read == NULL)
        {
            printf("\nERROR: File could not be opened.\n");
        }
        else 
        {
            // move pointer to 128 bytes from the end of the file
            fseek(fp_read, -128, SEEK_END);
            
            // index variable for loops
            register int i; 
            
            // read the first 3 bytes of the file into the tag array
            for (i=0; i<TAG; i++)
            {
                fread(&song.tag[i], sizeof(char), 1, fp_read);
            }
            
            // check the first 3 bytes first 3 bytes of the file into the tag array
            for (i=0; i<TAG; i++)
            {
                if (song.tag[i] == check_tag[i])
                {
                    check++;
                }
            }
            
            // display that song holds a valid TAG or not, if not, end the program
            if (check != 3)
            {
                printf("\nERROR: The file does not contain a valid audio tag.\n");
                printf("Program terminated.\n");
                exit(0);
            }
            else 
            {
                printf("\nSuccess:The file contains a valid audio tag.\n\n");
                
                // move the pointer to the location of the song title, read the title and print to screen
                fseek(fp_read, -125, SEEK_END);
                fread(&song.title, SIZE, 1, fp_read);
                
                // print if this info was not available when reading
                if (song.title[0] == ' ')
                {
                    printf("Title: Unknown\n");
                }
                else
                {
                    printf("Title: %s\n", song.title);
                }
                
                // move the pointer to the location of the song artist, read the artist and print to screen
                fseek(fp_read, -95, SEEK_END);
                fread(&song.artist, SIZE, 1, fp_read);
                
                // print if this info was not available when reading
                if (song.artist[0] == ' ')
                {
                    printf("Artist: Unknown\n");
                }
                else
                {
                    printf("Artist: %s\n", song.artist);
                }
                
                // move the pointer to the location of the song album, read the album and print to screen
                fseek(fp_read, -65, SEEK_END);
                fread(&song.album, SIZE, 1, fp_read);
                
                // print if this info was not available when reading
                if (song.album[0] == ' ')
                {
                    printf("Album: Unknown\n");
                }
                else
                {
                    printf("Album: %s\n", song.album);
                }
                
                // move the pointer to the location of the song year, read the year and print to screen
                fseek(fp_read, -35, SEEK_END);
                fread(&song.year, 4*sizeof(char), 1, fp_read);
                
                // print if this info was not available when reading
                if (song.year[0] == ' ')
                {
                    printf("Year: Unknown\n");
                }
                else
                {
                    printf("Year: %s\n", song.year);
                }
                
                // move the pointer to the location of the song comment and read the comment
                fseek(fp_read, -31, SEEK_END);
                fread(&song.comment, SIZE, 1, fp_read);
                // the program specifically requested that comments not be displayed in the output to screen, so these have been read but not displayed
                
                // move the pointer to the location of the song genre numeric value and read the value 
                fseek(fp_read, -1, SEEK_END);
                fread(&song.genre, sizeof(char), 1, fp_read);
                
                // convert the genre char value to an integer for comparing to the genre array
                int genre_type;
                genre_type = song.genre[0];
                
                // variable to check if genre was unknown
                int genre_check = 0;
                
                // loop through the genres 
                for(i=0; i<GENRES; i++)
                {
                    // if the genre numeric value matches the index
                    if (genre_type == i)
                    {
                        // print that genre type to the screen
                        printf("Genre: %s\n", genres[i]);
                        genre_check++;
                    }
                }
                
                // check if genre was unknown
                if (genre_check == 0)
                {
                    printf("Genre: Unknown\n");
                }
                
                
                // close the files
                fclose(fp_read);
                printf("\nFile closed. Program Terminated.\n");
                
                // end the program
                exit(0);
                
            } // end valid tag else
            
        } // end else check opening file for reading
        
    } // end valid args else
    
} // end main