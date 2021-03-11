#include <map>
#include <string>

///
/// Enum containg all the possible
/// Project Model value types
///
enum ValueType {
  String,
  List,
  Map
};

///
/// Class that represents a
/// value, it's pure virtual
///
struct Value {

  virtual ValueType type() = 0;

  virtual std::string str_repr() = 0;

};

struct MapValue : Value {

  std::map<std::string, Value*> values;

  MapValue(std::map<std::string, Value*> pvalues) 
    : values(pvalues) {};

  ValueType type() {
    return ValueType::Map;
  }

  std::string str_repr() {
    std::string repr = "{";
    for (auto it = values.begin(); it != values.end(); it++) {
      if (it != values.begin()) {
        repr += ", ";
      }
      repr += it->first;
      repr += " : ";
      repr += it->second->str_repr();
    }
    repr += "}";
    return repr;
  }
};

struct StringValue : Value {

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

struct ListValue : Value {

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