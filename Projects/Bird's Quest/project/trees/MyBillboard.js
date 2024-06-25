import { CGFobject, CGFappearance, CGFtexture } from "../../lib/CGF.js";
import { MyQuad } from "../primitives/MyQuad.js";

export class MyBillboard extends CGFobject {
	constructor(scene, x, y, z) {
		super(scene);
		this.x = x;
		this.y = y;
		this.z = z;
		this.quad = new MyQuad(scene);
		this.id_Texture = this.getRandom(1,3);
		this.texture = null;
		this.setTexture();
	}

	setTexture() {
		if (this.id_Texture === 1) {
			this.texture = new CGFtexture(this.scene, 'images/tree1.png');
		} else if (this.id_Texture === 2) {
			this.texture = new CGFtexture(this.scene, 'images/tree2.png');
		} else {
			this.texture = new CGFtexture(this.scene, 'images/tree3.png');
		}

		this.material = new CGFappearance(this.scene);
		this.material.setEmission(1, 1, 1, 1);
		this.material.setAmbient(1, 1, 1, 1);
		this.material.setDiffuse(1, 1, 1, 1);
		this.material.setSpecular(1, 1, 1, 1);
		this.material.setTexture(this.texture);
		this.material.setTextureWrap('REPEAT', 'REPEAT');
	}

	getRandom(min, max) {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}

	display() {
		 // Quad's Normal vector 
		let quad_normals = [0,0,1];

		// Camera position vector;
		let cam_pos = [this.scene.camera.position[0], 0, this.scene.camera.position[2]];    
		
		let angle = Math.acos((vec3.dot(quad_normals, cam_pos))* (Math.PI/180));
		
		let rot_axis = [0,0,1];

		vec3.cross(rot_axis, quad_normals, cam_pos);
		this.scene.pushMatrix();
		this.scene.scale(7, 10, 7);
		this.scene.translate(this.x,this.y,this.z);        
		this.scene.rotate(angle, rot_axis[0], rot_axis[1], rot_axis[2]);

		this.material.apply();
		this.quad.display();
		this.scene.popMatrix();
	}
}
