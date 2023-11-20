#pragma once
#include <iostream>
#include "player.h"
#include "GlobalVariablesOfClasses.h"
#include "GlobalVariablesForResources.h"
#include "general.h"
#include "Hitbox.h"

//оброка вин€ткових ситуац≥й врахована

// зм≥нна дл€ в≥дкладки
bool Hitbox::showHitbox = true; // зм≥нювати лише в код≥, зм≥ни дл€ розробник≥в

// конструктор класа гравц€
Player::Player() {
	Player_set_source();
}

// встановленн€ поатковоњ позиц≥њ гравц€
void Player::Player_set_source() {
	x = 0.3;
	y = mapHeight - 0.01;
	interval_walking.setInterval(100);
	interval_standing.setInterval(1000);
}

// перев≥рка кол≥з≥њ гравц€ з об'Їктами GameMap
bool Player::checkColision(float dx) {
	if (dx>0) return GameMap.collisionMap(Hitbox(hitbox.getRect().left, hitbox.getRect().top, hitbox.getRect().width + dx, hitbox.getRect().height));
	else return GameMap.collisionMap(Hitbox(hitbox.getRect().left + dx, hitbox.getRect().top, hitbox.getRect().width - dx, hitbox.getRect().height));
}

void Player::skipFrame() {
	interval_standing.update();
	interval_walking.update();
	if (prev_state != state) {
		interval_standing.restart();
		interval_walking.restart();
		if (state == 0) frame = 0;
		if (state == 1) frame = 2;
	}
	if (interval_standing.getValue()) {
		if (state == 0) {if (++frame > 1) frame = 0;}
	}
	if (interval_walking.getValue()) {
		if (state == 1) {if (++frame > 7) frame = 2;}
	}
	prev_state = state;
}

// оновленн€ гравц€
void Player::Update() {
	if (mov_flag == false && Y_start_climbing != -1) {
		float deltaY = 0.5 * delta_time.asSeconds() * speed_player;
		if (y + deltaY >= Y_start_climbing + 0.99) {
			y = Y_start_climbing + 0.99;
			Y_start_climbing = -1;
		}
		else y += deltaY;
	}
	else {
		mov_flag = false;
	}
	skipFrame();
	set_pos_hitbox_player();
	state = 0;
}

// встановленн€ х≥тбоксу гравц€ в≥дносно гравц€
void Player::set_pos_hitbox_player(){
	hitbox.setSizePos(x - playerWidth / 4.0, y - playerHeight, playerWidth / 2.0, playerHeight);
}

// метод дл€ отриманн€ часу останнього кадру
void Player::set_time(sf::Time dlt_tm) {
	delta_time = dlt_tm;
}

// метод дл€ перев≥рки руху вниз по драбин≥
bool Ladder_down(float x, float y) {
	if(GameMap.getMapBlock(trunc(x), trunc(y) + 1).getTypeBlock() == type_block_ladder) return true;
	return false;
}

// метод дл€ перев≥рки руху вверх по драбин≥
bool Ladder_up(float x, float y) {
	if (GameMap.getMapBlock(trunc(x), trunc(y)).getTypeBlock() == type_block_ladder) return true;
	return false;
}

// метод дл€ руху гравц€
void Player::move(float dx, float dy) {
	mov_flag = true;
	if (dx != 0) state = 1;
	if (dx > 0) rotate = false;
	if (dx < 0) rotate = true;

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

// метод дл€ в≥дкритт€ дверей гравцем
void Player::openDoor() {
	if (GameMap.getMapBlock(trunc(x), trunc(y)).getTypeBlock() == type_block_door){
		if (x - trunc(x) >= 0.35 && x - trunc(x) <= 0.65) {
			exam.start_test(GameMap.getMapBlock(trunc(x), trunc(y)).getTheme());
		}
	}
}

// метод дл€ рендеру гравц€ на в≥кн≥
void Player::drawPlayer(sf::RenderWindow& window) {
	scrollX = -x * sizeBlock + window.getSize().x/2.0;
	scrollY = -(y - 1.125) * sizeBlock;

	if (scrollX > 0) { scrollX = 0; }
	if (scrollY > 0) { scrollY = 0; }
	
	if (mapHeight * sizeBlock + scrollY < window.getSize().y) { scrollY = 0-(mapHeight * sizeBlock - float(window.getSize().y)); }
	if (mapWidth * sizeBlock + scrollX < window.getSize().x) { scrollX = 0-(mapWidth * sizeBlock - float(window.getSize().x)); }

	if (rotate) player_pers.setTexture(&texture_person_left);
	else player_pers.setTexture(&texture_person);
	float wf = texture_person.getSize().x / 8;
	float hf = texture_person.getSize().y;
	player_pers.setOrigin(playerWidth*sizeBlock/2.0, playerHeight*sizeBlock);
	player_pers.setPosition(x * sizeBlock + scrollX, y * sizeBlock + scrollY);
	player_pers.setSize(sf::Vector2f(playerWidth*sizeBlock,playerHeight*sizeBlock));
	player_pers.setTextureRect(sf::Rect<int>(frame * wf, 0, wf, hf));
	window.draw(player_pers);
	hitbox.draw(window);
}


