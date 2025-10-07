#include <print>
#include <conio.h>
#include <limits>
#include <nlohmann/json.hpp>
#include <fstream>
#include "task.h"

using json = nlohmann::json;

bool enumerate_tasks();
bool save();
bool load();

std::vector<task*> tasks;

int main() {
	load();
	while (true) {
		system("cls");
		std::string input;
		int user_variant = 0;
		std::print("Welcome to Pet. (0 - for help)\nChoose action: ");
		std::cin >> input;
		try {
			user_variant = std::stoi(input);
		}
		catch (const std::invalid_argument& e) {
			system("cls");
			std::println("Your answer is not a number. Please try again");
			system("pause");
			continue;
		}

		system("cls");
		switch (user_variant)
		{
		case 0: {
			std::cout <<
				"1 - Create new task" << std::endl <<
				"2 - Watch all tasks" << std::endl <<
				"3 - Change name or status of tasks" << std::endl <<
				"4 - Delete task" << std::endl <<
				"5 - Exit" << std::endl;
			break;
		}
		case 1: {
			task* tmp_task = new task;
			std::print("Write your task: ");
			std::getline(std::cin >> std::ws, tmp_task->task_name);
			tasks.push_back(tmp_task);
			save();
			break;
		}
		case 2:{
			enumerate_tasks();
			break;
		}
		case 3: {
			int selected_task_position = 0;
			int selected_parameter = 0;
			if (enumerate_tasks()) {
				system("pause");
				continue;
			}
			while (true) {
				std::println("Select your task by number: ");
				std::cin >> selected_task_position;
				if (selected_task_position <= 0 || selected_task_position > tasks.size()) { 
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::println("Wrong value: Try again");
				}
				else { break; }
			}
			auto* selected_task = tasks.at(selected_task_position - 1);
			std::println("What parameter you want to change? (1 - Name, 2 - Completion Status): ");
			std::cin >> selected_parameter;
			bool success = true;
			system("cls");
			switch (selected_parameter)
			{
			case 1: {
				std::println("Enter new task name: ");
				std::getline(std::cin >> std::ws, selected_task->task_name);
				break;
			}
			case 2: {
				bool success = false;
				while (!success) {
					bool status;
					std::println("Enter new completion status (true, or false): ");
					std::cin >> std::boolalpha >> status;
					if (std::cin.fail()) {
						system("cls");
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::println("Enter a valid value, and try again");
						system("pause");
						continue;
					}
					selected_task->status = status;
					success = true;
				}
				break;
			}
			default:
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::println("invalid");
				break;
			}
			save();
			break;
		}
		case 4: {
			int selected_task = 0;
			if (enumerate_tasks()) {
				system("pause");
				continue;
		}
			std::println("Select task that you want to delete: ");
			std::cin >> selected_task;

			tasks.erase(tasks.begin() + (selected_task - 1));
			system("cls");
			std::println("Done!");
			save();
			break;
		}
		case 5:
			return 0;
		default:
			std::println("Your answer is not a valid variant. Please check variants by pressing '0', and try again");
			break;
		}
		system("pause");
		std::cin.clear();
	}
}

bool enumerate_tasks() {
	if (tasks.size() <= 0) {
		std::println("There is no active tasks!");
		return true;
	}

	for (size_t _S = 0; _S < tasks.size(); _S++) {
		std::cout <<
			"Task " << _S + 1 << ": " << std::endl <<
			" Task Name: " << tasks.at(_S)->task_name << std::endl <<
			" Status: " << std::boolalpha << tasks.at(_S)->status << std::endl;
	}
	return false;
}

bool save() {
	json _J;
	std::string filename = "tasks.json";
	for (size_t _S = 0; _S < tasks.size(); _S++) {
		task* current = tasks.at(_S);
		_J[std::format("task{}", _S)]["name"] = current->task_name;
		_J[std::format("task{}", _S)]["status"] = current->status;
	}
	try {
		std::ofstream file(filename);
		if (!file.is_open()) {
			return false;
		}

		file << _J.dump(4);
		file.close();

		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

bool load() {
	std::string filename = "tasks.json";
	try {
		std::ifstream file(filename);
		if (!file.is_open()) {
			return false;
		}

		json _J;
		file >> _J;
		file.close();

		for (size_t _S = 0; _S < _J.size(); _S++) {
			task* tmp_task = new task;
			tmp_task->task_name = _J[std::format("task{}", _S)]["name"];
			tmp_task->status = _J[std::format("task{}", _S)]["status"];
			tasks.push_back(tmp_task);
		}

		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}