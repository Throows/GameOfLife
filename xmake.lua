add_rules("mode.debug", "mode.release")

add_requires("spdlog", "sfml")

set_runtimes("MD")

target("GameOfLife")
    set_version("0.0.1")

    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_includedirs("include/")

    add_packages("spdlog", "sfml")
    set_symbols("debug")