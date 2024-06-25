import { CGFobject, CGFappearance } from "../../lib/CGF.js";
import { MyCone } from "../primitives/MyCone.js";

export class MyNest extends CGFobject {
  constructor(scene) {
    super(scene);

    this.eggs_list = [];
    this.initBuffers();
    this.initMaterials();
  }

  initBuffers() {
    this.object = new MyCone(this.scene, 100, 1, 0.05, 0.05);
  }

  initMaterials() {
    this.material = new CGFappearance(this.scene);
    this.material.setEmission(1, 1, 1, 1);
    this.material.setAmbient(1, 1, 1, 1);
    this.material.setDiffuse(1, 1, 1, 1);
    this.material.setSpecular(1, 1, 1, 1);

    this.material.loadTexture("images/nest.jpg");
    this.material.setTextureWrap("REPEAT", "REPEAT");
  }

  display() {
    this.scene.pushMatrix();
    this.material.apply();
    this.scene.translate(0, 0, 0);
    this.scene.rotate(-Math.PI, 0, 1, 0);
    this.object.display();
    this.scene.popMatrix();
  }

  addEgg(egg) {
    this.eggs_list.push(egg);
  }
}
