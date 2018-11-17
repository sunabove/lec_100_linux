#include "Shape.h"

namespace esri {
    size_t ShapeCom::readData( FILE * file, void * buff, const int size, bool isSwap ) {
        return readData( file, buff, size, isSwap );
    }

    size_t readInteger( FILE * file, void * buff, bool isSwap ) {
        return readData( file, buff, 4, isSwap );
    }

    size_t readDouble ( FILE * file, void * buff, bool isSwap ) {
        return readData( file, buff, 8 , isSwap );
    }

    size_t readData( FILE * file, void * buff, const int size, bool isSwap ) {
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
}