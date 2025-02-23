#pragma once
#include "core/pawn.h"
#include <raylib.h>
#include <unordered_map>
#include <decisions/action_manager/action.h>
#include "drzewa_decyzyjne/enemy_in_range/enemy_in_range.h"
#include "utils/npc_action.h"
#include "utils/path.h"


class Enemy : public Pawn {

private:

	Color color = ORANGE;
	Pawn& targetRef;
	std::unique_ptr<Path> pathPtr;
	float distanceToTarget{};
	float distanceToPath{};
	std::unique_ptr<EnemyInRange> rootNode;  // AI
	// mapa możliwych Akcji, unique_ptr dla polimorfizmu
	std::unordered_map<NpcAction, std::unique_ptr<Action>> npcActions;

public:
	// debounce:
	double changeDirectionTime = 0.0;  // ostatnia Akcja CHANGE_DIRECTION
	const double debounceDelay = 0.5;  // debounce
	double lostAggroTime = 0.0;  // ostatnie stracenie aggro
	double aggroDelay;	// cooldown dla CHASE
	// cooldown:
	double lastDmgTime = 0.0;
	const double dmgDelay = 0.5;  // dmg debounce

	Enemy(Pawn& target);

	void draw() override;
	void update() override;
	void updateDistance();
	void moveTo(Vector2 destination);

	Pawn& getTargetRef();
	Path& getPathRef();
	float getTargetDistance();
	float getPathDistance();
	Vector2 getPatrolPoint();
	void setColor(Color newColor);
};
