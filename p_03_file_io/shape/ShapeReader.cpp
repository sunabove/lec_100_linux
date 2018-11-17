/* file open */
#include <errno.h>

#include "Shape.h" 

using namespace esri ;

static void custom_output_callback(const zf_log_message *msg, void *arg) {
	FILE * out = stdout ;
	fprintf( out, msg->buf, arg ); 
	fprintf( out, "\n" );
	fflush( out );
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
		return 0 ; 
	}

	MainFileHeader p ;

	const char * fileName = argv[ 1 ]; 		

	FILE * file = NULL ;
		
	if( 0 == errno ) { 
		file = fopen ( fileName, "r");  
	}

	ZF_LOGI( "double size = %zu", sizeof( double ) );

	if( 0 == errno ) {		
		auto nr = 1 ;

		nr = nr and readInteger( file, & p.fileCode, true );
		
		nr = nr and readInteger( file, & p.unused_1 );
		nr = nr and readInteger( file, & p.unused_2 );
		nr = nr and readInteger( file, & p.unused_3 );
		nr = nr and readInteger( file, & p.unused_4 );
		nr = nr and readInteger( file, & p.unused_5 );
		
		nr = nr and readInteger( file, & p.fileLength, true );
		nr = nr and readInteger( file, & p.version );
		nr = nr and readInteger( file, & p.shapeType );

		nr = nr and readDouble( file, & p.box.x.min );
		nr = nr and readDouble( file, & p.box.y.min );
		nr = nr and readDouble( file, & p.box.x.max );
		nr = nr and readDouble( file, & p.box.y.max );
		nr = nr and readDouble( file, & p.box.z.min );
		nr = nr and readDouble( file, & p.box.z.max );
		nr = nr and readDouble( file, & p.box.m.min );
		nr = nr and readDouble( file, & p.box.m.max );

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

		vector<Shape> shapes ; 

		while( nr ) { 
			fprintf( console, "%s\n", LINE );
			Header h ; 
			nr = nr and readInteger( file, & h.recordNo, true );
			nr = nr and readInteger( file, & h.contentLength, true );

			if( 0 == errno and nr ) {
				fprintf( console, "Record Number  = %d\n", h.recordNo );
				fprintf( console, "Content Length = %d\n", h.contentLength );
			}
		
			if( 0 != errno or 1 < nr ) {
				// do nothing.
			} else if( 1 == shapeType ) { // Point
				Point shape ; 
				shape.shapeType = shapeType ;

				nr = nr and readInteger( file, & shape.shapeType );

				nr = nr and readDouble( file, & shape.x );
				nr = nr and readDouble( file, & shape.y );

				fprintf( console, "Shape Type  = %d\n", shape.shapeType);
				fprintf( console, "X = %+011.6f\n", shape.x );
				fprintf( console, "Y = %+011.6f\n", shape.y );

				shapes.push_back( shape );
			} else if( 3 == shapeType ) { // Polyline
				Polyline shape ; 
				shape.shapeType = shapeType ;

				nr = nr and readInteger( file, & shape.shapeType );

				nr = nr and readDouble( file, & shape.box.x.min );
				nr = nr and readDouble( file, & shape.box.y.min );
				nr = nr and readDouble( file, & shape.box.x.max );
				nr = nr and readDouble( file, & shape.box.y.max );

				nr = nr and readInteger( file, & shape.numParts );
				nr = nr and readInteger( file, & shape.numPoints );

				int32_t part ;
				for( int i = 0, iLen = shape.numParts ; nr && i < iLen ; i ++ ) {
					nr = nr and readInteger( file, & part );
					if( nr ) {
						shape.parts.push_back( part ); 
					}
				}

				Point point ;
				for( int i = 0, iLen = shape.numPoints ; nr && i < iLen ; i ++ ) {
					nr = nr and readDouble( file, & point.x );
					nr = nr and readDouble( file, & point.y );
					if( nr ) {
						shape.points.push_back( point ); 
					}
				}

				fprintf( console, "Shape Type  = %d\n", shape.shapeType);
				fprintf( console, "numParts    = %d\n", shape.numParts );
				fprintf( console, "numPoints   = %d\n", shape.numParts );

				shapes.push_back( shape );
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
