import {CGFobject} from '../../lib/CGF.js';
/**
 * MyTriangleSmall
 * @constructor
 * @param scene - Reference to MyScene object
 */
export class MyTriangleSmall extends CGFobject {
    constructor(scene, color) {
        super(scene);
        this.initBuffers(color);
    }
    initBuffers(color) {
        this.vertices = [
          -1, 0, 0,
          0, 1, 0,
          1, 0, 0
          -1, 0, 0,
          0, 1, 0,
          1, 0, 0
        ];
      
        this.indices = [
          0, 1, 2,
          2, 1, 0
        ];
      
        this.normals = [
          0, 0, 1,
          0, 0, 1,
          0, 0, 1,
          0, 0, -1,
          0, 0, -1,
          0, 0, -1,
        ];
      
        this.texCoords = [
          0, 0,
          0, 1,
          1, 1
        ];
      
        this.primitiveType = this.scene.gl.TRIANGLES;
      
        this.initGLBuffers();
      }
      
   }