#include <windows.h>

#pragma comment(lib, "xinput.lib")
#include <xinput.h>

#include <iostream>

#define MAX_PLAYERS = 4	//maximum of 4 players

//show some info about the device's batteries
void PrintBatteryInfo(const int&);
//process the buttons
void ProcessFaceButtons(const XINPUT_STATE&);
void ProcessPadButtons(const XINPUT_STATE&);
void ProcessShoulderButtons(const XINPUT_STATE&);
void ProcessThumbButtons(const XINPUT_STATE&);
//process the triggers
void ProcessTriggers(const XINPUT_STATE&, const int& PlayerID);
//process the thumbsticks/joysticks
void ProcessThumbs(const XINPUT_STATE&, const int& PlayerID);
//process back and start button
void ProcessBackAndStartButtons(const XINPUT_STATE&);


//program entry point
int main()
{
	XINPUT_STATE State;
	int PlayerID = 0;	//0 - first user

	if (XInputGetState(PlayerID, &State) != ERROR_SUCCESS){	//device not found
		std::cout<<"Error: a device is not found for this user: "<<PlayerID<<" !\n";
	} 
	else {	//device is found
		std::cout<<"Success: a device is found for this user: "<<PlayerID<<" !\n";
	
		//prin out info about the batteries
		PrintBatteryInfo(PlayerID);

		//main loop
		while (1){
			if (XInputGetState(PlayerID, &State) == ERROR_SUCCESS){	//make sure device is connected

				//process the face buttons
				ProcessFaceButtons(State);
				//process the pad buttons
				ProcessPadButtons(State);
				//process the shoulder buttons
				ProcessShoulderButtons(State);
				//process the thumb buttons
				ProcessThumbButtons(State);
				//process the triggers
				ProcessTriggers(State, PlayerID);
				//process the thumbsticks/joysticks
				ProcessThumbs(State, PlayerID);
				//process back and start button
				ProcessBackAndStartButtons(State);
			}
		}

	}

	
	std::cin.get();
	return 0;
}

//print out info about the batteries
void PrintBatteryInfo(const int& PlayerID)
{
	XINPUT_BATTERY_INFORMATION bi;
	XInputGetBatteryInformation(PlayerID, XINPUT_FLAG_GAMEPAD, &bi);	//second argument: 0 for all devices(gamepad, wheel...), XINPUT_FLAG_GAMEPAD only for gamepad (xbox360 controller)

	std::cout<<"Battery info:\n";

	//check battery type
	switch (bi.BatteryType){
		case BATTERY_TYPE_DISCONNECTED:
			std::cout<<"\tBattery Type: BATTERY_TYPE_DISCONNECTED\n";
			break;
		case BATTERY_TYPE_WIRED:
			std::cout<<"\tBattery Type: BATTERY_TYPE_WIRED\n";
			break;
		case BATTERY_TYPE_ALKALINE:
			std::cout<<"\tBattery Type: BATTERY_TYPE_ALKALINE\n";
			break;
		case BATTERY_TYPE_NIMH:
			std::cout<<"\tBattery Type: BATTERY_TYPE_NIMH\n";
			break;
		case BATTERY_TYPE_UNKNOWN:
			std::cout<<"\tBattery Type: BATTERY_TYPE_UNKNOWN\n";
			break;
	}

	//check battery level
	switch (bi.BatteryLevel){
		case BATTERY_LEVEL_EMPTY:
			std::cout<<"\tBattery Level: BATTERY_LEVEL_EMPTY\n";
			break;
		case BATTERY_LEVEL_LOW:
			std::cout<<"\tBattery Level: BATTERY_LEVEL_LOW\n";
			break;
		case BATTERY_LEVEL_MEDIUM:
			std::cout<<"\tBattery Level: BATTERY_LEVEL_MEDIUM\n";
			break;
		case BATTERY_LEVEL_FULL:
			std::cout<<"\tBattery Level: BATTERY_LEVEL_FULL\n";
			break;
	}
}


//process the buttons
//face buttons
void ProcessFaceButtons(const XINPUT_STATE& State)
{
	//process the face buttons
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_A){
		std::cout<<"pressing: A\n";
	}

	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_B){
		std::cout<<"pressing: B\n";
	}

	if(State.Gamepad.wButtons & XINPUT_GAMEPAD_X){
		std::cout<<"pressing: X\n";
	}

	if(State.Gamepad.wButtons & XINPUT_GAMEPAD_Y){
		std::cout<<"pressing: Y\n";
	}
}
//dpad buttons
void ProcessPadButtons(const XINPUT_STATE& State)
{
	//process the dpad buttons
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP){
		std::cout<<"pressing: DPAD_UP\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
		std::cout<<"pressing: DPAD_DOWN\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT){
		std::cout<<"pressing: DPAD_LEFT\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
		std::cout<<"pressing: DPAD_RIGHT\n";
	}
}
//shoulder buttons
void ProcessShoulderButtons(const XINPUT_STATE& State)
{
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER){
		std::cout<<"pressing: LEFT_SHOULDER\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
		std::cout<<"pressing: RIGHT_SHOULDER\n";
	}
}
//thumb buttons
void ProcessThumbButtons(const XINPUT_STATE& State)
{
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB){
		std::cout<<"pressing: LEFT_THUMB\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB){
		std::cout<<"pressing: RIGHT_THUMB\n";
	}
}
//process the triggers
void ProcessTriggers(const XINPUT_STATE& State, const int& PlayerID)
{
	XINPUT_VIBRATION Vibration;
	Vibration.wLeftMotorSpeed = 0;
	Vibration.wRightMotorSpeed = 0;

	//left trigger
	if (State.Gamepad.bLeftTrigger > 0){
		Vibration.wLeftMotorSpeed = (WORD)(65535.0f * (State.Gamepad.bLeftTrigger / 255.0f));	//trigger values: 255 is full pressure, 0 no pressure.
	}
	//right trigger
	if (State.Gamepad.bRightTrigger > 0){
		Vibration.wRightMotorSpeed = (WORD)(65535.0f * (State.Gamepad.bRightTrigger / 255.0f));
	}

	XInputSetState(PlayerID, &Vibration);
}
//process the thumbsticks/joysticks
void ProcessThumbs(const XINPUT_STATE& State, const int& PlayerID)
{
	//TODO:
	/*

	thumb: 32.767 full right, 0 center, -32,768 full left

	*/
}
//process back and start button
void ProcessBackAndStartButtons(const XINPUT_STATE& State)
{
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK){
		std::cout<<"pressing: BACK\n";
	}
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_START){
		std::cout<<"pressing: START\n";
	}
}