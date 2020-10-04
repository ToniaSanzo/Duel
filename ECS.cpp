#include "ECS.h"

// Add this entity to a group
void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}
