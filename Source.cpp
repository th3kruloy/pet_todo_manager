#include <print>
#include <conio.h>
#include "task.h"

bool enumerate_tasks();
std::vector<task*> tasks;

int main() {
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
			std::cin >> tmp_task->task_name;
			tasks.push_back(tmp_task);
			break;
		}
		case 2:{
			enumerate_tasks();
			break;
		}
		case 3: {
			int selected_task = 0;
			int selected_parameter = 0;
			if (enumerate_tasks()) {
				system("pause");
				continue;
			}
			while (true) {
				std::println("Select your task by number: ");
				std::cin >> selected_task;
				if (selected_task <= 0 || selected_task > tasks.size()) { std::println("Wrong value: Try again"); }
				else { break; }
			}
			size_t selected_task_vector = selected_task - 1;
			std::println("What parameter you want to change? (1 - Name, 2 - Completion Status): ");
			std::cin >> selected_parameter;
			bool success = true;
			switch (selected_parameter)
			{
			case 1: {
				std::println("Enter new task name: ");
				std::cin >> tasks.at(selected_task_vector)->task_name;
				break;
			}
			case 2: {
				std::println("Enter new completion status (1 - true, 0 - false): ");
				std::cin >> tasks.at(selected_task_vector)->status;
				break;
			}
			default:
				std::println("invalid");
				break;
			}
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
			break;
		}
		case 5:
			return 0;
		default:
			std::println("Your answer is not a valid variant. Please check variants by pressing '0', and try again");
			break;
		}
		system("pause");
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