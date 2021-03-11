#include "../include/pmodel.h"
#include "../include/token.h"
#include "../include/stlutil.h"
#include <map>

const std::unordered_set<char> emptyCharSet;

enum ValueType {
  String,
  List,
  Map
};

struct Value {
  public:
  virtual ValueType type() = 0;

  virtual std::string str_repr() = 0;
};

struct MapValue : public Value {
  public:
  std::map<std::string, Value*> values;

  MapValue(std::map<std::string, Value*> pvalues) 
    : values(pvalues) {};

  ValueType type() {
    return ValueType::Map;
  }

  std::string str_repr() {
    std::string repr = "{";
    for (auto it = values.begin(); it != values.end(); it++) {
      repr += it->first;
      repr += " : ";
      repr += it->second->str_repr();
    }
    repr += "}";
    return repr;
  }
};

struct ListValue : public Value {
  public:
  Value* values;
  int length;

  ListValue(Value* pvalues, int plength) 
    : values(pvalues), length(plength) {};

  ValueType type() {
    return ValueType::List;
  }

  std::string str_repr() {
    std::string repr = "[";
    for (int i = 0; i < length; i++) {
      Value* value = values + i;
      if (i != 0) {
        repr += ", ";
      } else {
        repr += "]";
      }
      repr += value->str_repr();
    }
    return repr;
  }
};

struct StringValue : public Value {
  public:
  std::string value;

  StringValue(std::string pvalue) 
    : value(pvalue) {};

  ValueType type() {
    return ValueType::String;
  }

  std::string str_repr() {
    return value;
  }
};

///
/// Reads a string until a space or a 
/// line break is found
///
std::string read_string(std::istream* input, char* current, std::unordered_set<char> exclusions) {
  std::string value;
  while (true) {
    if (is_space_or_break(*current)) {
      // To give the next read a valid char
      while (is_space_or_break((*current = input->get())));
      break;
    } else if (input->eof()) {
      break;
    } else {
      value.push_back(*current);
      *current = (char) input->get();
      if (has(exclusions, *current)) {
        break;
      }
    }
  }
  return value;
}

Value* read_value(std::istream* input, char* current, std::unordered_set<char> exclusions) {
  
  if (is_letter(*current)) {
    return new StringValue(read_string(input, current, emptyCharSet));
  } else if (*current == '[') {
    *current = (char) input->get();
  } else if (*current == '{') {
    exclusions.insert('}');
    *current = (char) input->get();
    std::map<std::string, Value*> values;
    while (*current != '}' && !input->eof()) {
      std::string key = read_string(input, current, exclusions);
      Value* value = read_value(input, current, exclusions);
      values[key] = value;
    }
    return new MapValue(values);
  }

  return new StringValue("pito");
  //while (is_space_or_break((*current = input->get())));
  //return read_value(input, current, exclusions);
}

ProjectModel::ProjectModel(std::istream* input) {

  
  bool full = false;
  std::map<std::string, Value*> entries;
  char current = (char) input->get();

  while (!input->eof()) {
    std::string key = read_string(input, &current, std::unordered_set<char>());
    Value* value = read_value(input, &current, std::unordered_set<char>());

    std::cout << "Key: " << key << ". Value: " << value->str_repr() << std::endl;

    auto search = entries.find(key);
    if (search != entries.end()) {
      throw "Found duplicated definition for key '" + key 
        + "' with values '" + search->second->str_repr() + "' and '" + value->str_repr() + "'";
    }
    entries[key] = value;
  }

  StringValue* groupValue = (StringValue*) entries["group"];
  StringValue* nameValue = (StringValue*) entries["name"];
  StringValue* versionValue = (StringValue*) entries["version"];

  this->group = groupValue->value;
  this->name = nameValue->value;
  this->version = versionValue->value;
}