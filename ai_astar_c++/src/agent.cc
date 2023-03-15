#include "..\include\agent.h"

Agent::Agent()
{
	agent_type_ = kAgentType_Soldier;
	direction_ = kAgentMove_None;
	pos_grid_ = {0, 0};
	tail_id_closed = 0;
	state_ = AgentState_Normal;
	raw_distance_ = { 0, 0 };
	init_pos_grid_ = { 0, 0 };
}

Agent::~Agent()
{
	clear_vector();
}

void Agent::init()
{
	pos_grid_ = init_pos_grid_;
	set_position(pos_grid_.x, pos_grid_.y);
	sprite_.set_scale(sf::Vector2f(0.5f, 0.5f));

	goal_shape_.setPosition(0, 0);
	goal_shape_.setSize(sf::Vector2f(88.0f, 88.0f));
	goal_shape_.setFillColor(sf::Color(250, 0, 250, 100));

	switch (agent_type_) {
	case 0: sprite_.init("../../../data/gfx/agents/allied_engineer.bmp");
		break;
	case 1: sprite_.init("../../../data/gfx/agents/allied_medic.bmp");
		break;
	case 2: sprite_.init("../../../data/gfx/agents/allied_soldier.bmp");
		break;
	case 3: goal_shape_.setSize(sf::Vector2f(kWidthGrid, kHeightGrid));
		break;
	}
	destiny_pos_.setSize(sf::Vector2f(kWidthGrid, kHeightGrid));
	destiny_pos_.setFillColor(sf::Color(0, 255, 0, 150));
	destiny_pos_.setPosition(-kWidthGrid, -kHeightGrid);
	//destiny_pos_.setOrigin(kWidthGrid * 0.5f, kHeightGrid * 0.5f);

}

void Agent::init(const uint16_t agent_type, const int pos_x, const int pos_y)
{
	sprite_.set_scale(sf::Vector2f(0.5f, 0.5f));
	set_position(pos_x, pos_y);
	init_pos_grid_ = { pos_x, pos_y };
	goal_shape_.setPosition((pos_x - area_detect) * kWidthGrid, (pos_y - area_detect) * kHeightGrid);
	goal_shape_.setSize(sf::Vector2f(96.0f, 96.0f));
	goal_shape_.setFillColor(sf::Color(250, 255, 0, 50));

	agent_type_ = agent_type;
	switch (agent_type_) {
	case 0: sprite_.init("../../../data/gfx/agents/allied_engineer.bmp");
		break;
	case 1: sprite_.init("../../../data/gfx/agents/allied_medic.bmp");
		break;
	case 2: sprite_.init("../../../data/gfx/agents/allied_soldier.bmp");
		break;
	case 3: goal_shape_.setSize(sf::Vector2f(kWidthGrid, kHeightGrid));
		goal_shape_.setFillColor(sf::Color(240, 0, 255, 255));
		goal_shape_.setPosition(pos_x * kWidthGrid, pos_y * kHeightGrid);
		break;
	}
	destiny_pos_.setSize(sf::Vector2f(kWidthGrid, kHeightGrid));
	destiny_pos_.setPosition(-kWidthGrid, -kHeightGrid);
	destiny_pos_.setFillColor(sf::Color(0, 255, 0, 150));
	//destiny_pos_.setOrigin(kWidthGrid * 0.5f, kHeightGrid * 0.5f);

}

void Agent::randomMovement() {
	int last_direction = direction_;
	while (last_direction == direction_) {
		direction_ = rand() % 4 + 1;
	}
	direction();
	set_position(pos_grid_.x, pos_grid_.y);
}


int Agent::calculate_F(int x1, int y1, int x2, int y2, int distance)
{
	int difX = abs(x1 - x2);
	int difY = abs(y1 - y2);

	int H = (difX + difY) * 10;
	int F = distance + H;

	return F;
}

void Agent::clear_vector()
{
	openedList.clear();
	closedList.clear();
	finalList.clear();
}

void Agent::update()
{
	if (agent_type_ != kAgentType_Player) {
		switch (state_) {
		case 0: randomMovement();
			break;
		case 1: aStartMovement();
			break;
		case 2: aStartMovement();
			break;
		}
	}
	else {
		if (state_ == AgentState_PlayerRespawn) {
			clear_vector();
			set_position(init_pos_grid_.x, init_pos_grid_.y);
			state_ = AgentState_Normal;
			destiny_pos_.setPosition(-kWidthGrid, -kHeightGrid);

		}
	}
}

