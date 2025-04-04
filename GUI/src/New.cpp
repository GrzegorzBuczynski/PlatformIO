#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// ===============================
// Tools – pojedyncze funkcje
// ===============================
class Tools {
public:
    static void printMessage(const std::string& msg) {
        std::cout << "Message: " << msg << std::endl;
    }

    static void multiply(int a, int b) {
        std::cout << a << " * " << b << " = " << a * b << std::endl;
    }

    static void delay(int ms) {
        std::cout << "Delaying for " << ms << "ms..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
};

// ===============================
// Task – definicja co ma być zrobione
// ===============================
enum class ActionType {
    Print,
    Multiply,
    Delay
};

struct Action {
    ActionType type;
    std::vector<std::string> params;
};

class Task {
public:
    void addPrint(const std::string& message) {
        actions.push_back({ActionType::Print, {message}});
    }

    void addMultiply(int a, int b) {
        actions.push_back({ActionType::Multiply, {std::to_string(a), std::to_string(b)}});
    }

    void addDelay(int ms) {
        actions.push_back({ActionType::Delay, {std::to_string(ms)}});
    }

    const std::vector<Action>& getActions() const {
        return actions;
    }

private:
    std::vector<Action> actions;
};

// ===============================
// Executor – wykonuje taski
// ===============================
class Executor {
public:
    void run(const Task& task) {
        for (const auto& action : task.getActions()) {
            switch (action.type) {
                case ActionType::Print:
                    Tools::printMessage(action.params[0]);
                    break;
                case ActionType::Multiply:
                    Tools::multiply(std::stoi(action.params[0]), std::stoi(action.params[1]));
                    break;
                case ActionType::Delay:
                    Tools::delay(std::stoi(action.params[0]));
                    break;
            }
        }
    }
};

// ===============================
// Główna funkcja
// ===============================
int main() {
    Task task;
    task.addPrint("Start");
    task.addMultiply(6, 7);
    task.addDelay(1000);
    task.addPrint("Koniec");

    Executor exec;
    exec.run(task);

    return 0;
}
