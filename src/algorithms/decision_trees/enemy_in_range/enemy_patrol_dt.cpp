#include "algorithms/decision_trees/enemy_in_range/enemy_patrol_dt.h"
#include "decisions/decision_tree/final_decision.h"
#include "raymath.h"
#include "actions/chase.h"
#include "actions/change_direction.h"
#include "actions/patrol.h"

EnemyPatrolDT::EnemyPatrolDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color) :
	Npc(x, y, speed, radius, targetRef, color),
	rootNode(std::make_unique<EnemyInRange>(*this))
{
	Path& pathPtr = getPathRef();
	// patrolowana ścieżka:
	pathPtr.addPoint(50.0f, 100.0f);
	pathPtr.addPoint(50.0f, 400.0f);
	pathPtr.addPoint(50.0f, 700.0f);
	pathPtr.addPoint(50.0f, 400.0f);

	// inicjalizacja unordered_map
	npcActions[NpcAction::CHASE] = std::make_unique<Chase>(*this);
	npcActions[NpcAction::CHANGE_DIRECTION] = std::make_unique<ChangeDirection>(*this);
	npcActions[NpcAction::PATROL] = std::make_unique<Patrol>(*this);
}

void EnemyPatrolDT::draw()
{
	drawAfterUpdate();

	Vector2 position = this->getPosition();
	DrawCircle(position.x, position.y, getHitboxRadius(), getColor());
}

void EnemyPatrolDT::update()
{
	Pawn& targetRef = getTargetRef();
	// dmg debounce
	double now = GetTime();  // czas w sekundach
	bool canDmg = (now - lastDmgTime) > dmgDelay;
	bool collision = CheckCollisionCircles(targetRef.getPosition(), 
		targetRef.getHitboxRadius(), this->getPosition(), getHitboxRadius());

	if (collision  && canDmg) {
		lastDmgTime = now;
		targetRef.dealDmg(10);
	}
	// podejmij decyzję
	std::unique_ptr<DecisionTreeNode> decision = rootNode->makeDecision();
	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision<NpcAction>*>(decision.get());
	NpcAction actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();

	updateFinished();
}

