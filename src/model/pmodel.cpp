#include "pmodel.h"
#include "../core.h"
#include "pmodelparse.h"
#include "../read/streamr.h"
#include "../util/log.h"

Value* read_value(ParseContext& context) {

  if (is_letter(context.current) || is_number(context.current)) {
    return new StringValue(read_identifier(context));
  } else if (context.current == '[') {
    context.push_exclusion(']');
    ++context;
    context.skip_spaces();

    std::vector<Value *> values;

    while (context.current != ']' && context.input.eof()) {
      Value *value = read_value(context);
      values.push_back(value);
      context.skip_spaces();
    }
    context.assert_exclusion(']');
    return new ListValue(values);
  } else if (context.current == '{') {
    context.push_exclusion('}');
    ++context;
    context.skip_spaces();
    std::map<std::string, Value *> values;
    while (context.current != '}' && !context.input.eof()) {
      std::string key = read_identifier(context);
      Value *value = read_value(context);
      values[key] = value;
      context.skip_spaces();
    }
    context.assert_exclusion('}');
    return new MapValue(values);
  }

  return new StringValue("pito");
}

ProjectModel parse_project_model(std::istream &input) {

  std::map<std::string, Value *> entries;
  std::unordered_map<char, int> exclusions;
  ParseContext context(input, exclusions);

  while (!input.eof()) {

    std::string key = read_identifier(context);
    Value *value = read_value(context);

    info("Read " + key + " with value " + value->str_repr());

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