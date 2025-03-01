#pragma once
#include <memory>
#include <unordered_map>
#include <raylib.h>
#include <raymath.h>
#include "core/pawn.h"
#include "utils/npc_action.h"
#include "decision_trees/distance_decision/distance_decision.h"
#include "decisions/action_manager/action.h"

class NpcFollowDT : public Pawn {

public:
	Pawn& target;
	DistanceDecision rootNode = DistanceDecision(Vector2Distance(this->getPosition(), target.getPosition()));
	// mapa możliwych Akcji, unique_ptr dla polimorfizmu
	std::unordered_map<NpcAction, std::unique_ptr<Action>> npcActions;

	NpcFollowDT(Pawn& target);

	void draw() override;
	void update() override;
};
