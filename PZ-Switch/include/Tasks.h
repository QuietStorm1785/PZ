#pragma once
#include <string>
#include <string_view>
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
 TaskObjective(std::string_view desc);
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
 Task(std::string_view id, std::string_view title);
 ~Task() = default;
 
 const std::string& getId() const { return id; }
 const std::string& getTitle() const { return title; }
 const std::string& getDescription() const { return description; }
 
 void setDescription(std::string_view desc) { description = desc; }
 
 TaskState getState() const { return state; }
 void setState(TaskState s) { state = s; }
 
 void addObjective(std::shared_ptr<TaskObjective> obj);
 int getObjectiveCount() const noexcept { return objectives.size(); }
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
 Quest(std::string_view id, std::string_view title);
 ~Quest() = default;
 
 const std::string& getId() const { return id; }
 const std::string& getTitle() const { return title; }
 
 void addTask(std::shared_ptr<Task> task);
 std::shared_ptr<Task> getTask(std::string_view taskId);
 int getTaskCount() const noexcept { return tasks.size(); }
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
 
 std::shared_ptr<Quest> createQuest(std::string_view id, std::string_view title);
 std::shared_ptr<Quest> getQuest(std::string_view questId);
 
 std::shared_ptr<Task> createTask(std::string_view questId, std::string_view taskId, std::string_view title);
 
 void completeTask(std::string_view questId, std::string_view taskId);
 void completeQuest(std::string_view questId);
 
 void update(float deltaTime);
 
private:
 TaskManager() = default;
 ~TaskManager() = default;
 
 std::vector<std::shared_ptr<Quest>> quests;
};

} // namespace tasks
} // namespace zombie
