//
// Created by Dmytrenko Kyrylo on 21.09.2026.
//

module;

#include <iostream>
#include <utility>
#include <vector>
#include <string>

export module uml_rel_ex;

export namespace uml_relationships::association {
struct Researcher;

struct Project {
  Project(std::string  t): title(std::move(t)){}
  ~Project();
  void add_researcher(Researcher&);
  void remove_researcher(Researcher &);
  void remove_researcher(std::vector<Researcher*>::iterator);
  bool has_researcher(const Researcher &);
  std::vector<Researcher*>::iterator get_researcher_iterator(const Researcher &);
  std::vector<Researcher*>::iterator get_end_researchers_iterator(){return researchers_.end();}


private:
  std::string title;
  std::vector<Researcher*> researchers_;

};

struct Researcher {
  Researcher(std::string  n):name(std::move(n)){}
  ~Researcher();

  bool is_member_of(const Project &);
  std::vector<Project*>::iterator get_project_iterator(const Project &);
  std::vector<Project*>::iterator get_end_projects_iterator(){return projects_.end();}

  void add_to_project(Project&);
  void remove_from_project(Project&);
  void remove_from_project(std::vector<Project*>::iterator);

private:
  std::string name;
  std::vector<Project*> projects_;
};

void print_all(std::initializer_list<Project*> existing_proj);
void print_all(std::initializer_list<Researcher*> existing_researchers);
} // namespace uml_relationships::association

