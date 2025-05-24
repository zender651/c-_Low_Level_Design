#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Enums
enum ParkingSlotType { TwoWheeler, Compact, Medium, Large };
enum VehicleCategory { Bike, Hatchback, Sedan, SUV, Bus };

// Forward declarations
class Ticket;
class Vehicle;
class ParkingSlot;
class ParkingFloor;
class ParkingLot;

// Vehicle
class Vehicle {
    string vehicleNo;
    VehicleCategory category;

public:
    Vehicle(string no, VehicleCategory cat) : vehicleNo(no), category(cat) {}
    VehicleCategory getCategory() const { return category; }
    string getNumber() const { return vehicleNo; }
};

// ParkingSlot
class ParkingSlot {
    string name;
    bool isAvailable = true;
    ParkingSlotType type;
    Vehicle* vehicle = nullptr;

public:
    ParkingSlot(string n, ParkingSlotType t) : name(n), type(t) {}

    void addVehicle(Vehicle* v) {
        vehicle = v;
        isAvailable = false;
    }

    void removeVehicle() {
        vehicle = nullptr;
        isAvailable = true;
    }

    bool getAvailability() const { return isAvailable; }
    ParkingSlotType getSlotType() const { return type; }
    Vehicle* getVehicle() const { return vehicle; }
};

// Ticket
class Ticket {
    static int idCounter;
    int id;
    Vehicle* vehicle;
    ParkingSlot* parkingSlot;
    long long startTime;

public:
    Ticket(Vehicle* v, ParkingSlot* slot)
        : vehicle(v), parkingSlot(slot), id(++idCounter) {
        startTime = currentTimeMillis();
    }

    static long long currentTimeMillis() {
        return chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    }

    static Ticket* createTicket(Vehicle* v, ParkingSlot* p) {
        return new Ticket(v, p);
    }

    Vehicle* getVehicle() const { return vehicle; }
    ParkingSlot* getParkingSlot() const { return parkingSlot; }
    long long getStartTime() const { return startTime; }
};

int Ticket::idCounter = 0;

// ParkingFloor
class ParkingFloor {
    string name;
    map<ParkingSlotType, map<string, ParkingSlot*>> parkingSlots;

public:
    ParkingFloor(string n, map<ParkingSlotType, map<string, ParkingSlot*>> slots)
        : name(n), parkingSlots(slots) {}

    ParkingSlot* getSlotAndPark(Vehicle* vehicle) {
        ParkingSlotType type = getCorrectSlotType(vehicle->getCategory());
        for (auto& [id, slot] : parkingSlots[type]) {
            if (slot->getAvailability()) {
                slot->addVehicle(vehicle);
                return slot;
            }
        }
        return nullptr;
    }

    static ParkingSlotType getCorrectSlotType(VehicleCategory category) {
        switch (category) {
            case Bike: return TwoWheeler;
            case Hatchback:
            case Sedan: return Compact;
            case SUV: return Medium;
            case Bus: return Large;
        }
        return Compact;
    }
};

// ParkingLot Singleton
class ParkingLot {
    string name;
    string address;
    vector<ParkingFloor*> floors;
    static ParkingLot* instance;

    ParkingLot(string n, string addr, vector<ParkingFloor*> f)
        : name(n), address(addr), floors(f) {}

public:
    static ParkingLot* getInstance(string n, string addr, vector<ParkingFloor*> f) {
        if (!instance)
            instance = new ParkingLot(n, addr, f);
        return instance;
    }

    void addFloor(ParkingFloor* floor) {
        floors.push_back(floor);
    }

    Ticket* assignTicket(Vehicle* v) {
        ParkingSlot* slot = findSlotAndPark(v);
        if (!slot) return nullptr;
        return Ticket::createTicket(v, slot);
    }

    double scanAndPay(Ticket* ticket) {
        long long endTime = Ticket::currentTimeMillis();
        ticket->getParkingSlot()->removeVehicle();
        int duration = static_cast<int>((endTime - ticket->getStartTime()) / 1000);

        ParkingSlotType type = ticket->getParkingSlot()->getSlotType();
        double rate = 1.0;

        switch (type) {
            case TwoWheeler: rate = 0.5; break;
            case Compact: rate = 1.0; break;
            case Medium: rate = 1.5; break;
            case Large: rate = 2.0; break;
        }

        return duration * rate;
    }

private:
    ParkingSlot* findSlotAndPark(Vehicle* v) {
        for (auto* floor : floors) {
            ParkingSlot* slot = floor->getSlotAndPark(v);
            if (slot) return slot;
        }
        return nullptr;
    }
};

ParkingLot* ParkingLot::instance = nullptr;

// -------------------------- MAIN ----------------------------

int main() {
    // Create parking slots for Floor 1
    map<string, ParkingSlot*> compactSlotsF1 = {
        {"C1", new ParkingSlot("C1", Compact)},
        {"C2", new ParkingSlot("C2", Compact)}
    };
    map<string, ParkingSlot*> bikeSlotsF1 = {
        {"B1", new ParkingSlot("B1", TwoWheeler)}
    };

    map<ParkingSlotType, map<string, ParkingSlot*>> floor1Slots = {
        {Compact, compactSlotsF1},
        {TwoWheeler, bikeSlotsF1}
    };

    ParkingFloor* floor1 = new ParkingFloor("Ground", floor1Slots);

    // Create parking slots for Floor 2
    map<string, ParkingSlot*> mediumSlotsF2 = {
        {"M1", new ParkingSlot("M1", Medium)},
        {"M2", new ParkingSlot("M2", Medium)}
    };
    map<string, ParkingSlot*> largeSlotsF2 = {
        {"L1", new ParkingSlot("L1", Large)}
    };

    map<ParkingSlotType, map<string, ParkingSlot*>> floor2Slots = {
        {Medium, mediumSlotsF2},
        {Large, largeSlotsF2}
    };

    ParkingFloor* floor2 = new ParkingFloor("First", floor2Slots);

    // Initialize parking lot
    vector<ParkingFloor*> floors = { floor1, floor2 };
    ParkingLot* lot = ParkingLot::getInstance("MyLot", "Main Street", floors);

    // Create a list of vehicles with different categories
    vector<Vehicle*> vehicles = {
        new Vehicle("KA-01-BIKE1", Bike),
        new Vehicle("KA-01-HATCH1", Hatchback),
        new Vehicle("KA-01-SEDAN1", Sedan),
        new Vehicle("KA-01-SUV1", SUV),
        new Vehicle("KA-01-BUS1", Bus),
        new Vehicle("KA-01-BIKE2", Bike) // This should fail if no extra TwoWheeler slots
    };

    vector<Ticket*> tickets;

    for (Vehicle* v : vehicles) {
        Ticket* t = lot->assignTicket(v);
        if (t) {
            cout << "✅ Vehicle " << v->getNumber() << " parked successfully.\n";
            tickets.push_back(t);
        } else {
            cout << "❌ No slot available for vehicle " << v->getNumber() << "\n";
        }
    }

    // Simulate wait
    this_thread::sleep_for(chrono::seconds(2));

    // Scan and pay for all parked vehicles
    for (Ticket* t : tickets) {
        double price = lot->scanAndPay(t);
        cout << "💰 Parking fee for " << t->getVehicle()->getNumber() << ": ₹" << price << endl;
    }

    return 0;
}
