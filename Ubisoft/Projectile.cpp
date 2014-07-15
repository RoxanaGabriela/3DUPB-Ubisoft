#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
	projectile = NULL;
}

Projectile::Projectile(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[])
{
	float minX = 1;
	float maxX = -1;
	float minY = 1;
	float maxY = -1;
	for (int i = 0; i < 12; i += 3) {
		if (minX > vertex_buffer[i]) minX = vertex_buffer[i];
		if (maxX < vertex_buffer[i]) maxX = vertex_buffer[i];

		if (minY > vertex_buffer[i + 1]) minY = vertex_buffer[i + 1];
		if (maxY < vertex_buffer[i + 1]) maxY = vertex_buffer[i + 1];
	}

	float vb[] = {
		minX + (maxX - minX) / 4, maxY + 0.2f, 0.0f,
		minX + (maxX - minX) / 4, maxY, 0.0f,
		maxX - (maxX - minX) / 4, maxY, 0.0f,
		maxX - (maxX - minX) / 4, maxY + 0.2f, 0.0f
	};
	projectile = new Sprite(vb, texture_buffer, index_buffer);
}

Projectile::~Projectile()
{
	free(projectile);
}

void Projectile::Init(int shader_programme, const char *filename)
{
	projectile->Init(shader_programme, filename);
}

void Projectile::Draw()
{
	projectile->Draw();
}

void Projectile::move(float ty)
{
	glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, ty, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(projectile->vertex_buffer[i], projectile->vertex_buffer[i + 1],
			projectile->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;

		projectile->vertex_buffer[i] = result.x;
		projectile->vertex_buffer[i + 1] = result.y;
		projectile->vertex_buffer[i + 2] = result.z;
	}
}