void Agent::calculateAStarMovement(int pos_gridX, int pos_gridY, int limit)
{
	int adapted_limit = limit * 10;
	clear_vector();
	int agentX = pos_grid_.x;
	int agentY = pos_grid_.y;
	if (agentX == pos_gridX && agentY == pos_gridY || GM_.board_->isWall(pos_array_(pos_gridX, pos_gridY)) == 1) return;
	int tail_id_opened = 0;
	tail_id_closed = 0;
	NodePathfinding node;

	node.F = 0;
	node.x = agentX;
	node.y = agentY;
	node.id = tail_id_closed;
	node.id_parent = tail_id_closed;
	node.distance = 0;
	closedList.push_back(node);
	tail_id_closed++;

	bool finish = false;
	NodePathfinding* new_node = nullptr;
	while (!finish) {
		if (agent_type_ != kAgentType_Player) {
			if (node.distance > adapted_limit && adapted_limit > 0) {
				raw_distance_ = { -1, -1 };
				return;
			}			
		}
		
		agentX = closedList[tail_id_closed - 1].x;
		agentY = closedList[tail_id_closed - 1].y;
		
		if (GM_.board_->north(pos_array_(agentX, agentY)) == 1) {
			node.distance = closedList[tail_id_closed - 1].distance + 10;
			node.x = agentX;
			node.y = agentY - 1;
			node.F = calculate_F(node.x, node.y, pos_gridX, pos_gridY, node.distance);
			
			
			node.id = tail_id_opened;
			node.id_parent = tail_id_closed - 1;
			if (node.id_parent < 0 ) node.id_parent = 0;
			int isOnClosed = 0;
			int isOnOpened = 0;
			for (int i = 0; i < tail_id_closed; ++i) {
				if (closedList[i].x == node.x && closedList[i].y == node.y) {
					isOnClosed = 1;
				}
			}
			for (int i = 0; i < tail_id_opened; ++i) {
				if (openedList[i].x == node.x && openedList[i].y == node.y) {
					isOnOpened = 1;

				}
			}
			if (isOnClosed == 0 && isOnOpened == 0) {
				openedList.push_back(node);
				tail_id_opened++;
			}
		}
		
		if (GM_.board_->south(pos_array_(agentX, agentY)) == 1) {
			node.distance = closedList[tail_id_closed - 1].distance + 10;
			node.x = agentX;
			node.y = agentY + 1;
			node.F = calculate_F(node.x, node.y, pos_gridX, pos_gridY, node.distance);
			
			node.id = tail_id_opened;
			node.id_parent = tail_id_closed - 1;
			if (node.id_parent < 0) node.id_parent = 0;
			int isOnClosed = 0;
			int isOnOpened = 0;
			for (int i = 0; i < tail_id_closed; ++i) {
				if (closedList[i].x == node.x && closedList[i].y == node.y) {
					isOnClosed = 1;
				}
			}
			for (int i = 0; i < tail_id_opened; ++i) {
				if (openedList[i].x == node.x && openedList[i].y == node.y) {
					
					isOnOpened = 1;
				}
			}
			if (isOnClosed == 0 && isOnOpened == 0) {
				openedList.push_back(node);
				tail_id_opened++;
			}
		}
		
		if (GM_.board_->west(pos_array_(agentX, agentY)) == 1) {
			node.distance = closedList[tail_id_closed - 1].distance + 10;
			node.x = agentX - 1;
			node.y = agentY;
			node.F = calculate_F(node.x, node.y, pos_gridX, pos_gridY, node.distance);
			
			node.id = tail_id_opened;
			node.id_parent = tail_id_closed - 1;
			int isOnClosed = 0;
			int isOnOpened = 0;
			for (int i = 0; i < tail_id_closed; ++i) {
				if (closedList[i].x == node.x && closedList[i].y == node.y) {
					isOnClosed = 1;
				}
			}
			for (int i = 0; i < tail_id_opened; ++i) {
				if (openedList[i].x == node.x && openedList[i].y == node.y) {
					
					isOnOpened = 1;
				}
			}
			if (isOnClosed == 0 && isOnOpened == 0) {
				openedList.push_back(node);
				tail_id_opened++;
			}
		}
		
		if (GM_.board_->east(pos_array_(agentX, agentY)) == 1) {
			node.distance = closedList[tail_id_closed - 1].distance + 10;
			node.x = agentX + 1;
			node.y = agentY;
			node.F = calculate_F(node.x, node.y, pos_gridX, pos_gridY, node.distance);
			
			node.id = tail_id_opened;
			node.id_parent = tail_id_closed - 1;
			int isOnClosed = 0;
			int isOnOpened = 0;
			for (int i = 0; i < tail_id_closed; ++i) {
				if (closedList[i].x == node.x && closedList[i].y == node.y) {
					isOnClosed = 1;
				}
			}
			for (int i = 0; i < tail_id_opened; ++i) {
				if (openedList[i].x == node.x && openedList[i].y == node.y) {
					
					isOnOpened = 1;
				}
			}
			if (isOnClosed == 0 && isOnOpened == 0) {
				openedList.push_back(node);
				tail_id_opened++;
			}
		}
		
		
		int min_f = -1;
		int it = -1;
		for (int i = 0; i < tail_id_opened; ++i) {
			if (min_f < 0) {
				min_f = openedList[i].F;
				it = i;
			}
			if (min_f > openedList[i].F) {
				min_f = openedList[i].F;
				it = i;
			}
		}

		new_node = &openedList[it];
		new_node->id = tail_id_closed;
		closedList.push_back(*new_node);
		tail_id_closed++;
		openedList.erase(openedList.begin() + it);
		tail_id_opened--;

		if (tail_id_opened == 0) { return; }

		if (closedList[tail_id_closed - 1].x == pos_gridX && closedList[tail_id_closed - 1].y == pos_gridY) {
			finish = true;
			int copy = 0;
			

			int id_copy = tail_id_closed - 1;
			while (copy == 0) {
				if (id_copy == 0) {
					copy = 1;
				}
				finalList.push_back(closedList[id_copy]);
				id_copy = closedList[id_copy].id_parent;
				size_ = finalList.size() - 1;
			}
									
		}
		
	}
	
}

