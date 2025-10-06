add_requires("spdlog 1.15.*")

target("vi")
    set_kind("static")
    add_files("src/**.cpp")
    add_includedirs("src/", {public = true})
    add_packages("spdlog", {public = true})