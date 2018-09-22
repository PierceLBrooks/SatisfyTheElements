link_directories(${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/SFML/include)
link_libraries(sfml-system-2 sfml-window-2 sfml-graphics-2 sfml-audio-2 sfml-network-2)

set(INC ${PROJECT_SOURCE_DIR}/include/STE)
set(SRC ${PROJECT_SOURCE_DIR}/src/STE)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_FILES
	${INC}/STE.hpp
	${SRC}/main.cpp
	${SRC}/CherryBlossoms.cpp
	${SRC}/Menu.cpp
	${SRC}/State.cpp
	${SRC}/Entity.cpp
	${SRC}/Random.cpp
	${SRC}/Button.cpp
	${INC}/CherryBlossoms.hpp
	${INC}/Menu.hpp
	${INC}/State.hpp
	${INC}/Entity.hpp
	${INC}/Random.hpp
	${INC}/Button.hpp
)

add_executable(SatisfyTheElements ${PROJECT_FILES})

set_property(TARGET SatisfyTheElements PROPERTY CXX_STANDARD 14)
set_property(TARGET SatisfyTheElements PROPERTY CXX_STANDARD_REQUIRED ON)