void Agent::aStartMovement()
{
	if (finalList.size() > 0) {
		if (agent_type_ != kAgentType_Player) { 
			set_position(finalList[size_ - 1].x, finalList[size_ - 1].y); 
			if (size_ - 1 > 0) { size_--; }
			else { finalList.clear(); }
		}
		else { 
			set_position(finalList[size_].x, finalList[size_].y); 
			if (size_ > 0) { size_--; }
			else {
				finalList.clear();
				destiny_pos_.setPosition(-kWidthGrid, -kHeightGrid);
			}
		}

		
	}
}

void Agent::draw(sf::RenderWindow& window)
{
	sprite_.draw(window);
}

void Agent::set_position(int pos_x, int pos_y)
{
	pos_grid_.x = pos_x;
	pos_grid_.y = pos_y;
	sf::Vector2f pos = { (float)pos_grid_.x * kWidthGrid, (float)pos_grid_.y * kHeightGrid };
	
	sprite_.set_position(pos);
	if (agent_type_ != kAgentType_Player) {
		goal_shape_.setPosition((pos_x - area_detect) * kWidthGrid, (pos_y - area_detect) * kHeightGrid);
	}
	else {
		goal_shape_.setPosition(pos_x * kWidthGrid, pos_y * kHeightGrid);
	}
}

int Agent::pos_array_()
{
	return pos_grid_.y * kTotalRow + pos_grid_.x;
}

int Agent::pos_array_(int x, int y)
{
	return y * kTotalRow + x;
}

void Agent::direction()
{
	switch (direction_) {
	default:
		break;
	case 1: if (GM_.board_->north(pos_array_()) == 1)
	{
		pos_grid_.y -= kUnitMove;
	}
		  break;
	case 2: if (GM_.board_->south(pos_array_()) == 1)
	{
		pos_grid_.y += kUnitMove;
	}
		  break;
	case 4: if (GM_.board_->east(pos_array_()) == 1)
	{
		pos_grid_.x += kUnitMove;
	}
		  break;
	case 3: if (GM_.board_->west(pos_array_()) == 1)
	{
		pos_grid_.x -= kUnitMove;
	}
		  break;
	}
}
