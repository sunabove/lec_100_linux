#include "Shape.h"

namespace esri {

    Polyline::Polyline() {
        this->numParts = 0 ;
        this->numParts = 0 ;

        this->parts = nullptr ;
        this->points = nullptr ;
    }

    Polyline::~Polyline() {
        if( nullptr != this->parts ) {
            delete [] this->parts ;
        }

        if( nullptr != this->points ) {
            delete [] this->points ;
        }
    }

    size_t readInteger( FILE * file, void * buff, bool isSwap ) {
        return readData( file, buff, 4, isSwap );
    }

    size_t readDouble ( FILE * file, void * buff, bool isSwap ) {
        return readData( file, buff, 8, isSwap );
    }

    size_t readData( FILE * file, void * buff, size_t size, bool isSwap ) {
        size_t rn = fread(buff, size, 1 , file );

        if( isSwap ) {
            if( 4 == size ) {
                uint32_t * i = static_cast<uint32_t *>( buff ) ;
                * i = bswap_32( * i );
            } else if( 8 == size ) {
                double * d = static_cast<double *>( buff ) ;
                * d = bswap_64( * d );
            }
        }

        return rn ;
    }

    // readShapeFile
    string readShapeFile( ShapeFile * shapeFile, FILE * file ) {
        const char * LINE = "________________________________" ;

        size_t nr = 1 ;

        errno = 0 ;

        MainFileHeader * p = & shapeFile->mainFileHeader ;

        nr = nr and readInteger( file, & p->fileCode, true );
        
        nr = nr and readInteger( file, & p->unused_1 );
        nr = nr and readInteger( file, & p->unused_2 );
        nr = nr and readInteger( file, & p->unused_3 );
        nr = nr and readInteger( file, & p->unused_4 );
        nr = nr and readInteger( file, & p->unused_5 );
        
        nr = nr and readInteger( file, & p->fileLength, true );
        nr = nr and readInteger( file, & p->version );
        nr = nr and readInteger( file, & p->shapeType );

        nr = nr and readDouble( file, & p->box.x.min );
        nr = nr and readDouble( file, & p->box.y.min );
        nr = nr and readDouble( file, & p->box.x.max );
        nr = nr and readDouble( file, & p->box.y.max );
        nr = nr and readDouble( file, & p->box.z.min );
        nr = nr and readDouble( file, & p->box.z.max );
        nr = nr and readDouble( file, & p->box.m.min );
        nr = nr and readDouble( file, & p->box.m.max );
        
        if( 0 == errno and nr ) {
            p->fileLength = 2 * p->fileLength ;

            ZF_LOGI( "%s", LINE );
            ZF_LOGI( "MainFileHeader" );
            ZF_LOGI( "File Code        = %u" , p->fileCode );
            ZF_LOGI( "file Length      = %u" , p->fileLength );
            ZF_LOGI( "Version          = %u" , p->version );
            ZF_LOGI( "Shape Type       = %u" , p->shapeType );
            ZF_LOGI( "Bouding Box Xmin = %+011.6f" , p->box.x.min ); 
            ZF_LOGI( "Bouding Box Ymin = %+011.6f" , p->box.y.min ); 
            ZF_LOGI( "Bouding Box Xmax = %+011.6f" , p->box.x.max ); 
            ZF_LOGI( "Bouding Box Ymax = %+011.6f" , p->box.y.max ); 
            ZF_LOGI( "Bouding Box Zmin = %+011.6f" , p->box.z.min ); 
            ZF_LOGI( "Bouding Box Zmax = %+011.6f" , p->box.z.max ); 
            ZF_LOGI( "Bouding Box Mmin = %+011.6f" , p->box.m.min ); 
            ZF_LOGI( "Bouding Box Mmax = %+011.6f" , p->box.m.max );
            ZF_LOGI( "%s", LINE );
        }

        const auto shapeType = p->shapeType ; 

        auto shapes = & shapeFile->shapes ; 

        // Removes all elements from the vector
        shapes->clear();

        while( 0 == errno and nr ) { 			
            ZF_LOGI( "%s", LINE );

            Header header ; 
            nr = nr and readInteger( file, & header.recordNo, true );
            nr = nr and readInteger( file, & header.contentLength, true );

            if( 0 == errno and nr ) {
                ZF_LOGI( "Record Number  = %d", header.recordNo );
                ZF_LOGI( "Content Length = %d", header.contentLength );
            }

            Shape * shape = nullptr ;
        
            if( 0 != errno or 1 > nr ) {
                // do nothing.
            } else if( 1 == shapeType ) { // Point
                auto point = new Point() ;
                //Point * point = new Point() ;
                shape = point ; 
                shape->shapeType = shapeType ;

                nr = nr and readInteger( file, & shape->shapeType );

                nr = nr and readDouble( file, & point->x );
                nr = nr and readDouble( file, & point->y );

                if( 0 == errno and nr ) {
                    ZF_LOGI( "Shape Type  = %d", shape->shapeType);
                    ZF_LOGI( "X = %+011.6f", point->x );
                    ZF_LOGI( "Y = %+011.6f", point->y ); 
                }
            } else if( 3 == shapeType || 5 == shapeType ) { // Polyline, Polygon
                Polyline * poly = nullptr ;
                if ( 3 == shapeType ) { 
                    poly = new Polyline() ; 
                } else if ( 5 == shapeType ) { 
                    poly = new Polygon() ;
                }

                shape = poly; 
                shape->shapeType = shapeType ;

                nr = nr and readInteger( file, & shape->shapeType );

                auto box = & poly->box;

                nr = nr and readDouble( file, & box->x.min );
                nr = nr and readDouble( file, & box->y.min );
                nr = nr and readDouble( file, & box->x.max );
                nr = nr and readDouble( file, & box->y.max );

                nr = nr and readInteger( file, & poly->numParts );
                nr = nr and readInteger( file, & poly->numPoints );

                auto numParts = poly->numParts; 

                int32_t * parts = new int32_t[numParts] ;
                poly->parts = parts ;

                for( uint i = 0, iLen = numParts ; nr && i < iLen ; i ++ ) {
                    nr = nr and readInteger( file, parts ); 
                    parts ++ ;
                }

                auto numPoints = poly->numPoints ; 
                Point * points = new Point[ numPoints ] ; 
                poly->points = points ; 

                for( size_t i = 0, iLen = numPoints ; nr && i < iLen ; i ++ ) {
                    nr = nr and readDouble( file, & points->x );
                    nr = nr and readDouble( file, & points->y );
                    points ++ ; 
                }

                if( 0 == errno and nr ) {
                    ZF_LOGI( "Shape Type  = %d", shape->shapeType);
                    ZF_LOGI( "numParts    = %d", poly->numParts );
                    ZF_LOGI( "numPoints   = %d", poly->numParts ); 
                }
            }

            if( nullptr != shape ) {
                shape->header = header ; 
                shapes->push_back( * shape ); 
            }
        }

        string error ;
        if( 0 != errno ) {
           error = strerror( errno ) ;
           ZF_LOGW( "SYSTEM ERROR: %s", error.c_str() );
        } else {
           ZF_LOGI( "Done reading shape file. shape's count = %zu", shapes->size() );
           ZF_LOGI( "%s", LINE );
        }

        return error ;
    }
    // -- readShapeFile
    
}
