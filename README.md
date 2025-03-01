# LogFacade

This is a simple header file that provides a set of common logging interfaces for my projects.

# Usage

Example usage:
```cpp

#include "logfacade.hpp"
#include <iostream>


// Callback to handle incoming logs
void on_log(logfacade::LogLevel level, const std::string &name, const std::string &msg){
    std::cout << name << " - " << msg << "\n";
}

logfacade::logging::set_log_callback(on_log);

// Create a logger and log some messages.
logfacade::Logger example("Hello");
example.debug("World!");
// Expected output:
// Hello - World!

```

# Dependencies
1. `fmt` - For string interpolation / general formatting.