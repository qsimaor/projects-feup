import {CGFobject} from '../lib/CGF.js';
/**
 * MyUnitCube
 * @constructor
 * @param scene - Reference to MyScene object
 */
export class MyUnitCube extends CGFobject {
	constructor(scene) {
		super(scene);
		this.initBuffers();
	}
	
	initBuffers() {
		this.vertices = [
			0.5, 0.5, 0.5,		//0
			-0.5, -0.5, -0.5,	//1
			0.5, 0.5, -0.5,		//2
			0.5, -0.5, -0.5,	//3
            0.5, -0.5, 0.5,		//4
            -0.5, 0.5, -0.5,	//5
            -0.5, 0.5, 0.5,		//6
            -0.5, -0.5, 0.5,	//7

			0.5, 0.5, 0.5,		//0
			-0.5, -0.5, -0.5,	//1
			0.5, 0.5, -0.5,		//2
			0.5, -0.5, -0.5,	//3
            0.5, -0.5, 0.5,		//4
            -0.5, 0.5, -0.5,	//5
            -0.5, 0.5, 0.5,		//6
            -0.5, -0.5, 0.5,	//7

			0.5, 0.5, 0.5,		//0
			-0.5, -0.5, -0.5,	//1
			0.5, 0.5, -0.5,		//2
			0.5, -0.5, -0.5,	//3
            0.5, -0.5, 0.5,		//4
            -0.5, 0.5, -0.5,	//5
            -0.5, 0.5, 0.5,		//6
            -0.5, -0.5, 0.5,	//7
		];

		//Counter-clockwise reference of vertices
		this.indices = [
            0,6,4,		// Front
            7,4,6,		// Front

            0,3,2,		// Right
            4,3,0,		// Right

            0,5,6,		// Top
            0,2,5,		// Top

            7,3,4,		// Bottom
            7,1,3,		// Bottom

            5,2,3,		// Back
            5,3,1,		// Back
			
            6,5,7,		// Left
            7,5,1,      // Left
		];

		this.normals = [
			0, 0, 1,	// 0 - Front
			0, -1, 0,	// 1 - Bottom
			1, 0, 0,	// 2 - Right
			1, 0, 0,	// 3 - Right
			0, 0, 1,	// 4 - Front
			0, 1, 0,	// 5 - Top
			0, 0, 1,	// 6 - Front
			0, 0, 1,	// 7 - Front

			1, 0, 0, 	// 0 - Right
			0, 0, -1, 	// 1 - Back
			0, 1, 0,	// 2 - Top
			0, -1, 0,	// 3 - Bottom
			1, 0, 0,	// 4 - Right
			0, 0, -1,	// 5 - Back
			0, 1, 0, 	// 6 - Top
			0, -1, 0,	// 7 - Bottom

			0, 1, 0,	// 0 - Top
			-1, 0, 0,	// 1 - Left
			0, 0, -1,	// 2 - Back
			0, 0, -1,	// 3 - Back
			0, -1, 0,	// 4 - Bottom
			-1, 0, 0,	// 5 - Left
			-1, 0, 0,	// 6 - Left
			-1, 0, 0	// 7 - Left
		];
		
		//The defined indices (and corresponding vertices)
		//will be read in groups of three to draw triangles
		this.primitiveType = this.scene.gl.TRIANGLES;

		this.initGLBuffers();
	}
}