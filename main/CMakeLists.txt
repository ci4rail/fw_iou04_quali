idf_build_get_property(project_dir PROJECT_DIR)
idf_component_register(SRCS "src/main.c" "src/can_test.c" "src/com_test.c" "src/dcdc.c"
                       INCLUDE_DIRS "include")
