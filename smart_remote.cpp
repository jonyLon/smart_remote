#include <iostream>
#include <string>
#include <vector>
using namespace std;

__interface IDevice {
    void power();
    void plus();
    void minus();
    void next();
    void prev();
    void showInfo();
};
class TV : public IDevice{
    bool on = false;
    size_t volume = 50;
    size_t chanal = 1;
    size_t chanalMax = 125;
    string brand;
public:
    TV(string brand = "Unknown") : brand{brand} {}
    ~TV() {}
    void power() {
        if (on) {
            on = false;
        }
        else {
            on = true;
        }
    }
    void plus() {

        if (volume < 100)
        {
            volume+=5;
        }
    }
    void minus() {

        if (volume > 0)
        {
            volume-=5;
        }
    }
    void next() {

        if (chanal < chanalMax)
        {
            chanal++;
        }
    }
    void prev() {

        if (chanal > 1)
        {
            chanal--;
        }
    }
    void showInfo() {
        if (on) {
            cout << "Brand: " << brand <<"\t Current state: on" << "\t Current chanal: " << chanal << "\t Carrent volume: " << volume << endl;
            return;
        }
        cout << "Brand: " << brand << "\t Current state: off" << endl;
    }
};


enum Modes {
    heating, cooling, turbo, sleep
};

class AirConditioner : public IDevice{
    bool on = false;
    string brand;
    int temperature = 16;
    Modes mod = heating; 
    string modes[4] = { "heating", "cooling", "turbo", "sleep" };
public:
    AirConditioner(string brand = "Unknown") : brand{ brand } {}
    ~AirConditioner() {}
    void power() {
        if (on) {
            on = false;
        }
        else {
            on = true;
        }
    }
    void plus() {

        if (temperature < 25)
        {
            temperature++;
        }
    }
    void minus() {

        if (temperature > 16)
        {
            temperature--;
        }
    }
    void next() {
        if (mod == sleep)
        {
            mod = heating;
            return;
        }
        int current = mod;
        mod = static_cast<Modes>(++current);
    }
    void prev() {
        if (mod == heating)
        {
            mod = sleep;
            return;
        }
        int current = mod;
        mod = static_cast<Modes>(--current);
    }
    void showInfo() {
        if (on) {
            cout << "Brand: " << brand << "\t Current state: on" << "\t Current mod: " << modes[(int)mod] << "\t Current temperature: " << temperature << endl;
            return;
        }
        cout << "Brand: " << brand << "\t Current state: off" << endl;
    }
};

class SmartRemote {
    vector<IDevice*> devices;
    IDevice* cur_device;
public:
    SmartRemote() = default;
    SmartRemote(IDevice* cur_device) : cur_device{cur_device} {
        add(cur_device);
    }
    void add(IDevice* device) {
        devices.push_back(device);
    }
    void showAll() const {
        int counter = 0;
        for (auto x : devices) {
            cout << "Index: " << counter << "\tType: " << typeid(*x).name() << endl;
            x->showInfo();
            counter++;
        }
    }
    void showCurrentDevice() const {
        cout << "Current device: " << endl;
        cout << "Type: " << typeid(*cur_device).name() << endl;
        cur_device->showInfo();
    }

    void changeСurrentDevice(const int& index){
        if (index < 0 && index > devices.size())
        {
            cerr << "Invalid index" << endl;
            return;
        }
        cur_device = devices[index];
    }

    void power() {
        cur_device->power();
    };
    void plus() {
        cur_device->plus();
    };
    void minus() {
        cur_device->minus();
    };
    void next() {
        cur_device->next();
    };
    void prev() {
        cur_device->prev();
    };
    void showInfo(){
        cout << "Type: " << typeid(*cur_device).name() << endl;
        cur_device->showInfo();
    }

};

int main()
{
    TV LG("LG");
    AirConditioner GM("Goodman");

    SmartRemote controler(&LG);
    controler.add(&GM);
    controler.showAll();

    controler.showCurrentDevice();
    controler.power();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.next();
    controler.prev();
    controler.prev();
    controler.showInfo();






    controler.changeСurrentDevice(1);
    controler.showCurrentDevice();
    controler.power();
    controler.next();
    controler.prev();
    controler.prev();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.plus();
    controler.showInfo();
}


