#include <iostream>
#include <windows.h>

using namespace std;

class Machine
{
	class State* current;
public:
	Machine();
	void setCurrent(State* s)
	{
		current = s;
	}
	void IDLE();
	void SENSING();
	void PROCESSING();
};

class State
{
public:
	virtual void IDLE(Machine* M)
	{
		cout << "Nodes are in IDLE state..." << endl;
	}
	virtual void SENSING(Machine* M)
	{
		cout << "Nodes are in SENSING state..." << endl;
	}
	virtual void PROCESSING(Machine* M)
	{
		cout << "Nodes are in PROCESSING state..." << endl;
	}

};

void Machine::IDLE()
{
	current->IDLE(this);
}

void Machine::SENSING()
{
	current->SENSING(this);
}

void Machine::PROCESSING()
{
	current->PROCESSING(this);
}

class idle : public State
{
public:
	idle()
	{
		cout << "idle state constructor" << endl;
	};
	~idle()
	{
		cout << "destructor idle state" << endl;
	};
	void SENSING(Machine* M);

};

class sensing : public State
{
public:
	sensing()
	{
		cout << "sensing state constructor" << endl;
	};
	~sensing()
	{
		cout << "destructor sensing state" << endl;
	};
	void PROCESSING(Machine* M);

};

class processing : public State
{
public:
	processing()
	{
		cout << "processing state constructor" << endl;
	};
	~processing()
	{
		cout << "destructor processing state" << endl;
	};

	void IDLE(Machine* M);

};

void idle::SENSING(Machine* M)
{
	cout << "idle state to sensing state" << endl;
	M->setCurrent(new sensing());
	delete this;
	cout << "Reading the sensor values!" << endl;
	Sleep(2000);
	cout << "Getting data from the Humidity Sensor.." << endl;
	int a = 0;
	while (a++ < 6)
	{
		int HUMIDITY = (rand() % (100 - 20 + 5)) + 20;
		cout << "The Humidity Sensor Value: " << HUMIDITY << endl;
		Sleep(1000);
	}

	Sleep(2000);
	cout << "Getting data from the Temperature Sensor.." << endl;
	int b = 0;
	while (b++ < 6)
	{
		int temp = (rand() % (100 - 22 + 5)) + 22;
		cout << "The Temperature Sensor Value: " << temp << endl;
		Sleep(1000);
	}
	Sleep(2000);
	cout << "Values are ready for PROCESSING!" << endl;
	M->PROCESSING();
}

void sensing::PROCESSING(Machine* M)
{
	cout << "sensing state to processing state" << endl;
	M->setCurrent(new processing());
	delete this;
	cout << "processing the sensor data!" << endl;
	Sleep(2000);
	cout << "processing the humidity sensor data.." << endl;
	Sleep(2000);
	cout << "processing the temperature sensor data.." << endl;
	Sleep(2000);
	cout << "Back to idle state!" << endl;
	Sleep(2000);
	M->IDLE();
}

void processing::IDLE(Machine* M)
{
	cout << "processing state to idle state!" << endl;
	M->setCurrent(new idle());
	delete this;
}

Machine::Machine()
{
	current = new idle();
	cout << '\n';
}

int main()
{
	Machine finitestatemachine;
	char userPreference;
	while (1)
	{
		cout << "System is in IDLE state. Do you want to begin SENSING state? (y/n): ";
		cin >> userPreference;
		if (char(toupper(userPreference)) == 'Y')
		{
			finitestatemachine.SENSING();
			Sleep(2000);
		}
		else if (char(toupper(userPreference)) == 'N')
		{
			continue;
		}
		else
		{
			cout << "Entered an Invalid character!" << endl;
		}
	}
	return 0;
}
