add_contract(system.ore system.ore ${CMAKE_CURRENT_SOURCE_DIR}/src/system.ore.cpp)
target_include_directories(system.ore.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(system.ore.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
