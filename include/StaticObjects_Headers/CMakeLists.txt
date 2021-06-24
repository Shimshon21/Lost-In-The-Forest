target_include_directories (Project_David_Sapir_Shimshon_Polak PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources(Project_David_Sapir_Shimshon_Polak  PRIVATE 
"Bonus.h"
"Door.h"
"ExtraLife.h"
"Block.h"
"Gold.h"
"Hurricane.h"
"Key.h"
"StaticObject.h")

add_subdirectory(SpecialAbilty_Headers)