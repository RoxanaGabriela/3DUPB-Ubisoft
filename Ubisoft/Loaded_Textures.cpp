#include "stdafx.h"
#include "Loaded_Textures.h"
#include "rapidxml\rapidxml_iterators.hpp"
#include "rapidxml\rapidxml_print.hpp"
#include "rapidxml\rapidxml_utils.hpp"

Loaded_Textures::Loaded_Textures()
{
	shader_programme = 0;
}
Loaded_Textures::Loaded_Textures(int shader_programme)
{
	this->shader_programme = shader_programme;
}

Loaded_Textures::~Loaded_Textures()
{
	for (int i = 0; i < textures.size(); i++) free(textures[i]);
	for (int i = 0; i < sprites.size(); i++) free(sprites[i]);
	textures.clear();
	sprites.clear();
}

void Loaded_Textures::add(Loaded_Texture *texture)
{
	textures.push_back(texture);
}

void Loaded_Textures::add(Loaded_Sprite *sprite)
{
	sprites.push_back(sprite);
}

Loaded_Texture* Loaded_Textures::find(char *image)
{
	int j = -1;
	for (int i = 0; i < textures.size(); i++) {
		if (strcmp(textures[i]->name, image) == 0) {
			j = i;
			break;
		}
	}
	if (j == -1) return NULL;
	return textures[j];
}

int Loaded_Textures::LoadTexture(char *locationTex, float *width, float *height)
{
	float vertex_buffer[] = {
		-0.65f, 0.65f, 0.0f,
		-0.65f, 0.35f, 0.0f,
		-0.95f, 0.35f, 0.0f,
		-0.95f, 0.65f, 0.0f
	};

	float texture_buffer[] = {
		0.0f, *height,
		0.0f, 0.0f,
		*width, 0.0f,
		*width, *height
	};

	unsigned int index_buffer[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint vbo, tex_vbo, ibo, tex;

	// Generam un buffer in memoria video si scriem in el punctele din ram
	glGenBuffers(1, &vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

	// Generam un buffer in memoria video si scriem in el punctele din ram
	glGenBuffers(1, &tex_vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo); // setam bufferul generat ca bufferul curent 
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texture_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index_buffer, GL_STATIC_DRAW);

	this->shader_programme = shader_programme;

	// incarcam imaginea din fisier si ii fortam canalele RGBA
	int n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load(locationTex, (int*)width, (int*)height, &n, force_channels);
	if (image_data == NULL) fprintf(stderr, "Error loading sprite %s image!\n", locationTex);

	// Facem flip pe textura 
	FlipTexture(image_data, *width, *height, n);

	// Trimitem textura la memoria video
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
	// 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
	// 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint pos_loc = glGetAttribLocation(shader_programme, "vertex_position");
	glEnableVertexAttribArray(pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	GLint tex_loc = glGetAttribLocation(shader_programme, "texture_coordinates");
	glEnableVertexAttribArray(tex_loc);
	glVertexAttribPointer(tex_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	GLint texx = glGetUniformLocation(shader_programme, "basic_texture");
	glUseProgram(shader_programme);
	glUniform1i(texx, 0); // use active texture 0

	return tex;
}

void Loaded_Textures::Load()
{
	rapidxml::file<> xmlFile("../data/player.xml"); // Default template is char
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *pRoot = doc.first_node();

	rapidxml::xml_attribute<> *img = pRoot->first_attribute("imagePath");
	assert(img);
	char *imageName = img->value();

	// find image in Loaded textures
	Loaded_Texture* fnd = find(imageName);
	Loaded_Texture* needed_img = NULL;
	if (fnd == NULL) // did not find image
	{
		char *locationTex = (char*)malloc((strlen("../data/") + strlen(imageName)) * sizeof(char));
		strcpy(locationTex, "../data/");
		strcat(locationTex, imageName);
		
		float width, height;
		int texture = LoadTexture(locationTex, &width, &height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		needed_img = new Loaded_Texture();
		needed_img->set_texture_id(texture);
		needed_img->set_texture_name(imageName);
		needed_img->set_height(height);
		needed_img->set_width(width);
		add(needed_img);	
	}
	else
	{
		needed_img = fnd;
	}

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("SubTexture"); pNode; pNode = pNode->next_sibling())
	{

		Loaded_Sprite * new_entry = new Loaded_Sprite();
		rapidxml::xml_attribute<> *spr_name = pNode->first_attribute("name");
		new_entry->name = (char*)malloc(strlen(spr_name->value()) * sizeof(char));
		strcpy(new_entry->name, spr_name->value());
		
		rapidxml::xml_attribute<> *spr_x = pNode->first_attribute("x");
		assert(spr_x);
		new_entry->x = atof(spr_x->value());

		rapidxml::xml_attribute<> *spr_y = pNode->first_attribute("y");
		assert(spr_y);
		new_entry->y = atof(spr_y->value());

		rapidxml::xml_attribute<> *spr_w = pNode->first_attribute("width");
		assert(spr_w);
		new_entry->width = atof(spr_w->value());

		rapidxml::xml_attribute<> *spr_h = pNode->first_attribute("height");
		assert(spr_h);
		new_entry->height = atof(spr_h->value());

		new_entry->refTex = needed_img->get();

		add(new_entry);
	}
	doc.clear();
	show();
}

// exemplu de implementare
void Loaded_Textures::FlipTexture(unsigned char* image_data, int x, int y, int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
}

void Loaded_Textures::show()
{
	for (int i = 0; i < textures.size(); i++) {
		printf("%d %s %d %d\n", textures[i]->id, textures[i]->name, textures[i]->width, textures[i]->height);
	}
	for (int i = 0; i < sprites.size(); i++) {
		printf("%s %.1f %.1f %.1f %.1f\n", sprites[i]->name, sprites[i]->x, sprites[i]->y, sprites[i]->width, sprites[i]->height);
	}
}