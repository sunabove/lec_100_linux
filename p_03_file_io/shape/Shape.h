#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <byteswap.h>

#include <vector>

#include "zf_log.h" 

using namespace std ; 

namespace esri {
    size_t readData( FILE * file, void * buff, const int size, bool isSwap = false ) ; 
    size_t readInteger( FILE * file, void * buff, bool isSwap = false ) ; 
    size_t readDouble ( FILE * file, void * buff, bool isSwap = false ) ; 

    class ShapeCom {
        public: 
        size_t readData( FILE * file, void * buff, const int size, bool isSwap = false ) ; 
    };

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

	class Polyline : public Shape {
        public:
            Polyline() {
                this->numParts = 0 ;
                this->numParts = 0 ;
            }
        Box box;
        int32_t numParts ;
        int32_t numPoints ;
        vector<int32_t> parts ;
        vector<Point> points ;
	};

	class Polygon : public Shape {
		
	};

}