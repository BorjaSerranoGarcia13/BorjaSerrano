
#include "../include/bs_mastermind.h"

BsMastermind::BsMastermind() {
	total_agent_ = 0;
	total_player_ = 0;
	player_ = nullptr;
}

BsMastermind::~BsMastermind() {
	player_ = nullptr;
	delete player_;
	agentList_.clear();
}

void BsMastermind::addAgent(Agent* agent)
{
	if (agent->agent_type_ == kAgentType_Player) {
		player_ = agent;
		total_player_++;
	}
	else {
		agentList_.push_back(agent);
		total_agent_++;
	}

}

void BsMastermind::calculate_distance()
{
	int sumatory_distance = 0;
	for (int i = 0; i < total_agent_; ++i) {
		agentList_[i]->raw_distance_ = { abs(agentList_[i]->pos_grid_.x - player_->pos_grid_.x),
				abs(agentList_[i]->pos_grid_.y - player_->pos_grid_.y) };
		
		sumatory_distance = agentList_[i]->raw_distance_.x + agentList_[i]->raw_distance_.y;
		if (sumatory_distance <= 1) {
			player_->state_ = AgentState_PlayerRespawn;
		}
		
		switch (agentList_[i]->state_) {
		case AgentState_Normal: if (agentList_[i]->raw_distance_.x <= max_distance && agentList_[i]->raw_distance_.y <= max_distance) {
									agentList_[i]->calculateAStarMovement(player_->pos_grid_.x, player_->pos_grid_.y, max_distance_after_seen);
									if (agentList_[i]->raw_distance_.x > 0) {
										agentList_[i]->state_ = AgentState_PlayerSeen;
									}
								}
			break;
		case AgentState_PlayerSeen: if (agentList_[i]->raw_distance_.x <= max_distance && agentList_[i]->raw_distance_.y <= max_distance) {
										agentList_[i]->calculateAStarMovement(player_->pos_grid_.x, player_->pos_grid_.y, max_distance_after_seen);
									}
									if (agentList_[i]->raw_distance_.x > max_distance || agentList_[i]->raw_distance_.y > max_distance) {
										agentList_[i]->state_ = AgentState_PlayerEscaped;
									}
			break;
		case AgentState_PlayerEscaped: agentList_[i]->calculateAStarMovement(agentList_[i]->init_pos_grid_.x, agentList_[i]->init_pos_grid_.y, -1);
										if (agentList_[i]->init_pos_grid_ == agentList_[i]->pos_grid_) {
											agentList_[i]->state_ = AgentState_Normal;
										}
			break;
		}
		
	}
}

void BsMastermind::update()
{
	calculate_distance();
}
