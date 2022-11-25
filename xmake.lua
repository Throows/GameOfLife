add_rules("mode.debug", "mode.release")

add_requires("spdlog", "sfml")

set_runtimes("MD")
add_cxxflags("-std=c++20")

target("GameOfLife")
    set_version("0.0.1")

    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    --add_includedirs("include/")

    add_packages("spdlog", "sfml")
    set_symbols("debug")
    if is_mode("debug") then
        add_defines("DEBUG")
    end