idf_build_get_property(project_dir PROJECT_DIR)
idf_component_register(
    SRCS
        "src/main.c"
        "src/com_test.c"
    INCLUDE_DIRS "src"
)
