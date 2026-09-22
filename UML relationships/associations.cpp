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
  for (auto proj: existing_proj) {
    std::cout << proj->get_title() << ": \n";
    for (std::__wrap_iter<Researcher *const *> it = proj->get_begin_iterator();
      it != proj->get_end_iterator(); ++it) {
        std::cout << '\t' << (*it)->get_name() << '\n';
    }
  }
}


void print_all(std::initializer_list<Researcher *> existing_researchers) {
  for (auto researcher: existing_researchers) {
    std::cout << researcher->get_name() << ": \n";
    for (std::__wrap_iter<Project *const *> it = researcher->get_begin_iterator();
      it != researcher->get_end_iterator(); ++it) {
      std::cout << '\t' << (*it)->get_title() << '\n';
      }
  }
}


void test() {
  Researcher john("John");
  Researcher belly("Belly");


  Project prog("Prog");
  Project project_x("Project_x");

  {
    Researcher andrew("Andrew");
    Researcher sara("Sara");

    Project green("Green");

    green.add_researcher(john);
    green.add_researcher(sara);
    prog.add_researcher(andrew);
    sara.add_to_project(project_x);
    sara.add_to_project(project_x);

    print_all(std::initializer_list{&john,&belly,&andrew,&sara});
    print_all(std::initializer_list{&prog,&project_x,&green});
    std::cout << "-------------------";
  }




  prog.add_researcher(belly);
  john.add_to_project(project_x);

 // sara.remove_from_project(green);
 // sara.remove_from_project(green);


  print_all(std::initializer_list{&john,&belly});
  print_all(std::initializer_list{&prog,&project_x});
}

} // namespace uml_relationships::association