target(g_project_name)
    add_files(
        "src/*.c",
        "src/*.s"
    )

    remove_files(
        -- "src/startup_stm32f10x_hd.s"
    )

    add_includedirs(
        "inc"
    )
target_end()
