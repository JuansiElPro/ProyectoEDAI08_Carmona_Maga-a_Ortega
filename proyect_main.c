#include "proyect_playlist.h"

int main()
{
	Playlist* songs_list = New_Playlist();
	assert( songs_list );
	printf( "Número de canciones en la lista: %ld\n", Playlist_Num_Songs( songs_list ) );
	
	Insert_Song( songs_list, 120, "BlankSpace", "Taylor Swift" );
	Insert_Song( songs_list, 180, "Bohemian Rhapsody", "Queen" );
	Insert_Song( songs_list, 210, "Hotel California", "Eagles" );
	Insert_Song( songs_list, 240, "Imagine", "John Lennon" );
	Insert_Song( songs_list, 150, "Shape of You", "Ed Sheeran" );
	Insert_Song( songs_list, 190, "Stairway to Heaven", "Led Zeppelin" );
	printf( "Número de canciones en la lista: %ld\n", Playlist_Num_Songs( songs_list ) );
	
	Print_Playlist( songs_list );
	Print_Current_Song( songs_list );
	
	First_Song( songs_list );
	Next_Song( songs_list );
	Play_Current_Song( songs_list );
	
	if( Find_Song( songs_list, "Imagine" ) )
	{
		Play_Current_Song( songs_list );
	}
	
	Remove_Song( songs_list, "Shape of You" );
	printf( "Número de canciones en la playlist: %ld\n", Playlist_Num_Songs( songs_list ) );
	
	Play_Playlist( songs_list );
	
	Last_Song( songs_list );
	Prev_Song( songs_list );
	Play_Current_Song( songs_list );
	
	Playlist* playlist_10min = Playlist_limited( songs_list, 600 );
	
	printf( "Número de canciones en la playlist: %ld\n", Playlist_Num_Songs( playlist_10min ) );
	Print_Playlist( playlist_10min );
	
	Playlist* playlist_random = Playlist_random( songs_list );
	
	printf( "Número de canciones en la playlist: %ld\n", Playlist_Num_Songs( playlist_random ) );
	Print_Playlist( playlist_random );
	
	Playlist* playlist_ordered = New_Playlist();
	assert( playlist_ordered );
	Copy_Playlist( songs_list, playlist_ordered );
	Playlist_ordered_name( playlist_ordered, Playlist_Num_Songs( playlist_ordered ) );
	
	printf( "Número de canciones en la playlist: %ld\n", Playlist_Num_Songs( playlist_ordered ) );
	Print_Playlist( playlist_ordered );
	
	Delete_Playlist( &playlist_ordered );
	Delete_Playlist( &playlist_random );
	Delete_Playlist( &playlist_10min );
	Delete_Playlist( &songs_list );
	assert( songs_list == NULL);
}
