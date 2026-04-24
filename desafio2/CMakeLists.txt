cmake_minimum_required(VERSION 3.16)

project(desafio2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(desafio2 main.cpp


    torneo.h torneo.cpp
    grupo.h grupo.cpp
    equipo.h equipo.cpp
    jugador.h jugador.cpp
    partido.h partido.cpp
    cargarArchivos.h
    cargarArchivos.cpp
    eliminatoria.h eliminatoria.cpp
    estadisticajugador.h estadisticajugador.cpp
    estadisticaequipo.h estadisticaequipo.cpp
    tablagrupo.h tablagrupo.cpp
    InicializarDatos.h
    inicializarDatos.cpp
)

include(GNUInstallDirs)
install(TARGETS desafio2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
