#include "rclcpp/rclcpp.hpp"

class MyNode: public rclcpp::Node{

    public:
        MyNode(): Node("cpp_demo")
        {
            RCLCPP_INFO(this->get_logger(), "Hello CPP Node");s(1),std::bind(&MyNode::timerCallback, thi
            timer_ = this->create_wall_timer(std::chrono::seconds));
        }
    private:
        void timerCallback()
        {
            RCLCPP_INFO(this->get_logger(), "Hello!");
        }
        rclcpp::TimerBase::SharedPtr timer_ ;

};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    //RCLCPP_INFO(node->get_logger(), "Hello CPP Node!");
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;

}
