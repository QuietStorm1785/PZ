#include "SearchNodeCity.h"
#include "GoalNodeCity.h"

SearchNodeCity::SearchNodeCity(const std::string& name, std::shared_ptr<SearchNodeCity> parent, std::shared_ptr<GoalNodeCity> goal)
    : name_(name), parent_(parent), goal_(goal) {
    fillAdjacencyMatrix();
}

std::shared_ptr<ISearchNode> SearchNodeCity::getParent() const {
    return parent_;
}

void SearchNodeCity::getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const {
    auto it = adjacencyMatrix_.find(name_);
    if (it != adjacencyMatrix_.end()) {
        for (const auto& kv : it->second) {
            outSuccessors.push_back(std::make_shared<SearchNodeCity>(kv.first, std::make_shared<SearchNodeCity>(*this), goal_));
        }
    }
}

double SearchNodeCity::h() const {
    return name_ == goal_->getName() ? 0.0 : 1.0;
}

double SearchNodeCity::c(const std::shared_ptr<ISearchNode>& other) const {
    auto o = std::dynamic_pointer_cast<SearchNodeCity>(other);
    if (!o) return 1.0;
    auto it = adjacencyMatrix_.find(name_);
    if (it != adjacencyMatrix_.end()) {
        auto jt = it->second.find(o->name_);
        if (jt != it->second.end()) return jt->second;
    }
    return 1.0;
}

int SearchNodeCity::keyCode() const {
    std::hash<std::string> h;
    return static_cast<int>(h(name_));
}

bool SearchNodeCity::equals(const std::shared_ptr<ISearchNode>& other) const {
    auto o = std::dynamic_pointer_cast<SearchNodeCity>(other);
    return o && o->name_ == name_;
}

int SearchNodeCity::hashCode() const {
    return keyCode();
}

std::string SearchNodeCity::getName() const { return name_; }

void SearchNodeCity::fillAdjacencyMatrix() {
    adjacencyMatrix_["Saarbrücken"]["Kaiserslautern"] = 70;
    adjacencyMatrix_["Saarbrücken"]["Karlsruhe"] = 145;
    adjacencyMatrix_["Kaiserslautern"]["Frankfurt"] = 103;
    adjacencyMatrix_["Kaiserslautern"]["Ludwigshafen"] = 53;
    adjacencyMatrix_["Karlsruhe"]["Heilbronn"] = 84;
    adjacencyMatrix_["Frankfurt"]["Würzburg"] = 116;
    adjacencyMatrix_["Ludwigshafen"]["Würzburg"] = 183;
    adjacencyMatrix_["Heilbronn"]["Würzburg"] = 102;
}
