class Tree extends Primitive
{

	constructor(scene, th, tb, ch, cb, nt, tm)
	{
		super(scene);

		this.th = th;
		this.tb = tb;
		this.ch = ch;
		this.cb = cb;
		this.nt = nt;
		this.tm = tm;

		this.initBuffers();
	};


	initBuffers()
	{
		this.cone = new Cylinder(this.scene, this.tb, 0, this.th, 30, 30);

		this.triangle = new Triangle(this.scene, this.cb, 0, 0, -this.cb, 0, 0, 0 , this.ch, 0);

		this.triangle.indices.push(0);
		this.triangle.indices.push(2);
		this.triangle.indices.push(1);

		this.triangle.primitiveType=this.scene.gl.TRIANGLES;
		this.triangle.initGLBuffers();

		this.alpha = Math.PI*2/this.nt;
	};

	display()
	{
		this.scene.pushMatrix();
			this.scene.rotate(-Math.PI/2, 1, 0, 0);
			this.cone.display();
		this.scene.popMatrix();

		for (let i = 0; i < this.nt; i++)
		{
			this.scene.pushMatrix();
				this.scene.translate(0, this.th-this.ch, 0);
				this.scene.rotate(this.alpha*i, 0, 1, 0);
				this.triangle.display();
			this.scene.popMatrix();
		}
	};
};