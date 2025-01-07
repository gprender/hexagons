/**
 * @author Graeme Prendergast 
 */

#include "config.h"
#include "controller/app.h"


int main()
{
    std::vector<std::string> foo = split("what does you means", " ");
    std::cout << to_string(foo);

    App app;
    app.run();

    return 0;
}

