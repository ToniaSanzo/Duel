#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// Forward declare Component, and Entity (The compiler knows that we
// have these classes but we haven't defined them yet)
class Component;
class Entity;
class Manager;

// Typedefine ComponentID so that it is the same as saying 
// std::size_t
using ComponentID = std::size_t;
using Group = std::size_t;

// Defines a function inline, every time we call, everytime we 
// call this, lastID increments by one.
inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

// Maximum number of components that a entity can hold
constexpr std::size_t maxComponents = 32;

// We can have 32 groups or layers, these can be used as render 
// layers or collision layers
constexpr std::size_t maxGroups = 32;

// ComponentBitSet is used to see if an entity contains certain components
using ComponentBitSet = std::bitset<maxComponents>;

// GroupBitSet is a bitset for different groups/layers
using GroupBitSet = std::bitset<maxGroups>;

// An array of component pointers the length of our maxComponents
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
    Entity *entity;         // Reference to the entities owner
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};


class Entity
{
private:
    Manager &manager;
    bool active = true;     // If false we can remove this 
                            // entity from the game.

    // Vector collection of pointers to components
    std::vector<std::unique_ptr<Component>> components;

    // Array of 32 Component pointers
    ComponentArray componentArray;

    // Bitset to flag what components this entity contains
    ComponentBitSet componentBitSet;

    // Each entity has its own group bitset, we can now find out
    // what groups it is in
    GroupBitSet groupBitSet;

public:
    Entity(Manager &mManager) : manager(mManager) {}

    // Update each of this entity's component
    void update() {
        // update every component
        for (auto &c : components) c->update();
    }

    // Draw each component
    void draw(){
        // draw eah component
        for (auto &c : components) c->draw();
    }


    bool isActive () const { return active; }


    void destroy() { active = false;}

    // Check if the entity is in a specific group
    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    // The Entity needs to be able to add itself to a group
    void addGroup(Group mGroup);

    // The Entity needs to be able to delete itself from a group
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    // Returns true or false based on if the entity contains the
    // component.
    template <typename T> bool hasComponent() const
    {
        // Checks the bitset for a specific component based on
        // the component type.
        return componentBitSet[getComponentTypeID<T>()];
    }

    // A little advanced for me at the moment, but I'm assuming
    // it just adds a component to a entity
    template <typename T, typename... TArgs>
    T &addComponent(TArgs&&... mArgs) {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;


        c->init();
        return *c;
    }

    // The reason this method looks like this is to make 
    // calls on certain components like this.
    // gameobject.getComponent<positionComponent>().setXpos(25);
    template<typename T> T &getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};


class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;

public:
    // update each entity
    void update() {
        for (auto &e : entities) e->update();
    }

    // Draw each entity
    void draw()
    {
        for (auto &e : entities) e->draw();
    }

    // loop through the entities and remove the ones that
    // are not active
    void refresh() {
        // Move through each of our groups, and remove the groups
        // when necessary
        for (auto i(0u); i < maxGroups; i++) {
            auto &v(groupedEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v),
                    [i](Entity *mEntity)
                    {
                        return !mEntity->isActive() ||
                            !mEntity->hasGroup(i);
                    }), std::end(v));
                

        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));
    }

    // Add our entity to the group
    void addToGroup(Entity *mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    // Gets our entities as a list
    std::vector<Entity *> &getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    Entity &addEntity() {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};