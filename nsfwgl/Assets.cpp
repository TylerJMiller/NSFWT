#include "ogl\gl_core_4_4.h"
#include "nsfw.h"
#include "stb\stb_image.h"
#include "fbx\FBXFile.h"
#include "obj\tiny_obj_loader.h"
#include <fstream>


using namespace nsfw::ASSET;

const char *nsfw::TYPE_NAMES[eSIZE + 1] = { "NONE","vao","ibo","vbo","tri-size","fbo","rbo","texture","shader","SIZE" };

#ifdef _DEBUG
#define ASSET_LOG(type) do { std::cerr << "Trying to create key: <" << TYPE_NAMES[type] << ">" << name << std::endl; } while(0)
#else 
#define ASSET_LOG(type) do {} while (0)
#endif

nsfw::GL_HANDLE nsfw::Assets::getVERIFIED(const AssetKey &key) const
{
#ifdef _DEBUG
			if (!handles.count(key))
			{
				std::cerr << "Asset Key not found: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
				return 0;
			}
#endif
			return handles.at(key);
}

bool nsfw::Assets::setINTERNAL(ASSET::GL_HANDLE_TYPE t, const char *name, GL_HANDLE handle)
{
	AssetKey key(t, name);
#ifdef _DEBUG
	if (handles.count(key))
	{
		std::cerr << "Asset Key already exists: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;
	}
	else if (handle == 0)
	{
		std::cerr << "Handle is invalid: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;

	}
	else std::cerr << "Asset Key successfully created: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
#endif
	handles[key] = handle;
	return true;
}

bool nsfw::Assets::makeVAO(const char * name, const struct Vertex *verts, unsigned vsize,  const unsigned * tris, unsigned tsize)
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);		//array that stores vertices
	ASSET_LOG(GL_HANDLE_TYPE::IBO);		//array that stores which vertices make up triangles
	ASSET_LOG(GL_HANDLE_TYPE::VAO);		//association between vbo and ibo
	ASSET_LOG(GL_HANDLE_TYPE::SIZE);	//how many triangles does vao hold
	
	unsigned vbo, ibo, vao, size = tsize;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);			//vbo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size *sizeof(unsigned), tris, GL_STATIC_DRAW);	//ibo

	//vao
	glEnableVertexAttribArray(0);	//position	- spatial location
	glEnableVertexAttribArray(1);	//normal	- direction normalized
	glEnableVertexAttribArray(2);	//tangent	- direction normalized
	glEnableVertexAttribArray(3);	//texcoord	- spatial location 2d

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TANGENT);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	//unbinding buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setINTERNAL(GL_HANDLE_TYPE::VBO, name, vbo);
	setINTERNAL(GL_HANDLE_TYPE::IBO, name, ibo);
	setINTERNAL(GL_HANDLE_TYPE::VAO, name, vao);
	setINTERNAL(GL_HANDLE_TYPE::SIZE, name, size);

	return false;
}

bool nsfw::Assets::makeVAO(const char *name, const struct nParticleVertex *parts, unsigned psize)	// Not yet completed, reference only
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);		//array that stores vertices
	ASSET_LOG(GL_HANDLE_TYPE::IBO);		//array that stores which vertices make up triangles
	ASSET_LOG(GL_HANDLE_TYPE::VAO);		//association between vbo and ibo
	ASSET_LOG(GL_HANDLE_TYPE::SIZE);	//how many triangles does vao hold

	unsigned vbo, ibo, vao;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, psize * sizeof(nParticleVertex), parts, GL_STATIC_DRAW);			//vbo
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, size *sizeof(ParticleVertex), parts, GL_STATIC_DRAW);	//ibo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, psize *sizeof(unsigned), parts, GL_STATIC_DRAW);	//ibo
	
	//vao
	glEnableVertexAttribArray(0);	//position
	glEnableVertexAttribArray(1);	//velocity
	glEnableVertexAttribArray(2);	//lifetime
	glEnableVertexAttribArray(3);	//lifespan

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::VELOCITY);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::LIFETIME);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::LIFESPAN);

	//unbinding buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setINTERNAL(GL_HANDLE_TYPE::VBO, name, vbo);
	setINTERNAL(GL_HANDLE_TYPE::IBO, name, ibo);
	setINTERNAL(GL_HANDLE_TYPE::VAO, name, vao);
	setINTERNAL(GL_HANDLE_TYPE::SIZE, name, psize);

	return false;
}

