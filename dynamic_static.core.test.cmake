
execute_process(
    COMMAND "C:/Program Files/CMake/bin/ctest.exe" -R $<TARGET_FILE:dynamic_static.core.test>
    RESULT_VARIABLE result
)
if()
    file(REMOVE )
    message(FATAL_ERROR "Test failed")
endif()
