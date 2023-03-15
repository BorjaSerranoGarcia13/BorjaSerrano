#ifndef __AGENT_H__
#define __AGENT_H__ 1

#include "common_def.h"
#include "bs_texture.h"
#include "bs_game_manager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <math.h>  
#include <list>

const float kMove = 16.0f;
const int kMaxCheck = 50;
const float area_detect = 5.0f;
const int max_distance = 6;
const int max_distance_after_seen = 24;

enum AgentType {
	kAgentType_Engineer = 0,
	kAgentType_Medic = 1,
	kAgentType_Soldier = 2,
	kAgentType_Player = 3,
};

enum AgentMove {
	kAgentMove_None = 0,
	kAgentMove_Up = 1,
	kAgentMove_Down = 2,
	kAgentMove_Left = 3,
	kAgentMove_Right = 4,
};

enum AgentState {
	AgentState_Normal = 0,
	AgentState_PlayerSeen = 1,
	AgentState_PlayerEscaped = 2,
	AgentState_PlayerRespawn = 3,
};

struct NodePathfinding {
	int x;
	int y;
	int id;
	int id_parent;
	int distance;
	int F;

};

/**
/* Class agent
/* manage evrything from the agents (type, state, movement..)
*/
class Agent {
public:

	Agent();
	~Agent();
	
	/**
	* @brief constructor of class
    */
	void init();
	/**
	* @brief copy constructor of class
	*/
	void init(const uint16_t agent_type, const int pos_x, const int pos_y);
	/**
	* @brief random movement
	*/
	void randomMovement();
	/**
	* @brief do the math for A* algorithm
	*/
	void calculateAStarMovement(int pos_gridX, int pos_gridY, int limit);
	/**
	* @brief do the movement step by step after the math
	*/
	void aStartMovement();
	
	/**
	* @brief draw agent
	*/
	void draw(sf::RenderWindow& window);
	/**
	* @brief set position agent from a grid to coord in screen
	*/
	void set_position(int pos_x, int pos_y);
	/**
	* @brief return the pos in the array
	*/
	int pos_array_();
	/**
	* @brief return any given pos in the array
	*/
	int pos_array_(int x, int y);
	/**
	* @brief do the moves for the agent
	*/
	void direction();

	/**
	* @brief maths for F in A* algorithm
	*/
	int calculate_F(int x1, int y1, int x2, int y2, int distance);
	/**
	* @brief clears the vectors, openedList closedList finalList
	*/
	void clear_vector();
	/**
	* @brief updates the agent
	*/
	void update();


	int agent_type_;
	uint8_t direction_;
	int state_;
	sf::Vector2i raw_distance_;

	sf::Vector2i pos_grid_;

	sf::Vector2i init_pos_grid_;

	sf::RectangleShape goal_shape_;
	sf::RectangleShape destiny_pos_;

	BsTexture sprite_;

	BsGameManager& GM_ = BsGameManager::getInstance();

	std::vector<NodePathfinding> openedList;
	std::vector<NodePathfinding> closedList;
	std::vector<NodePathfinding> finalList;
	int tail_id_closed = 0;
	int size_ = 0;
};

#endif  // __AGENT_H__
