#include "Cube.h"

namespace openGLDriver {

	Cube::Cube() {
		init();
	}

	Cube::~Cube() {
	}

	void Cube::init() {

		std::vector<Vertex> vertexList(8);
		vertexList[0] = Vertex(-1.0, 1.0, 1.0, 1.0);
		vertexList[1] = Vertex(-1.0, -1.0, 1.0, 1.0);
		vertexList[2] = Vertex(1.0, -1.0, 1.0, 1.0);
		vertexList[3] = Vertex(1.0, 1.0, 1.0, 1.0);
		vertexList[4] = Vertex(-1.0, 1.0, -1.0, 1.0);
		vertexList[5] = Vertex(-1.0, -1.0, -1.0, 1.0);
		vertexList[6] = Vertex(1.0, -1.0, -1.0, 1.0);
		vertexList[7] = Vertex(1.0, 1.0, -1.0, 1.0);
		
		setVertexList(vertexList);

		std::vector<GLuint> indexList(24);
		indexList[0] = 0;   indexList[1] = 1;   indexList[2] = 2; 	indexList[3] = 3;
		indexList[4] = 3;   indexList[5] = 2;   indexList[6] = 6; 	indexList[7] = 7;   
		indexList[8] = 7;  indexList[9] = 6;  indexList[10] = 5; 	indexList[11] = 4;  
		indexList[12] = 4;  indexList[13] = 5;  indexList[14] = 1; 	indexList[15] = 0;  
		indexList[16] = 0;  indexList[17] = 3;  indexList[18] = 7; 	indexList[19] = 4; 
		indexList[20] = 1;  indexList[21] = 2;  indexList[22] = 6; 	indexList[23] = 5;  

		setIndexList(indexList);
	}

}
