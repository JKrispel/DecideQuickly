#include "drzewa_decyzyjne/distance_decision/npc.h"
#include <decisions/decision_tree/final_decision.h>
#include "actions/run.h"
#include "actions/walk.h"
#include "actions/stop.h"


Npc::Npc(Pawn& target):
	target(target)
{
	// inicjalizacja unordered_map
	npcActions[NpcAction::RUN] = std::make_unique<Run>(*this, target);
	npcActions[NpcAction::WALK] = std::make_unique<Walk>(*this, target);
	npcActions[NpcAction::STOP] = std::make_unique<Stop>();
}

void Npc::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, radius, BLUE);
}

void Npc::update()
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
