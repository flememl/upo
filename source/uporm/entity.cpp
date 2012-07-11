#include "uporm/entity.hpp"

using namespace std;
using namespace upo::orm;

Entity::Entity()
{
  // Create an entity witch is not stored in the DB yet
}

Entity::Entity(int id)
{
  // Get the entity from DB with id == id
}

Entity::~Entity()
{
}

bool Entity::commit()
{
  // Commits the changes made to the entity into the DB
}

bool Entity::drop()
{
  // Remove the entity from the DB
}

void* Entity::call(string name)
{
  return this->name_table[name];
}

Entity* Entity::get()
{
  // Return all entities
}
