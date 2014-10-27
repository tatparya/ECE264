#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>
#include "answer07.h"

#define FALSE 0
#define TRUE 1
#define perr(s) fprintf( stderr, "%s\n", s );

int img_isValid ( ImageHeader * header );

Image * Image_load ( const char * filename )
{
	// OPENING THE FILE
	FILE * fp = NULL;
	size_t read;
	ImageHeader header;
	Image * tmp_im = NULL;
	size_t n_bytes = 0;
	int err = FALSE;
	int offset = 0;

	if (!err)
	{
		fp = fopen ( filename, "rb" );
	}
	if ( !fp )
	{
		perr("Failed to open file");
		err = TRUE;
		return NULL;
	}
	
	//	READING THE HEADER
	if ( !err )
	{
		read = fread ( &header, sizeof ( ImageHeader ), 1, fp );
		offset = sizeof(header);
	}
	if ( read != 1 )
	{
		fprintf ( stderr, "Failed to read header from '%s'\n", filename );
		err = TRUE;
	}
	
	//	CHECK HEADER FOR CORRUPTION
	if ( !img_isValid( &header ) )
	{
		err = TRUE;
	}
	
	//	READING THE COMMENT
	if ( !err )
	{
	//	buffer for comment in image = Image->comment
		tmp_im = malloc ( sizeof ( Image ) );		
		if ( tmp_im == NULL )
		{
			perr( "Failed to allocate memory to tmp_im" );
			err = TRUE;
		}
		char * tmpCommentString;
		tmpCommentString = malloc ( sizeof ( char ) * header.comment_len );
		if ( tmpCommentString == NULL )
		{
			perr("Failed to allocate memory to tmpCommentString" );
			err = TRUE;
		}		
		if ( fseek( fp, offset, SEEK_SET ) == 0 )
		{
			fread ( tmpCommentString, sizeof ( char ), header.comment_len, fp ); 
			offset += ( sizeof( char ) * header.comment_len );
		}
		else 
		{
			perr ( "Failed to seek in file" );
			err = TRUE;
		}
		if ( tmpCommentString[ header.comment_len -1 ] != '\0' )
		{
			err = TRUE;
		}
		else 
		{	
			tmp_im->comment = strdup ( tmpCommentString );
			free ( tmpCommentString );
		}
	}
	
	// ALLOCATING IMAGE STRUCTURE
	if ( !err )
	{
		tmp_im->width = header.width;
		tmp_im->height = header.height;
		
	
		//	HANDLING IMAGE DATA
		n_bytes = sizeof ( int ) * header.width * header.height;
		tmp_im->data = malloc ( n_bytes );
		if ( tmp_im->data == NULL )
		{
			perr ( "Failed to allocate bytes for image data" );
			err = TRUE;
		}
	}
	
	//	SEEK START OF PIXEL DATA
	if ( !err )
	{
		if ( fseek( fp, offset, SEEK_SET ) != 0 )
		{
			perr( "Failed to seek while reading data" );
			err = TRUE;
		}
		else		//	READING PIXEL DATA
		{
			fread ( tmp_im->data, sizeof( int ), tmp_im->width * tmp_im->height, fp );
			offset += ( sizeof ( int ) * header.width * header.height );
		}
		
		if ( fgetc( fp ) != EOF )
		{
			perr ( "End of file not reached" );
			err = TRUE;
		}
	}	
	if ( err ) 
	{
		return NULL;
	}
	else
	{
		return tmp_im;
	}
}

int img_isValid ( ImageHeader * header )
{
	//	Magic Number
	if ( header->magic_number != ECE264_IMAGE_MAGIC_NUMBER )
	{
		fprintf ( stderr, "Magic number does not match" );
		return FALSE;
	}
	//	Width and Height not 0
	if ( header->width * header->height <= 0 )
	{
		fprintf ( stderr, "Width or Height of the image is 0" );
		return FALSE;
	}	
	//	Comment length not 0	
	if ( header->comment_len <= 0 )
	{
		fprintf ( stderr, "Comment length is 0" );
		return FALSE;
	}
	return TRUE;
}

int Image_save ( const char * filename, Image * image )
{
	int err = FALSE; 
    FILE * fp = NULL;
    int * buffer = NULL;    
    size_t written = 0;

    // Attempt to open file for writing
    fp = fopen(filename, "wb");
    if(fp == NULL) 
    {
		fprintf(stderr, "Failed to open '%s' for writing\n", filename);
		return FALSE;
    }

    // Number of bytes stored on each row
    size_t n_bytes = sizeof(int) * image->width * image->height;

    // Prepare the header
    ImageHeader header;
    header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    header.width = image->width;
    header.height = image->height;
    header.comment_len = strlen(image->comment) + 1;

    if(!err) 
    {  
    	// Write the header
		written = fwrite(&header, sizeof(ImageHeader), 1, fp);
		if(written != 1) 
		{
		    fprintf(stderr, "Error: only wrote %zd of %zd of file header to '%s'\n", written, sizeof(ImageHeader), filename);
		    err = TRUE;	
		}
    }

    if(!err) 
    { 
    	// Before writing, we'll need a write buffer
		buffer = malloc(n_bytes);
		if(buffer == NULL) 
		{
	    	fprintf(stderr, "Error: failed to allocate write buffer\n");
	    	err = TRUE;
		} 
		else 
		{
	    	// not strictly necessary, we output file will be tidier.
	    	memset(buffer, 0, n_bytes); 
		}
    }

	//	WRITE COMMENT
    if(!err) 
    {
     	written = fwrite ( image->comment, sizeof( char ), header.comment_len, fp );
     	if ( written != sizeof (char) * strlen( image->comment ) )
     	{
     		perr("Writing comment unsuccessful");
     		err = TRUE;
     	}
  	}
  	
  	//	WRITE DATA
  	if ( !err )
  	{
  		written = fwrite ( image->data, sizeof( int ), n_bytes, fp );
     	if ( written != sizeof ( n_bytes ) )
     	{
     		perr("Writing data unsuccessful");
     		err = TRUE;
     	}
  	}
    if(fp)
	fclose(fp);

    return !err;
}

void Image_free ( Image * image )
{
	if ( image != NULL )
	{
		free ( image->comment );
		free ( image->data );
		free ( image );
	}
}

void linearNormalization ( int width, int height, uint8_t * intensity )
{
	int dataSize = width * height;
	int i;
	int max;
	int min;
	max = 0;
	min = intensity[0];
	for ( i = 0; i < dataSize; i++ )
	{
		if ( min > intensity[i] )
		{
			min = intensity[i];
		}
		else if ( max < intensity[i] )
		{
			max = intensity[i];
		}
	}

	for ( i = 0; i < dataSize; i++ )
	{
		intensity[i] = ( intensity[i] - min ) * 255.0 / ( max - min ); 	
	}			
}
