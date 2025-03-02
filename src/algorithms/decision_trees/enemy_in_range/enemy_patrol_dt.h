#pragma once
#include "core/npc.h"
#include "raylib.h"
#include "unordered_map"
#include "decisions/action_manager/action.h"
#include "algorithms/decision_trees/enemy_in_range/enemy_in_range.h"
#include "utils/npc_action.h"
#include "utils/path.h"


class EnemyPatrolDT : public Npc {

private:
	std::unique_ptr<EnemyInRange> rootNode;  // AI
	// mapa możliwych Akcji, unique_ptr dla polimorfizmu
	std::unordered_map<NpcAction, std::unique_ptr<Action>> npcActions;

public:

	// cooldown:
	double lastDmgTime = 0.0;
	const double dmgDelay = 0.5;  // dmg debounce

	EnemyPatrolDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);

	void draw() override;
	void update() override;

};
