cmake_minimum_required(VERSION 3.18)

project(SlicerIssue5220)

set(Slicer_REQUIRED_QT_MODULES
  Core
  Widgets
  OpenGL
  )

set(QT_LIBRARIES)
foreach(lib IN LISTS Slicer_REQUIRED_QT_MODULES)
  if(lib MATCHES "^(LinguistTools)$")
    continue()
  endif()
  list(APPEND QT_LIBRARIES Qt5::${lib})
endforeach()

find_package(Qt5 COMPONENTS ${Slicer_REQUIRED_QT_MODULES} REQUIRED)

set(Slicer_VTK_COMPONENTS
  IOImage
  IOLegacy
  ImagingMath
  InteractionImage
  RenderingContextOpenGL2
  RenderingQt
  RenderingVolumeOpenGL2
  ViewsQt
  )

find_package(VTK COMPONENTS ${Slicer_VTK_COMPONENTS} REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MR-head.nrrd DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test test.cpp)
target_link_libraries(test
  ${QT_LIBRARIES}
  ${VTK_LIBRARIES}
  )

