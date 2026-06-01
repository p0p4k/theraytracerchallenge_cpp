#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "groups.h"
#include "smooth_triangle.h"
#include "triangle.h"
#include "tuple.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class ObjParser {
public:
  std::vector<RayPoint> vertices;
  std::vector<RayVector> normals;

  Group *default_group;
  std::map<std::string, Group *> named_groups;

  int ignored_lines = 0;

  ObjParser();
  ~ObjParser();

  void parse_string(const std::string &obj_data);

  void parse_file(const std::string &filename);

  Group *obj_to_group();

private:
  Group *current_group;
  void parse_line(const std::string &line);
};

#endif
