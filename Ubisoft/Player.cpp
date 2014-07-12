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

void Player::show()
{
	player->show();
}