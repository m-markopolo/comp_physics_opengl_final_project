#pragma once 

#include "physical_contact.hpp"
#include <optional>
#include "shapes.hpp"

Shape* get_shape( Physical_Entity const&, shapeID ID  );
std::optional<Contact> collide(Shape* a, Shape* b) ;

