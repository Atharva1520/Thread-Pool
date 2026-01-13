# CMakeList.txt : CMake project for ThreadPoolDesign, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ThreadPoolDesign	"src/ThreadPoolDesign.cpp" "include/ThreadPoolDesign.h"
									"include/ThreadPool.h" "include/TaskQueue.h" 
									"src/ThreadPool.cpp" "src/TaskQueue.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThreadPoolDesign PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
