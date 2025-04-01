#pragma once
#include "core/npc.h"
#include "raylib.h"
#include "unordered_map"
#include "decisions/action_manager/action.h"
#include "algorithms/decision_trees/enemy_in_range/patience_left.h"
#include "utils/npc_action.h"
#include "utils/path.h"


class EnemyPatrolDT : public Npc {

private:
	std::unique_ptr<PatienceLeft> rootNode;  // AI
	std::unordered_map<int, std::unique_ptr<Action>> npcActions; // mapa możliwych Akcji, unique_ptr dla polimorfizmu

public:
	EnemyPatrolDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);

	void draw() override;
	void update() override;

};
