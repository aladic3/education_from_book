//
// Created by Dmytrenko Kyrylo on 21.09.2026.
//
module;
#include <vector>
#include <iostream>
module uml_rel_ex;


namespace uml_relationships::association {

Project::~Project() {
  for (Researcher* el : this->researchers_) {
    el->remove_from_project(*this);
  }
}

void Project::add_researcher(Researcher & researcher) {
  if (this->has_researcher(researcher)) return;
  this->researchers_.push_back(&researcher);
  researcher.add_to_project(*this);
}


void Project::remove_researcher(Researcher & researcher) {
  researcher.remove_from_project(researcher.get_project_iterator(*this));
  remove_researcher(get_researcher_iterator(researcher));

  /*
  for (auto it = researchers_.begin(); it != researchers_.end();++it) {
    if (*it == &researcher) {
      researchers_.erase(it);
      break;
    }
  }
*/

 /* if (researcher.is_member_of(*this) )
      researcher.remove_from_project(*this);*/
}
void Project::remove_researcher(std::vector<Researcher *>::iterator it) {
  if (it != researchers_.end()) researchers_.erase(it);
}

bool Project::has_researcher(const Researcher & researcher) { //
  for (auto el : researchers_)
    if (el == &researcher) return true;

  return false;
}

Researcher::~Researcher() {
  for (Project* el : this->projects_) {
    el->remove_researcher(*this);
  }
}


bool Researcher::is_member_of(const Project & project) const {
  for (const auto el : projects_)
    if (el == &project) return true;


  return false;
}


std::vector<Researcher *>::iterator
Project::get_researcher_iterator(const Researcher & researcher) {
    for (auto it = researchers_.begin(); it != researchers_.end();++it)
      if (*it == &researcher) return it;

    return researchers_.end();
}


std::vector<Project *>::iterator
Researcher::get_project_iterator(const Project & project) {
  for (auto it = projects_.begin(); it != projects_.end();++it) {
    if (*it == &project) {
      return it;
    }
  }
  return projects_.end();
}


void Researcher::add_to_project(Project & project) {
  if (this->is_member_of(project)) return;
  this->projects_.push_back(&project);
  project.add_researcher(*this);
}


void Researcher::remove_from_project(Project & project) {
  remove_from_project(get_project_iterator(project));
  project.remove_researcher(project.get_researcher_iterator(*this));

  /*for (auto it = projects_.begin(); it != projects_.end();++it) { // first ver of method
    if (*it == &project) {
      projects_.erase(it);
      break;
    }
  }

  if (project.has_researcher(*this) )
      project.remove_researcher(*this);
*/
}


void Researcher::remove_from_project(std::vector<Project *>::iterator it) {
  if (it != projects_.end()) projects_.erase(it);
}

void print_all(std::initializer_list<Project *> existing_proj) {
  
}


void print_all(std::initializer_list<Researcher *> existing_researchers) {}

} // namespace uml_relationships::association