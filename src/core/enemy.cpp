#include "enemy.h"
#include <decisions/decision_tree/final_decision.h>
#include <raymath.h>
#include "actions/chase.h"
#include "actions/change_direction.h"
#include "actions/patrol.h"

#include <iostream>

Enemy::Enemy(Pawn& targetRef):
	targetRef(targetRef),
	pathPtr(std::make_unique<Path>()),
	rootNode(std::make_unique<EnemyInRange>(*this))
{	
	speed = 7.0;
	aggroDelay = 0.3 * speed;
	// patrolowana ścieżka:
	pathPtr->addPoint(50.0f, 100.0f);
	pathPtr->addPoint(50.0f, 400.0f);
	pathPtr->addPoint(50.0f, 700.0f);
	pathPtr->addPoint(50.0f, 400.0f);

	// inicjalizacja unordered_map
	npcActions[NpcAction::CHASE] = std::make_unique<Chase>(*this);
	npcActions[NpcAction::CHANGE_DIRECTION] = std::make_unique<ChangeDirection>(*this);
	npcActions[NpcAction::PATROL] = std::make_unique<Patrol>(*this);
}

void Enemy::draw()
{
	// DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	// DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, radius, color);
}

void Enemy::update()
{
	// dmg debounce
	double now = GetTime();  // czas w sekundach
	bool canDmg = (now - lastDmgTime) > dmgDelay;
	bool collision = CheckCollisionCircles(targetRef.position, targetRef.radius, position, radius);
	if (collision  && canDmg) {
		lastDmgTime = now;
		targetRef.dealDmg(10);
	}
	updateDistance();	// nowe informacje o odległościach dla decyzji
	// podejmij decyzję
	std::unique_ptr<DecisionTreeNode> decision = rootNode->makeDecision();
	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision<NpcAction>*>(decision.get());
	NpcAction actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();
}

void Enemy::updateDistance()
{
	distanceToTarget = Vector2Distance(position, targetRef.position);
	distanceToPath = Vector2Distance(position, pathPtr->getPointAtIndex(pathPtr->getCurrentIndex()));
}

void Enemy::moveTo(Vector2 destination)
{
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(destination, position));

	position = Vector2Add(position, Vector2Scale(directionVector, speed));
}

Pawn& Enemy::getTargetRef()
{
	return targetRef;
}

Path& Enemy::getPathRef()
{
	return *pathPtr;
}

float Enemy::getTargetDistance()
{
	return distanceToTarget;
}

float Enemy::getPathDistance()
{
	return distanceToPath;
}

Vector2 Enemy::getPatrolPoint()
{
	Vector2 point = pathPtr->getPointAtIndex(pathPtr->getCurrentIndex());
	//std::cout << "x: " << point.x <<", y: "<< point.y << std::endl;
	return point;
}

void Enemy::setColor(Color newColor)
{
	color = newColor;
}
