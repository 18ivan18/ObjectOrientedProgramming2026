#ifndef OBJECT_H
#define OBJECT_H

#include "Comparable.h"
#include "Debug.h"
#include "Serializable.h"
#include <string>

class Object : public Comparable, public Debug, public Serializable {
protected:
    std::string name;
    std::string location;
    std::string extension;

public:
    Object(const std::string& name, const std::string& location, const std::string& extension);
    virtual ~Object() {}

    std::string getPath() const;
    const std::string& getName() const;
    const std::string& getLocation() const;
    const std::string& getExtension() const;

    virtual Object* clone() const = 0;
};

#endif // OBJECT_H
