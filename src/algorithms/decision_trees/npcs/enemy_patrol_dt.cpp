﻿#include "algorithms/decision_trees/npcs/enemy_patrol_dt.h"
#include "decisions/decision_tree/final_decision.h"
#include "raymath.h"
#include "actions/chase.h"
#include "actions/change_direction.h"
#include "actions/patrol.h"
#include "actions/lose_patience.h"

#include <chrono>
#include "perfo/log_execution_time.h"
#include <iostream>


EnemyPatrolDT::EnemyPatrolDT(float x, float y, float speed, float radius, Pawn& targetRef, Color color) :
	Npc(x, y, speed, radius, targetRef, color),
	rootNode(std::make_unique<PatienceLeft>(*this))
{
	std::string filename = "patrol_dt";
	auto start = std::chrono::high_resolution_clock::now();
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
	npcActions[NpcAction::LOSE_PATIENCE] = std::make_unique<LosePatience>(*this);

	auto end = std::chrono::high_resolution_clock::now();
	double execution_time = std::chrono::duration<double, std::milli>(end - start).count();
	logExecutionTime(execution_time, filename);
	std::cout << "init time saved!";
}

void EnemyPatrolDT::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	if (!noPatience()) {
		DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
		DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f * (getPatience() / 100), 5.0f, YELLOW);
	}
	DrawCircle(position.x, position.y, getHitboxRadius(), getColor());
}

void EnemyPatrolDT::update()
{

	std::unique_ptr<DecisionTreeNode> decision = rootNode->makeDecision();

	// wykonaj Akcję
	auto* finalDecision = dynamic_cast<FinalDecision*>(decision.get());
	int actionType = finalDecision->getActionType();
	npcActions[actionType]->execute();

	updateFinished();
}
