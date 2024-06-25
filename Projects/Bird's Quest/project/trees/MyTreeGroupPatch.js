import { CGFobject,CGFappearance, CGFtexture } from "../../lib/CGF.js";
import { MyBillboard } from "./MyBillboard.js";

export class MyTreeGroupPatch extends CGFobject {
	constructor(scene, x, y, z) {
		super(scene);
        this.x = x;
        this.y = y;
        this.z = z;
        this.trees = [];

        // Criar as árvores
        for (let i = 0; i < 9; i++) {
            const treeX = this.x + (i % 3) + Math.random() * 0.5 - 0.25; // Posição X da árvore com deslocamento aleatório
            const treeZ = this.z + Math.floor(i / 3) * 1.5 + Math.random() * 0.5 - 0.25; // Posição X da árvore com deslocamento aleatório
            const tree = new MyBillboard(scene, treeX, this.y, treeZ);
            this.trees.push(tree);
        }
	}
    
    display(){
        for (let i = 0; i < this.trees.length; i++) {
            this.trees[i].display();
        }
    }
}