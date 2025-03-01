#include "decision_trees/distance_decision/npc_follow_dt.h"
#include "decisions/decision_tree/final_decision.h"
#include "actions/run.h"
#include "actions/walk.h"
#include "actions/stop.h"


NpcFollowDT::NpcFollowDT(Pawn& target):
	Pawn(50.0f, 50.0f, 4.0f, 20.0f),
	target(target)
{
	// inicjalizacja unordered_map
	npcActions[NpcAction::RUN] = std::make_unique<Run>(*this, target);
	npcActions[NpcAction::WALK] = std::make_unique<Walk>(*this, target);
	npcActions[NpcAction::STOP] = std::make_unique<Stop>();
}

void NpcFollowDT::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, getHitboxRadius(), BLUE);
}

void NpcFollowDT::update()
{
	// aktualizuj odgległość
	rootNode.setDistanceToTarget(Vector2Distance(getPosition(), target.getPosition()));
	// podejmij decyzję
	std::unique_ptr<DecisionTreeNode> decision = rootNode.makeDecision();
	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision<NpcAction>*>(decision.get());
	NpcAction actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();

	updateFinished();
}
