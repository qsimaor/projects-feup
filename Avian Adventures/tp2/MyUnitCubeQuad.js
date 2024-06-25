import {CGFobject} from '../lib/CGF.js';
import { MyQuad } from './MyQuad.js';
/**
 * MyDiamond
 * @constructor
 * @param scene - Reference to MyScene object
 */
export class MyUnitCubeQuad extends CGFobject {
	constructor(scene) {
		super(scene);
		this.quad = new MyQuad(scene);
	}
	
    display() {
        // Drawing the back side
        this.scene.pushMatrix();

        this.scene.translate(0, 0, -0.5);
        this.scene.scale(-1, 1, 1);
        this.quad.display();

        this.scene.popMatrix();

        // Drawing the top side
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, 0);
        this.scene.rotate(Math.PI/2, 1, 0, 0);
        this.scene.scale(-1, 1, 1);

        this.quad.display();

        this.scene.popMatrix();

        // Drawing the bottom side
        this.scene.pushMatrix();

        this.scene.translate(0, -0.5, 0);
        this.scene.rotate(Math.PI/2, 1, 0, 0);

        this.quad.display();

        this.scene.popMatrix();

        // Drawing the right side
        this.scene.pushMatrix();

        this.scene.translate(0.5, 0, 0);
        this.scene.rotate(Math.PI/2, 0, 1, 0);

        this.quad.display();

        this.scene.popMatrix();

        // Drawing the left side
        this.scene.pushMatrix();

        this.scene.translate(-0.5, 0, 0);
        this.scene.rotate(Math.PI/2, 0, 1, 0);
        this.scene.scale(-1, 1, 1);

        this.quad.display();

        this.scene.popMatrix();

        // Drawing the front side
        this.scene.pushMatrix();

        this.scene.translate(0, 0, 0.5);

        this.quad.display();

        this.scene.popMatrix();

    }
}