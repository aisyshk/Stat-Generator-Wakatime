#include "source_handler.h"

const wchar_t* WAKA_URL = L"https://wakatime.com/api/v1/users/@039e269a-c906-40c0-afd8-e33c509c9637/stats/all_time";
const wchar_t* DATA_FILE = L"waka_data.json";

WAKA_DATA WD{};

int source_handler::FETCH_SOURCE()
{
	//URLDownloadToFile(NULL, WAKA_URL, DATA_FILE, 0, NULL);
	std::ifstream F(DATA_FILE);
	json JSON_DATA = json::parse(F);

	PARSE_DATA(JSON_DATA);

	return 0;
}

int source_handler::PARSE_DATA(json JSON_DATA)
{
	if ((JSON_DATA["data"]["status"]) == "ok")
	{
		WD.STATUS = JSON_DATA["data"]["status"];
		WD.TOTAL_TIME = JSON_DATA["data"]["human_readable_total"];
		
		for (int i = 0; i < JSON_DATA["data"]["categories"].size(); i++)
		{
			WAKA_CATEGORY_DATA WCD{};
			WCD.CATEGORY = JSON_DATA["data"]["categories"][i]["name"];
			WCD.TIME = JSON_DATA["data"]["categories"][i]["text"];
			WCD.PERCENTAGE = JSON_DATA["data"]["categories"][i]["percent"];

			WD.CATEGORIES.push_back(WCD);
		}

		if (JSON_DATA["data"]["languages"].size() >= 5)
		{
			for (int i = 0; i < 5; i++)
			{
				WAKA_LANGUAGE_DATA WLD{};
				WLD.LANGUAGE = JSON_DATA["data"]["languages"][i]["name"];
				WLD.TIME = JSON_DATA["data"]["languages"][i]["text"];
				WLD.PERCENTAGE = JSON_DATA["data"]["languages"][i]["percent"];

				WD.LANGUAGES.push_back(WLD);
			}
		}
		else
		{
			for (int i = 0; i < JSON_DATA["data"]["languages"].size(); i++)
			{
				WAKA_LANGUAGE_DATA WLD{};
				WLD.LANGUAGE = JSON_DATA["data"]["languages"][i]["name"];
				WLD.TIME = JSON_DATA["data"]["languages"][i]["text"];
				WLD.PERCENTAGE = JSON_DATA["data"]["languages"][i]["percent"];

				WD.LANGUAGES.push_back(WLD);
			}
		}

		if (JSON_DATA["data"]["projects"].size() >= 5)
		{
			for (int i = 0; i < 5; i++)
			{
				WAKA_PROJECTS_DATA WPD{};
				WPD.PROJECT = JSON_DATA["data"]["projects"][i]["name"];
				WPD.TIME = JSON_DATA["data"]["projects"][i]["text"];
				WPD.PERCENTAGE = JSON_DATA["data"]["projects"][i]["percent"];

				WD.PROJECTS.push_back(WPD);
			}
		}
		else
		{
			for (int i = 0; i < JSON_DATA["data"]["projects"].size(); i++)
			{
				WAKA_PROJECTS_DATA WPD{};
				WPD.PROJECT = JSON_DATA["data"]["projects"][i]["name"];
				WPD.TIME = JSON_DATA["data"]["projects"][i]["text"];
				WPD.PERCENTAGE = JSON_DATA["data"]["projects"][i]["percent"];

				WD.PROJECTS.push_back(WPD);
			}
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
	std::cout << "[ Total Time ]" << std::endl << WD.TOTAL_TIME << std::endl;

	std::cout << "\n[ Categories ]" << std::endl;
	for (int i = 0; i < WD.CATEGORIES.size(); i++)
	{
		 std::cout << "[" << WD.CATEGORIES[i].CATEGORY << "] " << WD.CATEGORIES[i].TIME << std::endl;
		 CALCULATE_PROGRESS_BAR(WD.CATEGORIES[i].PERCENTAGE);
	}

	std::cout << "\n[ Languages ]" << std::endl;
	if (WD.LANGUAGES.size() > 5)
	{
		for (int i = 0; i < (WD.LANGUAGES.size() / 2); i++)
		{
			std::cout << "[" << WD.LANGUAGES[i].LANGUAGE << "] " << WD.LANGUAGES[i].TIME << std::endl;
			CALCULATE_PROGRESS_BAR(WD.LANGUAGES[i].PERCENTAGE);
		}
	}
	else
	{
		for (int i = 0; i < WD.LANGUAGES.size(); i++)
		{
			std::cout << "[" << WD.LANGUAGES[i].LANGUAGE << "] " << WD.LANGUAGES[i].TIME << std::endl;
			CALCULATE_PROGRESS_BAR(WD.LANGUAGES[i].PERCENTAGE);
		}
	}

	std::cout << "\n[ Projects ]" << std::endl;
	if (WD.PROJECTS.size() >= 5)
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "[" << WD.PROJECTS[i].PROJECT << "] " << WD.PROJECTS[i].TIME << std::endl;
			CALCULATE_PROGRESS_BAR(WD.PROJECTS[i].PERCENTAGE);
		}
	}
	else
	{
		for (int i = 0; i < WD.PROJECTS.size(); i++)
		{
			std::cout << "[" << WD.PROJECTS[i].PROJECT << "] " << WD.PROJECTS[i].TIME << std::endl;
			CALCULATE_PROGRESS_BAR(WD.PROJECTS[i].PERCENTAGE);
		}
	}

	std::cout << "\n[ Editors ] " << std::endl;
	for (int i = 0; i < WD.EDITORS.size(); i++)
	{
		std::cout << "[" << WD.EDITORS[i].EDITOR << "] " << WD.EDITORS[i].TIME << std::endl;
		CALCULATE_PROGRESS_BAR(WD.EDITORS[i].PERCENTAGE);
	}

	std::cout << "\n[ Operating Systems ] " << std::endl;
	for (int i = 0; i < WD.OS.size(); i++)
	{
		std::cout << "[" << WD.OS[i].OS << "] " << WD.OS[i].TIME << std::endl;
		CALCULATE_PROGRESS_BAR(WD.OS[i].PERCENTAGE);
	}

	return 0;
}

int source_handler::CALCULATE_PROGRESS_BAR(DOUBLE PERCENT)
{
	int SMALLER_PERCENT = PERCENT / 2;
	int MAX_PERCENT = 100 / 2;

	std::cout << "[";
	for (int i = 0; i < MAX_PERCENT; ++i)
	{
		if (i < SMALLER_PERCENT)
		{
			std::cout << "|";
		}
		/*else if (i == SMALLER_PERCENT)
		{
			std::cout << "-";
		}*/
		else
		{
			std::cout << " ";
		}
	}
	std::cout << "] " << PERCENT << "%" << std::endl;

	return 0;
}