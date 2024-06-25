import {CGFappearance, CGFobject,CGFtexture} from '../../lib/CGF.js';
import { MyBirdEgg } from './MyBirdEgg.js';
import { MyCone } from '../primitives/MyCone.js';
import { MyCylinder } from '../primitives/MyCylinder.js';
import { MyDiamond } from '../primitives/MyDiamond.js';
import { MyPyramid } from '../primitives/MyPyramid.js';
import { MyTriangleSmall } from '../primitives/MyTriangleSmall.js';
import { MyUnitCube } from '../primitives/MyUnitCube.js';
/**
* MyBird
* @constructor
 * @param scene - Reference to MyScene object
*/
export class MyBird extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initParts();
        this.initMaterials();
        
        this.x = 0;
        this.y = -20;
        this.z = 0;
        this.orientation = 0;
        this.maxWingAngle = Math.PI/6;
        this.dWingAngle = 0;

        this.dy = 0;
        this.yScale = 0.15;

        this.speed = 1;
        this.maxSpeed = 4;
        this.speedScale = 0.5;

        this.speedFactor = 1;

        this.catchegg = null;
        this.dropEgg = null;

        this.minHeight=-3;
        this.diveHeight=0;
     
    }

    initParts() {
        this.head = new BirdHead(this.scene);
        this.body = new BirdBody(this.scene);
        this.leftWing = new BirdWing(this.scene, "left");
        this.rightWing = new BirdWing(this.scene, "right");
        this.leftleg= new MyCylinder(this.scene);
        this.rightleg= new MyCylinder(this.scene);
        this.egg = new MyBirdEgg(this.scene,40, 40, 14, -9, 10);
       
    }

    initMaterials() {

        // Blue material (no ambient, high specular)
        this.blueMaterial = new CGFappearance(this.scene);
        this.blueMaterial.setAmbient(0,0,0,1.0);
        this.blueMaterial.setDiffuse(0.12, 0.56, 1.0, 1.0);
        this.blueMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.blueMaterial.setShininess(10);

        // Yellow material (no ambient, high specular)
        this.yellowMaterial = new CGFappearance(this.scene);
        this.yellowMaterial.setAmbient(0,0,0,1.0);
        this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
        this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.yellowMaterial.setShininess(10);

     

    }

    update(t, dt) {
        // Divide 't' and 'dt' by 1000 to convert into seconds.
        // Multiply by 2*Math.PI to get a period of 1 second.
        this.dy = this.yScale * Math.sin((t / 1000) * 2 * Math.PI);
        this.dWingAngle =
            -Math.sin(this.speedFactor * (1 + this.speed * this.speedScale) * (t / 1000) * 2 * Math.PI);

        this.x += this.speed * this.speedFactor * Math.sin(this.orientation) * (dt / 1000);
        this.y = -6 + this.diveHeight;
        this.z += this.speed * this.speedFactor * Math.cos(this.orientation) * (dt / 1000);

        this.leftWing.wingAngle = this.dWingAngle;
        this.rightWing.wingAngle = this.dWingAngle;


        if(this.diving){ 
            this.dive(0.5);
        }else{ 
            this.dive(-0.5);
        }


        this.checkCollisions();

    }

    accelerate(v) {
        this.speed = Math.max(0, Math.min(this.maxSpeed, this.speed + v));
    }

    turn(v) {
        this.orientation = (this.orientation + v * this.speedFactor) % (2*Math.PI);
    }

    resetBird() {
        this.x = 0;
        this.y = -6;
        this.z = 0;
        this.orientation=0;
        this.speed = 0;
    }


    dive(v){
        if (this.diveHeight <= 0 && this.diveHeight >= this.minHeight)
            this.diveHeight -= v;
        if (this.diveHeight>0) this.diveHeight = 0;
         else if (this.diveHeight<this.minHeight){
        this.diveHeight = this.minHeight;
        this.diving = false;

    }
}

    checkCollisions(){
          if (Math.abs(this.x - this.egg.x) < 2 &&
            Math.abs(this.y - this.egg.y) < 1 &&
            Math.abs(this.z - this.egg.z) < 2) {
            if(this.catchegg == null){
                this.catchegg = this.egg;
            }
        }
    }

    dropEgg(){
        if(this.catchegg != null){
            this.droppingEgg = this.catchegg;
            this.catchegg= null;
        }
        if(this.droppingEgg != null){
            this.droppingEgg.drop();
            if(this.droppingEgg.y==-9){
                this.egg = this.droppingEgg;
                this.egg.x= this.droppingEgg.x;
                this.egg.y= this.droppingEgg.y;
                this.egg.z= this.droppingEgg.z;
                this.droppingEgg = null;
            }

        }
    }


    display(){
        if(this.catchegg != null){
            this.catchegg.x=this.x;
            this.catchegg.y=this.y-0.5;
            this.catchegg.z=this.z;
            this.catchegg.display();
        }
        if(this.droppingEgg != null){
            this.droppingEgg.display();
        }

        this.scene.pushMatrix();
        this.scene.translate(this.x, this.y + this.dy, this.z);
        this.scene.translate(0.0, this.y, -0.6);
        this.scene.rotate(this.orientation,0,1,0);
        this.scene.translate(0.0, -this.y, 0.6);
        this.scene.scale(this.scaleFactor,this.scaleFactor,this.scaleFactor);

        this.head.display();
        this.body.display();
        this.leftWing.display();
        this.rightWing.display();
        this.scene.popMatrix()

        this.scene.pushMatrix();
        this.egg.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(2,1,-3);
        this.egg.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(-4,0,1);
        this.egg.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(5,1,2);
        this.egg.display();
        this.scene.popMatrix();
    }

}


