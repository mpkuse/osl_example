cmake_minimum_required (VERSION 2.8)
project (osl_examples)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}  "/home/mpkusex/Downloads/osg/CMakeModules/" )


find_package( glfw3 REQUIRED )
find_package( GLEW REQUIRED )
find_package( OpenGL REQUIRED )

#find_package(OpenThreads REQUIRED )
#find_package( osg REQUIRED components viewer )


set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable( helloDemo hello.cpp )

add_executable( osg_test osg_test.cpp )
add_executable( osg_shapes osg_shapes.cpp )
add_executable( osg_texture osg_texture.cpp )
add_executable( osg_lib_shapes osg_lib_shapes.cpp ) #uses basic-object from osg library
add_executable( osg_model osg_model.cpp ) #loads and transforms model
add_executable( osg_cyt_model osg_cyt_model.cpp ) #cyt model experimenting
add_executable( osg_cyt_composite osg_cyt_composite.cpp ) #cyt composite view
add_executable( osg_render_to_image osg_render_to_image.cpp ) # do not open window, instead render to image


target_link_libraries( helloDemo glfw GLEW GL )
target_link_libraries( osg_test osgViewer osgDB osgUtil osg )
target_link_libraries( osg_shapes osgViewer osgDB osgUtil osg )
target_link_libraries( osg_texture osgViewer osgDB osgUtil osg )
target_link_libraries( osg_lib_shapes osgViewer osgDB osgUtil osg )
target_link_libraries( osg_model osgViewer osgDB osgUtil osg osgGA osgText )
target_link_libraries( osg_cyt_model osgViewer osgDB osgUtil osg osgGA osgText )
target_link_libraries( osg_cyt_composite osgViewer osgDB osgUtil osg osgGA osgText )
target_link_libraries( osg_render_to_image osgViewer osgDB osgUtil osg osgGA osgText )
