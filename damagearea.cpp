#pragma once

#include "manager.h"

void dm_lineone::update(){
	auto &vec = manager::get().enemy_.v;
	auto &target = vec.end();
	double dist = 9999;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::CircleAndLine(obj.x, obj.y, obj.r, x, y, x + r * cos(angle), y + r * sin(angle)) &&
			dist > Func::dist(obj.x, obj.y, x, y)	){
			dist = Func::dist(obj.x, obj.y, x, y);
			target = i;
		}		
	}
	if (dist < 9000){
		(**target).hp -= damage;
		Func::addVector(knockbackdist, angle, (**target).x, (**target).y);
		manager::get().effect_.add<enemy_bloodsplash>((**target).x, (**target).y);
		auto p = manager::get().effect_.add<gunflash>(x, y);
		p->angle = angle;
		p->exratex = dist / 32.0;
	}
	else{
		auto p = manager::get().effect_.add<gunflash>(x, y);
		p->angle = angle;
		p->exratex = r / 32.0;
	}
}

void dm_lineall::update(){
	auto &vec = manager::get().enemy_.v;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::CircleAndLine(obj.x, obj.y, obj.r, x, y, x + r * cos(angle), y + r * sin(angle))){
			obj.hp -= damage;
			manager::get().effect_.add<enemy_bloodsplash>(obj.x, obj.y);
			Func::addVector(knockbackdist, angle, obj.x, obj.y);
		}
	}
	auto p = manager::get().effect_.add<gunflash>(x, y);
	p->angle = angle;
	p->exratex = r / 32.0;
}


void dm_circle::update(){
	auto &vec = manager::get().enemy_.v;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::Circles(obj.x, obj.y, obj.r, x, y, r)){
			obj.hp -= damage;
			Func::addVector(x, y, obj.x, obj.y, knockbackdist, obj.x, obj.y);
		}
	}
}

void dm_tlitbox::update(){
	auto &vec = manager::get().enemy_.v;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::BroadLinePointAng(obj.x, obj.y, x, y, r, angle, broad + obj.r)){
			manager::get().effect_.add<enemyhitfire>(obj.x, obj.y);
			obj.hp -= damage;
			Func::addVector(knockbackdist, angle, obj.x, obj.y);
		}
	}
}


void dm_chainsaw::update(){
	auto &vec = manager::get().enemy_.v;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::BroadLinePointAng(obj.x, obj.y, x, y, r + obj.r, angle, broad + obj.r)){
			manager::get().effect_.add<enemy_bloodsplash>(obj.x, obj.y);
			obj.hp -= damage;

			double ex = obj.x, ey = obj.y;
			Func::addVector(-0.8 * obj.r, angle, ex, ey);
			auto p = manager::get().effect_.add<slashef>(ex, ey);

			Func::addVector(knockbackdist, angle, obj.x, obj.y);
		}
	}
}

