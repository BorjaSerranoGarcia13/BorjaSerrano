#ifndef __BS_MASTERMIND_H__
#define __BS_MASTERMIND_H__ 1

#include <iostream>
#include "agent.h"

class BsMastermind {

 public:
  /// METHODS
   BsMastermind(); /**<  Constructor used to initilizate the class  */
  ~BsMastermind(); /**<   Destructor used to initilizate the class */

  /**
	* @brief add all agents to mastermind
	*/
  void addAgent(Agent* agent);

  /**
	* @brief do the math for agents to change agent state
	*/
  void calculate_distance();
  /**
	* @brief update the mastermind
	*/
  void update();

 private:
	 std::vector<Agent*> agentList_;
	 Agent* player_ = nullptr;

	 int total_agent_;
	 int total_player_;
};

#endif // __BS_MASTERMIND_H__
