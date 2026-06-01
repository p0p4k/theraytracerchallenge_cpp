#include "obj_parser.h"
#include "smooth_triangle.h"
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <sstream>

ObjParser::ObjParser() {
  vertices.push_back(RayPoint(0, 0, 0));
  normals.push_back(RayVector(0, 0, 0));

  default_group = new Group();
  current_group = default_group;
  ignored_lines = 0;
}

ObjParser::~ObjParser() {}

void ObjParser::parse_file(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open OBJ file: " << filename << std::endl;
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    parse_line(line);
  }
}

void ObjParser::parse_string(const std::string &obj_data) {
  std::istringstream stream(obj_data);
  std::string line;
  while (std::getline(stream, line)) {
    parse_line(line);
  }
}

void ObjParser::parse_line(const std::string &line) {
  if (line.empty())
    return;

  std::istringstream iss(line);
  std::string type;
  iss >> type;

  if (type == "v") {
    double x, y, z;
    if (iss >> x >> y >> z) {
      vertices.push_back(RayPoint(x, y, z));
    }
  } else if (type == "vn") {
    double x, y, z;
    if (iss >> x >> y >> z) {
      normals.push_back(RayVector(x, y, z));
    }
  } else if (type == "g") {
    std::string group_name;
    iss >> group_name;

    if (named_groups.find(group_name) == named_groups.end()) {
      named_groups[group_name] = new Group();
    }
    current_group = named_groups[group_name];
  } else if (type == "f") {
    std::vector<int> face_indices;
    std::vector<int> normal_indices;
    std::string vertex_data;

    while (iss >> vertex_data) {
      std::stringstream v_stream(vertex_data);
      std::string v_idx, vt_idx, vn_idx;

      // Split by slashes cleanly using getline
      std::getline(v_stream, v_idx, '/');
      if (!v_idx.empty()) {
        face_indices.push_back(std::stoi(v_idx));
      }

      if (std::getline(v_stream, vt_idx, '/')) {
        // If there is a second slash, grab what follows it (the normal)
        if (std::getline(v_stream, vn_idx, '/')) {
          if (!vn_idx.empty()) {
            normal_indices.push_back(std::stoi(vn_idx));
          }
        } else if (!vt_idx.empty()) {
          // Handles the "v/vn" style format if only one slash followed by data
          normal_indices.push_back(std::stoi(vt_idx));
        }
      }
    }

    // Fan Triangulation: Convert any polygon into triangles or smooth triangles
    for (size_t i = 1; i < face_indices.size() - 1; ++i) {
      if (normal_indices.empty()) {
        Triangle *t =
            new Triangle(vertices[face_indices[0]], vertices[face_indices[i]],
                         vertices[face_indices[i + 1]]);
        current_group->add_child(t);
      } else {
        SmoothTriangle *st = new SmoothTriangle(
            vertices[face_indices[0]], vertices[face_indices[i]],
            vertices[face_indices[i + 1]], normals[normal_indices[0]],
            normals[normal_indices[i]], normals[normal_indices[i + 1]]);
        current_group->add_child(st);
      }
    }
  } else {
    // Unrecognized lines (comments, smooth shading toggles, materials, etc.)
    ignored_lines++;
  }
}

Group *ObjParser::obj_to_group() {
  Group *master = new Group();
  master->add_child(default_group);

  for (auto const &[name, grp] : named_groups) {
    master->add_child(grp);
  }

  return master;
}
