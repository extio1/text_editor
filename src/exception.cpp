#include "../include/exception.h"

vector_dimension_exception::vector_dimension_exception(const std::string& message): 
    message(message)
{}

vector_dimension_exception::vector_dimension_exception(): 
    message("Vector dimension size exception")
{}

const char* vector_dimension_exception::what() const noexcept
{
    return message.c_str();
}

