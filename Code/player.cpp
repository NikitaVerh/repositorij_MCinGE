#pragma once
#include <iostream>
#include "player.h"
#include "GlobalVariablesOfClasses.h"
#include "GlobalVariablesForResources.h"

bool Hitbox::showHitbox = true; // змінювати лише в коді, зміни для розробників

bool Player::checkColision(float dx) {
	return GameMap.collisionMap(Hitbox(hitbox.getRect().left + dx, hitbox.getRect().top, hitbox.getRect().width, hitbox.getRect().height));
}

void Player::Update() {
	if (moving_flag == false && Y_start_climbing != -1) {
		float deltaY = 0.5 * delta_time.asSeconds() * speed_player;
		if (y + deltaY >= Y_start_climbing + 0.99) {
			y = Y_start_climbing + 0.99;
			Y_start_climbing = -1;
		}
		else y += deltaY;
	}
	else moving_flag = false;
	set_pos_hitbox_player();
}

void Player::set_pos_hitbox_player(){
	hitbox.setSizePos(x - playerWidth / 4.0, y - playerHeight, playerWidth / 2.0, playerHeight);
}

void Player::set_time(sf::Time dlt_tm) {
	delta_time = dlt_tm;
}

bool Ladder_down(float x, float y) {
	if(GameMap.getMapBlock(trunc(x), trunc(y) + 1).getTypeBlock() == type_block_ladder) return true;
	return false;
}

bool Ladder_up(float x, float y) {
	if (GameMap.getMapBlock(trunc(x), trunc(y)).getTypeBlock() == type_block_ladder) return true;
	return false;
}

void Player::move(float dx, float dy) {
	moving_flag = true;
	float deltaX = dx * delta_time.asSeconds() * speed_player;
	float deltaY = dy * delta_time.asSeconds() * speed_player;

	if (dx != 0 && x+deltaX<=mapWidth-0.05 && x+deltaX>=0.05 && Y_start_climbing == -1){
		if (checkColision(deltaX) != true) x += deltaX;
	}
	else if (dx != 0 && Y_start_climbing != -1) {
		if (x + deltaX - trunc(x + deltaX) <= 0.45) {
			x = trunc(x) + 0.45;
		}
		else if (x + deltaX - trunc(x + deltaX) >= 0.55) {
			x = trunc(x) + 0.55;
		}
		else x += deltaX;
	}

	if (dy!=0 && Y_start_climbing == -1){
		if (dy == 1 && Ladder_down(x, y) == true && x - trunc(x) >= 0.45 && x - trunc(x) <= 0.55) {
			Y_start_climbing = trunc(y) + 1;
			y += deltaY;
		}
		else if (dy == -1 && Ladder_up(x, y) == true && x - trunc(x) >= 0.45 && x - trunc(x) <= 0.55) {
			Y_start_climbing = trunc(y);
			y += deltaY;
		}
	}
	else if (dy!=0 && Y_start_climbing!=-1) {
		if (y + deltaY >= Y_start_climbing + 0.99) {
			y = Y_start_climbing + 0.99;
			Y_start_climbing = -1;
		}
		else if (y + deltaY <= Y_start_climbing - 0.01) {
			y = Y_start_climbing - 0.01;
			Y_start_climbing = -1;
		}
		else y += deltaY;
	}
}

void Player::openDoor() {
	if (GameMap.getMapBlock(trunc(x), trunc(y)).getTypeBlock() == type_block_door){
		if (x - trunc(x) >= 0.35 && x - trunc(x) <= 0.65) Menu = menu_test;
	}
}

void Player::drawPlayer(sf::RenderWindow& window) {
	player_pers.setOrigin(playerWidth*sizeBlock/2.0, playerHeight*sizeBlock);
	player_pers.setPosition(x * sizeBlock, y * sizeBlock);
	player_pers.setSize(sf::Vector2f(playerWidth*sizeBlock,playerHeight*sizeBlock));
	player_pers.setTexture(&texture_person);
	window.draw(player_pers);
	hitbox.draw(window);
}


