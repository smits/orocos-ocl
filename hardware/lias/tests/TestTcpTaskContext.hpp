#ifndef TEST_TCP_TASK_CONTEXT_H
#define TEST_TCP_TASK_CONTEXT_H

#include <rtt/RTT.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/Attribute.hpp>
#include <rtt/Ports.hpp>
#include <kdl/frames.hpp>


class TestTcpTaskContext
    : public RTT::TaskContext
{
    public:
    TestTcpTaskContext(std::string name="TestTcp");
    ~TestTcpTaskContext();

    protected:
    RTT::WriteDataPort<double> velocity;
    RTT::WriteDataPort<double> rotvel;
    RTT::ReadDataPort<std::string> inpPort;
    RTT::ReadDataPort<KDL::Wrench> inWrenchPort;


    RTT::Property<double> kv;
    RTT::Property<double> kw;
    RTT::Property<double> dv;
    RTT::Property<double> dw;

    virtual bool startup();
    virtual void update();
    virtual void shutdown();
};

#endif
