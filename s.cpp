#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Machine {
protected:
    string machineId;
    bool powerState;

public:
    static int totalMachines;

    Machine(string id) : machineId(id), powerState(true) {
        totalMachines++;
    }

    virtual ~Machine() {
        totalMachines--;
    }

    virtual void executeTask() = 0;
};

int Machine::totalMachines = 0;

class SensorModule : virtual public Machine {
protected:
    double readingAccuracy;

public:
    SensorModule(string id, double accuracy) : Machine(id), readingAccuracy(accuracy) {}

    void calibrateSensor() {
        cout << "Sensor [" << machineId << "] calibrated to " << readingAccuracy << "% accuracy." << endl;
    }
};

class ActuatorModule : virtual public Machine {
protected:
    double maxLoadCapacityKg;

public:
    ActuatorModule(string id, double load) : Machine(id), maxLoadCapacityKg(load) {}

    void testActuator() {
        cout << "Actuator [" << machineId << "] tested for " << maxLoadCapacityKg << " kg load." << endl;
    }
};

class SmartSortingRobot : public SensorModule, public ActuatorModule {
private:
    int itemsProcessed;

public:
    SmartSortingRobot(string id, double accuracy, double load, int items)
        : Machine(id),
          SensorModule(id, accuracy),
          ActuatorModule(id, load),
          itemsProcessed(items) {}

    ~SmartSortingRobot() {
        cout << "Robot " << machineId << " decommissioned after processing " << itemsProcessed << " items." << endl;
    }

    void executeTask() override {
        cout << "\n--- Smart Sorting Robot Report: " << machineId << " ---" << endl;
        calibrateSensor();
        testActuator();
        cout << "Total Items Processed: " << itemsProcessed << endl;
        cout << "Status: Operational" << endl;
    }
};

int main() {
    Machine* unit = new SmartSortingRobot("SR-99X", 99.4, 150.0, 4820);

    unit->executeTask();

    cout << "\nActive Machines on Floor: " << Machine::totalMachines << endl;

    delete unit;

    cout << "Active Machines After Teardown: " << Machine::totalMachines << endl;

    return 0;
}