//TODO: Adjust scaling and position
/**
* BirdHead
* @constructor
 * @param scene - Reference to MyScene object
*/
class BirdHead extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initParts();
        this.initMaterials();
    }

    initParts() {
        this.head = new MyUnitCube(this.scene, 36, 18);
        this.leftEye = new MyUnitCube(this.scene, 16, 8);
        this.rightEye = new MyUnitCube(this.scene, 16, 8);
        this.beak = new MyPyramid(this.scene, 3, 1);
        this.crista = new MyTriangleSmall(this.scene);
    }
    initMaterials() {
        this.material = new CGFappearance(this.scene);
        this.material.setSpecular(0.0, 0.0, 0.0, 1.0);

        //BLUE
        this.blueMaterial = new CGFappearance(this.scene);
        this.blueMaterial.setAmbient(0,0,0,1.0);
        this.blueMaterial.setDiffuse(0.12, 0.56, 1.0, 1.0);
        this.blueMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.blueMaterial.setShininess(10);

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

        // Yellow material (no ambient, high specular)
        this.yellowMaterial = new CGFappearance(this.scene);
        this.yellowMaterial.setAmbient(0,0,0,1.0);
        this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
        this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.yellowMaterial.setShininess(10);


        // Orange material (no ambient, high specular)
        this.orangeMaterial = new CGFappearance(this.scene);
        this.orangeMaterial.setAmbient(0,0,0,1.0);
        this.orangeMaterial.setDiffuse(1.0, 0.65, 0.0, 1.0);
        this.orangeMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.orangeMaterial.setShininess(10);
    }
    
    display() {
        this.yellowMaterial.apply();

        this.scene.pushMatrix();
        this.scene.scale(0.3, 0.28, 0.32);
        this.head.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.orangeMaterial.apply();
        this.scene.scale(0.1,0.28,0.16);
        this.scene.translate(0,0.5,0);
        this.scene.rotate(Math.PI/2, 0, 1, 0);
        this.crista.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.material.apply();
        this.scene.translate(-0.15, 0.05, 0.09);
        this.scene.scale(0.08, 0.07, 0.07);
        this.leftEye.display();
        this.scene.popMatrix();

    
        this.scene.pushMatrix();
        this.material.apply();
        this.scene.translate(0.15, 0.05, 0.09);
        this.scene.scale(0.08, 0.07, 0.07);
        this.rightEye.display();
        this.scene.popMatrix();

        this.woodMaterial.apply();
        this.scene.pushMatrix();
        this.scene.translate(0.0, -0.05, 0.15);
        this.scene.scale(0.1, 0.1, 0.3);
        this.scene.rotate(-Math.PI/6, 0, 0, 1);
        this.scene.rotate(Math.PI/2, 1, 0, 0);
        this.beak.display();
        this.scene.popMatrix();
    }
}

