#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define CHAR_TAM 30

typedef struct
{
	int duration; //Duración en segundos
	char name [CHAR_TAM];   //Nombre de la canción
	char artist [CHAR_TAM]; //Nombre del artista o los artistas
	
} Song;

typedef struct Node
{
	Song* song;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} Playlist;

Song* New_Song( int duration, char name[], char artist[] );
void  Delete_Song( Node* this );

Playlist* New_Playlist();
void Delete_Playlist( Playlist** this );

void Insert_Song_front( Playlist* this, int duration, char name[], char artist[]  );
void Insert_Song_back( Playlist* this, int duration, char name[], char artist[] );
void Insert_Song( Playlist* this, int duration, char name[], char artist[] );

void Erase_Song_front( Playlist* this );
void Erase_Song_back( Playlist* this );
void Erase_Song( Playlist* this );

void Remove_Song( Playlist* this, char key[] );
bool Find_Song( Playlist* this, char key[] );

int    Get_duration( Playlist* this );
char*  Get_name( Playlist* this );
char*  Get_artist( Playlist* this );

void First_Song( Playlist* this );
void Last_Song( Playlist* this );
void Next_Song( Playlist* this );
void Prev_Song( Playlist* this );
bool Playlist_end( Playlist* this );

void   Make_Playlist_Empty( Playlist* this );
bool   Playlist_Is_empty( Playlist* this );
size_t Playlist_Num_Songs( Playlist* this );

void Print_Current_Song( Playlist* this );
void Print_Playlist( Playlist* this );

void Play_Current_Song( Playlist* this );
void Play_Playlist( Playlist* this );

Playlist* Playlist_random( Playlist* this );
Playlist* Playlist_limited( Playlist* this, int max_duration );
void Playlist_ordered_duration( Playlist* this, size_t elems );
void Playlist_ordered_name( Playlist* this, size_t elems );
void Playlist_ordered_artist( Playlist* this, size_t elems );
void Copy_Playlist( Playlist* this, Playlist* other );
