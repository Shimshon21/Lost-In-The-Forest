target_include_directories (Project_David_Sapir_Shimshon_Polak PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources(Project_David_Sapir_Shimshon_Polak  PRIVATE 
"Animation.h"
"AnimationData.h"
"Board.h"
"CollisionHandling.h"
"Controller.h"
"GameObject.h"
"HealthBar.h"
"Macros.h"
"Operation.h"
"Resources.h")

add_subdirectory(MoveObjects_Headers)
add_subdirectory(Screens_Headers)
add_subdirectory(StaticObjects_Headers)