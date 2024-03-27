#include <exception>
#include <string>

class vector_dimension_exception : public std::exception
{
public:
    vector_dimension_exception();
    vector_dimension_exception(const std::string& message);
    
    const char* what() const noexcept override;
private:
    std::string message;
};

