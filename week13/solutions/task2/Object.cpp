#include "Object.h"

Object::Object(const std::string& name, const std::string& location, const std::string& extension)
    : name(name), location(location), extension(extension) {}

std::string Object::getPath() const {
    return location + "/" + name + "." + extension;
}

const std::string& Object::getName() const     { return name; }
const std::string& Object::getLocation() const { return location; }
const std::string& Object::getExtension() const { return extension; }
