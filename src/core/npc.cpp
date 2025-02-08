#include "npc.h"
#include <decisions/decision_tree/final_decision.h>
#include "actions/run.h"
#include "actions/walk.h"
#include "actions/stop.h"
// pomiary wydajności:
#include <chrono>
#include <iostream>

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
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, radius, BLUE);
}

void Npc::update()
{
	// aktualizuj odgległość
	rootNode.setDistanceToTarget(Vector2Distance(position, target.position));
	// czas start
	auto start = std::chrono::high_resolution_clock::now();
	// podejmij decyzję
	std::unique_ptr<DecisionTreeNode> decision = rootNode.makeDecision();
	// czas stop
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	// std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision<NpcAction>*>(decision.get());
	NpcAction actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();
}
// Pawn position bez settera!
