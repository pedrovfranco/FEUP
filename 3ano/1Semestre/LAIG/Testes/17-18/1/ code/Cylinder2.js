class Cylinder2 extends Primitive
{
	constructor(scene, base, top, height, slices , stacks)
	{
		super(scene);

		this.base = base;
		this.top = top;
		this.height = height;
		this.slices = slices;
		this.stacks = stacks;

		this.degree = 2;
		this.controlPoints = [];

		var rb = this.base;
		var rt = this.top;

		var P0 = [0.7, 4, -1, 1];
		var P1 = [0.7, 4, 1, 1];

		var P2 = [0, -2, -0.5, 1];
		var P3 = [0, -2, 0.5, 1];

		var P4 = [-0.7, 4, -1, 1];
		var P5 = [-0.7, 4, 1, 1];



		this.controlPoints = [
													 [
														 P0,P1
													 ],
													 [
														 P2,P3
													 ],
													 [
														 P4,P5
													 ],

												 ];

	//   console.log(this.controlPoints);
		 this.nurbsSurface = new CGFnurbsSurface(2, 1, this.controlPoints);
		 this.nurbsObject = new CGFnurbsObject(this.scene, this.slices, this.stacks, this.nurbsSurface);
	};

		

	display()
	{
		let slices = 12;
		let alpha = 2*Math.PI/slices;


		for (let i = 0; i < slices; i++)
		{
			this.scene.rotate(alpha*1, 0, 0, 1);
			this.nurbsObject.display();
		}
		
			this.scene.translate(0, -1, 0);

		
	};

};


class oo
{

		constructor(primitive)
		{
			this.primitive = primitive;
		}

		getPoint(v, u)
		{
			let h = this.primitive.height*this.primitive.base/(this.primitive.base-this.primitive.top);
			let coords = [(h-u*this.primitive.height)/h*this.primitive.base*Math.cos(v*2*Math.PI), (h-u*this.primitive.height)/h*this.primitive.base*Math.sin(v*2*Math.PI), u*this.primitive.height];
			return coords;
		}
 
}