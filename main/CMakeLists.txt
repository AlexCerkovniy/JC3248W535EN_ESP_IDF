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

idf_component_register(SRCS ${srcs}
                       PRIV_REQUIRES spi_flash esp_driver_spi esp_driver_gpio
                       INCLUDE_DIRS "."
                                    "ui"
                                    "ui/screen"
                                    "ui/font_src"
                                    "ui/media_src"
                                    "ui/widgets")
