#ifndef GUIDEDOG_H
#define GUIDEDOG_H

#include "Animal.h"
#include "Pet.h"

// With virtual public Animal in Pet AND here, there is exactly one
// shared Animal subobject in GuideDog. Without virtual, GuideDog
// would have two Animal subobjects (one from Pet, one direct) and
// accessing `name` would be ambiguous.
class GuideDog : public Pet, virtual public Animal
{
public:
    GuideDog(const char *name, const char *owner);
    void describe() const override;
};

#endif // GUIDEDOG_H
