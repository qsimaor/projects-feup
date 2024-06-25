import { CGFobject, CGFappearance, CGFtexture } from "../../lib/CGF.js";
import { MyBillboard } from "./MyBillboard.js";

export class MyTreeRowPatch extends CGFobject {
	constructor(scene, x, y, z) {
		super(scene);
		this.x = x;
		this.y = y;
		this.z = z;
		this.trees = [];

		for (let i = 0; i < 6; i++) {
			let treeX = this.x + i * 0.2;
			let treeZ = this.z + i ;
			let tree = new MyBillboard(scene, treeX, this.y, treeZ);
			this.trees.push(tree);
		}
	}

    getRandom(min, max) {
        min = Math.ceil(min);
        max = Math.floor(max);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

	display() {
		for (let i = 0; i < this.trees.length; i++) {
			this.scene.pushMatrix();
			this.scene.translate(this.trees[i].x, this.trees[i].y, this.trees[i].z);
            this.scene.rotate(90, 0, 1, 0);
			this.trees[i].display();
			this.scene.popMatrix();
		}
	}
}