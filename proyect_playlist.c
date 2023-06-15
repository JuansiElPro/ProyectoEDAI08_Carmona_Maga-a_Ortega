#include "proyect_playlist.h"

/**
* @brief Crea una nueva canción ligada a una Playlist.
*
* @param duration Duración de la canción.
* @param name Nombre de la canción.
* @param artist Nombre del artista.
*
* @return Una referencia a la nueva canción.
* @post Una canción ligada existente en el heap.
*/
static Node* New_Node( int duration, char name[], char artist[] )
{
	Node* n = (Node*) malloc( sizeof( Node ) );
	if( n != NULL )
	{
		Song* s = New_Song( duration, name, artist );
		assert( s );
		
		n->song = s;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

/**
* @brief Crea una nueva canción.
*
* @param duration Duración de la canción.
* @param name Nombre de la canción.
* @param artist Nombre del artista.
*
* @return Una referencia a la nueva canción.
* @post Una canción existente en el heap.
*/
Song* New_Song( int duration, char name[], char artist[] )
{
	Song* s = (Song*) malloc( sizeof( Song ) );
	if( s )
	{
		s->duration = duration;
		strncpy( s->name, name, CHAR_TAM - 1 );
		strncpy( s->artist, artist, CHAR_TAM - 1 );
	}
	return s;
}

/**
* @brief Destruye una canción.
*
* @param this Una Playlist.
*/
void Delete_Song( Node* this )
{
	assert( this->song );
	
	free( this->song );
	
	this->song = NULL;
}

/**
* @brief Crea Playlist basada en una lista doblemente enlazada.
*
* @return Una referencia a la nueva Playlist.
* @post Una lista existente en el heap.
*/
Playlist* New_Playlist()
{
	Playlist* list = (Playlist*) malloc( sizeof(Playlist) );
	if( list )
	{
		list->first = list->last = list->cursor = NULL;
		list->len = 0;
	}
	return list;
}

/**
* @brief Destruye una Playlist.
*
* @param this Una Playlist.
*/
void Delete_Playlist( Playlist** this )
{
	assert( *this );
	
	Make_Playlist_Empty( *this); // ¡primero borra todos los nodos!
	
	free( *this );// luego borra al propio objeto this
	
	*this = NULL; // luego haz que this sea NULL
}

/**
* @brief Inserta una canción en el principio de la Playlist.
*
* @param this Una Playlist.
* @param duration La duración de la canción a insertar.
* @param name El nombre de la canción a insertar.
* @param artist El nombre del artista de la canción a insertar.
*/
void Insert_Song_front( Playlist* this, int duration, char name[], char artist[] )
{
	assert( this );
	Node* n = New_Node( duration, name, artist );
	assert( n );
	
	if( this->first != NULL )
	{
		n->next = this->first;
		this->first->prev = n;
		this->first = n;
	}
	else
	{
		this->first = this->last = this->cursor = n;
	}
	++this->len;
}

/**
* @brief Inserta una canción al final de la Playlist.
*
* @param this Una Playlist.
* @param duration La duración de la canción a insertar.
* @param name El nombre de la canción a insertar.
* @param artist El nombre del artista de la canción a insertar.
*/
void Insert_Song_back( Playlist* this, int duration, char name[], char artist[] )
{
	assert( this );
	Node* n = New_Node( duration, name, artist );
	assert( n );
	
	if( this->first != NULL )
	{
		
		this->last->next = n;
		n->prev = this->last;
		this->last = n;
	}
	else
	{
		this->first = this->last = this->cursor = n;
	}
	++this->len;
}

/**
* @brief Inserta una canción a la derecha del cursor.
*
* @param this Una Playlist.
* @param duration La duración de la canción a insertar.
* @param name El nombre de la canción a insertar.
* @param artist El nombre del artista de la canción a insertar.
*/
void Insert_Song( Playlist* this, int duration, char name[], char artist[] )
{
	assert( this );
	if ( this->cursor == this->last )
	{
		Insert_Song_back( this, duration, name, artist );
		this->cursor = this->last;
	}
	else
	{
		Node* n = New_Node( duration, name, artist );
		assert( n );
		
		Node* right = this->cursor->next;
		this->cursor->next = n;
		n->next = right;
		right->prev = n;
		n->prev = this->cursor;
		this->cursor = n;
		++this->len;
	}
}

/**
* @brief Elimina la canción al principio de la Playlist dada.
*
* @param this Referencia a una Playlist.
*
* @post El cursor se mantiene en la posición en la que estaba cuando entró la función.
*/
void Erase_Song_front( Playlist* this )
{
	assert( this );
	assert( this->len > 0 );
	
	if( this->last != this->first ) // también funciona: if( this->len > 1 ){...}
	{
		Delete_Song( this->first );
		Node* tmp = this->first->next;
		free( this->first );
		tmp->prev = NULL;
		this->first = tmp;
		--this->len;
	}
	else
	{
		Delete_Song( this->first );
		free( this->first );
		this->first = this->last = this->cursor = NULL;
		this->len = 0;
	}
}

/**
* @brief Elimina la canción al final de la Playlist dada.
*
* @param this Referencia a una Playlist.
*
* @post El cursor se mantiene en la posición en la que estaba cuando entró la función.
*/
void Erase_Song_back( Playlist* this )
{
	assert( this );
	assert( this->len > 0 );
	// ERR: no se puede borrar nada de una lista vacía
	
	if( this->last != this->first ) // también funciona: if( this->len > 1 ){...}
	{
		Delete_Song( this->last );
		Node* x = this->last->prev;
		free( this->last );
		x->next = NULL;
		this->last = x;
		--this->len;
	}
	else
	{
		Delete_Song( this->last );
		free( this->last );
		this->first = this->last = this->cursor = NULL;
		this->len = 0;
	}
}

/**
* @brief Elimina la canción apuntada por el cursor en Playlist dada.
*
* @param this Referencia a una Playlist.
*
* @post El cursor se mueve a la derecha de la posición en la que estaba cuando entró la función.
*/
void Erase_Song( Playlist* this )
{
	assert( this );
	assert( this->len > 0 );
	assert ( this->cursor != NULL );
	
	if ( this->first == this->last )
	{
		Delete_Song( this->cursor );
		free( this->cursor );
		this->first = this->last = this->cursor = NULL;
		this->len = 0;
	}
	else if( this->cursor == this->last )
	{
		Erase_Song_back( this );
		this->cursor = this->last->next;
	}
	else if( this->cursor == this->first )
	{
		Erase_Song_front( this );
		this->cursor = this->first;
	}
	else
	{
		Delete_Song( this->cursor );
		Node* left = this->cursor->prev;
		Node* right = this->cursor->next;
		free( this->cursor);
		left->next = right;
		right->prev = left;
		this->cursor = right;
		--this->len;
	}
}

/**
* @brief Elimina la primer canción que coincida con la llave.
*
* @param this Una Playlist.
* @param key Nombre de la canción buscada.
*
*/
void Remove_Song( Playlist* this, char key[] )
{
	assert( this );
	
	Node* tmp = this->cursor;
	for( First_Song( this ); !Playlist_end( this ); Next_Song( this ) )
	{
		if( strcmp( Get_name( this ), key ) == 0 )
		{
			if( this->cursor == tmp )
			{
				tmp = this->cursor->next;
			}
			Erase_Song( this );
			break;
		}
	}
	this->cursor = tmp;
}

/**
* @brief Busca una canción en la Playlist. Si lo encuentra coloca ahí al cursor.
*
* @param this Una Playlist.
* @param key El nombre de la canción que se está buscando.
*
* @post Si se encontró una coincidencia coloca al cursor en esa canción; 
* en caso contrario el cursor vuelve a su posición original.
*
*/
bool Find_Song( Playlist* this, char key[] )
{
	assert( this );
	
	Node* tmp = this->cursor;
	for( First_Song( this ); !Playlist_end( this ); Next_Song( this ) )
	{
		if( strcmp( Get_name( this ), key ) == 0 )
		{
			return true;
		}
	}
	this->cursor = tmp;
	return false;
}

/**
* @brief Devuelve una copia de la duración de la canción apuntada por el cursor.
*
* @param this Una Playlist.
*
* @return La duración de la canción apuntada por el cursor.
*/
int Get_duration( Playlist* this )
{
	assert ( this->cursor != NULL );
	return ( this->cursor->song->duration );
}

/**
* @brief Devuelve una copia del nombre de la canción apuntada por el cursor.
*
* @param this Una Playlist.
*
* @return Nombre de la canción apuntada por el cursor.
*/
char* Get_name( Playlist* this )
{
	assert ( this->cursor != NULL );
	return ( this->cursor->song->name );
}

/**
* @brief Devuelve una copia del nombre del artista apuntada por el cursor.
*
* @param this Una Playlist.
*
* @return Nombre del artista apuntada por el cursor.
*/
char* Get_artist( Playlist* this )
{
	assert ( this->cursor != NULL );
	return ( this->cursor->song->artist );
}

/**
* @brief Coloca al cursor al inicio de la Playlist.
*
* @param this Una referencia a la Playlist.
*/
void First_Song( Playlist* this )
{
	this->cursor = this->first;
}

/**
* @brief Coloca al cursor al final de la Playlist.
*
* @param this Una referencia a la Playlist.
*/
void Last_Song( Playlist* this )
{
	this->cursor = this->last;
}

/**
* @brief Mueve al cursor a la siguiente canción de la derecha.
*
* @param this Una Playlist.
*/
void Next_Song( Playlist* this )
{
	assert ( this->cursor != NULL );
	this->cursor = this->cursor->next;
}

/**
* @brief Mueve al cursor a la siguiente canción de la izquierda.
*
* @param this Una Playlist.
*/
void Prev_Song( Playlist* this )
{
	assert ( this->cursor != NULL );
	this->cursor = this->cursor->prev;
}

/**
* @brief Indica si el cursor a finalizado el recorrido por la Playlist.
*
* @param this Una Playlist.
*
* @return true si llegó al final; false en caso contrario.
*/
bool Playlist_end( Playlist* this )
{
	return this->cursor == NULL ;
}

/**
* @brief Indica si la Playlist está vacía.
*
* @param this Referencia a una Playlist.
*
* @return true si la Playlist está vacía; false en caso contrario.
*/
bool Playlist_Is_empty( Playlist* this )
{
	assert( this );
	return( this->len == 0 );
}

/**
* @brief Devuelve el número actual de elementos en la Playlist.
*
* @param this Una Playlist.
*
* @return Devuelve el número actual de elementos en la Playlist.
*/
size_t Playlist_Num_Songs( Playlist* this )
{
	return ( this->len );
}

/**
* @brief Elimina todos las canciones de una Playlist sin eliminar la lista.
*
* @param this Una Playlist.
*/
void Make_Playlist_Empty( Playlist* this )
{
	assert( this );
	if ( Playlist_Num_Songs > 0 )
	{
		while( this->first )
		{
			Erase_Song_front( this );
		}
	}
}

/**
* @brief Imprime los datos de la canción apuntada por el cursor en una Playlist.
*
* @param this Una Playlist.
*/
void Print_Current_Song( Playlist* this )
{
	assert( this );
	
	if( Playlist_Num_Songs( this ) == 0 )
	{
		printf( "La playlist está vacía\n" );
	}
	else
	{
		printf( "Duración: %d:%02d\t Nombre: %s\t\t Artista: %s\t\n", 
			   Get_duration( this ) / 60, Get_duration( this ) % 60, //Imprime la duración en minutos y segundos
			   Get_name( this ),
			   Get_artist( this ));
	}
}

/**
* @brief Imprime los datos de toda una Playlist.
*
* @param this Una Playlist.
*/
void Print_Playlist( Playlist* this )
{
	assert( this );
	
	if( Playlist_Num_Songs( this ) == 0 )
	{
		printf( "La playlist está vacía\n" );
	}
	else
	{
		Node* tmp = this->cursor;
		for( First_Song( this ); !Playlist_end( this ); Next_Song( this ) )
		{
			Print_Current_Song( this );
		}
		this->cursor = tmp;
	}
}

/**
* @brief Reproduce la canción apuntada por el cursor en una Playlist.
*
* @param this Una Playlist.
*/
void Play_Current_Song( Playlist* this )
{
	assert( this );
	
	if( Playlist_Num_Songs( this ) == 0 )
	{
		printf( "La playlist está vacía\n" );
	}
	else
	{
		printf( "Reproduciendo la canción: %s\n", Get_name( this ) );
	}
}

/**
* @brief Reproduce toda una Playlist.
*
* @param this Una Playlist.
*/
void Play_Playlist( Playlist* this )
{
	assert( this );
	
	if( Playlist_Num_Songs( this ) == 0 )
	{
		printf( "La playlist está vacía\n" );
	}
	else
	{
		Node* tmp = this->cursor;
		for( First_Song( this ); !Playlist_end( this ); Next_Song( this ) )
		{
			Play_Current_Song( this );
		}
		this->cursor = tmp;
	}
}

/**
* @brief Crea una Playlist de tiempo limitado, tomando canciones de otra Playlist.
*
* @param this Una Playlist.
* @param max_duration Lo máximo que puede durar la Playlist.
* 
* @return Una referencia a la nueva Playlist.
*/
Playlist* Playlist_limited( Playlist* this, int max_duration )//Tiempo máximo en segundos
{
	assert( this );
	
	Playlist* limited = New_Playlist();
	assert( limited );
	int curr_time = 0;
	
	Node* tmp = this->cursor;
	First_Song( this );
	while ( curr_time < max_duration && !Playlist_end( this ) )
	{
		if ( (curr_time + Get_duration( this )) <= max_duration )
		{
			Insert_Song_back( limited, Get_duration( this ), Get_name( this ), Get_artist( this ) );
			curr_time += Get_duration( this );
			Next_Song( this );
		}
		else
		{
			break;   
		}
	}
	this->cursor = tmp;
	return limited;
}

/**
* @brief Crea una Playlist con canciones de otra, pero ordenándolos de forma aleatoria.
*
* @param this Una Playlist.
* 
* @return Una referencia a la nueva Playlist.
*/
Playlist* Playlist_random( Playlist* this )
{
	assert( this );
	
	Playlist* random = New_Playlist();
	assert( random );
	Playlist* tmp = New_Playlist();
	assert( tmp );
	
	Copy_Playlist( this, tmp );
	
	size_t i = 0;
	while( i < Playlist_Num_Songs( this ) && !Playlist_end( this ) )
	{
		First_Song( tmp );
		srand( time(NULL) );
		int randm = rand() % ( Playlist_Num_Songs( tmp ) );
		
		for( size_t j = 0; j < randm; ++j )
		{
			Next_Song( tmp );
		}
		Insert_Song_back( random, Get_duration( tmp ), Get_name( tmp ), Get_artist( tmp ) );
		Erase_Song( tmp );
		++i;
	}
	
	Delete_Playlist( &tmp );
	return random;
}

/**
* @brief Ordena una Playlist de mayor a menor duración.
*
* @param this Una Playlist.
* @param elems Tamaño de la Playlist.
* 
*/
void Playlist_ordered_duration( Playlist* this, size_t elems ) 
{
	if ( elems == 0 || elems == 1 ) 
	{
		return;
	}
	
	this->cursor = this->last;
	int i = 0;
	while ( i < elems ) 
	{
		this->cursor = this->last; // Mover esta línea aquí para corregir el error
		int j = elems - 1;
		while ( j > i ) 
		{
			if ( this->cursor->prev->song->duration < this->cursor->song->duration ) //Si se cumple ordenamos
			{
				//primero tiempo
				int duration_tmp = this->cursor->song->duration;
				this->cursor->song->duration = this->cursor->prev->song->duration;
				this->cursor->prev->song->duration = duration_tmp;
				//Despues los nombres de artistas
				char name_tmp[ CHAR_TAM ];
				strcpy( name_tmp,this->cursor->song->artist );
				strcpy( this->cursor->song->artist, this->cursor->prev->song->artist );
				strcpy( this->cursor->prev->song->artist, name_tmp );
				//Despues los nombres de las canciones
				char artist_tmp[ CHAR_TAM ];
				strcpy( artist_tmp, this->cursor->song->name );
				strcpy( this->cursor->song->name, this->cursor->prev->song->name );
				strcpy( this->cursor->prev->song->name, artist_tmp );
			}
			this->cursor = this->cursor->prev;
			j--;
		}
		i++;
	}
}

/**
* @brief Ordena una Playlist por nombre.
*
* @param this Una Playlist.
* @param elems Tamaño de la Playlist.
* 
*/
void Playlist_ordered_name( Playlist* this, size_t elems ) 
{
	if (elems == 0 || elems == 1) 
	{
		return;
	}
	this->cursor = this->last;
	int i = 0;
	while (i < elems) 
	{
		this->cursor = this->last; // Mover esta línea aquí para corregir el error
		int j = elems - 1;
		while (j > i) 
		{
			if (strcmp(this->cursor->prev->song->name, this->cursor->song->name) > 0) //Si se cumple ordenamos
			{
				//primero tiempo
				int tmp = this->cursor->song->duration;
				this->cursor->song->duration = this->cursor->prev->song->duration;
				this->cursor->prev->song->duration = tmp;
				//Despues los nombres de artistas
				char tmp2[CHAR_TAM];
				strcpy(tmp2,this->cursor->song->artist);
				strcpy(this->cursor->song->artist,this->cursor->prev->song->artist);
				strcpy(this->cursor->prev->song->artist,tmp2);
				//Despues los nombres de las canciones
				char tmp3[CHAR_TAM];
				strcpy(tmp3,this->cursor->song->name);
				strcpy(this->cursor->song->name,this->cursor->prev->song->name);
				strcpy(this->cursor->prev->song->name,tmp3);
			}
			this->cursor = this->cursor->prev;
			j--;
		}
		i++;
	}
}

/**
* @brief Ordena una Playlist por nombre del artista.
*
* @param this Una Playlist.
* @param elems Tamaño de la Playlist.
* 
*/
void Playlist_ordered_artist( Playlist* this, size_t elems ) 
{
	if (elems == 0 || elems == 1) 
	{
		return;
	}
	this->cursor = this->last;
	int i = 0;
	while (i < elems) 
	{
		this->cursor = this->last; // Mover esta línea aquí para corregir el error
		int j = elems - 1;
		while (j > i) 
		{
			if (strcmp(this->cursor->prev->song->artist, this->cursor->song->artist) > 0) //Si se cumple ordenamos
			{
				//primero tiempo
				int tmp = this->cursor->song->duration;
				this->cursor->song->duration = this->cursor->prev->song->duration;
				this->cursor->prev->song->duration = tmp;
				//Despues los nombres de artistas
				char tmp2[CHAR_TAM];
				strcpy(tmp2,this->cursor->song->artist);
				strcpy(this->cursor->song->artist,this->cursor->prev->song->artist);
				strcpy(this->cursor->prev->song->artist,tmp2);
				//Despues los nombres de las canciones
				char tmp3[CHAR_TAM];
				strcpy(tmp3,this->cursor->song->name);
				strcpy(this->cursor->song->name,this->cursor->prev->song->name);
				strcpy(this->cursor->prev->song->name,tmp3);
			}
			this->cursor = this->cursor->prev;
			j--;
		}
		i++;
	}
}

/**
* @brief Copia las canciones de una Playlist a otra.
*
* @param this Playlist original.
* @param other Playlist copia.
* 
*/
void Copy_Playlist( Playlist* this, Playlist* other )
{
	Node* temp = this->cursor;
	for( First_Song( this ); !Playlist_end( this ); Next_Song( this ) )
	{
		Insert_Song_back( other, Get_duration( this ), Get_name( this ), Get_artist( this ) );
	}
	this->cursor = temp;
}
