
#include "TaskManager.h"

int TaskManager::getNextId() {
    return m_id++;
}

/**
     * @brief Assigns a task to a person.
     *
     * @param personName The name of the person to whom the task will be assigned.
     * @param task The task to be assigned.
     */
void TaskManager::assignTask(const string &personName, const Task &task) {
    Task newTask = task;
    newTask.setId(getNextId());

    bool personFound = false;
    for (Person & person : m_list) {
        if (person.getName() == personName) {
            person.assignTask(newTask);
            personFound = true;
            break;
        }
    }
    if (!personFound) {
        if (m_peopleAmount >= MAX_PERSONS) {
            throw std::runtime_error("");
        }
        m_list[m_peopleAmount] = Person(personName);
        m_list[m_peopleAmount].assignTask(newTask);
        m_peopleAmount++;
    }
}

/**
 * @brief Completes the highest priority task assigned to a person.
 *
 * @param personName The name of the person who will complete the task.
 */
void TaskManager::completeTask(const string &personName) {
    for (Person& person : m_list) {
        if (person.getName() == personName) {
            person.completeTask();
            break;
        }
    }
}

/**
 * @brief Bumps the priority of all tasks of a specific type.
 *
 * @param type The type of tasks whose priority will be bumped.
 * @param priority The amount by which the priority will be increased.
 */
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority < 0) {
        return;
    }
    for (Person& person : m_list) {
        SortedList<Task> oldTasks = person.getTasks();
        SortedList<Task> newTasks = oldTasks.apply([type, priority](const Task& task) {
            if (task.getType() == type) {
                Task temp = Task(task.getPriority() + priority,
                                 task.getType(), task.getDescription());
                temp.setId(task.getId());
                return temp;
            } else {
                return task;
            }
        });
        person.setTasks(newTasks);
    }
}

/**
 * @brief Prints all employees and their tasks.
 */
void TaskManager::printAllEmployees() const {
    for (int i = 0; i < m_peopleAmount; i++) {
        std::cout << m_list[i] << std::endl;
    }
}

/**
 * @brief Prints all tasks of a specific type.
 *
 * @param type The type of tasks to be printed.
 */
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> temp;
    for (Person const& person : m_list) {
        SortedList<Task> filteredTasks = person.getTasks().filter([type](const Task& task) {
            return task.getType() == type;
        });
        for (const Task& task : filteredTasks) {
            temp.insert(task);
        }
    }
    for (const Task& task : temp) {
        std::cout << task << std::endl;
    }
}

/**
 * @brief Prints all tasks assigned to all employees.
 */
void TaskManager::printAllTasks() const {
    SortedList<Task> temp;
    for (Person const& person : m_list) {
        for (const Task& task : person.getTasks()) {
            temp.insert(task);
        }
    }
    for (const Task& task : temp) {
        std::cout << task << std::endl;
    }
}
