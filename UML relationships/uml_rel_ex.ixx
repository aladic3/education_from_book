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

void test();

struct Project {
  Project(std::string  t): title(std::move(t)){}
  ~Project();
  void add_researcher(Researcher&);
  void remove_researcher(Researcher &);
  void remove_researcher(std::vector<Researcher*>::iterator);
  bool has_researcher(const Researcher &);

  [[nodiscard]] std::__wrap_iter<Researcher *const *> get_begin_iterator() const {return researchers_.begin();}
  [[nodiscard]] std::__wrap_iter<Researcher *const *>  get_end_iterator() const {return researchers_.end();}

  std::vector<Researcher*>::iterator get_researcher_iterator(const Researcher &);
  //std::vector<Researcher*>::iterator get_end_researchers_iterator(){return researchers_.end();}
  const std::string& get_title(){return title;}


private:
  std::string title;
  std::vector<Researcher*> researchers_;

};

struct Researcher {
  Researcher(std::string  n):name(std::move(n)){}
  ~Researcher();

  [[nodiscard]] bool is_member_of(const Project &) const;
  std::vector<Project*>::iterator get_project_iterator(const Project &);
  std::vector<Project*>::iterator get_end_projects_iterator(){return projects_.end();}


  [[nodiscard]] std::__wrap_iter<Project *const *> get_begin_iterator() const {return projects_.begin();}
  [[nodiscard]] std::__wrap_iter<Project *const *>  get_end_iterator() const {return projects_.end();}

  void add_to_project(Project&);
  void remove_from_project(Project&);
  void remove_from_project(std::vector<Project*>::iterator);
  [[nodiscard]] const std::string& get_name() const {return name;}

private:
  std::string name;
  std::vector<Project*> projects_;
};

void print_all(std::initializer_list<Project*> existing_proj);
void print_all(std::initializer_list<Researcher*> existing_researchers);
} // namespace uml_relationships::association

