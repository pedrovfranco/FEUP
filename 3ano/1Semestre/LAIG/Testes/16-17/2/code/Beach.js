class Beach extends Primitive
{
	constructor(scene , idtexture, idheightmap, idMask, parts, heightscale)
	{
		super(scene);

		this.scene = scene;
		this.idtexture = idtexture;
		this.idheightmap = idheightmap;
		this.idMask = idMask;
		this.parts = parts;
		this.heightscale = heightscale;

		this.plane = new Plane(scene, this.parts, this.parts);

		this.texCoordsSet = false;

		this.initializeShaders();
	}

	initializeShaders()
	{

		this.shader = new CGFshader(this.scene.gl, "scenes/shaders/3.vert", "scenes/shaders/3.frag"),

		this.shader.setUniformsValues({uSampler2: 1});
		this.shader.setUniformsValues({maskSampler: 2});
		this.shader.setUniformsValues({normScale: this.heightscale});

		this.texture1 = new CGFtexture(this.scene, this.scene.graph.textures[this.idtexture]);
		this.texture2 = new CGFtexture(this.scene, this.scene.graph.textures[this.idheightmap]);
		this.texture3 = new CGFtexture(this.scene, this.scene.graph.textures[this.idMask]);
	};

	// updateTexCoords(s, t)
 //    {
 //        if (this.texCoordsSet != undefined && !this.texCoordsSet)
 //        {
 //            this.shader.setUniformsValues({length_s: s});
 //            this.shader.setUniformsValues({length_t: t});
    
 //            this.texCoordsSet = true;
 //        }
 //    }


	display()
	{

		this.scene.setActiveShader(this.shader);

		this.texture1.bind(0);
		this.texture2.bind(1);
		this.texture3.bind(2);

		this.plane.display();
		
		this.scene.setActiveShader(this.scene.defaultShader);

	};

};
