#include "../include/pmodel.h"
#include "../include/stlutil.h"
#include "../include/pmodelparse.h"
#include "../include/streamr.h"

const std::unordered_set<char> openChars = {'{', '['};


Value* read_value(std::istream* input, char* current, std::unordered_map<char, int> exclusions) {
  
  if (is_letter(*current) || is_number(*current)) {
    return new StringValue(read_identifier(input, current, exclusions));
  } else if (*current == '[') {
    put_or_increase(exclusions, ']');
    *current = (char) input->get();
    skip_spaces_checked(input, current);
    
    std::vector<Value*> values;

    while (*current != ']' && !input->eof()) {
      Value* value = read_value(input, current, exclusions);
      values.push_back(value);
      skip_spaces_checked(input, current);
    }
    // skip the last spaces
    skip_spaces(input, current);
    return new ListValue(values);
  } else if (*current == '{') {
    put_or_increase(exclusions, '}');
    *current = (char) input->get();
    skip_spaces_checked(input, current);
    std::map<std::string, Value*> values;
    while (*current != '}' && !input->eof()) {
      std::string key = read_identifier(input, current, exclusions);
      Value* value = read_value(input, current, exclusions);
      values[key] = value;
      skip_spaces_checked(input, current);
    }
    // skip the last spaces
    skip_spaces(input, current);
    return new MapValue(values);
  }

  return new StringValue("pito");
}

ProjectModel parse_project_model(std::istream* input) {

  
  bool full = false;
  std::map<std::string, Value*> entries;
  char current = (char) input->get();

  while (!input->eof()) {
    std::string key = read_identifier(input, &current, std::unordered_map<char, int>());
    Value* value = read_value(input, &current, std::unordered_map<char, int>());

    std::cout << "Key: " << key << ". Value: " << value->str_repr() << std::endl;

    auto search = entries.find(key);
    if (search != entries.end()) {
      throw "Found duplicated definition for key '" + key 
        + "' with values '" + search->second->str_repr() + "' and '" + value->str_repr() + "'";
    }
    entries[key] = value;
  }

  return ProjectModel(
    entries["group"]->str_repr(), 
    entries["name"]->str_repr(), 
    entries["version"]->str_repr()
  );
}