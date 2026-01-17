#include "Tasks.h"

namespace zombie {
namespace tasks {

TaskObjective::TaskObjective(const std::string& desc)
    : description(desc), completed(false) {
}

Task::Task(const std::string& id, const std::string& title)
    : id(id), title(title), state(TaskState::PENDING), experienceReward(0), itemReward(0) {
}

void Task::addObjective(std::shared_ptr<TaskObjective> obj) {
    if (obj) {
        objectives.push_back(obj);
    }
}

int Task::getCompletedObjectives() const {
    int count = 0;
    for (const auto& obj : objectives) {
        if (obj && obj->isCompleted()) count++;
    }
    return count;
}

float Task::getProgress() const {
    if (objectives.empty()) return 0.0f;
    return (float)getCompletedObjectives() / objectives.size();
}

bool Task::isComplete() const {
    if (objectives.empty()) return false;
    return getProgress() >= 1.0f;
}

Quest::Quest(const std::string& id, const std::string& title)
    : id(id), title(title) {
}

void Quest::addTask(std::shared_ptr<Task> task) {
    if (task) {
        tasks.push_back(task);
    }
}

std::shared_ptr<Task> Quest::getTask(const std::string& taskId) {
    for (auto& task : tasks) {
        if (task && task->getId() == taskId) {
            return task;
        }
    }
    return nullptr;
}

float Quest::getProgress() const {
    if (tasks.empty()) return 0.0f;
    float totalProgress = 0.0f;
    for (const auto& task : tasks) {
        if (task) totalProgress += task->getProgress();
    }
    return totalProgress / tasks.size();
}

bool Quest::isComplete() const {
    if (tasks.empty()) return false;
    return getProgress() >= 1.0f;
}

std::shared_ptr<Quest> TaskManager::createQuest(const std::string& id, const std::string& title) {
    auto quest = std::make_shared<Quest>(id, title);
    quests.push_back(quest);
    return quest;
}

std::shared_ptr<Quest> TaskManager::getQuest(const std::string& questId) {
    for (auto& quest : quests) {
        if (quest && quest->getId() == questId) {
            return quest;
        }
    }
    return nullptr;
}

std::shared_ptr<Task> TaskManager::createTask(const std::string& questId, const std::string& taskId, const std::string& title) {
    auto quest = getQuest(questId);
    if (quest) {
        auto task = std::make_shared<Task>(taskId, title);
        quest->addTask(task);
        return task;
    }
    return nullptr;
}

void TaskManager::completeTask(const std::string& questId, const std::string& taskId) {
    auto quest = getQuest(questId);
    if (quest) {
        auto task = quest->getTask(taskId);
        if (task) {
            task->setState(TaskState::COMPLETED);
        }
    }
}

void TaskManager::completeQuest(const std::string& questId) {
    auto quest = getQuest(questId);
    if (quest) {
        for (const auto& task : quest->getTasks()) {
            if (task) task->setState(TaskState::COMPLETED);
        }
    }
}

void TaskManager::update(float deltaTime) {
    // Update quest progress
}

} // namespace tasks
} // namespace zombie
