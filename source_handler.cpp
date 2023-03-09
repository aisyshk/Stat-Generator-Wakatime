#include "source_handler.h"

const wchar_t* WAKA_URL = L"https://wakatime.com/api/v1/users/039e269a-c906-40c0-afd8-e33c509c9637/stats/all_time";
const wchar_t* SAVE_FILE = L"C:\\waka_data.json";

WAKA_DATA WD{};

int source_handler::FETCH_SOURCE()
{
	if (S_OK == URLDownloadToFile(NULL, WAKA_URL, SAVE_FILE, 0, NULL))
	{
		std::cout << "Downloaded Wakatime data. >> " << &SAVE_FILE << std::endl;
		PARSE_DATA();
	}
	else { std::cerr << "Failed to download data."; }

	return 0;
}

int source_handler::PARSE_DATA()
{
	std::ifstream F(SAVE_FILE);
	json JSON_DATA = json::parse(F);

	if ((JSON_DATA["data"]["status"]) == "ok")
	{
		WD.STATUS = JSON_DATA["data"]["status"];
		WD.DAILY_AVERAGE = JSON_DATA["data"]["human_readable_daily_average"];
		
		for (int i = 0; i < JSON_DATA["data"]["categories"].size(); i++)
		{
			WAKA_CATEGORY_DATA WCD{};
			WCD.CATEGORY = JSON_DATA["data"]["categories"][i]["name"];
			WCD.TIME = JSON_DATA["data"]["categories"][i]["text"];
			WCD.PERCENTAGE = JSON_DATA["data"]["categories"][i]["percent"];

			WD.CATEGORIES.push_back(WCD);
		}

		for (int i = 0; i < JSON_DATA["data"]["languages"].size(); i++)
		{
			WAKA_LANGUAGE_DATA WLD{};
			WLD.LANGUAGE = JSON_DATA["data"]["languages"][i]["name"];
			WLD.TIME = JSON_DATA["data"]["languages"][i]["text"];
			WLD.PERCENTAGE = JSON_DATA["data"]["languages"][i]["percent"];

			WD.LANGUAGES.push_back(WLD);
		}

		for (int i = 0; i < JSON_DATA["data"]["projects"].size(); i++)
		{
			WAKA_PROJECTS_DATA WPD{};
			WPD.PROJECT = JSON_DATA["data"]["projects"][i]["name"];
			WPD.TIME = JSON_DATA["data"]["projects"][i]["text"];
			WPD.PERCENTAGE = JSON_DATA["data"]["projects"][i]["percent"];

			WD.PROJECTS.push_back(WPD);
		}

		for (int i = 0; i < JSON_DATA["data"]["editors"].size(); i++)
		{
			WAKA_EDITORS_DATA WED{};
			WED.EDITOR = JSON_DATA["data"]["editors"][i]["name"];
			WED.TIME = JSON_DATA["data"]["editors"][i]["text"];
			WED.PERCENTAGE = JSON_DATA["data"]["editors"][i]["percent"];

			WD.EDITORS.push_back(WED);
		}

		for (int i = 0; i < JSON_DATA["data"]["operating_systems"].size(); i++)
		{
			WAKA_OS_DATA WOD{};
			WOD.OS = JSON_DATA["data"]["operating_systems"][i]["name"];
			WOD.TIME = JSON_DATA["data"]["operating_systems"][i]["text"];
			WOD.PERCENTAGE = JSON_DATA["data"]["operating_systems"][i]["percent"];

			WD.OS.push_back(WOD);
		}

		WD.IS_UP_TO_DATE = JSON_DATA["data"]["is_up_to_date"];

	}
	else
	{
		std::cerr << "Error fetching data" << std::endl;
	}

	return 0;
}

int source_handler::OUTPUT_DATA()
{
	std::cout << "Status: " << WD.STATUS << 
		" | Daily Avg.: " << WD.DAILY_AVERAGE <<
		"\nUp to date?: " << WD.IS_UP_TO_DATE << std::endl << std::endl << std::endl;

	std::cout << "\nCategories: " << std::endl;
	for (int i = 0; i < WD.CATEGORIES.size(); i++)
	{
		 std::cout << WD.CATEGORIES[i].CATEGORY << " | " << WD.CATEGORIES[i].TIME << " | " << WD.CATEGORIES[i].PERCENTAGE << std::endl;
	}

	std::cout << "\nLanguages: " << std::endl;
	if (WD.LANGUAGES.size() > 5)
	{
		for (int i = 0; i < (WD.LANGUAGES.size() / 2); i++)
		{
			std::cout << WD.LANGUAGES[i].LANGUAGE << " | " << WD.LANGUAGES[i].TIME << " | " << WD.LANGUAGES[i].PERCENTAGE << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < WD.LANGUAGES.size(); i++)
		{
			std::cout << WD.LANGUAGES[i].LANGUAGE << " | " << WD.LANGUAGES[i].TIME << " | " << WD.LANGUAGES[i].PERCENTAGE << std::endl;
		}
	}

	std::cout << "\nProjects: " << std::endl;
	for (int i = 0; i < WD.PROJECTS.size(); i++)
	{
		std::cout << WD.PROJECTS[i].PROJECT << " | " << WD.PROJECTS[i].TIME << " | " << WD.PROJECTS[i].PERCENTAGE << std::endl;
	}

	std::cout << "\nEditors: " << std::endl;
	for (int i = 0; i < WD.EDITORS.size(); i++)
	{
		std::cout << WD.EDITORS[i].EDITOR << " | " << WD.EDITORS[i].TIME << " | " << WD.EDITORS[i].PERCENTAGE << std::endl;
	}

	std::cout << "\nOperating Systems: " << std::endl;
	for (int i = 0; i < WD.OS.size(); i++)
	{
		std::cout << WD.OS[i].OS << " | " << WD.OS[i].TIME << " | " << WD.OS[i].PERCENTAGE << std::endl;
	}

	return 0;
}