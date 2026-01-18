#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace zombie {
namespace tasks {

enum class TaskState {
 PENDING,
 ACTIVE,
 COMPLETED,
 FAILED,
 ABANDONED
};

class TaskObjective {
public:
 TaskObjective(const std::string& desc);
 ~TaskObjective() = default;
 
 const std::string& getDescription() const { return description; }
 bool isCompleted() const { return completed; }
 void setCompleted(bool c) { completed = c; }
 
private:
 std::string description;
 bool completed;
};

class Task {
public:
 Task(const std::string& id, const std::string& title);
 ~Task() = default;
 
 const std::string& getId() const { return id; }
 const std::string& getTitle() const { return title; }
 const std::string& getDescription() const { return description; }
 
 void setDescription(const std::string& desc) { description = desc; }
 
 TaskState getState() const { return state; }
 void setState(TaskState s) { state = s; }
 
 void addObjective(std::shared_ptr<TaskObjective> obj);
 int getObjectiveCount() const { return objectives.size(); }
 int getCompletedObjectives() const;
 
 float getProgress() const;
 bool isComplete() const;
 
 void setReward(int exp, int items) { experienceReward = exp; itemReward = items; }
 int getExperienceReward() const { return experienceReward; }
 int getItemReward() const { return itemReward; }
 
private:
 std::string id;
 std::string title;
 std::string description;
 TaskState state;
 std::vector<std::shared_ptr<TaskObjective>> objectives;
 
 int experienceReward;
 int itemReward;
};

class Quest {
public:
 Quest(const std::string& id, const std::string& title);
 ~Quest() = default;
 
 const std::string& getId() const { return id; }
 const std::string& getTitle() const { return title; }
 
 void addTask(std::shared_ptr<Task> task);
 std::shared_ptr<Task> getTask(const std::string& taskId);
 int getTaskCount() const { return tasks.size(); }
 const std::vector<std::shared_ptr<Task>>& getTasks() const { return tasks; }
 
 float getProgress() const;
 bool isComplete() const;
 
private:
 std::string id;
 std::string title;
 std::vector<std::shared_ptr<Task>> tasks;
};

class TaskManager {
public:
 static TaskManager& getInstance() {
 static TaskManager instance;
 return instance;
 }
 
 std::shared_ptr<Quest> createQuest(const std::string& id, const std::string& title);
 std::shared_ptr<Quest> getQuest(const std::string& questId);
 
 std::shared_ptr<Task> createTask(const std::string& questId, const std::string& taskId, const std::string& title);
 
 void completeTask(const std::string& questId, const std::string& taskId);
 void completeQuest(const std::string& questId);
 
 void update(float deltaTime);
 
private:
 TaskManager() = default;
 ~TaskManager() = default;
 
 std::vector<std::shared_ptr<Quest>> quests;
};

} // namespace tasks
} // namespace zombie
