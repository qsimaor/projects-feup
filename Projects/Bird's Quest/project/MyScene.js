import { CGFscene, CGFcamera, CGFaxis, CGFappearance, CGFtexture } from "../lib/CGF.js";
import { MySphere } from "./objects/MySphere.js";
import { MyPanorama } from "./objects/MyPanorama.js";
import { MyBird } from "./bird/MyBird.js";
import { MyTerrain } from "./objects/MyTerrain.js";
import { MyNest } from "./objects/MyNest.js";
import { MyTreeGroupPatch } from "./trees/MyTreeGroupPatch.js";
import { MyTreeRowPatch } from "./trees/MyTreeRowPatch.js";

export class MyScene extends CGFscene {
  constructor() {
    super();
  }

  init(application) {
    super.init(application);
    this.initCameras();
    this.initLights();

    this.timePrevFrame = Date.now();

    // Background color
    this.gl.clearColor(0.0, 0.0, 0.0, 1.0);
    this.gl.clearDepth(100.0);
    this.gl.enable(this.gl.DEPTH_TEST);
    this.gl.enable(this.gl.CULL_FACE);
    this.gl.depthFunc(this.gl.LEQUAL);

    this.enableTextures(true);

    this.slices = 40;
    this.stacks = 40;

    this.aceleration = 0.5;
    this.theta = 1;

    // Initialize scene objects
    this.axis = new CGFaxis(this);
    this.terrain = new MyTerrain(this);
    this.sphere = new MySphere(this, this.slices, this.stacks);
    this.panorama = new MyPanorama(this, new CGFtexture(this, "images/panorama4.jpg"));
    this.bird = new MyBird(this);
    this.treegroup = new MyTreeGroupPatch(this,3, -1.9, 2);
    this.treerow = new MyTreeRowPatch(this,7, -1.7, -5);
    this.nest = new MyNest(this);

    this.bird.scaleFactor = 1;
    this.setUpdatePeriod(100);

    // Objects connected to MyInterface
    this.displayAxis = true;
    this.scaleFactor = 1;
    this.displaySphere = true; //esfera

    //Textures
    this.texture = new CGFtexture(this, "images/terrain.jpg"); // Terreno
    this.appearance = new CGFappearance(this);
    this.appearance.setTexture(this.texture);
    this.appearance.setTextureWrap('REPEAT', 'REPEAT');

    this.gl.enable(this.gl.BLEND);
    this.gl.blendFunc(this.gl.SRC_ALPHA, this.gl.ONE_MINUS_SRC_ALPHA);
  }

  initLights() {
    this.lights[0].setPosition(15, 0, 5, 1);
    this.lights[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
    this.lights[0].enable();
    this.lights[0].update();
  }

  initCameras() {
    this.camera = new CGFcamera(1.0, 0.1, 1000, vec3.fromValues(8, -15, 7), vec3.fromValues(0,0,0));
  }

  setDefaultAppearance() {
    this.setAmbient(0.2, 0.4, 0.8, 1.0);
    this.setDiffuse(0.2, 0.4, 0.8, 1.0);
    this.setSpecular(0.2, 0.4, 0.8, 1.0);
    this.setEmission(0, 0, 0, 1);
    this.setShininess(10.0);
  }

  update(t) {
    this.checkKeys();
    var dt = t - this.timePrevFrame;
    this.bird.update(t, dt);
    this.timePrevFrame = t;

  }

  getBird() {
    return this.bird;
  }

  checkKeys() {
    var text = "Keys pressed: ";
    var keysPressed = false;

    if (this.gui.isKeyPressed("KeyW")) {
      text += " W ";
      this.bird.accelerate(this.aceleration);
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyS")) {
      text += " S ";
      this.bird.accelerate(-this.aceleration);
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyA")) {
      text += " A ";
      this.bird.turn(this.theta);
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyD")) {
      text += " D ";
      this.bird.turn(-this.theta);
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyR")) {
      text += " R ";
      this.bird.resetBird();
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyP")) {
      text += " P ";
      this.bird.diving=true;
      keysPressed = true;
    }

    if (this.gui.isKeyPressed("KeyO")) {
      text += " O ";
      this.bird.dropEgg();
      keysPressed = true;
    }

    if (keysPressed) console.log(text);
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

  
    if (this.displayAxis) this.axis.display();

    if (this.displaySphere) {
      this.pushMatrix();
      this.scale(10, 10, 10);
      this.translate(0.5, 10, 0.5);
      this.panorama.display();
      this.popMatrix();
      this.pushMatrix();
      this.terrain.display();
      this.popMatrix();

      this.pushMatrix();
      this.translate(30, -51, 37);
      this.scale(1.5, 1.5, 1.5); // Scale the nest
      this.nest.display();
      this.popMatrix();
    }

    this.pushMatrix();
    this.scale(5, 5, 5); // Scale the bird
    this.bird.display();
    this.popMatrix();
  
    this.pushMatrix();
    this.translate(8, -15, 7);
    this.scale(1.5, 1.5, 1.5); // Scale the tree group
    this.treegroup.display();
    this.popMatrix();
    
  }
}
