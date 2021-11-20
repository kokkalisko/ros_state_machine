#include "ros/ros.h"
#include "ros_state_machine/move_example_state_machine.h"

int main(int argc, char **argv)
{
    ROS_INFO("Starting state machine");

    ros::init(argc, argv, "state_machine_node");
    MoveStateMachine stateMachine;
    stateMachine.DefineTransitions();

    const Trigger TriggerVector[] = { Trigger::MOVE, Trigger::STOP, Trigger::RETREAT };
    std::string operation;

    while (true)
    {
        ROS_INFO("Current robot state: %s", ResolveState(stateMachine.GetCurrentState()).c_str());
        for ( auto trigger: TriggerVector )
            std::cout << static_cast<int>(trigger) << ": " << ResolveTrigger(trigger) << std::endl;

        std::cin >> operation;
        ProcessTransitionResult result = stateMachine.ProcessTrigger(static_cast<Trigger>(stoi(operation)));
        ROS_INFO("%s", ResolveTransitionResult(result).c_str());
    }

    return 0;
}