bool nsfw::Assets::makePVAO(const char *name, const struct nParticleVertex *parts, unsigned psize)	// Not yet completed, reference only
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);		//array that stores vertices
	ASSET_LOG(GL_HANDLE_TYPE::IBO);		//array that stores which vertices make up triangles
	ASSET_LOG(GL_HANDLE_TYPE::VAO);		//association between vbo and ibo
	ASSET_LOG(GL_HANDLE_TYPE::SIZE);	//how many triangles does vao hold

	unsigned vbo, ibo, vao;

	glGenVertexArrays(2, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, psize * sizeof(nParticleVertex), parts, GL_STATIC_DRAW);			//vbo
																									//glBufferData(GL_ELEMENT_ARRAY_BUFFER, size *sizeof(ParticleVertex), parts, GL_STATIC_DRAW);	//ibo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, psize *sizeof(nParticleVertex), parts, GL_STATIC_DRAW);	//ibo
																							//vao
	glEnableVertexAttribArray(0);	//position
	glEnableVertexAttribArray(1);	//velocity
	glEnableVertexAttribArray(2);	//lifetime
	glEnableVertexAttribArray(3);	//lifespan

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::VELOCITY);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::LIFETIME);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), (void*)nParticleVertex::LIFESPAN);

	//unbinding buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setINTERNAL(GL_HANDLE_TYPE::VBO, name, vbo);
	setINTERNAL(GL_HANDLE_TYPE::IBO, name, ibo);
	setINTERNAL(GL_HANDLE_TYPE::VAO, name, vao);
	setINTERNAL(GL_HANDLE_TYPE::SIZE, name, psize);

	return false;
}

