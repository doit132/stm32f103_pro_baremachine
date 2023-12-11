target(g_project_name)
    add_files(
        "uart/*.c"
    )

    remove_files(
        -- "src/startup_stm32f10x_hd.s"
    )

    add_includedirs(
        "uart"
    )
target_end()
