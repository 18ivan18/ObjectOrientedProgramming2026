#include "KNYAML_resizeable_set.h"
#include <iostream>

KNYAMLSpec::KNYAMLSpec(std::vector<SimplePair *> pairs) : pairs(comparePtr<SimplePair>)
{
    for (size_t i = 0; i < pairs.size(); i++)
    {
        this->pairs.add(pairs[i]->clone());
    }
}

KNYAMLSpec::KNYAMLSpec(const KNYAMLSpec &other) : pairs(comparePtr<SimplePair>)
{
    for (size_t i = 0; i < other.pairs.getSize(); i++)
    {
        this->pairs.add(other.pairs.getData()[i]->clone());
    }
}

KNYAMLSpec &KNYAMLSpec::operator=(const KNYAMLSpec &rhs)
{
    if (this != &rhs)
    {
        free();
        for (size_t i = 0; i < rhs.pairs.getSize(); i++)
        {
            this->pairs.add(rhs.pairs.getData()[i]->clone());
        }
    }
    return *this;
}

void KNYAMLSpec::free()
{
    for (size_t i = 0; i < pairs.getSize(); i++)
    {
        delete pairs.getData()[i];
    }
}

KNYAMLSpec::~KNYAMLSpec()
{
    free();
}

void KNYAMLSpec::operator[](const std::string &key)
{
    for (size_t i = 0; i < pairs.getSize(); i++)
    {
        if (*pairs.getData()[i] == key)
        {
            pairs.getData()[i]->printValue();
        }
    }
}