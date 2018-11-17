/* file open */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <byteswap.h>

#include "zf_log.h" 

static void custom_output_callback(const zf_log_message *msg, void *arg) {
	FILE * out = stdout ;
	fprintf( out, msg->buf, arg ); 
	fprintf( out, "\n" );
	fflush( out );
}

size_t readData( FILE * file, void * buff, const int size, bool isSwap = false ) {
	size_t rn = fread(buff, size, 1 , file );

	if( isSwap ) {
		if( 4 == size ) {
			int * i = (int *) buff ; 
			* i = bswap_32( * i );
		}else if( 8 == size ) {
			double * d = (double *) buff ; 
			* d = bswap_64( * d );
		}
	}

	return rn ; 
}

int main( int argc , char ** argv ) {
    zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
	zf_log_set_output_level(ZF_LOG_DEBUG);

	const char * LINE = "___________________________________________________\n" ; 
    ZF_LOGI( "%s", LINE );
 	ZF_LOGI( "argc = %d", argc );
	ZF_LOGI( "%s", LINE );

	errno = 0;
	FILE * console = stdout ;

	if( 2 > argc ) { 
		fprintf( console, "shape file name is requried.\n" );
		//return 0 ; 
	}

	class Interval {
		public :
		double min ;
		double max ;
	};

	class Box {
		public :
		Interval x;
		Interval y;
		Interval z;
		Interval m;
	};

	class MainFileHeader {
		public: 
		int32_t fileCode ;
		
		int32_t unused_1 ;
		int32_t unused_2 ;
		int32_t unused_3 ;
		int32_t unused_4 ;
		int32_t unused_5 ;

		int32_t fileLength ;
		
		int32_t version ;
		int32_t shapeType ;

		Box box ;
	} ; 

	class Header {
		public :
		int32_t recordNo ;
		int32_t contentLength ; 
	} ; 

	class Shape {
		public: 
		int32_t shapeType ;
	} ;

	class Point : public Shape {
		public :
		double x ;
		double y ; 
	};

	MainFileHeader p ;

	const char * fileName = argv[ 1 ]; 		

	FILE * file = NULL ;
		
	if( 0 == errno ) { 
		file = fopen ( fileName, "r"); 
	}

	if( true ) {
		char buff[ 100 ];
		ZF_LOGI( "sizeof( char buff[ 100 ] ) = %zu", sizeof( buff ) );
	}

	if( true ) {
		char * buff = new char[ 100 ];
		ZF_LOGI( "sizeof( char * buff = new char[ 100 ]; ) = %zu", sizeof( buff ) );
	}

	if( true ) {
		ZF_LOGI( "sizeof( double ) = %zu", sizeof( double ) );
	}

	if( 0 == errno ) {		
		auto nr = 1 ;

		nr = nr and readData( file, & p.fileCode, 4, true );
		
		nr = nr and readData( file, & p.unused_1, 4 );
		nr = nr and readData( file, & p.unused_2, 4 );
		nr = nr and readData( file, & p.unused_3, 4 );
		nr = nr and readData( file, & p.unused_4, 4 );
		nr = nr and readData( file, & p.unused_5, 4 );
		
		nr = nr and readData( file, & p.fileLength, 4 , true );
		nr = nr and readData( file, & p.version, 4 );
		nr = nr and readData( file, & p.shapeType, 4 );

		nr = nr and readData( file, & p.box.x.min, 8 );
		nr = nr and readData( file, & p.box.y.min, 8 );
		nr = nr and readData( file, & p.box.x.max, 8 );
		nr = nr and readData( file, & p.box.y.max, 8 );
		nr = nr and readData( file, & p.box.z.min, 8 );
		nr = nr and readData( file, & p.box.z.max, 8 );
		nr = nr and readData( file, & p.box.m.min, 8 );
		nr = nr and readData( file, & p.box.m.max, 8 );

		ZF_LOGI( "nr = %d", nr );
		
		if( 0 == errno and nr ) {
			p.fileLength = 2 * p.fileLength ;

			fprintf( console, "File = %s\n" , fileName );
			fprintf( console, "MainFileHeader\n" );
			fprintf( console, "File Code        = %u\n" , p.fileCode );
			fprintf( console, "file Length      = %u\n" , p.fileLength );
			fprintf( console, "Version          = %u\n" , p.version );
			fprintf( console, "Shape Type       = %u\n" , p.shapeType );
			fprintf( console, "Bouding Box Xmin = %+011.6f\n" , p.box.x.min ); 
			fprintf( console, "Bouding Box Ymin = %+011.6f\n" , p.box.y.min ); 
			fprintf( console, "Bouding Box Xmax = %+011.6f\n" , p.box.x.max ); 
			fprintf( console, "Bouding Box Ymax = %+011.6f\n" , p.box.y.max ); 
			fprintf( console, "Bouding Box Zmin = %+011.6f\n" , p.box.z.min ); 
			fprintf( console, "Bouding Box Zmax = %+011.6f\n" , p.box.z.max ); 
			fprintf( console, "Bouding Box Mmin = %+011.6f\n" , p.box.m.min ); 
			fprintf( console, "Bouding Box Mmax = %+011.6f\n" , p.box.m.max );
			fprintf( console, "\n" );
		}

		const auto shapeType = p.shapeType ;  

		while( false && nr ) { 
			fprintf( console, "%s\n", LINE );
			Header h ; 
			nr = nr and readData( file, & h.recordNo, 4, true );
			nr = nr and readData( file, & h.contentLength, 4, true );

			if( 0 == errno and nr ) {
				fprintf( console, "Record Number  = %d\n", h.recordNo );
				fprintf( console, "Content Length = %d\n", h.contentLength );
			}
		
			if( 1 == shapeType ) {
				Point shape ; 
				nr = nr and readData( file, & shape.shapeType, 4 );
				nr = nr and readData( file, & shape.x, 8 );
				nr = nr and readData( file, & shape.y, 8 );

				fprintf( console, "Shape Type  = %d\n", shape.shapeType);
				fprintf( console, "X = %+011.6f\n", shape.x );
				fprintf( console, "Y = %+011.6f\n", shape.y );
			}
		}
	}

	if( 0 == errno ) {
		if( NULL != file ) {  
			fclose ( file );
		}
	}

	if( 0 != errno ) {
		ZF_LOGW( "SYSTEM ERROR: %s", strerror(errno) );
	}

	ZF_LOGI( "%s", LINE );
    ZF_LOGI( "Good bye!" );
    ZF_LOGI( "%s", LINE );  

	return 0 ;
}
