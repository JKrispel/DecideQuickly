#include "algorithms/decision_trees/distance_decision/npc_follow_dt.h"
#include "decisions/decision_tree/final_decision.h"
#include "actions/run.h"
#include "actions/walk.h"
#include "actions/stop.h"

#include <chrono>
#include "utils/log_execution_time.h"

NpcFollowDT::NpcFollowDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color) :
	Npc(x, y, speed, radius, targetRef, color)
{
	// inicjalizacja unordered_map
	npcActions[NpcAction::RUN] = std::make_unique<Run>(*this, targetRef);
	npcActions[NpcAction::WALK] = std::make_unique<Walk>(*this, targetRef);
	npcActions[NpcAction::STOP] = std::make_unique<Stop>();
}

void NpcFollowDT::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, getHitboxRadius(), getColor());
}

void NpcFollowDT::update()
{
	std::string filename = "follow_dt_times.csv";
	auto start = std::chrono::high_resolution_clock::now();

	std::unique_ptr<DecisionTreeNode> decision = rootNode.makeDecision();

	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision*>(decision.get());
	int actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();

	auto end = std::chrono::high_resolution_clock::now();
	double execution_time = std::chrono::duration<double, std::milli>(end - start).count();
	logExecutionTime(execution_time, filename);

	updateFinished();
}
