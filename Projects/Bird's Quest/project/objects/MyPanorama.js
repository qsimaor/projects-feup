import { CGFobject, CGFappearance, CGFshader } from '../../lib/CGF.js';
import { MySphere } from './MySphere.js';

export class MyPanorama extends CGFobject {

  /**
   * @constructor
   * @param  {CGFscene} scene - MyScene object
   * @param  {CGFtexture} texture - CGFtexture object
   */
  
  constructor(scene, texture) {
    super(scene);

    // Create inverted sphere
    this.sphere = new MySphere(scene, 48, 24, -1);

    // Create emissive material with texture
    this.material = new CGFappearance(scene);
    this.material.setEmission(1, 1, 1, 1);
    this.material.setTexture(texture);
  }

  display() {
    this.scene.pushMatrix();

    // Scale and apply material with texture
    this.scene.scale(20, 20, 20);
    this.material.apply();

    // Display inverted sphere
    this.scene.rotate(Math.PI, 0, 1, 0);
    this.sphere.display();
    this.scene.popMatrix();
  }
}
