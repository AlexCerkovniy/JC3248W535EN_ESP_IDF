set(srcs "project.c"
         "ui/ui.c"
         "ui/macros.c"
         "ui/screen/startup_screen.c"
         "ui/screen/main_screen.c"
         "ui/screen/dash_screen.c"
         "ui/screen/obd2_page1_stats_screen.c"
         "ui/font_src/orbitron_30.c"
         "ui/media_src/st_icon_150x64.c"
         "ui/widgets/ex_value_indicator.c")

FILE(GLOB_RECURSE bsp_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(APPEND srcs ${bsp_sources})

FILE(GLOB_RECURSE lvgl_port_sources ${CMAKE_CURRENT_SOURCE_DIR}/lvgl_port/*.c)
list(APPEND srcs ${lvgl_port_sources})

idf_component_register(SRCS ${srcs}
                       PRIV_REQUIRES spi_flash esp_driver_spi esp_driver_gpio esp_lcd
                       INCLUDE_DIRS "."
                                    "ui"
                                    "ui/screen"
                                    "ui/font_src"
                                    "ui/media_src"
                                    "ui/widgets"
                                    "lvgl_port"
                                    "bsp")
