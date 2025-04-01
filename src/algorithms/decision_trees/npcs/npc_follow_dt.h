#pragma once
#include <memory>
#include <unordered_map>
#include "raylib.h"
#include "raymath.h"
#include "core/npc.h"
#include "utils/npc_action.h"
#include "algorithms/decision_trees/distance_decision/distance_decision.h"
#include "decisions/action_manager/action.h"

class NpcFollowDT : public Npc {

public:
	DistanceDecision rootNode = DistanceDecision(*this);
	// mapa możliwych Akcji, unique_ptr dla polimorfizmu
	std::unordered_map<int, std::unique_ptr<Action>> npcActions;

	NpcFollowDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);


	void draw() override;
	void update() override;
};
