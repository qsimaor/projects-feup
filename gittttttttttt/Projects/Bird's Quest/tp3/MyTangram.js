import {CGFappearance, CGFobject} from '../lib/CGF.js';
import { MyDiamond } from "./MyDiamond.js";
import { MyParallelogram } from "./MyParallelogram.js";
import { MyTriangle } from "./MyTriangle.js";
import { MyTriangleBig } from "./MyTriangleBig.js";
import { MyTriangleSmall } from "./MyTriangleSmall.js";
import { MyScene } from "./MyScene.js"
/**
 * MyTangram
 * @constructor
 * @param scene - Reference to MyScene object
 */

export class MyTangram extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initObjects();
        this.initMaterials();
    }

    initObjects() {
        this.diamond = new MyDiamond(this.scene);
        this.blueTriangle = new MyTriangleBig(this.scene);
        this.orangeTriangle = new MyTriangleBig(this.scene);
        this.parallelogram = new MyParallelogram(this.scene);
        this.pinkTriangle = new MyTriangle(this.scene);
        this.purpleTriangle = new MyTriangleSmall(this.scene);
        this.redTriangle = new MyTriangleSmall(this.scene);

        this.objects = [
            this.diamond, 
            this.blueTriangle, 
            this.orangeTriangle, 
            this.parallelogram, 
            this.pinkTriangle, 
            this.purpleTriangle, 
            this.redTriangle
        ];
    }

    initMaterials() {
        // Pink material (no ambient, high specular)
        this.pinkMaterial = new CGFappearance(this.scene);
        this.pinkMaterial.setAmbient(0, 0, 0, 1.0);
        this.pinkMaterial.setDiffuse(1.0, 0.61, 0.81, 1.0);
        this.pinkMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.pinkMaterial.setShininess(10);

        // Purple material (no ambient, high specular)
        this.purpleMaterial = new CGFappearance(this.scene);
        this.purpleMaterial.setAmbient(0, 0, 0, 1.0);
        this.purpleMaterial.setDiffuse(0.59, 0.31, 0.59, 1.0);
        this.purpleMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.purpleMaterial.setShininess(10);

        // Red material (no ambient, high specular)
        this.redMaterial = new CGFappearance(this.scene);
        this.redMaterial.setAmbient(0, 0, 0, 1.0);
        this.redMaterial.setDiffuse(1.0, 0.11, 0.11, 1.0);
        this.redMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.redMaterial.setShininess(10);

        // Green material (no ambient, high specular)
        this.greenMaterial = new CGFappearance(this.scene);
        this.greenMaterial.setAmbient(0,0,0,1.0);
        this.greenMaterial.setDiffuse(0.0, 1.0, 0.0, 1.0);
        this.greenMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.greenMaterial.setShininess(10);

        // Blue material (no ambient, high specular)
        this.blueMaterial = new CGFappearance(this.scene);
        this.blueMaterial.setAmbient(0,0,0,1.0);
        this.blueMaterial.setDiffuse(0.12, 0.56, 1.0, 1.0);
        this.blueMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.blueMaterial.setShininess(10);

        // Orange material (no ambient, high specular)
        this.orangeMaterial = new CGFappearance(this.scene);
        this.orangeMaterial.setAmbient(0,0,0,1.0);
        this.orangeMaterial.setDiffuse(1.0, 0.65, 0.0, 1.0);
        this.orangeMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.orangeMaterial.setShininess(10);

        // Yellow material (no ambient, high specular)
        this.yellowMaterial = new CGFappearance(this.scene);
        this.yellowMaterial.setAmbient(0,0,0,1.0);
        this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
        this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.yellowMaterial.setShininess(10);

        //Wood Material
        this.woodMaterial = new CGFappearance(this.scene);
        this.woodMaterial.setAmbient(0.92, 0.64, 0.51, 1.0);
        this.woodMaterial.setDiffuse(1.0, 0.64, 0.51, 1.0);
        this.woodMaterial.setSpecular(0.0, 0.0, 0.0, 1.0);
        this.woodMaterial.setShininess(10.0);
    } 

    updateBuffers() {
        for(var object of this.objects) {
            object.updateBuffers();
        }
    }

    enableNormalViz() {
        for(var object of this.objects) {
            object.enableNormalViz();
        }
    }

    display() {
        //CABEÇA TRANSLAÇÃO(VERDE)
        //this.greenMaterial.apply();
        this.scene.pushMatrix();

          var matrixTranslate =[
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            -3.3,1.9,0,1
        ];
      
        this.scene.multMatrix(matrixTranslate);
    
        this.diamond.display();
      
        this.scene.popMatrix();

        //ORELHA1 TRANSLAÇÃO e ROTAÇÃO(ROXO)
        this.purpleMaterial.apply();
        this.scene.pushMatrix();
      
        this.scene.translate(-2.3,2.9,0)
        this.scene.rotate(Math.PI/2,0,0,1);
      
        this.purpleTriangle.display();
      
        this.scene.popMatrix();

        //ORELHA2 TRANSLAÇÃO e ROTAÇÃO(VERMELHO)
        this.redMaterial.apply();
        this.scene.pushMatrix();

        this.scene.translate(-4.3,2.9,0)
        this.scene.rotate(-Math.PI/2,0,0,1); 

        this.redTriangle.display();

        this.scene.popMatrix();

        //PESCOÇO TRANSLAÇÃO (LARANJA)
        this.orangeMaterial.apply();
        this.scene.pushMatrix();
       
        this.scene.translate(-2.6,-0.4,0);
       
        this.orangeTriangle.display();
       
        this.scene.popMatrix();

        //CORPO1 (ROSA)
        this.pinkMaterial.apply();
        this.scene.pushMatrix();
      
        this.scene.translate(0,0.4,0);
        this.scene.rotate(Math.PI/4,0,0,1);
      
        this.pinkTriangle.display();
      
        this.scene.popMatrix();
      
        //CORPO2 (AZUL)
        this.blueMaterial.apply();
        this.scene.pushMatrix();
      
        this.scene.translate(1.4,-1.6,0);
      
        this.blueTriangle.display();
      
        this.scene.popMatrix();
      
        //RABO (AMARELO)
        this.yellowMaterial.apply();
        this.scene.pushMatrix();
      
        this.scene.scale(1,-1,1);
        this.scene.translate(2.8,1,0);
      
        this.parallelogram.display();
      
        this.scene.popMatrix();
    
    }
}
