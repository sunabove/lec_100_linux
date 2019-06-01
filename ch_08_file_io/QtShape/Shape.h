#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <byteswap.h>
#include <errno.h>

#include <iostream>
#include <vector>

#include "zf_log.h"

using namespace std ; 

namespace esri {

    class Interval {
		public :
		double min ;
		double max ;
	};

	class Box {
		public :
		Interval x;
		Interval y;
	};

	class BoxZm : public Box {
		public : 
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

		BoxZm box ;
	} ; 

	class Header {
		public :
		int32_t recordNo ;
		int32_t contentLength ; 
	} ;

	class Shape {
		public: 
		Header header;
        int32_t shapeType ;
	} ;

	class Point : public Shape {
		public :
		double x ;
		double y ; 
	};

	class Polyline : public Shape {
        public:
            Polyline() ;
			virtual ~Polyline() ;

        Box box;
        uint32_t numParts ;
        uint32_t numPoints ;
        int32_t * parts ;
        Point * points ;
	};

	class Polygon : public Polyline {
	};

	class ShapeFile {
		public: 
		MainFileHeader mainFileHeader ; 
		vector<Shape> shapes;

        auto size() {
            return shapes.size();
        }
	};

    size_t readData( FILE * file, void * buff, size_t size, bool isSwap = false ) ;
    size_t readInteger( FILE * file, void * buff, bool isSwap = false ) ;
    size_t readDouble ( FILE * file, void * buff, bool isSwap = false ) ;
    string readShapeFile( ShapeFile * shapeFile, FILE * file ) ;

}
