#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::Player(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[])
{
	player = new Sprite(vertex_buffer, texture_buffer, index_buffer);
}

Player::~Player()
{
	free(player);
}

void Player::Init(int shader_programme, const char * filename)
{
	player->Init(shader_programme, filename);
}

void Player::Draw()
{
	player->Draw();
}

void Player::moveOY(float ty)
{
	glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, ty, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(player->vertex_buffer[i], player->vertex_buffer[i + 1], 
									player->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;
		
		player->vertex_buffer[i] = result.x;
		player->vertex_buffer[i + 1] = result.y;
		player->vertex_buffer[i + 2] = result.z;
	}
	//GLuint transf_loc = glGetUniformLocation(player->shader_programme, "u_transfMatrix");
	//glUniformMatrix4fv(transf_loc, 1, GL_FALSE, &transMatrix[0][0]);

}

void Player::moveOX(float tx)
{
	glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, 0, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(player->vertex_buffer[i], player->vertex_buffer[i + 1],
			player->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;

		player->vertex_buffer[i] = result.x;
		player->vertex_buffer[i + 1] = result.y;
		player->vertex_buffer[i + 2] = result.z;
	}
}

void Player::rotate(float angle)
{
	float originX, originY;
	float minX = 1;
	float maxX = -1;
	float minY = 1;
	float maxY = -1;

	for (int i = 0; i < 12; i += 3) {
		if (minX > player->vertex_buffer[i]) minX = player->vertex_buffer[i];
		if (maxX < player->vertex_buffer[i]) maxX = player->vertex_buffer[i];

		if (minY > player->vertex_buffer[i + 1]) minY = player->vertex_buffer[i + 1];
		if (maxY < player->vertex_buffer[i + 1]) maxY = player->vertex_buffer[i + 1];
	}
	originX = minX + (maxX - minX) / 2;
	originY = minY + (maxY - minY) / 2;
	moveOX(-originX);
	moveOY(-originY);

	glm::mat4 rotateMatrix = glm::mat4(cosf(angle), sinf(angle), 0, 0, -sinf(angle), cosf(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(player->vertex_buffer[i], player->vertex_buffer[i + 1],
			player->vertex_buffer[i + 2], 1);
		glm::vec4 result = rotateMatrix * vector;

		player->vertex_buffer[i] = result.x;
		player->vertex_buffer[i + 1] = result.y;
		player->vertex_buffer[i + 2] = result.z;
	}

	moveOX(originX);
	moveOY(originY);
}

void Player::show()
{
	player->show();
}