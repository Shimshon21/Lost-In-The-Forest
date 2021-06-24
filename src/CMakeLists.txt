add_subdirectory (MoveObjects_cpp)
add_subdirectory (Screens_cpp)
add_subdirectory (StaticObjects_cpp)
add_subdirectory (CustomObjects_cpp)


target_sources (Project_David_Sapir_Shimshon_Polak PRIVATE 
"main.cpp"
"Animation.cpp"
"Board.cpp"
"Controller.cpp"
"GameObject.cpp"
"Resources.cpp"
"CollisionHandling.cpp"
"EventClock.cpp")
