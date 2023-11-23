import {CGFobject} from '../lib/CGF.js';
import { MyDiamond } from "./MyDiamond.js";
import { MyParallelogram } from "./MyParallelogram.js";
import { MyTriangle } from "./MyTriangle.js";
import { MyTriangleBig } from "./MyTriangleBig.js";
import { MyTriangleSmall } from "./MyTriangleSmall.js";
/**
 * MyTangram
 * @constructor
 * @param scene - Reference to MyScene object
 */

export class MyTangram extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initObjects();
    }

    initObjects() {
        this.diamond = new MyDiamond(this.scene);
        this.trianglebig1 = new MyTriangleBig(this.scene);
        this.trianglebig2 = new MyTriangleBig(this.scene);
        this.parallelogram = new MyParallelogram(this.scene);
        this.triangle = new MyTriangle(this.scene);
        this.trianglesmall1 = new MyTriangleSmall(this.scene);
        this.trianglesmall2= new MyTriangleSmall(this.scene);
    }

    display() {
        this.scene.pushMatrix();

        var matrixTranslate1 =[
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            -3.3,1.9,0,1
        ];
          
        //CABEÇA TRANSLAÇÃO(VERDE)
        this.scene.multMatrix(matrixTranslate1);
        this.diamond.display();
      
        this.scene.popMatrix();
         
        //ORELHA1 TRANSLAÇÃO e ROTAÇÃO(ROXO)
        this.scene.pushMatrix();
      
        this.scene.translate(-2.3,2.9,0)
        this.scene.rotate(Math.PI/2,0,0,1);
        this.trianglesmall1.display();
      
        this.scene.popMatrix();
      
        //ORELHA2 TRANSLAÇÃO e ROTAÇÃO(VERMELHO)
        this.scene.pushMatrix();
      
        this.scene.translate(-4.3,2.9,0)
        this.scene.rotate(-Math.PI/2,0,0,1); 
        this.trianglesmall2.display();

        this.scene.popMatrix();
      
        //PESCOÇO TRANSLAÇÃO (LARANJA)
        this.scene.pushMatrix();

        this.scene.translate(-2.6,-0.4,0);
        this.trianglebig1.display();

        this.scene.popMatrix();
      
        //CORPO1 (ROSA)
        this.scene.pushMatrix();
      
        this.scene.translate(0,0.4,0);
        this.scene.rotate(Math.PI/4,0,0,1);
        this.triangle.display();
      
        this.scene.popMatrix();
      
        //CORPO2 (AZUL)
        this.scene.pushMatrix();
      
        this.scene.translate(1.4,-1.6,0);
        this.trianglebig2.display();

        this.scene.popMatrix();
      
        //RABO (AMARELO)
        this.scene.pushMatrix();

        this.scene.scale(1,-1,1);
        this.scene.translate(2.8,1,0);
        this.parallelogram.display();

        this.scene.popMatrix();
        }
}