/**
* BirdBody
* @constructor
 * @param scene - Reference to MyScene object
*/
class BirdBody extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initParts();
        this.initMaterials();

    }

    initParts() {
        this.torso = new MyUnitCube(this.scene, 36, 18);

   
    }
    initMaterials() {
      

        //BLUE
        this.blueMaterial = new CGFappearance(this.scene);
        this.blueMaterial.setAmbient(0,0,0,1.0);
        this.blueMaterial.setDiffuse(0.12, 0.56, 1.0, 1.0);
        this.blueMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.blueMaterial.setShininess(10);

        // Yellow material (no ambient, high specular)
        this.yellowMaterial = new CGFappearance(this.scene);
        this.yellowMaterial.setAmbient(0,0,0,1.0);
        this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
        this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.yellowMaterial.setShininess(10);
    }
    display() {
        this.yellowMaterial.apply();
        this.scene.pushMatrix();
        this.scene.translate(0.0, -0.3, -0.4);
        this.scene.scale(0.4, 0.32, 0.7);
        this.torso.display();
        this.scene.popMatrix();
    }
}

/**
* BirdWing
* @constructor
 * @param scene - Reference to MyScene object
 * @param side  - Whether it's the right or the left wing
*/
class BirdWing extends CGFobject {
    constructor(scene, side) {
        super(scene);
        this.initParts();
        this.initMaterials();
        this.side = side;
        this.wingAngle = Math.PI/4;
    }
    
    initParts() {
        this.innerWing = new MyDiamond(this.scene);
        this.outerWing = new MyTriangleSmall(this.scene);
    }
    initMaterials() {
        this.material = new CGFappearance(this.scene);
        this.material.setSpecular(0.0, 0.0, 0.0, 1.0);

        //BLUE
        this.blueMaterial = new CGFappearance(this.scene);
        this.blueMaterial.setAmbient(0,0,0,1.0);
        this.blueMaterial.setDiffuse(0.12, 0.56, 1.0, 1.0);
        this.blueMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.blueMaterial.setShininess(10);

        // Yellow material (no ambient, high specular)
        this.yellowMaterial = new CGFappearance(this.scene);
        this.yellowMaterial.setAmbient(0,0,0,1.0);
        this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
        this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
        this.yellowMaterial.setShininess(10);

    }

  
    display() {
        this.yellowMaterial.apply();

        this.scene.pushMatrix();
        if (this.side == "right") this.scene.scale(-1, 1, 1);
        this.scene.translate(0.3, -0.3, -0.45);
        this.scene.rotate(this.wingAngle, 0, 0, 1);
      
        this.scene.pushMatrix(); // Inner wing
        this.scene.scale(0.25, 1.0, 0.4);
        this.scene.rotate(Math.PI / 4, 0, 1, 0);
        this.scene.rotate(-Math.PI / 2, 1, 0, 0);
        this.innerWing.display();
        this.scene.popMatrix();
      
        this.scene.pushMatrix(); // Outer wing
        this.scene.translate(0.37, 0.025, 0.24);
        this.scene.rotate(Math.PI / 8, 0, 1, 0);
        this.scene.rotate(-Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.24, 0.6, 0.4);
        this.outerWing.display();
        this.scene.popMatrix();
      
        this.scene.popMatrix();

                
    }
}

/**
* BirdTail
* @constructor
 * @param scene - Reference to MyScene object
*/
class BirdTail extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initParts();
        this.initMaterials();
    }

    initParts() {
        this.tail = new MyCone(this.scene, 4, 4, Math.PI/2);
    }

    initMaterials() {
        this.material = new CGFappearance(this.scene);
        this.material.setSpecular(0.0, 0.0, 0.0, 1.0);

         // Yellow material (no ambient, high specular)
         this.yellowMaterial = new CGFappearance(this.scene);
         this.yellowMaterial.setAmbient(0,0,0,1.0);
         this.yellowMaterial.setDiffuse(1.0, 1.0, 0.0, 1.0);
         this.yellowMaterial.setSpecular(0.8, 0.8, 0.8, 1.0);
         this.yellowMaterial.setShininess(10);

        // Add your material properties here

    }

    display() {
        this.yellowMaterial.apply();
        this.scene.pushMatrix();
        this.scene.translate(0, -0.3, -0.95);
        this.scene.scale(0.2, 0.2, 0.2);
        this.scene.rotate(Math.PI/4, 0, 0, 1);
        this.scene.rotate(-Math.PI/2, 1, 0, 0);
        this.scene.scale(1, -1, -1);
        this.tail.display();
        this.scene.popMatrix();
    }
}
