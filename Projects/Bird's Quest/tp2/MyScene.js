import { CGFscene, CGFcamera, CGFaxis } from "../lib/CGF.js";
import { MyDiamond } from "./MyDiamond.js";
import { MyParallelogram } from "./MyParallelogram.js";
import { MyTriangle } from "./MyTriangle.js";
import { MyTriangleBig } from "./MyTriangleBig.js";
import { MyTriangleSmall } from "./MyTriangleSmall.js";
import { MyUnitCube } from "./MyUnitCube.js";
import { MyTangram } from "./MyTangram.js";
import { MyQuad } from "./MyQuad.js";
import { MyUnitCubeQuad } from "./MyUnitCubeQuad.js";

/**
 * MyScene
 * @constructor
 */
export class MyScene extends CGFscene {
  constructor() {
    super();
  }

  init(application) {
    super.init(application);
    
    this.initCameras();
    this.initLights();

    //Background color
    this.gl.clearColor(0.0, 0.0, 0.0, 1.0);

    this.gl.clearDepth(100.0);
    this.gl.enable(this.gl.DEPTH_TEST);
    this.gl.enable(this.gl.CULL_FACE);
    this.gl.depthFunc(this.gl.LEQUAL);

    //Initialize scene objects
    this.axis = new CGFaxis(this);
    this.diamond = new MyDiamond(this);
    this.triangle = new MyTriangle(this);
    this.parallelogram = new MyParallelogram(this);
    this.trianglesmall = new MyTriangleSmall(this);
    this.trianglebig = new MyTriangleBig(this);
    this.unitcube = new MyUnitCube(this);
    this.tangram = new MyTangram(this);
    this.quad = new MyQuad(this);
    this.unitcubequad = new MyUnitCubeQuad(this);

    //Objects connected to MyInterface
    this.displayAxis = true;
    this.scaleFactor = 1;
  }
  initLights() {
    this.lights[0].setPosition(15, 2, 5, 1);
    this.lights[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
    this.lights[0].enable();
    this.lights[0].update();
  }
  initCameras() {
    this.camera = new CGFcamera(
      0.4,
      0.1,
      500,
      vec3.fromValues(15, 15, 15),
      vec3.fromValues(0, 0, 0)
    );
  }
  setDefaultAppearance() {
    this.setAmbient(0.2, 0.4, 0.8, 1.0);
    this.setDiffuse(0.2, 0.4, 0.8, 1.0);
    this.setSpecular(0.2, 0.4, 0.8, 1.0);
    this.setShininess(10.0);
  }
  display() {
    // ---- BEGIN Background, camera and axis setup
    // Clear image and depth buffer everytime we update the scene
    this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
    this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
    // Initialize Model-View matrix as identity (no transformation
    this.updateProjectionMatrix();
    this.loadIdentity();
    // Apply transformations corresponding to the camera position relative to the origin
    this.applyViewMatrix();

    // Draw axis
    if (this.displayAxis) this.axis.display();

    this.setDefaultAppearance();

    var sca = [
      this.scaleFactor,
      0.0,
      0.0,
      0.0,
      0.0,
      this.scaleFactor,
      0.0,
      0.0,
      0.0,
      0.0,
      this.scaleFactor,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
    ];

    this.multMatrix(sca);

/*
    var matrixTranslate1 =[
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      -3.3,1.9,0,1
    ];
    
  //CABEÇA TRANSLAÇÃO(VERDE)
  this.pushMatrix();

  this.multMatrix(matrixTranslate1);
  this.diamond.display();

  this.popMatrix();
   
  //ORELHA1 TRANSLAÇÃO e ROTAÇÃO(ROXO)
    this.pushMatrix();

    this.translate(-2.3,2.9,0)
    this.rotate(Math.PI/2,0,0,1);
    this.trianglesmall.display();

    this.popMatrix();

  //ORELHA2 TRANSLAÇÃO e ROTAÇÃO(VERMELHO)
    this.pushMatrix();

    this.translate(-4.3,2.9,0)
    this.rotate(-Math.PI/2,0,0,1);
    this.trianglesmall.display();

    this.popMatrix();

  //PESCOÇO TRANSLAÇÃO (LARANJA)
    this.pushMatrix();

    this.translate(-2.6,-0.4,0);
    this.trianglebig.display();

    this.popMatrix();

  //CORPO1 (ROSA)
    this.pushMatrix();

    this.translate(0,0.4,0);
    this.rotate(Math.PI/4,0,0,1);
    this.triangle.display();

    this.popMatrix();

  //CORPO2 (AZUL)
    this.pushMatrix();

    this.translate(1.4,-1.6,0);
    this.trianglebig.display();

    this.popMatrix();

  //RABO (AMARELO)
    this.pushMatrix();

    this.scale(1,-1,1);
    this.translate(2.8,1,0);
    this.parallelogram.display();

    this.popMatrix();
*/

    // ---- BEGIN Primitive drawing section

    //this.diamond.display();
    //this.triangle.display();
    //this.parallelogram.display();
    //this.trianglebig.display();

    /*
    //EXERCICIO 3
    this.pushMatrix();

    this.translate(-0.5,-0.5,-0.5);
    this.rotate(Math.PI/2,0,1,0);
    this.unitcube.display();

    this.popMatrix();
    this.pushMatrix();

    this.rotate(Math.PI/2,0,1,0);
    this.tangram.display();

    this.popMatrix();
    */

    //this.quad.display();
    this.unitcubequad.display();

    // ---- END Primitive drawing section
  }
}
