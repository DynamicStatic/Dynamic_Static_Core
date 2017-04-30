
# set(GLFW glfw-3.2.1)
# set(GLFW_LIBRARY_NAME libglfw3.a)
# set(GLFW_URL ${CMAKE_SOURCE_DIR}/Dynamic_Static.Core/external/${GLFW}.zip)
# set(GLFW_URL_MD5 824C99EEA073BDD6D2FEC76B538F79AF)
# 
# ExternalProject_Add(
#     ${GLFW}
#     PREFIX ${GLFW}
#     URL ${GLFW_URL}
#     URL_MD5 ${GLFW_URL_MD5}
#     INSTALL_COMMAND cmake ""
# )
# 
# ExternalProject_Get_Property(${GLFW} SOURCE_DIR)
# ExternalProject_Get_Property(${GLFW} BINARY_DIR)
# set(GLFW_LIBRARY ${BINARY_DIR}/src/${GLFW_LIBRARY_NAME})
# set(GLFW_INCLUDE ${SOURCE_DIR}/include/)
# 
# add_custom_command(
#     TARGET ${GLFW} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${GLFW_LIBRARY} ${PACKAGE_DIRECTORY}/lib/${GLFW_LIBRARY_NAME}
# )