bool nsfw::Assets::makeFBO(const char * name, unsigned w, unsigned h, unsigned nTextures, const char * names[], const unsigned depths[])
{
	ASSET_LOG(GL_HANDLE_TYPE::FBO);
	
	unsigned fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//8 guaranted color attachments
	//1 stencil attachment
	//1 depth attachment
	int n = 0;
	for (int i = 0; i < nTextures; i++)
	{
		makeTexture(names[i], w, h, depths[i]);
		unsigned attachment;
		if (depths[i] == GL_DEPTH_COMPONENT)
			attachment = GL_DEPTH_ATTACHMENT;
		else if (depths[i] == GL_DEPTH_STENCIL)
			attachment = GL_STENCIL_ATTACHMENT;
		else	/*is color*/
			attachment = GL_COLOR_ATTACHMENT0 + n++;

		glFramebufferTexture(GL_FRAMEBUFFER, attachment, get<TEXTURE>(names[i]), 0);
	}

	GLenum *colorAttachments = new GLenum[n];

	for (int i = 0; i < n; i++)
		colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(n, colorAttachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	setINTERNAL(GL_HANDLE_TYPE::FBO, name, fbo);
	return true;
}

bool nsfw::Assets::makeTexture(const char * name, unsigned w, unsigned h, unsigned depth, const unsigned char *pixels)
{
	ASSET_LOG(GL_HANDLE_TYPE::TEXTURE);
	unsigned texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//valid values for depth GL_RGBA, GL_RGB, GL_RG, GL_RED, GL_DEPTH_COMPONENT, GL_DEPTH STENCIL
	glTexImage2D(GL_TEXTURE_2D, 0, depth, w, h, 0, depth, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	setINTERNAL(GL_HANDLE_TYPE::TEXTURE, name, texture);
	return true;
}

bool nsfw::Assets::loadTexture(const char * name, const char * path)
{
	int w, h, d;
	unsigned char *p;

	p = stbi_load(path, &w, &h, &d, STBI_default);

	switch (d)
	{
	case STBI_grey:	d = GL_RED;	break;
	case STBI_grey_alpha:	d = GL_RG;	break;
	case STBI_rgb:	d = GL_RGB;	break;
	case STBI_rgb_alpha:	d = GL_RGBA;	break;
	}

	makeTexture(name, w, h, d , p);
	stbi_image_free(p);
	return true;
}

bool nsfw::Assets::loadShader(unsigned int type, const char * path)
{
	//ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	GLuint shader = glCreateProgram();;

	std::ifstream in(path);

	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	GLuint tShader = glCreateShader(type);
	
	const char *s = contents.c_str();

	glShaderSource(tShader, 1, &s, 0);

	glCompileShader(tShader);

	glAttachShader(shader, tShader);

	glLinkProgram(shader);
	int success = GL_FALSE;

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infolength = 0;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infolength);
		char* infolog = new char[infolength];
		glGetProgramInfoLog(shader, infolength, 0, infolog);
		printf_s("[ERROR] FAILED TO LINK SHADER ", path, "\n");
		printf_s(infolog);
		delete[] infolog;
	}

	glDeleteShader(tShader);

	//setINTERNAL(GL_HANDLE_TYPE::SHADER, name, shader);

	return false;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	GLuint shader = glCreateProgram();;

	std::ifstream vin(vpath);
	std::ifstream fin(fpath);

	std::string vcontents((std::istreambuf_iterator<char>(vin)), std::istreambuf_iterator<char>());
	std::string fcontents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vs = vcontents.c_str();
	const char *fs = fcontents.c_str();

	glShaderSource(vShader, 1, &vs, 0);
	glShaderSource(fShader, 1, &fs, 0);

	glCompileShader(vShader);
	glCompileShader(fShader);

	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);

	glLinkProgram(shader);
	int success = GL_FALSE;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infolength = 0;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infolength);
		char* infolog = new char[infolength];
		glGetProgramInfoLog(shader, infolength, 0, infolog);
		printf_s("[ERROR] FAILED TO LINK SHADER ", name, "\n");
		printf_s(infolog);
		delete[] infolog;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	//int success = GL_FALSE;
	//glGetProgramiv(shader, GL_LINK_STATUS, &success);


	setINTERNAL(GL_HANDLE_TYPE::SHADER, name, shader);
	return true;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * gpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	GLuint shader = glCreateProgram();;

	std::ifstream vin(vpath);
	std::ifstream gin(gpath);
	std::ifstream fin(fpath);

	std::string vcontents((std::istreambuf_iterator<char>(vin)), std::istreambuf_iterator<char>());
	std::string gcontents((std::istreambuf_iterator<char>(gin)), std::istreambuf_iterator<char>());
	std::string fcontents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint gShader = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vs = vcontents.c_str();
	const char *gs = gcontents.c_str();
	const char *fs = fcontents.c_str();

	glShaderSource(vShader, 1, &vs, 0);
	glShaderSource(gShader, 1, &gs, 0);
	glShaderSource(fShader, 1, &fs, 0);

	glCompileShader(vShader);
	glCompileShader(gShader);
	glCompileShader(fShader);

	glAttachShader(shader, vShader);
	glAttachShader(shader, gShader);
	glAttachShader(shader, fShader);

	glLinkProgram(shader);
	int success = GL_FALSE;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infolength = 0;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infolength);
		char* infolog = new char[infolength];
		glGetProgramInfoLog(shader, infolength, 0, infolog);
		printf_s("[ERROR] FAILED TO LINK SHADER ", name, "\n");
		printf_s(infolog);
		delete[] infolog;
	}

	glDeleteShader(vShader);
	glDeleteShader(gShader);
	glDeleteShader(fShader);

	setINTERNAL(GL_HANDLE_TYPE::SHADER, name, shader);
	return true;
}

