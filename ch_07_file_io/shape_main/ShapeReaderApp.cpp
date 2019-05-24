#include <iostream>

#include "Shape.h"

using namespace std ;
using namespace esri ;

static void custom_output_callback(const zf_log_message *msg, void *arg) {
	FILE * out = stdout ;
	fprintf( out, msg->buf, arg ); 
	fprintf( out, "\n" );
	fflush( out );
} 
    
int main( int argc , char ** argv ) {
	errno = 0;
	FILE * console = stdout ;

	if( 2 > argc ) { 
		string cmd = argv[0] ;

		auto index = cmd.find_last_of( "/" ) ;
		if( index >= 0 ) {
			cmd = cmd.substr( index + 1 );
		}

		fprintf( console, "Usage: %s shapeFile.shp\n", cmd.c_str() );

		return 0 ;
	} 
	
	const char * LINE = "____________________________________\n" ; 

    zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
	zf_log_set_output_level(ZF_LOG_DEBUG);

	ZF_LOGI( "%s", LINE );
 	ZF_LOGI( "Hello..." );
	ZF_LOGI( "%s", LINE );
	
	const char * fileName = argv[ 1 ]; 	

	//const char * fileName = "/home/sunabove/shapefiles/usa-major-cities.shp" ;

	FILE * file = NULL ;
		
	if( 0 == errno ) { 
		file = fopen ( fileName, "r" );  

		ZF_LOGI( "File = %s\n" , fileName );		
	}

	if( 0 == errno ) {
		ShapeFile shapeFile ;
		readShapeFile( & shapeFile, file );
	}

	ZF_LOGI( "%s", LINE );
    ZF_LOGI( "Good bye!" );
    ZF_LOGI( "%s", LINE ); 

	return 0 ;
}

//
