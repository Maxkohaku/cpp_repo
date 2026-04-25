#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
using namespace std;
namespace TemperatureSensor {
class TemperatureSensorHandler
{
private:
    int _warningValue;
    function<void(int)> _callback;
    TemperatureSensorHandler(int warningValue = 80) : _warningValue(warningValue) {}
    TemperatureSensorHandler(const TemperatureSensorHandler&) = delete;
    TemperatureSensorHandler& operator=(const TemperatureSensorHandler&) = delete;
    TemperatureSensorHandler(TemperatureSensorHandler&&) = delete;
    TemperatureSensorHandler& operator=(TemperatureSensorHandler&&) = delete;

public:
    ~ TemperatureSensorHandler() = default;
    static TemperatureSensorHandler& getInstance(int temperature) {
        cout << "[call_func]|TemperatureSensorHandler::getInstance" << endl;
        static TemperatureSensorHandler instance(temperature);
        return instance;
    }
    void setWarningValue(int val) {
        _warningValue = val;
    }
    int getWarningValue() const {
        return _warningValue;
    }
    void registerCallback(function<void(int)> callback) {
        cout << "[call_func]|TemperatureSensorHandler::registerCallback" << endl;
        _callback = callback;
    }
    void monitorSensorData() {
        cout << "[call_func]|TemperatureSensorHandler::parseSensorData" << endl;
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(0, 99);
        while (true)
        {
            auto sensorData = distribution(generator);
            cout << "current temperature:" << sensorData << endl;;
            if (sensorData > _warningValue)
            {
                if (_callback)
                {
                    _callback(sensorData);
                }
            }
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }
};
};

void cbFunc(int temperature)
{
    cout << "Current Temperature(" << temperature << ") is Dangerous !!!" << endl;
}

void testFunc()
{
    auto& instance = TemperatureSensor::TemperatureSensorHandler::getInstance(80);
    instance.setWarningValue(80);
    cout << instance.getWarningValue() << endl;
    instance.registerCallback(cbFunc);
    thread monitorThread(&TemperatureSensor::TemperatureSensorHandler::monitorSensorData, &instance);
    monitorThread.join();
}

int main(int argc, char *argv[])
{
    testFunc();
    return 0;
}