bool nsfw::Assets::loadFBX(const char * name, const char * path)
{
	FBXFile file;

	file.load(path, FBXFile::UNITS_METER);

	for (int i = 0; i < file.getMeshCount(); i++)
	{
		unsigned tsize, vsize;
		unsigned *tris;
		Vertex *verts;
		auto m = file.getMeshByIndex(i);

		vsize = m->m_vertices.size();
		tsize = m->m_indices.size();

		verts = new Vertex[vsize];
		tris = new unsigned[tsize];

		for (int i = 0; i < tsize; ++i)
			tris[i] = m->m_indices[i];

		for (int i = 0; i < vsize; ++i)
		{
			verts[i].position = m->m_vertices[i].position;
			verts[i].normal = m->m_vertices[i].normal;
			verts[i].tangent = m->m_vertices[i].tangent;
			verts[i].texCoord = m->m_vertices[i].texCoord1;
		}

		std::string n = name;
		makeVAO(n.c_str(), verts, vsize, tris, tsize);
		delete[]verts;
		delete[]tris;
	}

	for (int i = 0; i < file.getTextureCount(); i++)
	{
		auto t = file.getTextureByIndex(i);
								//how do multiple textures
		std::string n = t->name;// = name;
		//n += t->name;
		loadTexture(n.c_str(), t->path.c_str());
	}

	file.unload();
	return true;
}

bool nsfw::Assets::loadOBJ(const char * name, const char * path)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;

	std::string objerror = tinyobj::LoadObj(shapes, materials, path);

	for (unsigned int mesh_index = 0; mesh_index < shapes.size(); mesh_index++)
	{
		tinyobj::mesh_t tmesh = shapes[0].mesh;

		vec4 *tpos = new vec4[tmesh.positions.size()];
		for (unsigned int i = 0; i < tmesh.positions.size() / 3; i++)
		{
			tpos[i].xyzw = vec4(tmesh.positions[3 * i], tmesh.positions[3 * i + 1], tmesh.positions[3 * i + 2], 1);
		}

		vec4 *tnorm = new vec4[tmesh.normals.size()];
		for (unsigned int i = 0; i < tmesh.normals.size() / 3; i++)
		{
			tnorm[i].xyzw = vec4(tmesh.normals[3 * i], tmesh.normals[3 * i + 1], tmesh.normals[3 * i + 2], 1);
		}

		vec2 *tcoord = new vec2[tmesh.texcoords.size()];
		for (unsigned int i = 0; i < tmesh.texcoords.size() / 2; i++)
		{
			tcoord[i].xy = vec2(tmesh.texcoords[2 * i], tmesh.texcoords[2 * i + 1]);
		}

		for (unsigned int i = 0; i < tmesh.indices.size(); i++)
		{
			indices.emplace_back(tmesh.indices.at(i));
		}

		for (unsigned int i = 0; i < tmesh.positions.size(); i++)
		{
			Vertex tvert;
			tvert.position = tpos[i].xyzw;
			tvert.normal = tnorm[i].xyzw;
			//tvert.texCoord = tcoord[i].xy;
			verts.emplace_back(tvert);
		}
	}
	makeVAO(name, verts.data(), verts.size(), indices.data(), indices.size());

	return true;
}

void nsfw::Assets::init()
{
	setINTERNAL(FBO,"Final",0);
	
	//makeVAO("Cube",CubeVerts,24,CubeTris,36);
	makeVAO("Quad",QuadVerts, 4, QuadTris,6);
	
	unsigned char w[] = { 150,0,150,255 };
	makeTexture("Purple", 1, 1, GL_RGBA, w);
	

}

void nsfw::Assets::term()
{
	for each(std::pair<AssetKey,unsigned> k in handles)
	{
		GLuint handle = k.second;
		switch (k.first.first)
		{
		case VBO:		glDeleteBuffers(1, &handle);		break;
		case IBO:		glDeleteBuffers(1, &handle);		break;
		case VAO:		glDeleteVertexArrays(1, &handle);	break;
		case SHADER:	glDeleteProgram(handle);			break;
		case TEXTURE:	glDeleteTextures(1, &handle);		break;
		//case RBO:		TODO_D("RBO deletion");				break;
		case FBO:		glDeleteFramebuffers(1, &handle);	break;
		}
	}
}


