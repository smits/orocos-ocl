#include "IOComponent.hpp"


#include "ocl/ComponentLoader.hpp"
ORO_CREATE_COMPONENT( OCL::IOComponent )

using namespace Orocos;

namespace OCL
{

    void IOComponent::createAPI()
    {
        // Adding a single channel:
        this->addOperation("addAnalogInput", &IOComponent::addAnalogInput, this, RTT::ClientThread).doc("Add an analog input as data port").arg("PortName", "The name of the port to create.").arg("Inputname", "The name of the AnalogInInterface device to use.").arg("Channel", "The channel of the device to use.");
        this->addOperation("addAnalogOutput", &IOComponent::addAnalogOutput, this, RTT::ClientThread).doc("Add an analog input as data port").arg("PortName", "The name of the port to create.").arg("Outputname", "The name of the AnalogOutInterface device to use.").arg("Channel", "The channel of the device to use.");
        this->addOperation("addDigitalInput", &IOComponent::addDigitalInput, this, RTT::ClientThread).doc("Add an digital input").arg("Name", "The name of the new input.").arg("Inputname", "The name of the DigitalInInterface device to use.").arg("Channel", "The channel of the device to use.").arg("Invert", "Set to true to invert this bit.");
        this->addOperation("addDigitalOutput", &IOComponent::addDigitalOutput, this, RTT::ClientThread).doc("Add an digital input").arg("Name", "The name of the new output.").arg("Outputname", "The name of the DigitalOutInterface device to use.").arg("Channel", "The channel of the device to use.").arg("Invert", "Set to true to invert this bit.");

        // Add whole device:
        this->addOperation("addAnalogInputs", &IOComponent::addAnalogInInterface, this, RTT::ClientThread).doc("Add an AnalogInInterface as an array data port").arg("PortName", "The name of the port to create.").arg("Inputname", "The name of the AnalogInInterface device to use.");

        this->addOperation("addAnalogOutputs", &IOComponent::addAnalogOutInterface, this, RTT::ClientThread).doc("Add an AnalogOutInterface as an array data port").arg("PortName", "The name of the port to create.").arg("Outputname", "The name of the AnalogOutInterface device to use.");

        this->addOperation("addInputChannel", &IOComponent::addInputChannel, this, RTT::ClientThread).doc("Add an analog input signal into InputValues").arg("Pos", "The position of the signal in ChannelValues.").arg("InputName", "The name of the AnalogInInterface device to use.").arg("Channel", "The channel of the device to use.");
        this->addOperation("addOutputChannel", &IOComponent::addOutputChannel, this, RTT::ClientThread).doc("Add an analog input signal into OutputValues").arg("Pos", "The position of the signal in ChannelValues.").arg("OutputName", "The name of the AnalogOutInterface device to use.").arg("Channel", "The channel of the device to use.");

        // Digital/Analog querries
        this->addOperation("switchOn", &IOComponent::switchOn, this, RTT::ClientThread).doc("Switch A Digital Output on").arg("Name", "The Name of the DigitalOutput.");
        this->addOperation("isOn", &IOComponent::isOn, this, RTT::ClientThread).doc("Inspect the status of a Digital Input or Output.").arg("Name", "The Name of the Digital Input or Output.");
        this->addOperation("switchOff", &IOComponent::switchOff, this, RTT::ClientThread).doc("Switch A Digital Output off").arg("Name", "The Name of the DigitalOutput.");
        this->addOperation("value", &IOComponent::value, this, RTT::ClientThread).doc("Inspect the value of an Analog Input or Output.").arg("Name", "The Name of the Analog Input or Output.");
        this->addOperation("rawValue", &IOComponent::rawValue, this, RTT::ClientThread).doc("Inspect the raw value of an Analog Input or Output.").arg("Name", "The Name of the Analog Input or Output.");
        this->addOperation("inputChannels", &IOComponent::getInputChannels, this, RTT::ClientThread).doc("Get the number of channels this component monitors.");
        this->addOperation("outputChannels", &IOComponent::getOutputChannels, this, RTT::ClientThread).doc("Get the number of channels this component outputs.");
    }
}
