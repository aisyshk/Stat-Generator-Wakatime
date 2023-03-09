#include <iostream>
#include <string>
#include <fstream>
#include <urlmon.h>
#include <vector>
#include <nlohmann/json.hpp>

#pragma comment(lib, "urlmon.lib")

using namespace nlohmann;

class WAKA_CATEGORY_DATA;
class WAKA_LANGUAGE_DATA;
class WAKA_PROJECTS_DATA;
class WAKA_EDITORS_DATA;
class WAKA_OS_DATA;

#pragma once
class source_handler
{
public:
	static int FETCH_SOURCE();
	static int PARSE_DATA(json JSON_DATA);
	static int OUTPUT_DATA();
	static int CALCULATE_PROGRESS_BAR(DOUBLE PERCENT);
};

class WAKA_DATA
{
public:
	std::string STATUS;
	std::vector<WAKA_CATEGORY_DATA> CATEGORIES;
	std::string TOTAL_TIME;
	std::vector <WAKA_LANGUAGE_DATA> LANGUAGES;
	std::vector<WAKA_PROJECTS_DATA> PROJECTS;
	std::vector<WAKA_EDITORS_DATA> EDITORS;
	std::vector<WAKA_OS_DATA> OS;
	BOOL IS_UP_TO_DATE;
};

class WAKA_CATEGORY_DATA
{
public:
	std::string CATEGORY;
	std::string TIME;
	DOUBLE PERCENTAGE;
};

class WAKA_LANGUAGE_DATA
{
public:
	std::string LANGUAGE;
	std::string TIME;
	DOUBLE PERCENTAGE;
};

class WAKA_PROJECTS_DATA
{
public:
	std::string PROJECT;
	std::string TIME;
	DOUBLE PERCENTAGE;
};

class WAKA_EDITORS_DATA
{
public:
	std::string EDITOR;
	std::string TIME;
	DOUBLE PERCENTAGE;
};

class WAKA_OS_DATA
{
public:
	std::string OS;
	std::string TIME;
	DOUBLE PERCENTAGE;
};