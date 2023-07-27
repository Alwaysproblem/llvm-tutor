set(main_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(main ${main_SOURCES})

target_include_directories(
  main
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(main
  LLVMCore LLVMPasses LLVMIRReader LLVMSupport
)
